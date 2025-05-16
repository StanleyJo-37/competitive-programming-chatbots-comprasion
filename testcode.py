import subprocess
import tempfile
import os
import time
import psutil
import pandas as pd
import numpy as np

OUTPUT_PATH = './responses'
INPUT_PATH = './prompts/input.csv'
MODELS = ['chatgpt_4o_solutions.csv', 'deepseek-r1-solutions.csv', 'gemini_2.0_flash_solutions.csv']
TIMEOUT = 5  # seconds
MEMLIMIT = 1 * 1024 * 1024 # 1 GB in bytes
prefix = ">>> "

indf = pd.read_csv(f"{INPUT_PATH}")
indf.reset_index(drop=True, inplace=True)

for model in MODELS:
    if not os.path.exists(f"{OUTPUT_PATH}/{model}"):
        print(f"File {model} does not exist in {OUTPUT_PATH}.")
        exit(1)
    
    # Read the CSV file
    outdf = pd.read_csv(f"{OUTPUT_PATH}/{MODELS[0]}")
    
    assert len(outdf) == len(indf), "Input and output dataframes must have the same length."

    outdf.reset_index(drop=True, inplace=True)

    # Initialize default values, for lists, they need to be initialized as empty lists for each row
    # this is important to avoid issues with appending later (think of it as setting the same pointer to all the rows if using "=[]")
    outdf['execution_time'] = [[] for _ in range(len(outdf))]
    outdf['memory_usage_mb'] = [[] for _ in range(len(outdf))]
    outdf['return_code'] = [[] for _ in range(len(outdf))]
    outdf['stdout'] = [[] for _ in range(len(outdf))]
    outdf['stderr'] = [[] for _ in range(len(outdf))]
    outdf['correct'] = [[] for _ in range(len(outdf))]
    outdf['compilation_return_code'] = np.nan
    outdf['passed'] = False

    for i, data in enumerate(outdf.values):
        print(f"=================== Processing row {i + 1}/{len(outdf)} ===================")

        print(f"{prefix}Writing temp file ...")
        # Step 1: Write C++ code to temp file
        with tempfile.NamedTemporaryFile(mode='w', suffix='.cpp', delete=False) as cpp_file:
            cpp_file.write(data['solutions'])
            cpp_filename = cpp_file.name

        try:
            # Step 2: Compile it
            print(f"{prefix}Compiling C++ code ...")
            exe_filename = cpp_filename.replace('.cpp', '.exe')
            compile_result = subprocess.run(['g++', cpp_filename, '-o', exe_filename], capture_output=True, text=True)
            outdf.loc[i, 'compilation_return_code'] = compile_result.returncode

            if compile_result.returncode != 0:
                print(f"{prefix}Compilation failed:")
                print(f"{prefix}{compile_result.stderr}")
                
            else:
                print(f"{prefix}Running compiled C++ code...\n")
                input_data = eval(indf['inputs']) if isinstance(indf['inputs'], str) else indf['inputs']

                for j, input_item in enumerate(input_data):
                    
                    print(f"{prefix}Testing test case {j+1} / {len(input_data)} ...")
                    # Step 3: Launch and monitor with psutil
                    start_time = time.perf_counter()
                    try:
                        proc = subprocess.Popen([exe_filename], stdout=subprocess.PIPE, stderr=subprocess.PIPE, stdin=subprocess.PIPE, text=True)
                        ps_proc = psutil.Process(proc.pid)

                        # Send input to the program
                        proc.stdin.write(input_item + '\n')
                        proc.stdin.flush()  # Ensure the input is sent

                        peak_memory = 0
                        try:
                            while proc.poll() is None:
                                mem = ps_proc.memory_info().rss  # in bytes
                                peak_memory = max(peak_memory, mem)
                                memory_limit_str = indf.loc[j,"memory_limit"] if indf.loc[j,"memory_limit"] else f"{MEMLIMIT} megabytes"
                                memory_limit = int(memory_limit_str.split()[0])
                                if mem > memory_limit:
                                    proc.terminate()
                                    print(f"{prefix}!!! Process exceeded memory limit of {memory_limit} MB at test case {j+1} / {len(input_data)} !!!")
                                    raise MemoryError(f"Memory limit exceeded: {mem / 1024 / 1024} MB")
                                time.sleep(0.01)  # check every 10ms
                                
                                # Check if the process has exceeded the timeout or time limit
                                time_limit_str = indf.loc[j, "time_limit"] if indf.loc[j,"time_limit"] else f"{TIMEOUT} seconds"
                                time_limit = int(time_limit_str.split()[0])
                                if time.perf_counter() - start_time > time_limit:
                                    proc.terminate()
                                    print(f"{prefix}!!! Process exceeded timeout of {time_limit} seconds at test case {j+1} / {len(input_data)} !!!")
                                    raise subprocess.TimeoutExpired(proc.args, time_limit)

                        except psutil.NoSuchProcess:
                            pass

                        end_time = time.perf_counter()

                        stdout, stderr = proc.communicate()

                        print(f"{prefix}Output:")
                        print(f"{prefix}{stdout}")
                        if len(stderr) > 0:
                            print(stderr)
                        print(f"{prefix}Execution Time: {round(end_time - start_time, 4)} seconds")
                        print(f"{prefix}Peak Memory Usage: {round(peak_memory / 1024 / 1024, 2)} MB")

                        # Store results in DataFrame
                        outdf.at[i, 'execution_time'].append(round(end_time - start_time, 4))
                        outdf.at[i, 'memory_usage_mb'].append(round(peak_memory / 1024 / 1024, 2))
                        outdf.at[i, 'return_code'].append(proc.returncode)
                        outdf.at[i, 'stdout'].append(stdout)
                        outdf.at[i, 'stderr'].append(stderr)
                        outdf.at[i, 'correct'].append(indf['outputs'][j].strip() == stdout.strip())
                    except (subprocess.SubprocessError, subprocess.CalledProcessError, subprocess.TimeoutExpired) as e:
                        print(f"{prefix}Runtime error occurred: {e}")
                        outdf.at[i, 'execution_time'].append(None)
                        outdf.at[i, 'memory_usage_mb'].append(None)
                        outdf.at[i, 'return_code'].append(e.returncode)
                        outdf.at[i, 'stdout'].append(None)
                        outdf.at[i, 'stderr'].append(str(e))
                        outdf.at[i, 'correct'].append(False)
                    except MemoryError as e:
                        print(f"{prefix}Memory error occurred: {e}")
                        outdf.at[i, 'execution_time'].append(None)
                        outdf.at[i, 'memory_usage_mb'].append(None)
                        outdf.at[i, 'return_code'].append(None)
                        outdf.at[i, 'stdout'].append(None)
                        outdf.at[i, 'stderr'].append(str(e))
                        outdf.at[i, 'correct'].append(False)
                
                # Check if the program passed
                if all(outdf.at[i, 'correct']):
                    outdf.at[i, 'passed'] = True
                    print(f"{prefix}Test passed for row {i + 1}/{len(outdf)}")
                else:
                    outdf.at[i, 'passed'] = False
                    print(f"{prefix}Test failed for row {i + 1}/{len(outdf)}")

        finally:
            if os.path.exists(cpp_filename):
                os.remove(cpp_filename)
            if os.path.exists(exe_filename):
                os.remove(exe_filename)
    
    # Save the DataFrame to a new CSV file
    outdf.to_csv(f"{OUTPUT_PATH}/{model}", index=False)
    print(f"{prefix}Results saved to {OUTPUT_PATH}/{model}")

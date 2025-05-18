import subprocess
import tempfile
import os
import time
import psutil
import pandas as pd
import numpy as np
import sys

OUTPUT_PATH = './responses'
INPUT_PATH = './prompts/input.csv'
MODELS = ['chatgpt_4o_solutions.csv', 'deepseek-r1-solutions.csv', 'gemini_2.5_flash_solutions.csv']
TIMEOUT = 5  # seconds
MEMLIMIT = 1 * 1024 * 1024 # 1 GB in bytes
prefix = ">>> "

args = sys.argv
model = args[1] if len(args) > 1 else None
if model is None:
    print("Testing all models.")
else:
    if model == "chatgpt":
        MODELS = ['chatgpt_4o_solutions.csv']
    elif model == "deepseek":
        MODELS = ['deepseek-r1-solutions.csv']
    elif model == "gemini":
        MODELS = ['gemini_2.5_flash_solutions.csv']

# indf = pd.read_csv(f"{INPUT_PATH}")
# indf.reset_index(drop=True, inplace=True)

for model in MODELS:
    if not os.path.exists(f"{OUTPUT_PATH}/{model}"):
        print(f"File {model} does not exist in {OUTPUT_PATH}.")
        exit(1)
    
    # Read the CSV file
    outdf = pd.read_csv(f"{OUTPUT_PATH}/{model}")
    
    outdf.reset_index(drop=True, inplace=True)

    # Initialize default values, for lists, they need to be initialized as empty lists for each row
    # this is important to avoid issues with appending later (think of it as setting the same pointer to all the rows if using "=[]")
    for col in ['execution_time', 'memory_usage_mb', 'private_memory_usage_mb', 'return_code', 'stdout', 'stderr', 'correct']: # Added 'private_memory_usage_mb'
        outdf[col] = [[] for _ in range(len(outdf))]
    outdf['compilation_return_code'] = np.nan
    outdf['passed'] = False

    for i, data_row_values in enumerate(outdf.values): # Renamed 'data' to avoid confusion
        print(f"=================== Processing row {i + 1}/{len(outdf)} ===================")

        print(f"{prefix}Writing temp file ...")
        # Step 1: Write C++ code to temp file
        with tempfile.NamedTemporaryFile(mode='w', suffix='.cpp', delete=False) as cpp_file:
            cpp_file.write(outdf.loc[i, 'response']) # Use outdf.loc here
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
                current_problem_inputs_str = outdf.loc[i, 'inputs'] # Get inputs for current problem i
                input_data = eval(current_problem_inputs_str) if isinstance(current_problem_inputs_str, str) else current_problem_inputs_str

                # It's safer to use json.loads if your CSV stores lists as JSON strings:
                # import json
                # input_data = json.loads(current_problem_inputs_str) if isinstance(current_problem_inputs_str, str) else current_problem_inputs_str
                
                # Initialize lists for storing results for problem i
                # These are already initialized outside the loop, which is good.
                # Ensure they are cleared or correctly managed if re-running for the same problem index i (not an issue with current structure)

                all_test_cases_passed = True # Flag for current problem i

                for j, input_item in enumerate(input_data):
                    
                    print(f"{prefix}Testing test case {j+1} / {len(input_data)} ...")
                    try:
                        start_time = time.perf_counter()
                        proc = subprocess.Popen([exe_filename], stdout=subprocess.PIPE, stderr=subprocess.PIPE, stdin=subprocess.PIPE, text=True)
                        ps_proc = psutil.Process(proc.pid)

                        # Send input to the program
                        if input_item is list:
                            input_item = '\n'.join(map(str, input_item))

                        proc.stdin.write(str(input_item) + '\n')  # Send input to the program
                        proc.stdin.flush()  # Ensure the input is sent

                        # peak_memory = 0 # Will be peak_rss_memory
                        peak_rss_memory = 0 
                        peak_private_memory = 0 # For tracking peak private memory
                        try:
                            while proc.poll() is None:
                                # mem = ps_proc.memory_info().rss  # in bytes
                                # peak_memory = max(peak_memory, mem)
                                try:
                                    mem_info = ps_proc.memory_info()
                                    current_rss = mem_info.rss
                                    current_private = mem_info.private # Get private working set on Windows
                                    
                                    peak_rss_memory = max(peak_rss_memory, current_rss)
                                    peak_private_memory = max(peak_private_memory, current_private)
                                except psutil.NoSuchProcess: # Process might have ended
                                    break 
                                
                                # Get memory limit for current problem i
                                current_problem_memory_limit_str = outdf.loc[i, "memory_limit"] if pd.notna(outdf.loc[i, "memory_limit"]) and outdf.loc[i, "memory_limit"] else ""
                                if current_problem_memory_limit_str and "megabytes" in current_problem_memory_limit_str.lower():
                                    memory_limit_val = int(current_problem_memory_limit_str.split()[0]) * 1024 * 1024 # Convert MB to Bytes
                                elif current_problem_memory_limit_str and "bytes" in current_problem_memory_limit_str.lower():
                                    memory_limit_val = int(current_problem_memory_limit_str.split()[0]) # Already in Bytes
                                else: # Default if format is unknown or empty
                                    memory_limit_val = MEMLIMIT # MEMLIMIT is in Bytes

                                # MEMLIMIT check is still against total RSS (peak_rss_memory or current_rss)
                                if current_rss > memory_limit_val:
                                    proc.terminate()
                                    print(f"{prefix}!!! Process exceeded memory limit (RSS: {current_rss / (1024*1024):.2f} MB > Limit: {memory_limit_val / (1024*1024):.2f} MB) at test case {j+1} / {len(input_data)} !!!")
                                    raise MemoryError(f"Memory limit exceeded (RSS): {current_rss / 1024 / 1024:.2f} MB")
                                time.sleep(0.01)  # check every 10ms
                                
                                # Check if the process has exceeded the timeout or time limit
                                # Get time limit for current problem i
                                current_problem_time_limit_str = outdf.loc[i, "time_limit"] if pd.notna(outdf.loc[i, "time_limit"]) and outdf.loc[i, "time_limit"] else f"{TIMEOUT} seconds"
                                time_limit = int(current_problem_time_limit_str.split()[0]) # Assumes "X seconds"
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
                        print(f"{prefix}Peak RSS Memory Usage: {round(peak_rss_memory / 1024 / 1024, 2)} MB")
                        print(f"{prefix}Peak Private Memory Usage: {round(peak_private_memory / 1024 / 1024, 2)} MB")

                        # Store results in DataFrame
                        outdf.at[i, 'execution_time'].append(round(end_time - start_time, 4))
                        # outdf.at[i, 'memory_usage_mb'].append(round(peak_memory / 1024 / 1024, 2))
                        outdf.at[i, 'memory_usage_mb'].append(round(peak_rss_memory / 1024 / 1024, 2)) # This is RSS
                        outdf.at[i, 'private_memory_usage_mb'].append(round(peak_private_memory / 1024 / 1024, 2)) # Store private memory
                        outdf.at[i, 'return_code'].append(proc.returncode)
                        outdf.at[i, 'stdout'].append(stdout)
                        outdf.at[i, 'stderr'].append(stderr)
                        
                        # Get expected outputs for current problem i
                        current_problem_expected_outputs_str = outdf.loc[i, 'outputs']
                        expected_outputs_list = eval(current_problem_expected_outputs_str) if isinstance(current_problem_expected_outputs_str, str) else current_problem_expected_outputs_str
                        # Again, consider json.loads for safety:
                        # import json
                        # expected_outputs_list = json.loads(current_problem_expected_outputs_str) if isinstance(current_problem_expected_outputs_str, str) else current_problem_expected_outputs_str

                        if j < len(expected_outputs_list):
                            is_correct = expected_outputs_list[j].strip() == stdout.strip()
                        else:
                            print(f"{prefix}Warning: Not enough expected outputs for problem {i}, test case {j}.")
                            is_correct = False # Or handle as an error
                        outdf.at[i, 'correct'].append(is_correct)
                        if not is_correct:
                            all_test_cases_passed = False
                    except (subprocess.SubprocessError, subprocess.CalledProcessError, subprocess.TimeoutExpired) as e:
                        print(f"{prefix}Runtime error occurred: {e}")
                        outdf.at[i, 'execution_time'].append(None)
                        outdf.at[i, 'memory_usage_mb'].append(None)
                        outdf.at[i, 'return_code'].append(getattr(e, 'returncode', None)) # Safer access
                        outdf.at[i, 'stdout'].append(None)
                        outdf.at[i, 'stderr'].append(str(e))
                        outdf.at[i, 'correct'].append(False)
                        all_test_cases_passed = False
                    except MemoryError as e:
                        print(f"{prefix}Memory error occurred: {e}")
                        outdf.at[i, 'execution_time'].append(None)
                        # outdf.at[i, 'memory_usage_mb'].append(round(peak_memory / 1024 / 1024, 2) if peak_memory > 0 else None)
                        outdf.at[i, 'memory_usage_mb'].append(round(peak_rss_memory / 1024 / 1024, 2) if peak_rss_memory > 0 else None)
                        outdf.at[i, 'private_memory_usage_mb'].append(round(peak_private_memory / 1024 / 1024, 2) if peak_private_memory > 0 else None)
                        outdf.at[i, 'return_code'].append(None) # MemoryError doesn't have returncode
                        outdf.at[i, 'stdout'].append(None)
                        outdf.at[i, 'stderr'].append(str(e))
                        outdf.at[i, 'correct'].append(False)
                        all_test_cases_passed = False
        
            # Check if the program passed all test cases for problem i
            # The 'correct' list for outdf.at[i, 'correct'] now holds booleans for each test case
            if compile_result.returncode == 0 and outdf.at[i, 'correct'] and all(outdf.at[i, 'correct']): # Also ensure compilation succeeded
                outdf.at[i, 'passed'] = True
                print(f"{prefix}All test cases PASSED for problem {i + 1}/{len(outdf)}")
            else:
                # Ensure 'passed' is False if compilation failed or any test case failed
                outdf.at[i, 'passed'] = False 
                if compile_result.returncode != 0:
                    print(f"{prefix}Compilation FAILED for problem {i + 1}/{len(outdf)}")
                else:
                    print(f"{prefix}One or more test cases FAILED for problem {i + 1}/{len(outdf)}")

        finally:
            # Clean up temp files for the current problem i
            if 'cpp_filename' in locals() and os.path.exists(cpp_filename):
                try:
                    os.remove(cpp_filename)
                    # print(f"{prefix}Removed temp C++ file: {cpp_filename}") # Optional: for debugging
                except OSError as e:
                    print(f"{prefix}Error removing temp C++ file {cpp_filename}: {e}")
            if 'exe_filename' in locals() and os.path.exists(exe_filename):
                try:
                    os.remove(exe_filename)
                    # print(f"{prefix}Removed temp EXE file: {exe_filename}") # Optional: for debugging
                except OSError as e:
                    print(f"{prefix}Error removing temp EXE file {exe_filename}: {e}")

# After processing all problems for the current model, save the DataFrame
print(f"{prefix}Saving updated results to {OUTPUT_PATH}/{model} ...")
outdf.to_csv(f"{OUTPUT_PATH}/{model}", index=False)

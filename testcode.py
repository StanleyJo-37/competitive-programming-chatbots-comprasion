import subprocess
import tempfile
import os
import time
import psutil
import pandas as pd
import numpy as np

cpp_code = """
#include <iostream>
#include <vector>
int main() {
    std::vector<int> v(10000000, 42); // Use some memory
    std::cout << "C++ program running!" << std::endl;
    return 0;
}
"""
OUTPUT_PATH = './responses'
MODELS = ['chatgpt_4o_solutions.csv', 'deepseek-r1-solutions.csv', 'gemini_2.0_flash_solutions.csv']

outdf = pd.read_csv(f"{OUTPUT_PATH}/{MODELS[0]}")

outdf['execution_time'] = np.nan
outdf['memory_usage_mb'] = np.nan
outdf['correct'] = False


# Step 1: Write C++ code to temp file
with tempfile.NamedTemporaryFile(mode='w', suffix='.cpp', delete=False) as cpp_file:
    cpp_file.write(cpp_code)
    cpp_filename = cpp_file.name

input_data = [12,31,51,123]

# Step 2: Compile it
exe_filename = cpp_filename.replace('.cpp', '')

compile_result = subprocess.run(['g++', cpp_filename, '-o', exe_filename], capture_output=True, text=True)

if compile_result.returncode != 0:
    print("Compilation failed:")
    print(compile_result.stderr)
else:
    print("Running compiled C++ code...\n")

    # Step 3: Launch and monitor with psutil
    start_time = time.perf_counter()
    proc = subprocess.Popen([exe_filename], stdout=subprocess.PIPE, stderr=subprocess.PIPE, stdin=subprocess.PIPE, text=True)
    ps_proc = psutil.Process(proc.pid)

    # Send input to the program
    proc.stdin.write(input_data)
    proc.stdin.flush()  # Ensure the input is sent

    peak_memory = 0
    try:
        while proc.poll() is None:
            mem = ps_proc.memory_info().rss  # in bytes
            peak_memory = max(peak_memory, mem)
            time.sleep(0.01)  # check every 10ms
    except psutil.NoSuchProcess:
        pass

    end_time = time.perf_counter()

    stdout, stderr = proc.communicate()

    print("Output:")
    print(stdout)
    if len(stderr) > 0:
        print(stderr)
    print("Execution Time:", round(end_time - start_time, 4), "seconds")
    print("Peak Memory Usage:", round(peak_memory / 1024 / 1024, 2), "MB")

# Step 4: Clean up
os.remove(cpp_filename)
if os.path.exists(exe_filename):
    os.remove(exe_filename)

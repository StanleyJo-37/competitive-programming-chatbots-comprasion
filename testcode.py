import subprocess
import tempfile
import os
import time
import psutil

cpp_code = """
#include <iostream>
#include <vector>
int main() {
    std::vector<int> v(10000000, 42); // Use some memory
    std::cout << "C++ program running!" << std::endl;
    return 0;
}
"""

# Step 1: Write C++ code to temp file
with tempfile.NamedTemporaryFile(mode='w', suffix='.cpp', delete=False) as cpp_file:
    cpp_file.write(cpp_code)
    cpp_filename = cpp_file.name

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
    proc = subprocess.Popen([exe_filename], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    ps_proc = psutil.Process(proc.pid)

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
    print(stdout.decode())
    print("Execution Time:", round(end_time - start_time, 4), "seconds")
    print("Peak Memory Usage:", round(peak_memory / 1024 / 1024, 2), "MB")

# Step 4: Clean up
os.remove(cpp_filename)
if os.path.exists(exe_filename):
    os.remove(exe_filename)

#include <iostream> // Required for input/output operations

// The main function where the program execution begins
int main() {
    // Optimize C++ standard streams for faster input/output.
    // This unties cin/cout from C's stdio and disables synchronization,
    // which can significantly speed up I/O operations in competitive programming.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int T; // Declare an integer variable T to store the number of test cases
    std::cin >> T; // Read the number of test cases

    // Loop through each test case
    while (T--) {
        int N; // Declare an integer variable N to store the size of the array
        std::cin >> N; // Read the size of the array

        // Initialize min_val to a value larger than any possible A[i].
        // According to constraints, A[i] is positive and <= 10^5,
        // so 100001 is a safe initial maximum value.
        int min_val = 100001; 
        int min_idx = -1; // Initialize min_idx to an invalid value, will be updated

        // Loop N times to read each element of the array.
        // We use 1-based indexing for 'i' (from 1 to N) to match the problem's definition
        // of prefixSum(i) and suffixSum(i) and the desired output index.
        for (int i = 1; i <= N; ++i) {
            int current_A_val; // Declare a variable to store the current array element
            std::cin >> current_A_val; // Read the current array element

            // The problem asks to minimize prefixSum(i) + suffixSum(i).
            // Let's analyze the sum:
            // prefixSum(i) = A[1] + A[2] + ... + A[i]
            // suffixSum(i) = A[i] + A[i+1] + ... + A[N]
            //
            // So, prefixSum(i) + suffixSum(i) = (A[1] + ... + A[i]) + (A[i] + ... + A[N])
            // This can be rewritten as:
            // prefixSum(i) + suffixSum(i) = (A[1] + A[2] + ... + A[N]) + A[i]
            //
            // Let TotalSum = A[1] + A[2] + ... + A[N]. This is the sum of all elements in the array.
            // Then, the expression becomes: TotalSum + A[i].
            //
            // Since TotalSum is constant for a given array, minimizing TotalSum + A[i]
            // is equivalent to minimizing A[i].
            //
            // Therefore, the problem reduces to finding the minimum value in the array A
            // and the *least* index 'i' at which this minimum value is attained.

            // If the current element is strictly less than the minimum value found so far
            if (current_A_val < min_val) {
                min_val = current_A_val; // Update min_val to the new minimum
                min_idx = i;             // Update min_idx to the current 1-based index
            }
            // If current_A_val is equal to min_val, we do nothing.
            // This is crucial because the problem asks for the *minimum* index
            // if multiple indices yield the same minimum sum. By iterating
            // from left to right (1 to N) and only updating min_idx when a
            // *strictly smaller* value is found, the first occurrence of the
            // overall minimum value will correctly set min_idx, and subsequent
            // occurrences of the same minimum value (which would have larger indices)
            // will be ignored, thus preserving the least index.
        }

        // Output the minimum index found for the current test case
        std::cout << min_idx << "\n"; 
    }

    return 0; // Indicate successful program execution
}

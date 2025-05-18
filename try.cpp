// Include necessary headers
#include <iostream> // For input/output operations (cin, cout)
#include <limits>   // For std::numeric_limits (to get the maximum possible value for int)

// Main function where the program execution begins
int main() {
    // Use fast I/O to speed up reading input and writing output.
    // This is common practice in competitive programming to handle large inputs efficiently.
    std::ios_base::sync_with_stdio(false); // Unties C++ streams from C stdio
    std::cin.tie(NULL); // Unties cin from cout

    int T; // Variable to store the number of test cases
    std::cin >> T; // Read the number of test cases

    // Loop through each test case
    while (T--) {
        int N; // Variable to store the number of elements in the array A
        std::cin >> N; // Read the number of elements

        // Problem Analysis:
        // We are given an array A of N positive integers. The array elements are A_1, A_2, ..., A_N.
        // We need to find the minimum index i (1-based, 1 <= i <= N) such that prefixSum(i) + suffixSum(i) is minimized.
        // The problem defines:
        // prefixSum(i) = sum of the first i numbers of the array (A_1 + A_2 + ... + A_i)
        // suffixSum(i) = sum of the last N - i + 1 numbers of the array (A_i + A_{i+1} + ... + A_N)
        // Note: The index 'i' in suffixSum(i) refers to the starting index from the beginning of the array.
        // For example, suffixSum(1) is the sum of the last N numbers (A_1...A_N),
        // suffixSum(N) is the sum of the last N - N + 1 = 1 number (A_N).
        // This definition of suffixSum(i) matches the common interpretation where suffixSum(i) is the sum
        // of elements from index i to N (using 1-based indexing).

        // Let's analyze the sum prefixSum(i) + suffixSum(i):
        // prefixSum(i) + suffixSum(i) = (A_1 + A_2 + ... + A_i) + (A_i + A_{i+1} + ... + A_N)
        // This sum includes elements A_1 through A_{i-1} once, element A_i twice, and elements A_{i+1} through A_N once.
        // We can rearrange the terms:
        // prefixSum(i) + suffixSum(i) = (A_1 + A_2 + ... + A_i + A_{i+1} + ... + A_N) + A_i
        // The term (A_1 + A_2 + ... + A_N) is the sum of all elements in the array, which is a constant value for a given array. Let's call this TotalSum.
        // So, prefixSum(i) + suffixSum(i) = TotalSum + A_i.

        // To minimize the value of prefixSum(i) + suffixSum(i), we need to minimize TotalSum + A_i.
        // Since TotalSum is constant for a given array, minimizing TotalSum + A_i is equivalent to minimizing A_i.
        // The problem asks for the minimum index i (1-based) for which this minimum value is attained.
        // This means we need to find the minimum index i (1-based) such that A_i is the minimum element in the array.
        // If there are multiple occurrences of the minimum value, we need the smallest index among them.

        // We need to find the minimum value in the array and the index of its first occurrence.
        // We can do this by iterating through the array once.
        // We don't need to store the entire array in memory because we only need the minimum value and its index.
        // This approach uses O(1) auxiliary space, which is important given the memory limit (50000 bytes) and N up to 10^5.
        // Storing an array of 10^5 integers would require approximately 10^5 * sizeof(int) bytes, which is around 400KB, exceeding the limit.

        int min_val = std::numeric_limits<int>::max(); // Initialize minimum value found so far to the largest possible integer value.
                                                      // Since A[i] are positive (1 <= A[i] <= 10^5), any element will be smaller than this initial value.
        int min_idx = -1; // Variable to store the 1-based index of the minimum value found so far.
                          // Initialize to an invalid index.

        // Loop through the N elements of the array.
        // We use 0-based indexing for the loop counter 'i' (from 0 to N-1) for convenience in C++.
        // The problem requires a 1-based index for the answer (from 1 to N).
        for (int i = 0; i < N; ++i) {
            int current_val; // Variable to store the current element being read
            std::cin >> current_val; // Read the current element (conceptually A_{i+1})

            // Check if the current element is strictly less than the minimum value found so far.
            if (current_val < min_val) {
                // If it is, we found a new minimum value.
                min_val = current_val; // Update the minimum value.
                min_idx = i + 1; // Update the minimum index. Convert the 0-based loop index 'i' to a 1-based index 'i + 1'.
                                 // This step correctly finds the index of the *first* occurrence of the minimum value.
                                 // When we find a new minimum, its index is guaranteed to be the first occurrence of *that specific minimum value*.
            }
            // If current_val is equal to min_val, we do nothing.
            // This is because we are looking for the *minimum* index among all occurrences of the minimum value.
            // If current_val == min_val, the current index (i + 1) is greater than the index already stored in min_idx
            // (which corresponds to the first time min_val was set). So, we keep the smaller index stored in min_idx.
        }

        // After iterating through all N elements, min_idx holds the 1-based index
        // of the first occurrence of the minimum element in the array A.
        // This is the index 'i' that minimizes the value prefixSum(i) + suffixSum(i).

        // Output the result (the minimum 1-based index) for the current test case.
        std::cout << min_idx << std::endl;
    }

    return 0; // Indicate successful program execution
}
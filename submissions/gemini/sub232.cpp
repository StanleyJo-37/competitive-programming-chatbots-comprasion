#include <iostream> // Required for standard input/output operations (std::cin, std::cout)
#include <vector>   // Required for std::vector to store the sequence elements
#include <algorithm> // Required for std::max function

// Function to solve a single test case
void solve() {
    int n; // Declare an integer 'n' to store the size of the sequence
    std::cin >> n; // Read the value of 'n' from standard input

    // Declare a vector 'a' of size 'n' to store the sequence elements.
    // Use 'long long' for elements because their values can be up to 10^9,
    // which might exceed the range of a 32-bit integer.
    std::vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i]; // Read each element into the vector 'a'
    }

    // Initialize 'total_max_sum' to 0. This variable will accumulate the sum
    // of the chosen elements for the maximum length alternating subsequence.
    // Use 'long long' because the sum can be up to N * max_abs_value,
    // which is 2 * 10^5 * 10^9 = 2 * 10^14, exceeding a 32-bit integer's range.
    long long total_max_sum = 0;

    // Initialize an index 'i' to traverse the sequence 'a'.
    // This 'i' pointer will mark the beginning of the current block of same-signed numbers.
    int i = 0;
    while (i < n) { // Loop until 'i' goes beyond the end of the sequence
        // Determine the sign of the current block.
        // If a[i] is positive, the current block consists of positive numbers.
        // If a[i] is negative, the current block consists of negative numbers.
        bool current_block_is_positive = (a[i] > 0);

        // Initialize 'current_max_in_block' with the first element of the current block.
        // This variable will store the maximum value found within the current block.
        long long current_max_in_block = a[i];

        // Use a second index 'j' to iterate through the current block.
        // 'j' starts from the element immediately after 'i'.
        int j = i + 1;
        // Continue as long as 'j' is within bounds and the element a[j] has the same sign
        // as the current block (determined by 'current_block_is_positive').
        while (j < n && (a[j] > 0 == current_block_is_positive)) {
            // If a[j] belongs to the current block, update 'current_max_in_block'
            // if a[j] is greater than the current maximum.
            // For positive numbers, std::max picks the larger positive value.
            // For negative numbers, std::max picks the negative number closest to zero (e.g., max(-1, -5) is -1),
            // which is the "largest" in terms of value.
            current_max_in_block = std::max(current_max_in_block, a[j]);
            j++; // Move to the next element in the sequence
        }

        // After the inner loop finishes, 'j' points to the first element of the next block
        // (or 'n' if the end of the sequence is reached).
        // 'current_max_in_block' now holds the maximum value from the block that started at 'i'
        // and ended at 'j-1'.
        // Add this maximum value to the 'total_max_sum'. This greedy choice is optimal
        // because to maximize the sum for a fixed length, we must pick the largest possible value
        // from each alternating sign block.
        total_max_sum += current_max_in_block;

        // Move the main index 'i' to the beginning of the next block.
        // This ensures that the outer loop continues processing from where the previous block ended.
        i = j;
    }

    // Print the final calculated maximum sum for the current test case, followed by a newline.
    std::cout << total_max_sum << std::endl;
}

int main() {
    // Optimize C++ standard streams for faster input/output operations.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams,
    // which can significantly speed up I/O.
    std::ios_base::sync_with_stdio(false);
    // std::cin.tie(NULL) prevents std::cout from flushing before std::cin reads input.
    // This is useful when mixing cin and cout, but generally good practice for competitive programming.
    std::cin.tie(NULL);

    int t; // Declare an integer 't' to store the number of test cases
    std::cin >> t; // Read the value of 't'

    while (t--) { // Loop 't' times, calling the 'solve' function for each test case
        solve();
    }

    return 0; // Indicate successful program execution
}

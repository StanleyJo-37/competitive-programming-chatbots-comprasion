#include <iostream> // Required for input/output operations (std::cin, std::cout).
#include <vector>   // Not strictly necessary for this solution, but often useful.
#include <numeric>  // Not strictly necessary for this solution, but often useful (e.g., for std::iota).

// Define the maximum possible value for an XOR sum.
// Since a_i < 2^20, the maximum XOR sum will also be less than 2^20.
// This means values range from 0 to (2^20 - 1).
// An array of size 1 << 20 (which is 2^20) is needed to cover all possible values.
const int MAX_XOR_VAL = 1 << 20; // 2^20 = 1,048,576

// Declare global arrays to store counts of prefix XOR sums.
// Global arrays are zero-initialized by default, which is convenient here.
// count_even[val] stores how many times 'val' has appeared as P[k] where k is an even index.
int count_even[MAX_XOR_VAL];
// count_odd[val] stores how many times 'val' has appeared as P[k] where k is an odd index.
int count_odd[MAX_XOR_VAL];

int main() {
    // Optimize C++ standard streams for faster input/output.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams.
    // std::cin.tie(NULL) prevents std::cout from flushing before std::cin reads input.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n; // Declare an integer variable 'n' to store the size of the array.
    std::cin >> n; // Read the value of 'n' from standard input.

    // current_prefix_xor will store the prefix XOR sum up to the current element a_j.
    // This is equivalent to P[j] in our mathematical notation.
    int current_prefix_xor = 0;
    // total_funny_pairs will store the final count of funny pairs.
    // Use long long because the number of pairs can be very large (up to N^2/4, which is ~10^10 for N=3*10^5).
    long long total_funny_pairs = 0;

    // Initialize P[0] = 0.
    // The index 0 is considered even. So, we increment the count for XOR sum 0 at an even index.
    count_even[0] = 1;

    // Iterate through the array elements from a_1 to a_n.
    // In the problem, array elements are 1-indexed.
    // 'j' represents the current 1-indexed position in the array 'a'.
    // So, 'j' also represents the index for the prefix XOR sum P[j].
    for (int j = 1; j <= n; ++j) {
        int a_j; // Declare an integer variable to store the current array element.
        std::cin >> a_j; // Read the current array element a_j.
        
        // Calculate the current prefix XOR sum: P[j] = P[j-1] XOR a_j.
        // 'current_prefix_xor' effectively holds P[j-1] before this line, and P[j] after.
        current_prefix_xor ^= a_j;

        // The problem condition is: a_l ⊕ … ⊕ a_{mid} = a_{mid + 1} ⊕ … ⊕ a_r.
        // This simplifies to P[l-1] = P[r].
        // Let i = l-1 and j = r. We need to find pairs (i, j) such that P[i] = P[j].
        // Also, the length of the subarray (r - l + 1) must be even.
        // Substituting l = i+1 and r = j, the length is j - (i+1) + 1 = j - i.
        // So, we need j - i to be an even number.
        // This implies that 'i' and 'j' must have the same parity (both even or both odd).

        if (j % 2 == 0) { // If the current index 'j' is even
            // We need 'i' to be even (same parity as 'j').
            // Add the count of previous even-indexed prefix XOR sums that are equal to 'current_prefix_xor' (P[j]).
            total_funny_pairs += count_even[current_prefix_xor];
            // Increment the count for 'current_prefix_xor' at an even index (j).
            count_even[current_prefix_xor]++;
        } else { // If the current index 'j' is odd
            // We need 'i' to be odd (same parity as 'j').
            // Add the count of previous odd-indexed prefix XOR sums that are equal to 'current_prefix_xor' (P[j]).
            total_funny_pairs += count_odd[current_prefix_xor];
            // Increment the count for 'current_prefix_xor' at an odd index (j).
            count_odd[current_prefix_xor]++;
        }
    }

    // Print the total number of funny pairs found.
    std::cout << total_funny_pairs << std::endl;

    return 0; // Indicate successful execution.
}

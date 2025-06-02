#include <iostream> // Required for standard input/output operations (std::cin, std::cout, std::endl)
#include <vector>   // Required for std::vector (specifically std::vector<bool> for space efficiency)
#include <string>   // Required for std::string to handle the binary string S

// Function to solve a single test case
void solve() {
    int N, K; // N: length of the binary string, K: length of the substring to flip
    std::cin >> N >> K; // Read N and K
    std::string S; // Declare the string S
    std::cin >> S; // Read the binary string S

    // flip_ops[i] will be true if an operation (flipping a substring of length K)
    // is performed starting at index i.
    // std::vector<bool> is a specialized template that stores booleans as bits,
    // making it very memory-efficient (N bits = N/8 bytes).
    // For N=10^5, this uses approximately 12.5 KB, which is crucial given the memory limit.
    std::vector<bool> flip_ops(N, false);

    // num_active_flips keeps track of the count of operations that are currently
    // affecting the character S[i].
    // An operation starting at index 'j' affects characters from S[j] to S[j+K-1].
    // When we are at index 'i', we are interested in operations that started
    // at 'j' such that j <= i and j+K-1 >= i.
    // This means 'j' must be in the range [max(0, i-K+1), i].
    // This variable acts as a sliding window sum of flip_ops[j] for 'j' in this range.
    int num_active_flips = 0;

    // Iterate through the string from left to right (index i from 0 to N-1).
    // This greedy approach aims to make the string lexicographically smallest.
    // To achieve this, we try to make S[i] '0' if possible, for each 'i' in order.
    for (int i = 0; i < N; ++i) {
        // Step 1: Update num_active_flips by removing operations that are no longer active.
        // An operation starting at index (i-K) affects characters up to (i-K) + K - 1 = i-1.
        // So, when we move from index (i-1) to 'i', the operation that started at (i-K)
        // (if it was performed) no longer affects S[i].
        if (i >= K) { // Check if i-K is a valid index (i.e., we've processed at least K characters)
            if (flip_ops[i - K]) { // If an operation was performed at (i-K)
                num_active_flips--; // Decrement the count of active flips
            }
        }

        // Step 2: Determine the current effective character at S[i].
        // The original character S[i] is flipped if num_active_flips is odd.
        // (S[i] - '0') converts '0' to integer 0 and '1' to integer 1.
        // XOR with (num_active_flips % 2) effectively flips the bit if num_active_flips is odd.
        // If num_active_flips is even, (num_active_flips % 2) is 0, so XORing with 0 leaves the bit unchanged.
        // If num_active_flips is odd, (num_active_flips % 2) is 1, so XORing with 1 flips the bit.
        int current_char_val = (S[i] - '0') ^ (num_active_flips % 2);

        // Step 3: Decide whether to perform a new operation starting at index 'i'.
        // We want S[i] to be '0'.
        // If current_char_val is '1' (meaning S[i] is effectively '1' after previous operations):
        // We must perform an operation to flip it to '0'.
        // The only new operation we can perform to affect S[i] at this stage (processing left-to-right)
        // is one that starts exactly at 'i'.
        // An operation starting at 'i' is only possible if the substring S[i...i+K-1]
        // is entirely within the bounds of the string. This means i+K-1 must be less than N,
        // or equivalently, i must be less than or equal to N-K.
        if (current_char_val == 1 && i <= N - K) {
            // If S[i] is '1' and we can start an operation at 'i':
            // Perform an operation starting at 'i'.
            flip_ops[i] = true;
            // This new operation becomes active and affects S[i] (and subsequent K-1 characters).
            // So, increment the count of active flips.
            num_active_flips++;
            // S[i] effectively becomes '0' due to this new flip.
            S[i] = '0'; // Update the string S in place
        } else {
            // If current_char_val is '0' (meaning S[i] is already '0' after previous operations),
            // we don't need to do anything. Performing an operation would make it '1', which is worse.
            // OR, if current_char_val is '1' but we cannot start an operation at 'i' (because i > N-K),
            // then we have no choice but to leave S[i] as '1'.
            // In both these cases, S[i] will be its current effective value.
            S[i] = (current_char_val == 0 ? '0' : '1'); // Update the string S in place
        }
    }

    // After iterating through all characters, the string S contains the lexicographically
    // smallest string achievable.
    std::cout << S << std::endl; // Output the result
}

int main() {
    // Optimize C++ standard streams for faster input/output.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams.
    // std::cin.tie(NULL) prevents std::cout from flushing before std::cin reads input.
    // These optimizations are standard practice in competitive programming for performance.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int T; // T: number of test cases
    std::cin >> T; // Read the number of test cases
    while (T--) { // Loop T times, decrementing T each iteration
        solve(); // Call the solve function for each test case
    }

    return 0; // Indicate successful execution
}

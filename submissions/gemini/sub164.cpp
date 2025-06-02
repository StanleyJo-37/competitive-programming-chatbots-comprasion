#include <iostream>
#include <algorithm> // Required for std::min

// Define the modulo constant as a global constant for easy access.
const long long MOD = 1e9 + 7;

// Function to solve a single test case.
void solve() {
    unsigned long long L, R;
    // Read the input values L and R.
    std::cin >> L >> R;

    long long total_sum = 0; // Initialize the sum S to 0. This will store the result modulo MOD.
    unsigned long long current_val = L; // This variable stores the current value of (L & (L+1) & ... & i).
                                        // Initially, for i=L, this value is L.
    unsigned long long current_idx = L; // This variable marks the starting index of the current segment
                                        // where the value of (L & ... & i) remains constant.

    // The main loop iterates through segments where the value of f(i) = (L & ... & i) is constant.
    // Since f(i) is non-increasing and eventually becomes 0, there are at most 60 such segments
    // (as L, R are up to 10^18, which is less than 2^60).
    while (current_idx <= R) {
        // If current_val becomes 0, it means all subsequent f(i) values will also be 0
        // because bitwise AND with 0 results in 0. So, no more non-zero values will be added to the sum.
        if (current_val == 0) {
            break;
        }

        // Find the smallest 'next_idx' such that f(next_idx) < current_val.
        // This means 'current_val & next_idx' must be less than 'current_val'.
        // This condition is met when 'next_idx' has a 0 at some bit position 'k'
        // where 'current_val' has a 1.
        // To find the smallest such 'next_idx', we iterate through all bit positions 'k'
        // where 'current_val' has a 1. For each such 'k', we calculate the smallest number 'X_k'
        // that is greater than or equal to 'current_idx' and has a 0 at bit 'k'.
        // The 'next_idx_candidate' will be the minimum of all such 'X_k' values.
        unsigned long long next_idx_candidate = -1ULL; // Initialize with the maximum possible unsigned long long value.

        // Iterate through bit positions from 0 up to 62.
        // (10^18 is less than 2^60, so bits up to 59 are relevant. 63 bits cover all unsigned long long values.)
        for (int k = 0; k < 63; ++k) {
            // Check if the k-th bit of 'current_val' is 1.
            if ((current_val >> k) & 1) {
                unsigned long long X_k;
                // If the k-th bit of 'current_idx' is already 0, then 'current_idx' itself
                // is the smallest number >= 'current_idx' that has a 0 at bit 'k'.
                if (!((current_idx >> k) & 1)) {
                    X_k = current_idx;
                } else {
                    // If the k-th bit of 'current_idx' is 1, we need to find the next number
                    // that has a 0 at bit 'k'. This is achieved by clearing all bits from 0 to k
                    // in 'current_idx' and then adding 2^(k+1). This effectively rounds 'current_idx' up
                    // to the next multiple of 2^(k+1).
                    // Example: current_idx = 10110 (22), k=2. Bit 2 is 1.
                    // (1ULL << (k + 1)) - 1ULL creates a mask like 0...0111 (for k=2, it's 7).
                    // ~((1ULL << (k + 1)) - 1ULL) creates a mask like 1...1000 (for k=2, it's ~7).
                    // current_idx & ~mask clears bits 0 to k. (22 & ~7 = 16, i.e., 10000_2).
                    // Then add (1ULL << (k + 1)) which is 2^(k+1). (16 + 8 = 24, i.e., 11000_2).
                    X_k = (current_idx & ~((1ULL << (k + 1)) - 1ULL)) + (1ULL << (k + 1));
                }
                // Update 'next_idx_candidate' with the minimum 'X_k' found so far.
                next_idx_candidate = std::min(next_idx_candidate, X_k);
            }
        }

        // The current segment where f(i) = current_val is [current_idx, end_of_range].
        // This segment ends either at R (the overall upper bound) or at (next_idx_candidate - 1),
        // whichever comes first.
        unsigned long long end_of_range = std::min(R, next_idx_candidate - 1);

        // Calculate the number of elements in this segment.
        // The count is (end_of_range - current_idx + 1).
        unsigned long long count = end_of_range - current_idx + 1;

        // Add (current_val * count) to the total sum, taking modulo MOD at each step.
        // We take modulo for 'current_val' and 'count' before multiplication to prevent
        // intermediate overflow if they were large, and then take modulo of the product.
        total_sum = (total_sum + (current_val % MOD) * (count % MOD)) % MOD;

        // Move to the next segment. The new starting index is one past the end of the current segment.
        current_idx = end_of_range + 1;
        // The new 'current_val' is calculated by ANDing the previous 'current_val' with the new 'current_idx'.
        // This is based on the property f(i) = f(i-1) & i. So, f(current_idx) = f(current_idx - 1) & current_idx.
        // Here, f(current_idx - 1) was the 'current_val' from the previous segment.
        current_val = current_val & current_idx;
    }

    // Print the final calculated sum modulo MOD.
    std::cout << total_sum << std::endl;
}

int main() {
    // Optimize C++ standard streams for faster input/output.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams.
    // std::cin.tie(NULL) prevents std::cout from flushing before std::cin reads input.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int T;
    // Read the number of test cases.
    std::cin >> T;
    // Loop through each test case.
    while (T--) {
        solve();
    }

    return 0;
}
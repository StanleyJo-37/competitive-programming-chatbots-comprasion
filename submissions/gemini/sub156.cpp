#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

// Function to count numbers in the range [0, n] that have the k-th bit set.
// This is a crucial helper function for efficiently determining the bit counts
// in the original sequence [l, r].
long long count_bits_up_to_n(int n, int k) {
    // If n is negative, it means the range is empty or invalid for this calculation (e.g., l-1 when l=0).
    // In such cases, there are no numbers to count, so return 0.
    if (n < 0) {
        return 0;
    }

    // 'block_size' represents the cycle length of the k-th bit pattern (0...01...1).
    // For the k-th bit, the pattern is 2^k zeros followed by 2^k ones, repeating.
    // So, a full block has a size of 2^k + 2^k = 2^(k+1).
    long long block_size = 1LL << (k + 1);

    // 'num_full_blocks' is the number of complete 'block_size' cycles within the range [0, n].
    // We consider (n + 1) elements from 0 to n.
    long long num_full_blocks = (n + 1) / block_size;

    // Each full block contributes exactly 2^k set bits.
    long long count = num_full_blocks * (1LL << k);

    // 'remainder' is the number of elements remaining after accounting for all full blocks.
    long long remainder = (n + 1) % block_size;

    // These 'remainder' elements form a partial block.
    // If this partial block extends into the 'ones' part of the cycle (which starts after 2^k zeros),
    // then it contributes additional set bits.
    // The 'ones' part of a block starts at index 2^k (0-indexed) within that block.
    // So, if 'remainder' is greater than 2^k, the number of set bits contributed by the remainder
    // is 'remainder - 2^k'. We use std::max to ensure it's not negative if remainder is small.
    count += std::max(0LL, remainder - (1LL << k));

    return count;
}

void solve() {
    int l, r;
    std::cin >> l >> r; // Read the range [l, r]
    int n = r - l + 1; // Calculate the length of the array

    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i]; // Read the given array 'a'
    }

    int x = 0; // Initialize the secret integer x to 0. We will build it bit by bit.

    // The maximum value for r is less than 2^17, meaning numbers are in [0, 2^17 - 1].
    // Thus, we only need to consider bit positions from 0 up to 16.
    const int MAX_BITS = 17;

    // Iterate through each bit position 'k' from 0 to MAX_BITS - 1.
    // For each bit, we determine if the k-th bit of 'x' should be 0 or 1.
    for (int k = 0; k < MAX_BITS; ++k) {
        // Calculate 'count_set_b_k': the number of elements in the original sequence [l, r]
        // that have the k-th bit set. This is done by using the precomputed counts:
        // (count of set k-th bits up to r) - (count of set k-th bits up to l-1).
        long long count_set_b_k = count_bits_up_to_n(r, k) - count_bits_up_to_n(l - 1, k);

        // Calculate 'count_set_a_k': the number of elements in the given array 'a'
        // that have the k-th bit set. This requires iterating through 'a'.
        long long count_set_a_k = 0;
        for (int val : a) {
            if ((val >> k) & 1) { // Check if the k-th bit of 'val' is set
                count_set_a_k++;
            }
        }

        // Determine the k-th bit of 'x' based on the counts:
        // Case 1: If the k-th bit of 'x' is 0 (x_k = 0).
        // In this case, for any original number b_i, (b_i XOR x)_k = (b_i)_k.
        // This means the k-th bits are preserved. So, the count of set k-th bits
        // in 'a' must be equal to the count of set k-th bits in 'b'.
        if (count_set_a_k == count_set_b_k) {
            // x_k is 0. No action needed as 'x' is initialized to 0.
        }
        // Case 2: If the k-th bit of 'x' is 1 (x_k = 1).
        // In this case, for any original number b_i, (b_i XOR x)_k = 1 - (b_i)_k.
        // This means the k-th bits are flipped. So, the count of set k-th bits
        // in 'a' must be equal to the count of unset k-th bits in 'b'.
        // The count of unset k-th bits in 'b' is (total elements N) - (count of set k-th bits in 'b').
        else if (count_set_a_k == n - count_set_b_k) {
            // x_k is 1. Set the k-th bit in 'x' using bitwise OR.
            x |= (1 << k);
        }
        // The problem guarantees that a valid 'x' exists, so one of the above two conditions
        // must always be true for each bit 'k'. No 'else' branch for error handling is necessary.
    }

    // Print the determined secret integer 'x'.
    std::cout << x << std::endl;
}

int main() {
    // Optimize C++ standard streams for faster input/output operations.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams.
    // std::cin.tie(NULL) prevents std::cout from flushing before std::cin reads input.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t; // Read the number of test cases.
    while (t--) {
        solve(); // Solve each test case.
    }

    return 0;
}

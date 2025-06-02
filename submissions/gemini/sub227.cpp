#include <iostream>
#include <vector>
#include <numeric> // Not strictly needed for this solution, but useful for other permutation problems

void solve() {
    int n;
    std::cin >> n;
    // Use long long for shoe sizes as they can be up to 10^9.
    // Although int (typically 2*10^9) would suffice, long long is safer.
    std::vector<long long> s(n); 
    for (int i = 0; i < n; ++i) {
        std::cin >> s[i];
    }

    // p will store the 0-indexed permutation.
    // p[i] means student (i+1) gets shoes from student (p[i]+1).
    std::vector<int> p(n); 
    int current_idx = 0; // Start of the current block being processed

    // Iterate through the array to find maximal contiguous blocks of identical shoe sizes
    while (current_idx < n) {
        int block_start = current_idx;
        int block_end = current_idx;

        // Find the end of the current block
        // All elements from s[block_start] to s[block_end] will have the same value
        while (block_end + 1 < n && s[block_end + 1] == s[block_start]) {
            block_end++;
        }

        // Calculate the size of the current block
        int block_size = block_end - block_start + 1;

        // If a block has size 1, it means a student has a unique shoe size (relative to their neighbors).
        // As proven in the thought process, students within a maximal block of identical shoe sizes
        // must exchange shoes only among themselves. If a block has size 1, say student 'k',
        // then 'k' must get shoes from 'k' (p_k = k) to satisfy the size condition within its block.
        // However, the problem requires p_k != k. Thus, it's impossible.
        if (block_size == 1) {
            std::cout << -1 << std::endl;
            return; // No valid permutation exists for this test case
        }

        // If the block size is 2 or more, we can perform a cyclic shift within the block.
        // For a block of indices [block_start, ..., block_end]:
        // Student block_start gets shoes from block_start + 1
        // Student block_start + 1 gets shoes from block_start + 2
        // ...
        // Student block_end - 1 gets shoes from block_end
        // Student block_end gets shoes from block_start
        // This ensures p_k != k for all k in the block and s_k <= s_{p_k} (since s_k = s_{p_k} here).
        for (int i = block_start; i < block_end; ++i) {
            p[i] = i + 1;
        }
        p[block_end] = block_start;

        // Move current_idx to the start of the next block
        current_idx = block_end + 1;
    }

    // Output the resulting permutation, converting 0-indexed values to 1-indexed as required
    for (int i = 0; i < n; ++i) {
        std::cout << p[i] + 1 << (i == n - 1 ? "" : " ");
    }
    std::cout << std::endl;
}

int main() {
    // Optimize C++ standard streams for competitive programming.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams,
    // potentially speeding up I/O.
    // std::cin.tie(NULL) prevents std::cout from flushing before std::cin reads input.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t; // Number of test cases
    std::cin >> t;
    while (t--) {
        solve(); // Solve each test case
    }

    return 0;
}

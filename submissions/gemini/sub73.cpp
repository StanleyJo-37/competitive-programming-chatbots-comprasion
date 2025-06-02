#include <iostream>
#include <vector>
#include <algorithm>

void solve() {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    
    // `positions[v]` stores a list of 0-indexed positions where value `v` appears in the input array `a`.
    // The size is 27 to accommodate values from 1 to 26 (using 1-based indexing for values).
    std::vector<std::vector<int>> positions(27); 
    
    // `prefix_counts[v][i]` stores the count of value `v` in the subarray `a[0...i-1]`.
    // The size `n + 1` allows `prefix_counts[v][0]` to be 0 (count before index 0)
    // and `prefix_counts[v][n]` to be the total count in `a[0...n-1]`.
    std::vector<std::vector<int>> prefix_counts(27, std::vector<int>(n + 1, 0));

    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
        // Record the current index for the value `a[i]`.
        positions[a[i]].push_back(i);
        
        // For each value `v` from 1 to 26, copy its count from the previous index `i` to `i+1`.
        // This ensures `prefix_counts[v][i+1]` starts with the count of `v` in `a[0...i-1]`.
        for (int v = 1; v <= 26; ++v) {
            prefix_counts[v][i+1] = prefix_counts[v][i];
        }
        // Then, increment the count for the specific value `a[i]` at index `i+1`.
        // This makes `prefix_counts[a[i]][i+1]` reflect the count of `a[i]` in `a[0...i]`.
        prefix_counts[a[i]][i+1]++;
    }

    // Initialize `max_len` to 0. An empty sequence is a valid three-blocks palindrome of length 0.
    int max_len = 0;

    // First, consider palindromes consisting of only one distinct element.
    // These are of the form `[a, a, ..., a]`.
    // The maximum length for such a palindrome is simply the total count of that element in `a`.
    // This covers cases like `x=0, y>0` (e.g., `[b,b,b]`) or `x>0, y=0` (e.g., `[a,a,a]`),
    // and also the case where `val_a` equals `val_b` in the two-distinct-element structure.
    for (int val = 1; val <= 26; ++val) {
        max_len = std::max(max_len, (int)positions[val].size());
    }

    // Next, consider palindromes consisting of two distinct elements: `[a, ..., a, b, ..., b, a, ..., a]`.
    // Iterate over all possible values for the outer elements (`val_a`).
    for (int val_a = 1; val_a <= 26; ++val_a) {
        int k = positions[val_a].size(); // Total occurrences of `val_a` in `a`.

        // Iterate over possible number of `val_a`s in each outer block (`x`).
        // `x` can range from 1 up to `k/2`.
        // If `x=0`, it's covered by the single-element case.
        // If `k < 2`, `k/2` will be 0, so this loop won't run, which is correct as we need at least two `val_a`s for outer blocks.
        for (int x = 1; x <= k / 2; ++x) {
            // `left_idx` is the 0-indexed position of the `x`-th `val_a` from the left.
            // For example, if `x=1`, it's `positions[val_a][0]`.
            int left_idx = positions[val_a][x - 1];
            
            // `right_idx` is the 0-indexed position of the `x`-th `val_a` from the right.
            // This corresponds to the `(k-x)`-th element in the `positions[val_a]` vector (0-indexed).
            // For example, if `x=1`, it's `positions[val_a][k-1]`.
            int right_idx = positions[val_a][k - x];

            // If `left_idx` is greater than or equal to `right_idx`, it means the chosen outer `val_a`s
            // overlap or are adjacent, leaving no space for a middle block.
            // In this scenario, a valid three-block palindrome with `x` outer elements and a middle block
            // cannot be formed.
            if (left_idx >= right_idx) {
                continue;
            }

            // Find the maximum count of any element (`val_b`) that can form the middle block.
            // The middle segment consists of elements in `a` strictly between `left_idx` and `right_idx`.
            // That is, `a[left_idx+1 ... right_idx-1]`.
            int current_y = 0;
            for (int val_b = 1; val_b <= 26; ++val_b) {
                // The count of `val_b` in `a[L...R]` is `prefix_counts[val_b][R+1] - prefix_counts[val_b][L]`.
                // Here, `L = left_idx + 1` and `R = right_idx - 1`.
                // So, the count is `prefix_counts[val_b][(right_idx - 1) + 1] - prefix_counts[val_b][left_idx + 1]`,
                // which simplifies to `prefix_counts[val_b][right_idx] - prefix_counts[val_b][left_idx + 1]`.
                int count_b_in_middle = prefix_counts[val_b][right_idx] - prefix_counts[val_b][left_idx + 1];
                current_y = std::max(current_y, count_b_in_middle);
            }
            
            // The total length of this three-blocks palindrome is `2 * x` (for the outer `val_a`s)
            // plus `current_y` (for the middle `val_b`s).
            max_len = std::max(max_len, 2 * x + current_y);
        }
    }

    std::cout << max_len << std::endl;
}

int main() {
    // Optimize C++ standard streams for faster input/output.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}

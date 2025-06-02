#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

// Function to count pairs (l, r) such that l_low <= l <= l_high, r_low <= r <= r_high, and l <= r.
// All parameters are 1-indexed. N is the maximum possible index.
long long count_in_rect_with_l_le_r(int l_low, int l_high, int r_low, int r_high, int N) {
    // Clip ranges to be within [1, N]
    l_low = std::max(1, l_low);
    l_high = std::min(N, l_high);
    r_low = std::max(1, r_low);
    r_high = std::min(N, r_high);

    // If any range is invalid (e.g., l_low > l_high), no pairs exist
    if (l_low > l_high || r_low > r_high) {
        return 0;
    }

    long long ans = 0;

    // Case 1: l < r_low. In this case, l <= r is always satisfied since r >= r_low.
    // 'l' ranges from l_low to min(l_high, r_low - 1)
    // 'r' ranges from r_low to r_high
    long long current_l_start_part1 = l_low;
    long long current_l_end_part1 = std::min(l_high, r_low - 1);
    
    if (current_l_start_part1 <= current_l_end_part1) {
        long long count_l_part1 = current_l_end_part1 - current_l_start_part1 + 1;
        ans += count_l_part1 * (r_high - r_low + 1);
    }

    // Case 2: l >= r_low. In this case, l <= r must be explicitly checked (r >= l).
    // 'l' ranges from max(l_low, r_low) to l_high
    // 'r' ranges from l to r_high
    long long current_l_start_part2 = std::max(l_low, r_low);
    long long current_l_end_part2 = l_high;

    if (current_l_start_part2 <= current_l_end_part2) {
        // Sum (r_high - l + 1) for l from current_l_start_part2 to current_l_end_part2
        // This is equivalent to summing (r_high + 1) - l.
        // This can be calculated as (r_high + 1) * (number of terms) - sum(l from current_l_start_part2 to current_l_end_part2)
        long long num_terms = current_l_end_part2 - current_l_start_part2 + 1;
        long long sum_l = (current_l_start_part2 + current_l_end_part2) * num_terms / 2;
        ans += (r_high + 1) * num_terms - sum_l;
    }

    return ans;
}

int main() {
    // Optimize C++ standard streams for faster input/output.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    std::cin >> n;

    std::vector<int> p(n);
    std::vector<int> pos_p(n + 1); // pos_p[val] stores index of val in p (1-indexed)
    for (int i = 0; i < n; ++i) {
        std::cin >> p[i];
        pos_p[p[i]] = i + 1; // Store 1-indexed position
    }

    std::vector<int> q(n);
    std::vector<int> pos_q(n + 1); // pos_q[val] stores index of val in q (1-indexed)
    for (int i = 0; i < n; ++i) {
        std::cin >> q[i];
        pos_q[q[i]] = i + 1; // Store 1-indexed position
    }

    // min_idx_p[k] stores the minimum index among pos_p[1], ..., pos_p[k]
    // max_idx_p[k] stores the maximum index among pos_p[1], ..., pos_p[k]
    // These are 1-indexed positions.
    std::vector<int> min_idx_p(n + 1);
    std::vector<int> max_idx_p(n + 1);
    std::vector<int> min_idx_q(n + 1);
    std::vector<int> max_idx_q(n + 1);

    // Initialize for k=0 (representing the empty set of numbers 1..k-1).
    // min_idx_p[0] and min_idx_q[0] should be effectively N+1 (larger than any valid index)
    // max_idx_p[0] and max_idx_q[0] should be effectively 0 (smaller than any valid index)
    min_idx_p[0] = n + 1;
    max_idx_p[0] = 0;
    min_idx_q[0] = n + 1;
    max_idx_q[0] = 0;

    // Precompute min/max indices for values 1 to k
    for (int k = 1; k <= n; ++k) {
        min_idx_p[k] = std::min(min_idx_p[k - 1], pos_p[k]);
        max_idx_p[k] = std::max(max_idx_p[k - 1], pos_p[k]);
        min_idx_q[k] = std::min(min_idx_q[k - 1], pos_q[k]);
        max_idx_q[k] = std::max(max_idx_q[k - 1], pos_q[k]);
    }

    long long total_count = 0;

    // Iterate through possible MEX values, k, from 1 to N.
    // For a segment [l, r] to have MEX = k, it must contain 1, ..., k-1,
    // and it must NOT contain k.
    for (int k = 1; k <= n; ++k) {
        // L_k is the minimum possible 'l' for a segment to contain 1..k-1 in both p and q.
        // R_k is the maximum possible 'r' for a segment to contain 1..k-1 in both p and q.
        // min_idx_p[k-1] refers to the min index of values 1 to k-1.
        int L_k = std::min(min_idx_p[k - 1], min_idx_q[k - 1]);
        int R_k = std::max(max_idx_p[k - 1], max_idx_q[k - 1]);

        // x_p is the 1-indexed position of value k in permutation p.
        // x_q is the 1-indexed position of value k in permutation q.
        int x_p = pos_p[k];
        int x_q = pos_q[k];

        // We need to count pairs (l, r) such that:
        // 1. 1 <= l <= L_k
        // 2. R_k <= r <= N
        // 3. l <= r
        // 4. x_p is NOT in [l, r] (i.e., l > x_p or r < x_p)
        // 5. x_q is NOT in [l, r] (i.e., l > x_q or r < x_q)

        // Calculate total pairs (l, r) satisfying conditions 1, 2, 3 (the trapezoid region)
        long long total_T = count_in_rect_with_l_le_r(1, L_k, R_k, n, n);

        // Calculate pairs where x_p IS in [l, r] (violates condition 4)
        // This means l <= x_p <= r.
        // Combined with 1, 2, 3: l in [1, min(L_k, x_p)], r in [max(R_k, x_p), N]
        long long count_Sp = count_in_rect_with_l_le_r(1, std::min(L_k, x_p), std::max(R_k, x_p), n, n);

        // Calculate pairs where x_q IS in [l, r] (violates condition 5)
        // This means l <= x_q <= r.
        // Combined with 1, 2, 3: l in [1, min(L_k, x_q)], r in [max(R_k, x_q), N]
        long long count_Sq = count_in_rect_with_l_le_r(1, std::min(L_k, x_q), std::max(R_k, x_q), n, n);

        // Calculate pairs where x_p IS in [l, r] AND x_q IS in [l, r] (violates both 4 and 5)
        // This means l <= min(x_p, x_q) and r >= max(x_p, x_q).
        // Combined with 1, 2, 3: l in [1, min(L_k, min(x_p, x_q))], r in [max(R_k, max(x_p, x_q)), N]
        long long count_Sp_Sq = count_in_rect_with_l_le_r(1, std::min(L_k, std::min(x_p, x_q)), std::max(R_k, std::max(x_p, x_q)), n, n);

        // Apply inclusion-exclusion principle:
        // Valid pairs for current k = Total_T - (count_Sp + count_Sq - count_Sp_Sq)
        total_count += total_T - (count_Sp + count_Sq - count_Sp_Sq);
    }

    // Handle the special case where MEX = N+1.
    // This occurs if and only if the segment is [1, N] (contains all numbers from 1 to N).
    // For p, MEX([p_1, ..., p_N]) = N+1.
    // For q, MEX([q_1, ..., q_N]) = N+1.
    // Thus, the pair (1, N) always satisfies the condition for MEX = N+1.
    total_count += 1; 

    std::cout << total_count << std::endl;

    return 0;
}

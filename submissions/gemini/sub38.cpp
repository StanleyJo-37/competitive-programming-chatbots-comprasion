#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

// Define a large enough value for infinity.
// The maximum possible length of a segment is 1000.
// The maximum number of segments is 10000.
// The DP state `j` represents `E_i - min_i` (distance from current end to left boundary).
// The value `dp[j]` represents `max_i - E_i` (distance from current end to right boundary).
// The total length of coverage is `j + dp[j]`.
// The problem constraints and typical competitive programming patterns suggest that
// the relevant range for these relative distances is bounded by a small multiple of max_A.
// If `E_i - min_i` or `max_i - E_i` exceeds `MAX_COORD_DIFF`, we cap it at `MAX_COORD_DIFF`.
// This is because if these distances are very large, the segment is likely already very long,
// and further extending it in that direction won't lead to an optimal solution.
// A common heuristic for this type of problem is to cap the state at 2 * max_A.
// Max a_i is 1000, so 2 * 1000 = 2000.
// The maximum possible value for `j + dp[j]` (total length) could be 2000 + 2000 = 4000.
// So INF should be greater than 4000.
const int INF = 1e9; // A sufficiently large value for infinity.

// Max possible value for a_i is 1000.
// This constant defines the upper bound for the `left_dist` and `right_dist` values
// that we explicitly track in our DP table. Values exceeding this are capped.
const int MAX_COORD_DIFF = 2000; 

void solve() {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    // dp[j] stores the minimum 'right_dist' (max_i - E_i)
    // such that 'left_dist' (E_i - min_i) is j.
    // Initialize with INF, meaning no path to this state yet.
    std::vector<int> dp(MAX_COORD_DIFF + 1, INF);

    // Base case for the first segment a[0]
    // Option 1: Place [0, a[0]]. E_1 = a[0], min_1 = 0, max_1 = a[0].
    // left_dist = a[0] - 0 = a[0].
    // right_dist = a[0] - a[0] = 0.
    // We cap a[0] at MAX_COORD_DIFF if it's larger.
    dp[std::min(a[0], MAX_COORD_DIFF)] = std::min(dp[std::min(a[0], MAX_COORD_DIFF)], 0);

    // Option 2: Place [-a[0], 0]. E_1 = -a[0], min_1 = -a[0], max_1 = 0.
    // left_dist = -a[0] - (-a[0]) = 0.
    // right_dist = 0 - (-a[0]) = a[0].
    // We cap a[0] at MAX_COORD_DIFF if it's larger.
    dp[0] = std::min(dp[0], std::min(a[0], MAX_COORD_DIFF));

    // Iterate through the remaining segments from the second one (index 1)
    for (int i = 1; i < n; ++i) {
        int current_segment_len = a[i];
        // new_dp will store the states for the current segment 'a[i]'
        std::vector<int> new_dp(MAX_COORD_DIFF + 1, INF);

        // Iterate over all possible previous states (left_dist_prev)
        // 'j' represents 'left_dist_prev'
        for (int j = 0; j <= MAX_COORD_DIFF; ++j) {
            if (dp[j] == INF) {
                continue; // This previous state is unreachable, so skip
            }

            int left_dist_prev = j;
            int right_dist_prev = dp[j];

            // Option 1: Place current segment to the left of the previous end.
            // The new segment is [E_prev - current_segment_len, E_prev].
            // The new end point is E_curr = E_prev - current_segment_len.
            //
            // Calculate new left_dist:
            // If current_segment_len is greater than left_dist_prev, it means the new segment
            // extends past the previous minimum coordinate. So, E_curr becomes the new min_coord,
            // and new_left_dist becomes 0.
            // Otherwise, new_left_dist is simply left_dist_prev - current_segment_len.
            int new_left_dist1 = left_dist_prev - current_segment_len;
            if (new_left_dist1 < 0) { 
                new_left_dist1 = 0; 
            }
            // Calculate new right_dist:
            // The previous max_coord remains the same, but the end point moved left.
            // So, right_dist increases by current_segment_len.
            int new_right_dist1 = right_dist_prev + current_segment_len;
            
            // Cap the new relative distances at MAX_COORD_DIFF to keep the state space manageable.
            new_left_dist1 = std::min(new_left_dist1, MAX_COORD_DIFF);
            new_right_dist1 = std::min(new_right_dist1, MAX_COORD_DIFF);
            
            // Update new_dp with the minimum right_dist for this new_left_dist.
            // We take the minimum because multiple paths might lead to the same (left_dist, right_dist) state.
            new_dp[new_left_dist1] = std::min(new_dp[new_left_dist1], new_right_dist1);

            // Option 2: Place current segment to the right of the previous end.
            // The new segment is [E_prev, E_prev + current_segment_len].
            // The new end point is E_curr = E_prev + current_segment_len.
            //
            // Calculate new left_dist:
            // The previous min_coord remains the same, but the end point moved right.
            // So, left_dist increases by current_segment_len.
            int new_left_dist2 = left_dist_prev + current_segment_len;
            // Calculate new right_dist:
            // If current_segment_len is greater than right_dist_prev, it means the new segment
            // extends past the previous maximum coordinate. So, E_curr becomes the new max_coord,
            // and new_right_dist becomes 0.
            // Otherwise, new_right_dist is simply right_dist_prev - current_segment_len.
            int new_right_dist2 = right_dist_prev - current_segment_len;
            if (new_right_dist2 < 0) { 
                new_right_dist2 = 0; 
            }

            // Cap the new relative distances at MAX_COORD_DIFF.
            new_left_dist2 = std::min(new_left_dist2, MAX_COORD_DIFF);
            new_right_dist2 = std::min(new_right_dist2, MAX_COORD_DIFF);

            // Update new_dp with the minimum right_dist for this new_left_dist.
            new_dp[new_left_dist2] = std::min(new_dp[new_left_dist2], new_right_dist2);
        }
        // After processing all previous states for a[i], update dp for the next iteration.
        dp = new_dp; 
    }

    // After processing all segments, find the minimum total coverage length
    // which is left_dist + right_dist for all reachable states.
    int min_total_coverage = INF;
    for (int j = 0; j <= MAX_COORD_DIFF; ++j) {
        if (dp[j] != INF) {
            min_total_coverage = std::min(min_total_coverage, j + dp[j]);
        }
    }

    std::cout << min_total_coverage << std::endl;
}

int main() {
    // Optimize C++ standard streams for competitive programming.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}

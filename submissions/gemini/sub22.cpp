#include <iostream>
#include <vector>
#include <algorithm>

// Function to solve a single test case
void solve() {
    int n;
    long long a, b;
    std::cin >> n >> a >> b; // Read n, a, b

    std::vector<long long> x(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> x[i]; // Read kingdom positions
    }

    // x_val will store kingdom positions including x_0 = 0 at index 0.
    // This simplifies 1-based indexing for DP and prefix sums.
    std::vector<long long> x_val(n + 1);
    x_val[0] = 0; // Capital's initial position
    for (int i = 0; i < n; ++i) {
        x_val[i+1] = x[i]; // Store x_1 at x_val[1], x_2 at x_val[2], etc.
    }

    // dp[i] stores the minimum cost to conquer kingdoms x_1, ..., x_i,
    // with the capital currently at x_i.
    std::vector<long long> dp(n + 1);
    // min_cost_to_0[i] stores the minimum cost to conquer kingdoms x_1, ..., x_i,
    // with the capital currently at 0.
    std::vector<long long> min_cost_to_0(n + 1);

    // Base cases for DP:
    // Before conquering any kingdom (i=0), capital is at 0, cost is 0.
    dp[0] = 0; // Represents the state where x_0 is "conquered" (it's the capital) with 0 cost.
    min_cost_to_0[0] = 0; // Represents the state where capital is at 0 with 0 cost.

    // Calculate prefix sums of kingdom positions.
    // S_x[i] = sum of x_val[1] through x_val[i].
    std::vector<long long> S_x(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        S_x[i] = S_x[i-1] + x_val[i];
    }

    // Fill DP tables for i from 1 to n
    for (int i = 1; i <= n; ++i) {
        // Calculate min_cost_to_0[i]: Minimum cost to conquer x_1...x_i, capital at 0.
        // Option 1: Capital was already at 0 after conquering x_1...x_{i-1}.
        //   Cost: min_cost_to_0[i-1] (cost to conquer x_1...x_{i-1} and be at 0)
        //         + b * x_val[i] (cost to conquer x_i from 0).
        //   Capital remains at 0.
        long long cost1_to_0 = min_cost_to_0[i-1] + b * x_val[i];

        // Option 2: Capital was at x_{i-1} after conquering x_1...x_{i-1}.
        //   Cost: dp[i-1] (cost to conquer x_1...x_{i-1} and be at x_{i-1})
        //         + a * x_val[i-1] (cost to move capital from x_{i-1} to 0)
        //         + b * x_val[i] (cost to conquer x_i from 0).
        //   Capital remains at 0.
        long long cost2_to_0 = dp[i-1] + a * x_val[i-1] + b * x_val[i];
        min_cost_to_0[i] = std::min(cost1_to_0, cost2_to_0);

        // Calculate dp[i]: Minimum cost to conquer x_1...x_i, capital at x_i.
        // Option 1: Capital was at 0 after conquering x_1...x_{i-1}.
        //   Cost: min_cost_to_0[i-1] (cost to conquer x_1...x_{i-1} and be at 0)
        //         + b * x_val[i] (cost to conquer x_i from 0)
        //         + a * x_val[i] (cost to move capital from 0 to x_i).
        //   Capital is at x_i.
        long long cost1_to_xi = min_cost_to_0[i-1] + (a + b) * x_val[i];

        // Option 2: Capital was at x_{i-1} after conquering x_1...x_{i-1}.
        //   Cost: dp[i-1] (cost to conquer x_1...x_{i-1} and be at x_{i-1})
        //         + b * (x_val[i] - x_val[i-1]) (cost to conquer x_i from x_{i-1})
        //         + a * (x_val[i] - x_val[i-1]) (cost to move capital from x_{i-1} to x_i).
        //   Capital is at x_i.
        long long cost2_to_xi = dp[i-1] + (a + b) * (x_val[i] - x_val[i-1]);
        dp[i] = std::min(cost1_to_xi, cost2_to_xi);
    }

    // The minimum total cost is found by considering all possible "pivot" points k.
    // A pivot point k means we conquer kingdoms x_1, ..., x_k using the DP logic,
    // and then conquer the remaining kingdoms x_{k+1}, ..., x_n from the capital
    // position established at x_k (or 0).
    long long min_total_cost = -1; // Initialize with a value that will be overwritten

    // Iterate through all possible pivot points k (from 0 to n).
    // k represents the index of the last kingdom conquered using the DP logic.
    // If k=0, it means we conquer all kingdoms from the initial capital at 0.
    // If k=n, it means all kingdoms are conquered using the DP logic.
    for (int k = 0; k <= n; ++k) {
        // Path 1: After conquering x_1...x_k, capital is at x_k.
        // This path is valid for k >= 0. If k=0, capital is at x_0=0.
        // Cost to conquer x_1...x_k and have capital at x_k is dp[k].
        // Then conquer x_{k+1}...x_n from x_k.
        // The cost for remaining conquests is sum of b * (x_j - x_k) for j from k+1 to n.
        // This sum can be rewritten as b * (sum(x_j for j=k+1 to n) - (n-k) * x_k).
        // Using prefix sums: b * ((S_x[n] - S_x[k]) - (long long)(n-k) * x_val[k]).
        long long current_path_cost_from_xk = dp[k] + b * (S_x[n] - S_x[k] - (long long)(n - k) * x_val[k]);
        
        if (min_total_cost == -1 || current_path_cost_from_xk < min_total_cost) {
            min_total_cost = current_path_cost_from_xk;
        }

        // Path 2: After conquering x_1...x_k, capital is at 0.
        // This path is valid for k >= 0.
        // Cost to conquer x_1...x_k and have capital at 0 is min_cost_to_0[k].
        // Then conquer x_{k+1}...x_n from 0.
        // The cost for remaining conquests is sum of b * x_j for j from k+1 to n.
        // Using prefix sums: b * (S_x[n] - S_x[k]).
        long long current_path_cost_from_0 = min_cost_to_0[k] + b * (S_x[n] - S_x[k]);

        if (min_total_cost == -1 || current_path_cost_from_0 < min_total_cost) {
            min_total_cost = current_path_cost_from_0;
        }
    }

    std::cout << min_total_cost << std::endl;
}

int main() {
    // Optimize C++ standard streams for competitive programming.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t; // Read the number of test cases
    while (t--) {
        solve(); // Solve each test case
    }

    return 0;
}

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

// For each test case, we use dynamic programming.
// dp[i]: minimum cost to conquer all kingdoms up to i (x[0]..x[i]), with capital at x[i].
// We can either:
// 1. Conquer x[i] from current capital (which is at x[i-1]) without moving capital (cost: b*(x[i]-x[i-1]))
// 2. Move capital to x[i] after conquering it, and then conquer next kingdoms from there (cost: a*(x[i]-x[i-1]) + b*(x[i]-x[i-1]))
// But, since we can only conquer next kingdom if all between are conquered, we must process in order.
// We also need to consider the cost of conquering from 0 (the initial capital).
// We use prefix sums to optimize the calculation.

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        long long a, b;
        cin >> n >> a >> b;
        vector<long long> x(n);
        for (int i = 0; i < n; ++i) cin >> x[i];

        // dp[i]: minimum cost to conquer all up to x[i], with capital at x[i]
        // Initially, capital is at 0
        // We can only conquer x[0] from 0
        // dp[0] = b * (x[0] - 0)
        // Optionally, we can move capital to x[0] after conquering it: cost += a * (x[0] - 0)
        // For each i > 0, we can:
        // - Conquer x[i] from current capital (at x[i-1]), cost = dp[i-1] + b*(x[i]-x[i-1])
        // - Move capital to x[i] after conquering it, cost = dp[i-1] + a*(x[i]-x[i-1]) + b*(x[i]-x[i-1])
        // But, since we can only move capital to a conquered kingdom, and only after conquering it, we can
        // always consider the minimum cost to reach x[i] as:
        // dp[i] = min(dp[i-1] + b*(x[i]-x[i-1]), min_cost_to_move_capital_to_xi)
        // But, moving capital to x[i] is only beneficial if a < b, otherwise, just conquer from previous capital.

        // We can optimize by keeping track of the minimum cost to reach x[i] with capital at x[i]
        // Let's use a variable to keep the minimum cost so far if we move capital to x[i]
        long long res = LLONG_MAX;
        long long cost = 0; // cost so far
        long long min_cost = 0; // minimum cost to reach current position with capital at current position

        // At the start, capital is at 0
        // We can conquer x[0] from 0: cost = b * (x[0] - 0)
        // Optionally, move capital to x[0]: cost += a * (x[0] - 0)
        // But since we can only move capital to a conquered kingdom, and only after conquering it,
        // we must conquer first, then move capital.
        // So, for i = 0:
        // - conquer x[0] from 0: cost = b * (x[0] - 0)
        // - move capital to x[0]: cost += a * (x[0] - 0)
        // For i > 0:
        // - conquer x[i] from current capital (at x[i-1]): cost = min_cost + b*(x[i]-x[i-1])
        // - move capital to x[i]: cost = min_cost + a*(x[i]-x[i-1]) + b*(x[i]-x[i-1])
        // But, we can also consider conquering all remaining kingdoms from current capital, without moving.

        // Let's precompute the cost if we never move the capital (always conquer from 0)
        long long total_cost = 0;
        long long prev = 0;
        for (int i = 0; i < n; ++i) {
            total_cost += b * (x[i] - prev);
            prev = x[i];
        }
        res = total_cost;

        // Now, try moving the capital to each x[i] after conquering it, and see if it's better
        // We'll process from left to right, keeping track of the cost to conquer up to x[i], and the cost if we move capital to x[i]
        cost = 0;
        prev = 0;
        for (int i = 0; i < n; ++i) {
            // Conquer x[i] from prev capital
            cost += b * (x[i] - prev);
            // Now, consider moving capital to x[i] after conquering it
            // The cost to move capital is a * (x[i] - prev)
            // After moving capital to x[i], the cost to conquer all remaining kingdoms is:
            // For j = i+1 to n-1: b * (x[j] - x[i])
            // So, total cost = cost so far + a*(x[i]-prev) + b*sum_{j=i+1}^{n-1}(x[j]-x[i])
            long long move_cost = cost + a * (x[i] - prev);
            if (i < n - 1) {
                // sum of (x[j] - x[i]) for j = i+1 to n-1 = (x[n-1] - x[i]) + (x[n-2] - x[i]) + ... + (x[i+1] - x[i])
                // = (sum_{j=i+1}^{n-1} x[j]) - (n-1-i)*x[i]
                long long sum_remain = 0;
                for (int j = i + 1; j < n; ++j) sum_remain += x[j];
                move_cost += b * (sum_remain - (n - 1 - i) * x[i]);
            }
            res = min(res, move_cost);
            prev = x[i];
        }

        cout << res << '\n';
    }
    return 0;
}
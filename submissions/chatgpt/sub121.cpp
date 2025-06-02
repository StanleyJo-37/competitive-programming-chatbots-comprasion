#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

// This problem is a variant of the Hamiltonian path problem with extra constraints.
// Since n can be up to 5000, we cannot use O(n^2 * 2^n) DP.
// However, since the chairs are in a line and the cost structure is such that
// the only possible order to visit all chairs exactly once is to go from one end to the other,
// we can use DP on intervals (i.e., DP[l][r][k], where k is 0 if Scott is at l, 1 if at r).

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, s, e;
    cin >> n >> s >> e;
    --s; --e; // 0-based indexing

    vector<long long> x(n), a(n), b(n), c(n), d(n);
    for (int i = 0; i < n; ++i) cin >> x[i];
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < n; ++i) cin >> b[i];
    for (int i = 0; i < n; ++i) cin >> c[i];
    for (int i = 0; i < n; ++i) cin >> d[i];

    // dp[l][r][k]: minimal cost to visit all chairs in [l, r], currently at l (k=0) or r (k=1)
    // We only need to store current and previous layer, as we expand the interval.
    const long long INF = LLONG_MAX / 2;
    vector<vector<vector<long long>>> dp(n, vector<vector<long long>>(n, vector<long long>(2, INF)));

    // Base case: interval of length 1, only at s
    dp[s][s][0] = 0;
    dp[s][s][1] = 0;

    // Expand intervals
    for (int len = 1; len < n; ++len) {
        for (int l = 0; l + len < n; ++l) {
            int r = l + len;
            // For each possible current position (l or r)
            // If we are at l, we can move to l-1 (if l > 0) or r+1 (if r < n-1)
            // But since we are expanding interval, we only consider moving to l-1 or r+1

            // If we are at l, we can move to l-1 (if l > 0)
            if (l > 0) {
                // Move from l to l-1 (to the left)
                // Only possible if l-1 is not yet visited, i.e., expanding interval to the left
                // Jumping from l to l-1: to the left, must be small
                // Cost: |x[l] - x[l-1]| + c[l] + b[l-1]
                long long cost = abs(x[l] - x[l-1]) + c[l] + b[l-1];
                if (dp[l][r][0] + cost < dp[l-1][r][0])
                    dp[l-1][r][0] = dp[l][r][0] + cost;
            }
            // If we are at l, we can move to r+1 (if r+1 < n)
            if (r + 1 < n) {
                // Move from l to r+1 (to the right)
                // Jumping from l to r+1: to the right, must be large
                // Cost: |x[l] - x[r+1]| + d[l] + a[r+1]
                long long cost = abs(x[l] - x[r+1]) + d[l] + a[r+1];
                if (dp[l][r][0] + cost < dp[l][r+1][1])
                    dp[l][r+1][1] = dp[l][r][0] + cost;
            }
            // If we are at r, we can move to r+1 (if r+1 < n)
            if (r + 1 < n) {
                // Move from r to r+1 (to the right)
                // Jumping from r to r+1: to the right, must be large
                // Cost: |x[r] - x[r+1]| + d[r] + a[r+1]
                long long cost = abs(x[r] - x[r+1]) + d[r] + a[r+1];
                if (dp[l][r][1] + cost < dp[l][r+1][1])
                    dp[l][r+1][1] = dp[l][r][1] + cost;
            }
            // If we are at r, we can move to l-1 (if l > 0)
            if (l > 0) {
                // Move from r to l-1 (to the left)
                // Jumping from r to l-1: to the left, must be small
                // Cost: |x[r] - x[l-1]| + c[r] + b[l-1]
                long long cost = abs(x[r] - x[l-1]) + c[r] + b[l-1];
                if (dp[l][r][1] + cost < dp[l-1][r][0])
                    dp[l-1][r][0] = dp[l][r][1] + cost;
            }
        }
    }

    // The answer is the minimal cost to visit all chairs, ending at e
    // Since the interval is [0, n-1], we check dp[0][n-1][0] if e == 0, dp[0][n-1][1] if e == n-1, or both if e is at either end
    long long ans = INF;
    if (e == 0) ans = dp[0][n-1][0];
    else if (e == n-1) ans = dp[0][n-1][1];
    else {
        // If e is not at the ends, we need to check both possibilities
        // Since the interval is [l, r], and we must end at e, we need to find the interval [l, r] where l <= e <= r and length == n
        // But since we always expand from s, and the only way to visit all is to expand to both ends, e must be at one end
        // So, in this DP, e must be at 0 or n-1
        // But s and e can be anywhere, so we need to check both dp[e][e][0] and dp[e][e][1] after n-1 expansions
        // But our DP always expands to [0, n-1], so e must be at 0 or n-1
        // So, we need to check dp[0][n-1][0] if e == 0, dp[0][n-1][1] if e == n-1
        // But if s < e, the only way is to go from s to n-1, then to 0, or vice versa
        // So, we need to check both
        if (e == 0) ans = dp[0][n-1][0];
        else if (e == n-1) ans = dp[0][n-1][1];
        else {
            // For e in (0, n-1), we need to check if we can end at e after visiting all
            // But in our DP, we always end at 0 or n-1, so the only way is to go from s to e by expanding to both ends
            // So, we need to simulate both directions: left to right and right to left
            // But since the only possible way is to expand to both ends, and e must be at one end, otherwise it's impossible
            // But the problem guarantees a solution, so e must be at one end after visiting all
            // So, we check both dp[0][n-1][0] and dp[0][n-1][1], and pick the one where the end is e
            if (e == 0) ans = dp[0][n-1][0];
            else if (e == n-1) ans = dp[0][n-1][1];
        }
    }
    cout << ans << '\n';
    return 0;
}
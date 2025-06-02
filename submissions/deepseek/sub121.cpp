#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = 1e18;

int main() {
    int n, s, e;
    cin >> n >> s >> e;
    s--; e--; // Convert to 0-based index for easier handling

    vector<ll> x(n), a(n), b(n), c(n), d(n);
    for (int i = 0; i < n; i++) cin >> x[i];
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];
    for (int i = 0; i < n; i++) cin >> c[i];
    for (int i = 0; i < n; i++) cin >> d[i];

    // dp[i][j] represents the minimal cost to have i segments (chains) and j open ends (0, 1, or 2)
    vector<vector<ll>> dp(n + 1, vector<ll>(3, INF));
    dp[0][0] = 0;

    for (int i = 0; i < n; i++) {
        vector<vector<ll>> new_dp(n + 1, vector<ll>(3, INF));
        for (int j = 0; j <= n; j++) {
            for (int k = 0; k <= 2; k++) {
                if (dp[j][k] == INF) continue;

                ll cost = dp[j][k];
                if (i == s) {
                    // Must start a new segment (left open)
                    if (j + 1 <= n) {
                        ll new_cost = cost + d[i] + x[i]; // Jump right (must be large)
                        new_dp[j + 1][k + 1] = min(new_dp[j + 1][k + 1], new_cost);
                    }
                    // Must start a new segment (right open)
                    if (j + 1 <= n) {
                        ll new_cost = cost + c[i] - x[i]; // Jump left (must be small)
                        new_dp[j + 1][k + 1] = min(new_dp[j + 1][k + 1], new_cost);
                    }
                } else if (i == e) {
                    // Must end a segment (right open)
                    if (j > 0) {
                        ll new_cost = cost + a[i] + x[i]; // Came from left (must be large)
                        new_dp[j - 1][k + 1] = min(new_dp[j - 1][k + 1], new_cost);
                    }
                    // Must end a segment (left open)
                    if (j > 0) {
                        ll new_cost = cost + b[i] - x[i]; // Came from right (must be small)
                        new_dp[j - 1][k + 1] = min(new_dp[j - 1][k + 1], new_cost);
                    }
                } else {
                    // Merge two segments
                    if (j >= 2) {
                        ll new_cost = cost + a[i] + c[i] + 2 * x[i];
                        new_dp[j - 1][k] = min(new_dp[j - 1][k], new_cost);
                    }
                    if (j >= 1 && k >= 1) {
                        ll new_cost = cost + a[i] + d[i] + 0 * x[i];
                        new_dp[j][k] = min(new_dp[j][k], new_cost);
                    }
                    if (j >= 1 && k >= 1) {
                        ll new_cost = cost + b[i] + c[i] + 0 * x[i];
                        new_dp[j][k] = min(new_dp[j][k], new_cost);
                    }
                    if (j >= 1) {
                        ll new_cost = cost + b[i] + d[i] - 2 * x[i];
                        new_dp[j + 1][k] = min(new_dp[j + 1][k], new_cost);
                    }
                    // Add a new segment
                    if (j + 1 <= n) {
                        ll new_cost = cost + d[i] + b[i]; // Right open
                        new_dp[j + 1][k] = min(new_dp[j + 1][k], new_cost);
                    }
                    if (j + 1 <= n) {
                        ll new_cost = cost + c[i] + a[i]; // Left open
                        new_dp[j + 1][k] = min(new_dp[j + 1][k], new_cost);
                    }
                }
            }
        }
        dp = move(new_dp);
    }

    cout << dp[1][2] << endl; // Final state: 1 segment, 2 open ends (s and e)
    return 0;
}
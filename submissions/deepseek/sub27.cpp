#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

int main() {
    int n, l, r;
    cin >> n >> l >> r;

    // Calculate the count of numbers ≡ 0, 1, 2 mod 3 in [l, r]
    long long cnt0 = r / 3 - (l - 1) / 3;
    long long cnt1 = (r + 2) / 3 - (l + 1) / 3;
    long long cnt2 = (r + 1) / 3 - l / 3;

    // DP[i][j] represents the number of arrays of length i with sum ≡ j mod 3
    vector<vector<long long>> dp(n + 1, vector<long long>(3, 0));
    dp[0][0] = 1; // Base case: empty array has sum 0 ≡ 0 mod 3

    for (int i = 1; i <= n; ++i) {
        // For each possible remainder j (0, 1, 2) in the current step
        for (int j = 0; j < 3; ++j) {
            // The new remainder (j + k) mod 3 can be formed by adding a number ≡ k mod 3
            // So, we sum over all possible k (0, 1, 2)
            dp[i][j] = (dp[i][j] + dp[i-1][j] * cnt0) % MOD; // k=0
            dp[i][j] = (dp[i][j] + dp[i-1][(j + 2) % 3] * cnt1) % MOD; // k=1 (since (j + 1) mod 3)
            dp[i][j] = (dp[i][j] + dp[i-1][(j + 1) % 3] * cnt2) % MOD; // k=2 (since (j + 2) mod 3)
        }
    }

    cout << dp[n][0] << endl;
    return 0;
}
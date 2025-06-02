#include <bits/stdc++.h>
using namespace std;
const int MOD = 1000000007;

// Function to count the number of square subsequences in a string
int countSquareSubsequences(const string &s) {
    int n = s.size();
    int res = 0;

    // Iterate over all possible split points to divide the subsequence into two equal parts
    for (int split = 1; split < n; ++split) {
        // dp[i][j] represents the number of common subsequences between s[0..i-1] and s[split..j-1]
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

        for (int i = 1; i <= split; ++i) {
            for (int j = 1; j <= n - split; ++j) {
                if (s[i - 1] == s[split + j - 1]) {
                    // If characters match, add 1 (new subsequence of length 1) plus all previous matches
                    dp[i][j] = (dp[i - 1][j - 1] + 1) % MOD;
                }
                // Sum of dp[i-1][j] and dp[i][j-1] minus dp[i-1][j-1] to avoid double counting
                dp[i][j] = (dp[i][j] + (dp[i - 1][j] + dp[i][j - 1] - dp[i - 1][j - 1]) % MOD + MOD) % MOD;
            }
        }
        res = (res + dp[split][n - split]) % MOD;
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        string s;
        cin >> s;
        cout << countSquareSubsequences(s) << '\n';
    }
    return 0;
}
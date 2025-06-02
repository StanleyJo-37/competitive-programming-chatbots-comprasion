#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int MOD = 1000000007;

int main() {
    // Optimize C++ standard streams for faster input/output.
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T; // Number of test cases
    cin >> T;
    while (T--) {
        string S; // Input string
        cin >> S;
        int n = S.length();

        vector<vector<long long>> dp(n + 1, vector<long long>(n + 1, 0));

        long long totalSquareSubsequences = 0;

        for (int i = 1; i <= n; ++i) {
            for (int j = n - 1; j >= i; --j) {
                dp[i][j] = dp[i - 1][j];

                dp[i][j] = (dp[i][j] + dp[i][j + 1]) % MOD;

                dp[i][j] = (dp[i][j] - dp[i - 1][j + 1] + MOD) % MOD;

                if (S[i - 1] == S[j]) {
                    dp[i][j] = (dp[i][j] + dp[i - 1][j + 1] + 1) % MOD;
                }
                totalSquareSubsequences = (totalSquareSubsequences + dp[i][j]) % MOD;
            }
        }
        cout << totalSquareSubsequences << endl;
    }
    return 0;
}
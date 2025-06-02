#include <iostream>
#include <vector>
#include <string>
#include <cstring>
using namespace std;

const int MOD = 1000000007;

// Function to count square subsequences in string S
int countSquareSubsequences(const string& S) {
    int n = S.size();
    // dp[i][j][l]: number of ways to form two equal subsequences of length l
    // from S[0..i-1] and S[0..j-1] (i < j)
    // We only need to consider i < j to avoid double counting and ensure order
    // dp is 3D: [n+1][n+1][len+1], where len <= n/2
    // To save space, we use two layers for l and swap
    vector<vector<vector<int>>> dp(2, vector<vector<int>>(n+1, vector<int>(n+1, 0)));
    int result = 0;

    // For all possible lengths of half of the square string
    for (int len = 1; len <= n/2; ++len) {
        // Clear dp for current len
        for (int i = 0; i <= n; ++i)
            for (int j = 0; j <= n; ++j)
                dp[len%2][i][j] = 0;

        // Base case: dp[0][i][j] = 1 for all i < j (empty string)
        for (int i = 0; i < n; ++i)
            for (int j = i+1; j < n; ++j)
                dp[0][i][j] = 1;

        // DP for current len
        for (int l = 1; l <= len; ++l) {
            for (int i = 0; i < n; ++i) {
                for (int j = i+1; j < n; ++j) {
                    // If S[i] == S[j], we can take both and extend
                    if (S[i] == S[j]) {
                        if (i > 0 && j > 0)
                            dp[l%2][i][j] = dp[(l-1)%2][i-1][j-1];
                        else
                            dp[l%2][i][j] = 0;
                    } else {
                        dp[l%2][i][j] = 0;
                    }
                    // We can also skip S[i] or S[j]
                    if (i > 0)
                        dp[l%2][i][j] = (dp[l%2][i][j] + dp[l%2][i-1][j]) % MOD;
                    if (j > 0)
                        dp[l%2][i][j] = (dp[l%2][i][j] + dp[l%2][i][j-1]) % MOD;
                    if (i > 0 && j > 0)
                        dp[l%2][i][j] = (dp[l%2][i][j] - dp[l%2][i-1][j-1] + MOD) % MOD;
                }
            }
        }
        // Sum up all dp[len][i][j] for i < j
        for (int i = 0; i < n; ++i)
            for (int j = i+1; j < n; ++j)
                result = (result + dp[len%2][i][j]) % MOD;
    }
    return result;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        string S;
        cin >> S;
        cout << countSquareSubsequences(S) << endl;
    }
    return 0;
}
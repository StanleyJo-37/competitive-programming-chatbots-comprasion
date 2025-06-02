#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    // dp[i][j] represents the maximum total length when the last note of the first melody is a[i] and the last note of the second melody is a[j]
    // To optimize space, we can use a 2D array of size n x n, but since n can be 5000, we need to manage it carefully.
    vector<vector<int>> dp(n, vector<int>(n, 0));

    // Initialize dp[i][j] where i and j are the first two notes of the subsequences
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j) continue; // Subsequences must be non-intersecting
            dp[i][j] = 2; // At least two notes, one in each subsequence
        }
    }

    int max_len = 0;
    // We will iterate over all possible pairs (i, j) where i < j or j < i to fill the dp table
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j) continue;
            // Try to extend the first subsequence ending at i or the second ending at j
            for (int k = max(i, j) + 1; k < n; ++k) {
                // Check if a[k] can extend the first subsequence ending at a[i]
                if (abs(a[k] - a[i]) == 1 || (a[k] % 7 == a[i] % 7)) {
                    if (dp[k][j] < dp[i][j] + 1) {
                        dp[k][j] = dp[i][j] + 1;
                        if (dp[k][j] > max_len) {
                            max_len = dp[k][j];
                        }
                    }
                }
                // Check if a[k] can extend the second subsequence ending at a[j]
                if (abs(a[k] - a[j]) == 1 || (a[k] % 7 == a[j] % 7)) {
                    if (dp[i][k] < dp[i][j] + 1) {
                        dp[i][k] = dp[i][j] + 1;
                        if (dp[i][k] > max_len) {
                            max_len = dp[i][k];
                        }
                    }
                }
            }
        }
    }

    // The answer is the maximum value in the dp table
    cout << max_len << endl;

    return 0;
}
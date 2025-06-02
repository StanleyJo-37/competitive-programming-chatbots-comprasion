#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Function to solve the problem for a single test case
int solve() {
    int n;
    cin >> n;
    vector<pair<int, int>> intervals(n);
    for (int i = 0; i < n; ++i) {
        cin >> intervals[i].first >> intervals[i].second;
    }
    
    // Sort intervals by their end points in ascending order
    sort(intervals.begin(), intervals.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
        return a.second < b.second;
    });
    
    // dp[i][j] represents the maximum subset size where the last two intervals are i and j
    // To optimize space, we use a 2D array of size n x n, but only track the last two intervals
    vector<vector<int>> dp(n, vector<int>(n, 0));
    int max_size = 0;
    
    // Initialize dp[i][j] for all i < j
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            // Check if intervals i and j overlap
            if (intervals[i].second >= intervals[j].first) {
                // If they overlap, we can only take 2 intervals (i and j)
                dp[i][j] = 2;
            } else {
                // If they don't overlap, we can take 2 intervals (i and j)
                dp[i][j] = 2;
                // Try to find a previous interval k that doesn't overlap with j
                for (int k = 0; k < i; ++k) {
                    if (intervals[k].second < intervals[j].first) {
                        dp[i][j] = max(dp[i][j], dp[k][i] + 1);
                    }
                }
            }
            max_size = max(max_size, dp[i][j]);
        }
    }
    
    // The answer is the maximum value in dp, but at least 2 if n >= 2
    return max(max_size, n >= 2 ? 2 : n);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int S;
    cin >> S;
    while (S--) {
        cout << solve() << '\n';
    }
    
    return 0;
}
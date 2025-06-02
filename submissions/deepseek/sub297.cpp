#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<int> start(m + 2, 0), end(m + 2, 0);

    // Read segments and mark their start and end points
    for (int i = 0; i < n; ++i) {
        int l, r;
        cin >> l >> r;
        start[l]++;
        end[r]++;
    }

    // Compute the number of segments covering each point
    vector<int> cnt(m + 1, 0);
    int active = 0;
    for (int i = 1; i <= m; ++i) {
        active += start[i];
        cnt[i] = active;
        active -= end[i];
    }

    // Compute the longest non-decreasing subsequence (LNDS) for cnt array
    // This helps in finding the maximum set of points where Sasha can't be sure
    vector<int> dp(m + 1, 0);
    vector<int> lis; // To store the LIS sequence
    for (int i = 1; i <= m; ++i) {
        auto it = upper_bound(lis.begin(), lis.end(), cnt[i]);
        if (it == lis.end()) {
            lis.push_back(cnt[i]);
        } else {
            *it = cnt[i];
        }
        dp[i] = lis.size();
    }

    // Similarly compute the longest non-increasing subsequence (LNIS) from the right
    vector<int> dp_rev(m + 2, 0);
    vector<int> lds;
    for (int i = m; i >= 1; --i) {
        auto it = upper_bound(lds.begin(), lds.end(), cnt[i], greater<int>());
        if (it == lds.end()) {
            lds.push_back(cnt[i]);
        } else {
            *it = cnt[i];
        }
        dp_rev[i] = lds.size();
    }

    // The answer is the maximum (dp[i] + dp_rev[i+1]) for all i from 1 to m-1
    int max_len = 0;
    for (int i = 1; i <= m; ++i) {
        if (i < m) {
            max_len = max(max_len, dp[i] + dp_rev[i + 1]);
        } else {
            max_len = max(max_len, dp[i]);
        }
    }

    cout << max_len << '\n';
    return 0;
}
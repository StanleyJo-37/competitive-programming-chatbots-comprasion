#include <bits/stdc++.h>
using namespace std;

void solve() {
    int t;
    cin >> t;
    while (t--) {
        int n, p, k;
        cin >> n >> p >> k;
        string a;
        cin >> a;
        int x, y;
        cin >> x >> y;

        // dp[i] will store the minimal cost to fix positions i, i+k, i+2k, ... starting from i
        vector<int> dp(n + 1, 0);
        for (int i = n; i >= 1; --i) {
            if (i + k > n) {
                dp[i] = (a[i-1] == '0') ? x : 0;
            } else {
                dp[i] = dp[i + k] + ((a[i-1] == '0') ? x : 0);
            }
        }

        int min_time = INT_MAX;
        // We can remove the first 's' cells (0 <= s <= n - p)
        for (int s = 0; s <= n - p; ++s) {
            int current_p = p + s;
            int cost = s * y + dp[current_p];
            if (cost < min_time) {
                min_time = cost;
            }
        }
        cout << min_time << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
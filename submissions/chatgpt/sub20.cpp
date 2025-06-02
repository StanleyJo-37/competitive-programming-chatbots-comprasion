#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n, p, k;
        cin >> n >> p >> k;
        string a;
        cin >> a;
        int x, y;
        cin >> x >> y;

        // dp[i]: number of platforms to add if we start at cell i (1-based) and go every k-th cell
        vector<int> dp(n + 2, 0); // n+2 to avoid out-of-bounds

        // Fill dp from the end to the start
        for (int i = n; i >= 1; --i) {
            // If current cell has no platform, need to add one
            int add = (a[i - 1] == '0') ? 1 : 0;
            // If i + k is within bounds, add its dp value
            if (i + k <= n)
                dp[i] = add + dp[i + k];
            else
                dp[i] = add;
        }

        int ans = 1e9 + 7; // Large initial value

        // Try all possible numbers of removals (from 0 up to n-p)
        // For each, the starting cell is p + remove
        // The cost is remove * y + dp[p + remove] * x
        for (int remove = 0; p + remove <= n; ++remove) {
            int start = p + remove;
            int cost = remove * y + dp[start] * x;
            if (cost < ans)
                ans = cost;
        }

        cout << ans << '\n';
    }
    return 0;
}
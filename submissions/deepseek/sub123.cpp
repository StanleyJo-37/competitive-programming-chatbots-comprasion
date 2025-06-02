#include <bits/stdc++.h>
using namespace std;

void solve() {
    int T;
    cin >> T;
    while (T--) {
        int N, Q;
        cin >> N >> Q;
        vector<int> P(N);
        for (int i = 0; i < N; ++i) {
            cin >> P[i];
        }
        sort(P.begin(), P.end()); // Sort enemies to pick the smallest first
        
        // Precompute prefix sums and a vector to store the minimal required X to kill first i enemies
        vector<long long> prefix(N + 1, 0);
        for (int i = 0; i < N; ++i) {
            prefix[i + 1] = prefix[i] + P[i];
        }
        
        vector<long long> minX(N + 1, 0);
        minX[0] = 0;
        for (int i = 1; i <= N; ++i) {
            // The minimal X to kill i enemies is the minimal X such that X > P[i-1] and X + sum_{k=0}^{i-2} (X_k - P_k) > P[i-1]
            // Simplified, it's the minimal X where X > P[i-1] - (sum of previous (X_k - P_k))
            // But after analysis, it's better to compute the minimal X required to kill i enemies as follows:
            // The minimal X is the maximum between P[i-1] + 1 and ceil((prefix[i] + 1) / 2)
            // However, a better approach is to realize that the minimal X to kill i enemies is the minimal X such that X > (prefix[i] + 1) / 2
            minX[i] = max((long long)P[i - 1] + 1, (prefix[i] + 1) / 2);
        }
        
        // Since minX is non-decreasing, we can binary search for the maximum i where minX[i] <= X
        for (int q = 0; q < Q; ++q) {
            int X;
            cin >> X;
            // Find the largest i such that minX[i] <= X
            int low = 0, high = N;
            int ans = 0;
            while (low <= high) {
                int mid = (low + high) / 2;
                if (mid <= N && minX[mid] <= X) {
                    ans = mid;
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            }
            cout << ans << "\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
#include <bits/stdc++.h>
using namespace std;

void solve() {
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        vector<int> h(n);
        for (int i = 0; i < n; ++i) {
            cin >> h[i];
        }
        
        bool possible = true;
        // The first and last sections must be on the ground.
        // For the sections in between, we need to ensure that the height difference
        // between consecutive sections is at most k-1 (since each section is height k).
        // The idea is to maintain a range [low, high] for each section's possible height.
        // The range is updated based on the previous section's range.
        int low = h[0], high = h[0];
        for (int i = 1; i < n && possible; ++i) {
            // The current section's low is max(h[i], previous low - (k - 1))
            // The current section's high is min(h[i] + k - 1, previous high + k - 1)
            low = max(h[i], low - (k - 1));
            high = min(h[i] + k - 1, high + k - 1);
            if (low > high) {
                possible = false;
            }
        }
        // The last section must be exactly on the ground.
        if (h.back() < low || h.back() > high) {
            possible = false;
        }
        cout << (possible ? "YES" : "NO") << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
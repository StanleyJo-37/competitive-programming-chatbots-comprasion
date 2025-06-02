#include <bits/stdc++.h>
using namespace std;

void solve() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }
        
        // The minimal coverage is determined by the maximum distance between the leftmost and rightmost points.
        // The leftmost point can be either (sum of left moves) or (sum of right moves), but the minimal coverage
        // is achieved when the leftmost and rightmost points are as close as possible.
        // The minimal coverage is the maximum between:
        // 1. The sum of all segment lengths (if all segments are placed in the same direction)
        // 2. The maximum between the leftmost and rightmost points when segments are placed optimally.
        // However, the optimal placement alternates directions to minimize the spread.
        
        // The minimal coverage is the maximum between the sum of all segments (if all same direction)
        // or twice the maximum segment length (if one segment is larger than the sum of all others).
        // Because if one segment is larger than the sum of others, the minimal coverage is 2*max_seg - sum_others.
        // Otherwise, the minimal coverage is the sum of all segments.
        
        int sum = accumulate(a.begin(), a.end(), 0);
        int max_seg = *max_element(a.begin(), a.end());
        
        if (max_seg > sum - max_seg) {
            cout << 2 * max_seg - (sum - max_seg) << '\n';
        } else {
            cout << sum << '\n';
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
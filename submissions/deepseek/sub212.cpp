#include <bits/stdc++.h>
using namespace std;

void solve() {
    int N, M;
    cin >> N >> M;
    vector<pair<int, int>> intervals(N);
    for (int i = 0; i < N; ++i) {
        cin >> intervals[i].first >> intervals[i].second;
    }
    
    // Sort intervals by start time since they are non-overlapping and disjoint
    sort(intervals.begin(), intervals.end());
    
    vector<int> starts(N);
    for (int i = 0; i < N; ++i) {
        starts[i] = intervals[i].first;
    }
    
    while (M--) {
        int P;
        cin >> P;
        
        // Find the first interval where start > P using upper_bound
        auto it = upper_bound(starts.begin(), starts.end(), P);
        
        if (it == starts.begin()) {
            // All intervals start after P, so the first interval is the answer
            cout << (intervals[0].first - P) << '\n';
        } else if (it == starts.end()) {
            // P is after all intervals
            if (P < intervals.back().second) {
                // P is in the last interval
                cout << 0 << '\n';
            } else {
                // P is after the last interval ends
                cout << -1 << '\n';
            }
        } else {
            int idx = it - starts.begin();
            if (P < intervals[idx - 1].second) {
                // P is in the (idx-1)th interval
                cout << 0 << '\n';
            } else {
                // P is between (idx-1)th and idx-th interval
                cout << (intervals[idx].first - P) << '\n';
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    
    return 0;
}
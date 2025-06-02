#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<long long> k(n), h(n);
    for (int i = 0; i < n; ++i) cin >> k[i];
    for (int i = 0; i < n; ++i) cin >> h[i];
    
    // We'll process monsters in reverse to determine the required segments
    vector<pair<long long, long long>> segments;
    for (int i = n - 1; i >= 0; --i) {
        long long start = k[i] - h[i] + 1;
        long long end = k[i];
        // Merge overlapping or adjacent segments
        if (segments.empty()) {
            segments.emplace_back(start, end);
        } else {
            auto &last = segments.back();
            if (start < last.first) {
                // Need to merge, new segment starts before current last segment
                last.first = min(last.first, start);
                last.second = max(last.second, end);
            } else if (start <= last.second) {
                // Overlapping or adjacent, merge
                last.second = max(last.second, end);
            } else {
                segments.emplace_back(start, end);
            }
        }
    }
    reverse(segments.begin(), segments.end());
    
    long long total = 0;
    for (auto &seg : segments) {
        long long len = seg.second - seg.first + 1;
        total += len * (len + 1) / 2;
    }
    cout << total << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
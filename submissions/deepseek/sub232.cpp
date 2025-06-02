#include <bits/stdc++.h>
using namespace std;

void solve() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<long long> a(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }
        
        long long sum = 0;
        int i = 0;
        while (i < n) {
            int current_sign = a[i] > 0 ? 1 : -1;
            long long max_in_segment = a[i];
            // Iterate through the current segment of same sign elements
            while (i < n && (a[i] > 0 ? 1 : -1) == current_sign) {
                max_in_segment = max(max_in_segment, a[i]);
                ++i;
            }
            sum += max_in_segment;
        }
        cout << sum << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
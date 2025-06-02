#include <bits/stdc++.h>
using namespace std;

void solve() {
    int t;
    cin >> t;
    while (t--) {
        int n, s;
        cin >> n >> s;
        vector<int> a(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }
        
        int total = accumulate(a.begin(), a.end(), 0);
        if (total < s) {
            cout << -1 << '\n';
            continue;
        }
        if (total == s) {
            cout << 0 << '\n';
            continue;
        }
        
        // We need to find the smallest window where sum is (total - s)
        int target = total - s;
        int left = 0, sum = 0, max_len = 0;
        for (int right = 0; right < n; ++right) {
            sum += a[right];
            while (sum > target) {
                sum -= a[left];
                left++;
            }
            if (sum == target) {
                max_len = max(max_len, right - left + 1);
            }
        }
        cout << (n - max_len) << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
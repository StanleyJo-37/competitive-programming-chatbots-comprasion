#include <bits/stdc++.h>
using namespace std;

void solve() {
    int t;
    cin >> t;
    while (t--) {
        int n, q;
        cin >> n >> q;
        vector<int> a(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }
        // The optimal solution is to take all positive contributions (odd positions in sorted descending order)
        // and subtract all negative contributions (even positions in sorted descending order).
        // So, sort the array in descending order and sum a[0] - a[1] + a[2] - a[3] + ... 
        sort(a.begin(), a.end(), greater<int>());
        long long res = 0;
        for (int i = 0; i < n; ++i) {
            if (i % 2 == 0) {
                res += a[i];
            } else {
                res -= a[i];
            }
        }
        cout << res << '\n';
        // Since q=0, no need to process swaps
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
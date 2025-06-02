#include <bits/stdc++.h>
using namespace std;

void solve() {
    int t;
    cin >> t;
    while (t--) {
        int n, q;
        cin >> n >> q;
        string s;
        cin >> s;
        vector<int> prefix(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            int val = (s[i - 1] == '+') ? 1 : -1;
            if (i % 2 == 0) val *= -1;
            prefix[i] = prefix[i - 1] + val;
        }
        while (q--) {
            int l, r;
            cin >> l >> r;
            int sum = prefix[r] - prefix[l - 1];
            if (sum == 0) {
                cout << "0\n";
            } else if ((r - l + 1) % 2 == 1) {
                cout << "1\n";
            } else {
                cout << "2\n";
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
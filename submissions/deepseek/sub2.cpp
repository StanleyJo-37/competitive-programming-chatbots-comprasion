#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    
    int res = 0;
    for (int i = 0; i < n; ) {
        if (s[i] == '1') {
            res += a[i];
            ++i;
        } else {
            // Check if the next position has a '1' and if moving it back is beneficial
            if (i + 1 < n && s[i+1] == '1') {
                int sum = 0;
                int min_val = a[i];
                int j = i + 1;
                // Collect all consecutive '1's after the '0'
                while (j < n && s[j] == '1') {
                    sum += a[j];
                    min_val = min(min_val, a[j]);
                    ++j;
                }
                // Compare the sum of all '1's vs sum + a[i] - min_val (moving the first '1' back)
                if (a[i] > min_val) {
                    res += sum + a[i] - min_val;
                } else {
                    res += sum;
                }
                i = j;
            } else {
                ++i;
            }
        }
    }
    cout << res << '\n';
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
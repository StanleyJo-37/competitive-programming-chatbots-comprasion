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
        // The optimal approach is to paint the largest element as RED and the next k smallest as BLUE,
        // where k is as small as possible but > (Count(RED) = 1). So k = 2.
        // Thus, we need Sum(RED) = largest element > Sum(BLUE) = sum of two smallest elements.
        // Also, Count(RED) = 1 < Count(BLUE) = 2.
        if (n < 3) {
            cout << "NO\n";
            continue;
        }
        sort(a.begin(), a.end());
        long long sumRed = a.back();
        long long sumBlue = a[0] + a[1];
        if (sumRed > sumBlue) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
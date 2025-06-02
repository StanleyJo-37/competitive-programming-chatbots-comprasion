#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    
    // The key observation is that the minimal maximum XOR between adjacent elements
    // is 1 when n is a power of 2. Otherwise, it's the next higher power of 2 minus 1.
    // However, a better approach is to arrange numbers such that all adjacent XORs are
    // as small as possible. One such pattern is the Gray code sequence, but it's not
    // straightforward to implement for arbitrary n. Instead, we can use the following approach:
    // For numbers from 0 to m-1 (where m is the largest power of 2 <= n), arrange them
    // in a sequence where each adjacent pair has XOR of 1 (like 0,1,3,2, etc.), and then
    // append the remaining numbers in any order (since their highest bit is already set).
    
    int m = 1;
    while (m * 2 <= n - 1) {
        m *= 2;
    }
    
    // The first part is from m-1 down to 0
    for (int i = m - 1; i >= 0; --i) {
        cout << i << ' ';
    }
    // The second part is from m to n-1
    for (int i = m; i < n; ++i) {
        cout << i << ' ';
    }
    cout << '\n';
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
#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    
    vector<int> res(n, 0);
    int current_cream = 0; // Tracks the active cream affecting layers
    
    // Process from top to bottom to determine which layers are drenched
    for (int i = n - 1; i >= 0; --i) {
        current_cream = max(current_cream, a[i]);
        if (current_cream > 0) {
            res[i] = 1;
            current_cream--;
        }
    }
    
    for (int i = 0; i < n; ++i) {
        cout << res[i] << " ";
    }
    cout << "\n";
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
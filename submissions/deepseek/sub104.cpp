#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    
    vector<int> res;
    int current_or = 0;
    
    for (int i = 0; i < n; ++i) {
        // Find the element that maximizes the OR with current_or
        int best_idx = -1;
        int max_or = current_or;
        for (int j = 0; j < a.size(); ++j) {
            if ((current_or | a[j]) > max_or) {
                max_or = current_or | a[j];
                best_idx = j;
            }
        }
        if (best_idx == -1) {
            // No element increases the OR, add remaining elements in any order
            for (int num : a) {
                res.push_back(num);
            }
            break;
        }
        res.push_back(a[best_idx]);
        current_or |= a[best_idx];
        a.erase(a.begin() + best_idx);
    }
    
    for (int num : res) {
        cout << num << " ";
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
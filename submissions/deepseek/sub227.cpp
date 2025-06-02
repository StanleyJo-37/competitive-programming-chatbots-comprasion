#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> s(n);
    for (int i = 0; i < n; ++i) {
        cin >> s[i];
    }
    
    // Check if all elements are the same. If yes, any derangement works.
    bool allSame = true;
    for (int i = 1; i < n; ++i) {
        if (s[i] != s[0]) {
            allSame = false;
            break;
        }
    }
    if (allSame) {
        // Output a cyclic shift (e.g., 2 3 ... n 1)
        for (int i = 1; i <= n; ++i) {
            cout << (i % n) + 1 << " ";
        }
        cout << "\n";
        return;
    }
    
    // For non-uniform sizes, we need to ensure s[p_i] >= s_i and p_i != i.
    // We can use a two-pointer approach to find the smallest j > i where s[j] >= s[i].
    vector<int> p(n);
    int j = 1; // j is the next candidate to assign to i
    bool possible = true;
    for (int i = 0; i < n; ++i) {
        // Find the first j != i where s[j] >= s[i]
        while (j < n && (j == i || s[j] < s[i])) {
            ++j;
        }
        if (j >= n) {
            // No valid j found for i
            possible = false;
            break;
        }
        p[i] = j + 1; // 1-based index
        ++j;
    }
    
    if (!possible) {
        cout << "-1\n";
    } else {
        // Verify that no p[i] == i+1 (1-based)
        bool valid = true;
        for (int i = 0; i < n; ++i) {
            if (p[i] == i + 1) {
                valid = false;
                break;
            }
        }
        if (!valid) {
            cout << "-1\n";
        } else {
            for (int num : p) {
                cout << num << " ";
            }
            cout << "\n";
        }
    }
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
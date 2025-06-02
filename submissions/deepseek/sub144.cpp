#include <bits/stdc++.h>
using namespace std;

void solve() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }
        
        // The key observation is that if the total XOR of the array is zero,
        // then it's always possible to make all elements equal (to zero).
        // Otherwise, we need to partition the array into at least two segments
        // where each segment's XOR equals the total XOR.
        int total_xor = 0;
        for (int num : a) {
            total_xor ^= num;
        }
        
        if (total_xor == 0) {
            cout << "YES\n";
            continue;
        }
        
        // Now, check if we can split the array into at least two parts with XOR equal to total_xor.
        int current_xor = 0;
        int count = 0;
        for (int i = 0; i < n; ++i) {
            current_xor ^= a[i];
            if (current_xor == total_xor) {
                count++;
                current_xor = 0; // Reset for next segment
            }
        }
        
        // If we have at least two segments and the remaining XOR is zero, it's possible.
        if (count >= 2 && current_xor == 0) {
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
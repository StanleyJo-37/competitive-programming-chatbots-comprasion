#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    
    // Calculate original inversions (0s after 1s)
    long long original_inv = 0;
    int count_1 = 0;
    for (int i = 0; i < n; ++i) {
        if (a[i] == 1) {
            count_1++;
        } else {
            original_inv += count_1;
        }
    }
    
    // Calculate best possible inversion count after flipping a single 0 to 1
    long long max_inv = original_inv;
    int count_0 = 0;
    for (int i = n - 1; i >= 0; --i) {
        if (a[i] == 0) {
            count_0++;
        } else {
            // Flipping this 1 to 0 would gain (count_0) and lose (count_1 - 1)
            // Net change: (count_0 - (count_1 - 1))
            long long new_inv = original_inv + (count_0 - (count_1 - 1));
            max_inv = max(max_inv, new_inv);
            count_1--;
        }
    }
    
    // Reset counts for flipping 0 to 1
    count_1 = 0;
    for (int i = 0; i < n; ++i) {
        if (a[i] == 1) {
            count_1++;
        } else {
            // Flipping this 0 to 1 would lose (count_1) and gain (number of 0s after it)
            // Net change: ((n - 1 - i - (count_0 - 1)) - count_1)
            // count_0 is total 0s, (count_0 - 1) is remaining 0s after this one
            long long new_inv = original_inv - count_1 + ((n - 1 - i) - (count_0 - 1));
            max_inv = max(max_inv, new_inv);
            count_0--;
        }
    }
    
    cout << max_inv << '\n';
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
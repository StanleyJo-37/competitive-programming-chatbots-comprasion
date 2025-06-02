#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int l, r;
        cin >> l >> r;
        int n = r - l + 1;
        vector<int> a(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }

        int x = 0;
        // Check each bit from 0 to 16 (since r < 2^17)
        for (int bit = 0; bit < 17; ++bit) {
            int expected = 0;
            // Count the number of set bits in the original array [l..r] at position 'bit'
            for (int num = l; num <= r; ++num) {
                expected += (num >> bit) & 1;
            }
            int actual = 0;
            // Count the number of set bits in the given array at position 'bit'
            for (int num : a) {
                actual += (num >> bit) & 1;
            }
            // If counts differ, this bit must be set in x
            if (expected != actual) {
                x |= (1 << bit);
            }
        }
        cout << x << '\n';
    }
    return 0;
}
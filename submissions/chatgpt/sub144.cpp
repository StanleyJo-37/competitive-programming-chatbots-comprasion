#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false); // Fast IO
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int &x : a) cin >> x;

        // Compute the total XOR of the array
        int total_xor = 0;
        for (int x : a) total_xor ^= x;

        // If total_xor is 0, we can always partition into at least 2 equal parts
        if (total_xor == 0) {
            cout << "YES\n";
            continue;
        }

        // Try to partition the array into at least 3 parts with equal XOR (total_xor)
        int curr = 0, cnt = 0;
        for (int i = 0; i < n; ++i) {
            curr ^= a[i];
            if (curr == total_xor) {
                ++cnt;
                curr = 0;
            }
        }

        // If we can partition into at least 3 parts, answer is YES
        if (cnt >= 2) cout << "YES\n";
        else cout << "NO\n";
    }
    return 0;
}
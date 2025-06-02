#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false); // Fast IO
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n, q;
        cin >> n >> q;
        string s;
        cin >> s;

        // Precompute prefix sums of the sign-variable sum
        // sign_sum[i] = sum_{j=1}^{i} (-1)^{j-1} * a_j
        // where a_j = 1 if s[j-1] == '+', -1 otherwise
        vector<int> sign_sum(n + 1, 0); // 1-based indexing

        for (int i = 1; i <= n; ++i) {
            int a = (s[i - 1] == '+') ? 1 : -1;
            // If i is odd, sign is +, else -
            if (i % 2 == 1)
                sign_sum[i] = sign_sum[i - 1] + a;
            else
                sign_sum[i] = sign_sum[i - 1] - a;
        }

        while (q--) {
            int l, r;
            cin >> l >> r;
            // Calculate the sign-variable sum for [l, r]
            int sum = sign_sum[r] - sign_sum[l - 1];

            // If sum is zero, no need to remove any rods
            if (sum == 0) {
                cout << 0 << '\n';
            } else {
                // If the length is odd, we can always make the sum zero by removing 1 rod
                // If the length is even, we need to remove 2 rods
                int len = r - l + 1;
                if (len % 2 == 1) {
                    cout << 1 << '\n';
                } else {
                    cout << 2 << '\n';
                }
            }
        }
    }
    return 0;
}
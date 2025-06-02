#include <bits/stdc++.h>
using namespace std;

// For each test case, we want to find the largest subarray where all elements
// have the same remainder modulo some m >= 2.
// Observation: For a subarray a[l..r], if all a_k mod m == x, then
// (a_k - a_l) mod m == 0 for all k in [l, r], i.e., all differences are divisible by m.
// So, for a subarray, the GCD of all differences (a_k - a_{k-1}) for k in [l+1, r] must be divisible by m.
// So, for each subarray, the GCD of consecutive differences is a candidate for m.
// We can use a sliding window with GCD to find the largest such subarray.

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<long long> a(n);
        for (int i = 0; i < n; ++i) cin >> a[i];

        // If n == 1, the answer is 1 (only one element)
        if (n == 1) {
            cout << 1 << '\n';
            continue;
        }

        // Compute the absolute differences between consecutive elements
        vector<long long> diff(n - 1);
        for (int i = 0; i < n - 1; ++i) {
            diff[i] = abs(a[i + 1] - a[i]);
        }

        // We want the longest subarray of diff where the GCD is >= 1 (since m >= 2)
        // For each position, we can use a map to keep track of all possible GCDs ending at that position
        // But we can do it more efficiently with a sliding window and two pointers

        int ans = 1; // At least one element
        int l = 0;
        long long cur_gcd = 0;
        for (int r = 0; r < n - 1; ++r) {
            // Expand the window to the right
            cur_gcd = diff[r];
            int rr = r;
            // Try to expand as much as possible to the left
            for (int ll = r; ll >= l; --ll) {
                cur_gcd = gcd(cur_gcd, diff[ll]);
                if (cur_gcd == 1) {
                    // No m >= 2 divides all differences in this window
                    break;
                }
                // The subarray a[ll..rr+1] has all differences divisible by cur_gcd >= 2
                // So, the length is (rr - ll + 2)
                ans = max(ans, rr - ll + 2);
            }
        }

        cout << ans << '\n';
    }
    return 0;
}
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

        // We use two pointers: l (left) and r (right)
        // For each l, we find the maximum r such that [a_l, ..., a_r] is good
        // A subarray [a_l, ..., a_r] is good if for all i in [l, r], a_i >= (i - l + 1)
        // We maintain r for each l, and for each l, the number of good subarrays is (r - l + 1)
        long long ans = 0;
        int r = 0;
        for (int l = 0; l < n; ++l) {
            // Move r as far as possible while the subarray is good
            // For current l, we need a[r] >= (r - l + 1)
            // r starts from previous value or l
            if (r < l) r = l;
            while (r < n && a[r] >= (r - l + 1)) {
                ++r;
            }
            // All subarrays [l, l], [l, l+1], ..., [l, r-1] are good
            ans += (r - l);
        }
        cout << ans << '\n';
    }
    return 0;
}
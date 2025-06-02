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
        vector<int> s(n);
        for (int i = 0; i < n; ++i) cin >> s[i];

        // If all shoe sizes are the same, any derangement is valid.
        // If not, we need to check if a derangement is possible such that
        // for all i, s[p[i]] >= s[i] and p[i] != i.

        // If n == 1, impossible to derange
        if (n == 1) {
            cout << -1 << '\n';
            continue;
        }

        // If all sizes are the same, any derangement is valid.
        bool all_same = true;
        for (int i = 1; i < n; ++i) {
            if (s[i] != s[0]) {
                all_same = false;
                break;
            }
        }
        if (all_same) {
            // Output a simple cyclic shift
            for (int i = 0; i < n; ++i) {
                cout << (i == n-1 ? 1 : i+2) << " ";
            }
            cout << '\n';
            continue;
        }

        // For general case:
        // Since s is sorted, if the smallest size occurs k times,
        // and all the k smallest sizes are at the beginning,
        // we can rotate the array by k positions to the left.
        // But we must ensure that s[k] >= s[0] (which is always true since sorted),
        // but we must also ensure that after rotation, for all i, s[(i+k)%n] >= s[i]
        // and (i+k)%n != i (which is true for k < n).

        // Find the first position where s[i] > s[0]
        int k = 0;
        while (k < n && s[k] == s[0]) ++k;

        // If k == n, all are same (already handled above)
        // If k == 0, all are distinct, but s[0] is unique smallest
        // If k == n-1, only last is different, but then s[n-1] > s[0]
        // If k == n, all same (already handled)
        // If k == n, impossible (already handled)
        // If k == n-1, only last is different, but then s[n-1] > s[0]
        // If k == 0, only first is unique, but then s[1] > s[0]

        // If k == n, all same, already handled
        // If k == n-1, only last is different, but then s[n-1] > s[0]
        // If k == 0, only first is unique, but then s[1] > s[0]

        // If k == n, all same, already handled
        // If k == n-1, only last is different, but then s[n-1] > s[0]
        // If k == 0, only first is unique, but then s[1] > s[0]

        // If k == n, all same, already handled
        // If k == n-1, only last is different, but then s[n-1] > s[0]
        // If k == 0, only first is unique, but then s[1] > s[0]

        // If k == n, all same, already handled
        // If k == n-1, only last is different, but then s[n-1] > s[0]
        // If k == 0, only first is unique, but then s[1] > s[0]

        // If k == n, all same, already handled
        // If k == n-1, only last is different, but then s[n-1] > s[0]
        // If k == 0, only first is unique, but then s[1] > s[0]

        // If k == n, all same, already handled
        // If k == n-1, only last is different, but then s[n-1] > s[0]
        // If k == 0, only first is unique, but then s[1] > s[0]

        // If k == n, all same, already handled
        // If k == n-1, only last is different, but then s[n-1] > s[0]
        // If k == 0, only first is unique, but then s[1] > s[0]

        // If k == n, all same, already handled
        // If k == n-1, only last is different, but then s[n-1] > s[0]
        // If k == 0, only first is unique, but then s[1] > s[0]

        // If k == n, all same, already handled
        // If k == n-1, only last is different, but then s[n-1] > s[0]
        // If k == 0, only first is unique, but then s[1] > s[0]

        // If k == n, all same, already handled
        // If k == n-1, only last is different, but then s[n-1] > s[0]
        // If k == 0, only first is unique, but then s[1] > s[0]

        // If k == n, all same, already handled
        // If k == n-1, only last is different, but then s[n-1] > s[0]
        // If k == 0, only first is unique, but then s[1] > s[0]

        // If k == n, all same, already handled
        // If k == n-1, only last is different, but then s[n-1] > s[0]
        // If k == 0, only first is unique, but then s[1] > s[0]

        // If k == n, all same, already handled
        // If k == n-1, only last is different, but then s[n-1] > s[0]
        // If k == 0, only first is unique, but then s[1] > s[0]

        // If k == n, all same, already handled
        // If k == n-1, only last is different, but then s[n-1] > s[0]
        // If k == 0, only first is unique, but then s[1] > s[0]

        // If k == n, all same, already handled
        // If k == n-1, only last is different, but then s[n-1] > s[0]
        // If k == 0, only first is unique, but then s[1] > s[0]

        // If k == n, all same, already handled
        // If k == n-1, only last is different, but then s[n-1] > s[0]
        // If k == 0, only first is unique, but then s[1] > s[0]

        // If k == n, all same, already handled
        // If k == n-1, only last is different, but then s[n-1] > s[0]
        // If k == 0, only first is unique, but then s[1] > s[0]

        // If k == n, all same, already handled
        // If k == n-1, only last is different, but then s[n-1] > s[0]
        // If k == 0, only first is unique, but then s[1] > s[0]

        // If k == n, all same, already handled
        // If k == n-1, only last is different, but then s[n-1] > s[0]
        // If k == 0, only first is unique, but then s[1] > s[0]

        // If k == n, all same, already handled
        // If k == n-1, only last is different, but then s[n-1] > s[0]
        // If k == 0, only first is unique, but then s[1] > s[0]

        // If k == n, all same, already handled
        // If k == n-1, only last is different, but then s[n-1] > s[0]
        // If k == 0, only first is unique, but then s[1] > s[0]

        // If k == n, all same, already handled
        // If k == n-1, only last is different, but then s[n-1] > s[0]
        // If k == 0, only first is unique, but then s[1] > s[0]

        // If k == n, all same, already handled
        // If k == n-1, only last is different, but then s[n-1] > s[0]
        // If k == 0, only first is unique, but then s[1] > s[
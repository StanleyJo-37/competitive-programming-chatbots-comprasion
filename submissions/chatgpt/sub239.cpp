#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int main() {
    ios::sync_with_stdio(false); // Fast IO
    cin.tie(nullptr);

    int q;
    cin >> q;
    while (q--) {
        int n, k;
        cin >> n >> k;

        vector<int> a(k); // positions of air conditioners (1-based)
        vector<int> t(k); // temperatures of air conditioners

        for (int i = 0; i < k; ++i) {
            cin >> a[i];
            --a[i]; // convert to 0-based for easier indexing
        }
        for (int i = 0; i < k; ++i) {
            cin >> t[i];
        }

        // Initialize all cells with a very large value (infinity)
        vector<long long> res(n, LLONG_MAX);

        // Set the temperature at air conditioner positions
        for (int i = 0; i < k; ++i) {
            res[a[i]] = t[i];
        }

        // First pass: left to right
        // For each cell, keep track of the minimum temperature that can be reached from the left
        long long cur = LLONG_MAX;
        for (int i = 0; i < n; ++i) {
            if (res[i] < cur) cur = res[i];
            else if (cur != LLONG_MAX) cur++;
            if (cur < res[i]) res[i] = cur;
        }

        // Second pass: right to left
        // For each cell, keep track of the minimum temperature that can be reached from the right
        cur = LLONG_MAX;
        for (int i = n - 1; i >= 0; --i) {
            if (res[i] < cur) cur = res[i];
            else if (cur != LLONG_MAX) cur++;
            if (cur < res[i]) res[i] = cur;
        }

        // Output the result for this test case
        for (int i = 0; i < n; ++i) {
            cout << res[i] << (i == n - 1 ? '\n' : ' ');
        }
    }
    return 0;
}
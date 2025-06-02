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

        // Compute initial inversion count
        // For each 1, count number of 0s to its right
        int cnt0 = 0;
        long long inv = 0;
        for (int i = n - 1; i >= 0; --i) {
            if (a[i] == 0) {
                cnt0++;
            } else {
                inv += cnt0;
            }
        }

        // Try flipping each element at most once, and compute the new inversion count
        // We only need to consider flipping the first 0 to 1, and the last 1 to 0
        // because flipping any other 0 or 1 will not give a better result.

        // Find first 0 and last 1
        int first0 = -1, last1 = -1;
        for (int i = 0; i < n; ++i) {
            if (a[i] == 0 && first0 == -1) first0 = i;
            if (a[i] == 1) last1 = i;
        }

        long long max_inv = inv;

        // Try flipping first 0 to 1
        if (first0 != -1) {
            // Flipping a 0 at position i to 1:
            // - It will lose all inversions where this 0 was to the right of a 1 (i.e., all 1s to its left)
            // - It will gain all inversions where this 1 is to the left of a 0 (i.e., all 0s to its right)
            // So, we need to count number of 1s to the left and 0s to the right of first0
            int ones_left = 0, zeros_right = 0;
            for (int i = 0; i < first0; ++i) if (a[i] == 1) ones_left++;
            for (int i = first0 + 1; i < n; ++i) if (a[i] == 0) zeros_right++;
            long long new_inv = inv - ones_left + zeros_right;
            if (new_inv > max_inv) max_inv = new_inv;
        }

        // Try flipping last 1 to 0
        if (last1 != -1) {
            // Flipping a 1 at position i to 0:
            // - It will lose all inversions where this 1 was to the left of a 0 (i.e., all 0s to its right)
            // - It will gain all inversions where this 0 is to the right of a 1 (i.e., all 1s to its left)
            int ones_left = 0, zeros_right = 0;
            for (int i = 0; i < last1; ++i) if (a[i] == 1) ones_left++;
            for (int i = last1 + 1; i < n; ++i) if (a[i] == 0) zeros_right++;
            long long new_inv = inv - zeros_right + ones_left;
            if (new_inv > max_inv) max_inv = new_inv;
        }

        cout << max_inv << '\n';
    }
    return 0;
}
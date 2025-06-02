#include <iostream>
#include <vector>
#include <algorithm>
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

        // To keep track of which elements are used
        vector<bool> used(n, false);
        vector<int> result;

        int cur_or = 0; // Current prefix OR

        // For up to 32 steps (since 32 bits in 10^9), try to greedily pick the element
        // that increases the prefix OR the most at each step.
        for (int step = 0; step < min(n, 32); ++step) {
            int best_idx = -1;
            int best_val = cur_or;
            // Find the unused element that maximizes (cur_or | a[i])
            for (int i = 0; i < n; ++i) {
                if (!used[i]) {
                    int val = cur_or | a[i];
                    if (val > best_val) {
                        best_val = val;
                        best_idx = i;
                    }
                }
            }
            if (best_idx == -1) break; // No improvement, break
            used[best_idx] = true;
            result.push_back(a[best_idx]);
            cur_or |= a[best_idx];
        }

        // Add the remaining unused elements in any order (doesn't affect prefix OR)
        for (int i = 0; i < n; ++i) {
            if (!used[i]) result.push_back(a[i]);
        }

        // Output the result
        for (int i = 0; i < n; ++i) {
            cout << result[i] << (i + 1 == n ? '\n' : ' ');
        }
    }
    return 0;
}
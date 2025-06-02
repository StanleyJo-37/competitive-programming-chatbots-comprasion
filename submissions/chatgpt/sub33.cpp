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
        int n, k;
        cin >> n >> k;
        vector<int> h(n);
        for (int i = 0; i < n; ++i) cin >> h[i];

        // For each section, we maintain the possible range of the top of the fence
        // Let the bottom of the i-th section be at b_i, then the top is b_i + k
        // The bottom of the first and last must be exactly h[0] and h[n-1]
        // For the rest, the bottom can be in [h[i], h[i] + k - 1]
        // The top of each section must overlap with the previous one by at least 1 unit

        // We keep track of the possible range of the top of the previous section
        // For the first section, the bottom is h[0], so the top is [h[0] + k, h[0] + k]
        int low = h[0], high = h[0]; // possible bottom of current section

        bool possible = true;
        for (int i = 1; i < n; ++i) {
            // The bottom of the current section can be in [h[i], h[i] + k - 1]
            // The top of the previous section is in [low + k, high + k]
            // The bottom of the current section must be such that the overlap is at least 1
            // So, the bottom of the current section can be at least (low - (k - 1))
            // and at most (high + (k - 1))
            int new_low = max(h[i], low - (k - 1));
            int new_high = min(h[i] + (k - 1), high + (k - 1));
            // If the range is invalid, it's impossible
            if (new_low > new_high) {
                possible = false;
                break;
            }
            low = new_low;
            high = new_high;
        }
        // For the last section, the bottom must be exactly h[n-1]
        if (!(low <= h[n-1] && h[n-1] <= high)) possible = false;

        cout << (possible ? "YES" : "NO") << '\n';
    }
    return 0;
}
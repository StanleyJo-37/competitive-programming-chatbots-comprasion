#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n, l, r;
        cin >> n >> l >> r;
        vector<int> left(l), right(r);

        // Read left socks
        for (int i = 0; i < l; ++i) cin >> left[i];
        // Read right socks
        for (int i = 0; i < r; ++i) cin >> right[i];

        // Count colors for left and right socks
        unordered_map<int, int> cntL, cntR;
        for (int c : left) cntL[c]++;
        for (int c : right) cntR[c]++;

        // First, greedily match as many pairs as possible without any operation
        for (auto& [color, cnt] : cntL) {
            int match = min(cnt, cntR[color]);
            cntL[color] -= match;
            cntR[color] -= match;
            l -= match;
            r -= match;
        }

        // Now, l and r are the number of unmatched left and right socks
        // We want to balance the number of left and right socks (make both n/2)
        // It's always optimal to convert socks from the side with more socks to the other side

        int res = 0;
        // If left > right, swap so that left is always <= right
        if (l > r) {
            swap(l, r);
            swap(cntL, cntR);
        }
        // Now, r >= l

        int diff = (r - l) / 2; // Number of right socks to convert to left to balance
        int ops = 0;

        // Try to convert right socks of the same color (with at least 2 unpaired right socks)
        // Each such conversion can fix 2 socks with 1 operation
        for (auto& [color, cnt] : cntR) {
            int pairs = cnt / 2;
            int take = min(pairs, diff - ops);
            ops += take;
            cntR[color] -= take * 2;
            if (ops == diff) break;
        }

        // Each conversion costs 1, so add ops to result
        res += diff;
        // After balancing, both sides have n/2 socks
        // The remaining unmatched socks (l + r - 2*ops) must be paired by recoloring
        // Each pair needs 1 recolor operation
        res += (n / 2 - ops);

        cout << res << '\n';
    }
    return 0;
}
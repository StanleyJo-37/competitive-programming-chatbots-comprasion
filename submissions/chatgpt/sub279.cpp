#include <iostream>
#include <vector>
using namespace std;

// This problem can be solved efficiently using a Disjoint Set Union (DSU) with path compression.
// However, since each knight can only be conquered once, we can use a "next" array to skip over already conquered knights.

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    // ans[i] will store the knight who conquered knight i+1 (0-based index)
    vector<int> ans(n, 0);

    // next[i] will point to the next alive knight after i (0-based index)
    // Initially, next[i] = i+1, and next[n-1] = n (out of bounds)
    vector<int> next(n + 2);
    for (int i = 0; i <= n + 1; ++i) next[i] = i;

    // Find function with path compression to skip over already conquered knights
    auto find = [&](int x) {
        // Returns the next alive knight >= x (0-based)
        if (next[x] != x) next[x] = find(next[x]);
        return next[x];
    };

    // Process each fight
    for (int i = 0; i < m; ++i) {
        int l, r, x;
        cin >> l >> r >> x;
        // Convert to 0-based indices
        --l; --r; --x;

        // For all knights in [l, r] except x, mark them as conquered by x+1
        int pos = find(l);
        while (pos <= r) {
            if (pos != x) {
                ans[pos] = x + 1; // conquered by knight x+1
                next[pos] = pos + 1; // skip this knight in future
            }
            pos = find(pos + 1);
        }
    }

    // Output the result
    for (int i = 0; i < n; ++i) {
        cout << ans[i] << " ";
    }
    cout << "\n";
    return 0;
}
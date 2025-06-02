#include <iostream>
using namespace std;

// For each query, we need to determine if we can reach v from u
// by a sequence of moves where each move is: from x to x + y, where (x & y) == y
// This means: at each step, we can add to x any y such that all bits set in y are also set in x

// Key insight:
// - We can only move forward (increase the value).
// - We can only set bits in the result that are already set in u (since we can only add y where y's bits are subset of current x).
// - So, to reach v from u, all bits set in u must be enough to "cover" the bits set in v, and we must not need to "set" a bit in v before we have enough bits in u to do so.

// The correct approach is to check, for each bit from LSB to MSB, that at every point, the number of set bits in u up to that bit is at least as many as in v.
// If at any point, v has more set bits up to that position than u, it's impossible.

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int q;
    cin >> q;
    while (q--) {
        int u, v;
        cin >> u >> v;

        // If u > v, we can never reach v (since we can only increase)
        if (u > v) {
            cout << "NO\n";
            continue;
        }

        // Count the number of set bits up to each position
        int cnt_u = 0, cnt_v = 0;
        bool possible = true;
        for (int i = 0; i < 30; ++i) {
            // Check i-th bit
            if (u & (1 << i)) cnt_u++;
            if (v & (1 << i)) cnt_v++;
            // At any point, if v has more set bits up to this position than u, it's impossible
            if (cnt_v > cnt_u) {
                possible = false;
                break;
            }
        }
        cout << (possible ? "YES" : "NO") << '\n';
    }
    return 0;
}
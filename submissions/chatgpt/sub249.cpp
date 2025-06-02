#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<ll> k(n), h(n);
        for (int i = 0; i < n; ++i) cin >> k[i];
        for (int i = 0; i < n; ++i) cin >> h[i];

        // We'll process monsters from last to first, grouping overlapping intervals.
        // Each monster at k[i] with health h[i] requires a spell of at least h[i] at time k[i].
        // To minimize mana, we want to merge overlapping intervals of required spell sequences.

        ll ans = 0;
        // We'll keep track of the current interval [l, r] (inclusive) that needs to be covered by a spell sequence.
        // r: right end (current monster's appearance time)
        // l: left end (start time of the spell sequence)
        ll l = k[n-1] - h[n-1] + 1;
        ll r = k[n-1];

        // Process from the second last monster to the first
        for (int i = n-2; i >= 0; --i) {
            ll new_l = k[i] - h[i] + 1;
            ll new_r = k[i];
            // If the current monster's required interval overlaps with the current [l, r], merge them
            if (new_r >= l) {
                // Merge intervals: new left is min(l, new_l), right is max(r, new_r) (but r always increases)
                l = min(l, new_l);
                // r remains the same (since we process from right to left, r is always the rightmost)
            } else {
                // No overlap, so we finalize the current interval [l, r]
                // The mana cost for a sequence of length len is sum_{i=1}^{len} i = len*(len+1)/2
                ll len = r - l + 1;
                ans += len * (len + 1) / 2;
                // Start a new interval for the current monster
                l = new_l;
                r = new_r;
            }
        }
        // Don't forget to add the last interval
        ll len = r - l + 1;
        ans += len * (len + 1) / 2;

        cout << ans << '\n';
    }
    return 0;
}
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// Function to compute the number of valid segments where MEX of p[l..r] equals MEX of q[l..r]
ll solve(int n, vector<int>& p, vector<int>& q) {
    // Precompute the positions of each element in p and q
    vector<int> pos_p(n + 2), pos_q(n + 2);
    for (int i = 0; i < n; ++i) {
        pos_p[p[i]] = i;
        pos_q[q[i]] = i;
    }

    ll res = 0;
    int l = 0, r = -1; // [l, r] is the current segment where MEX is m for both p and q
    for (int m = 1; m <= n + 1; ++m) {
        // The positions of m in p and q
        int a = (m <= n) ? pos_p[m] : n;
        int b = (m <= n) ? pos_q[m] : n;
        // The new segment boundaries must include all 1..m-1 and exclude m
        int new_l = min(a, b);
        int new_r = max(a, b);
        if (new_l < l || new_r > r) {
            // The segment must be adjusted to include new_l and new_r
            if (r < new_l) {
                // No overlap, reset the segment
                res += (ll)(new_l - r) * (n - new_r + 1);
            } else if (new_r < l) {
                // No overlap, reset the segment
                res += (ll)(l - new_r) * (new_l + 1);
            } else {
                // Overlapping segments, adjust l and r
                int curr_l = min(l, new_l);
                int curr_r = max(r, new_r);
                res += (ll)(curr_l - l + 1) * (r - curr_r + 1);
            }
            l = min(l, new_l);
            r = max(r, new_r);
        }
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> p(n), q(n);
    for (int i = 0; i < n; ++i) cin >> p[i];
    for (int i = 0; i < n; ++i) cin >> q[i];

    cout << solve(n, p, q) << '\n';
    return 0;
}
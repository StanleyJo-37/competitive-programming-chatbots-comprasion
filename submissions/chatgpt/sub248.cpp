#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Read input
    int n;
    cin >> n;
    vector<int> p(n+1), q(n+1); // 1-based indexing for easier mapping
    for (int i = 1; i <= n; ++i) cin >> p[i];
    for (int i = 1; i <= n; ++i) cin >> q[i];

    // pos_p[x] = position of value x in p
    // pos_q[x] = position of value x in q
    vector<int> pos_p(n+2), pos_q(n+2); // n+2 to avoid out-of-bounds for mex=n+1
    for (int i = 1; i <= n; ++i) pos_p[p[i]] = i;
    for (int i = 1; i <= n; ++i) pos_q[q[i]] = i;

    // The answer will be the sum of valid (l, r) pairs for all possible MEX values
    ll ans = 0;

    // For MEX = 1, the only valid segment is the one that does not contain 1 in both p and q
    // That is, l > max(pos_p[1], pos_q[1]) or r < min(pos_p[1], pos_q[1])
    // But since all values are from 1 to n, the only segment with MEX=1 is the empty segment before the first 1
    // But as per the problem, l <= r, so only singletons before the first 1
    // Actually, for MEX=1, the only valid segments are those that do not contain 1 in both p and q
    // So, all segments [l, r] such that r < min(pos_p[1], pos_q[1]) are valid
    int left1 = min(pos_p[1], pos_q[1]) - 1;
    ans += 1LL * left1 * (left1 + 1) / 2; // number of segments in [1, left1]

    // Now, for MEX from 2 to n+1
    // For each MEX x, the segment must contain all numbers 1..x-1, and must not contain x
    // So, the minimal segment is from min(pos_p[1..x-1], pos_q[1..x-1]) to max(pos_p[1..x-1], pos_q[1..x-1])
    // The segment must not contain x, so its left > max(pos_p[x], pos_q[x]) or right < min(pos_p[x], pos_q[x])
    // But since we want segments that contain all 1..x-1 and not x, we can use two pointers

    // We'll maintain the minimal and maximal positions of 1..x-1 in both p and q
    int minL = min(pos_p[1], pos_q[1]);
    int maxR = max(pos_p[1], pos_q[1]);
    for (int mex = 2; mex <= n+1; ++mex) {
        // For mex = x, we need all 1..x-1 in the segment, and not x
        // The minimal segment is [minL, maxR]
        // The segment must not contain x, so:
        // - left end >= minL, right end <= maxR
        // - and segment [l, r] does not contain pos_p[x] nor pos_q[x]
        // So, valid l in [minL, maxR], valid r in [minL, maxR], and for all l <= r
        // But if pos_p[x] or pos_q[x] in [minL, maxR], we must split the interval

        int px = pos_p[mex], qx = pos_q[mex];

        int L = minL, R = maxR;
        int left = min(px, qx), right = max(px, qx);

        // If both px and qx are outside [L, R], then the whole interval is valid
        if ((px < L && qx < L) || (px > R && qx > R)) {
            // Number of segments in [L, R]
            ll len = R - L + 1;
            ans += len * (len + 1) / 2;
        } else {
            // px or qx is inside [L, R], so we need to split
            // Segments [L, min(px, qx)-1] and [max(px, qx)+1, R] are valid
            if (left > L) {
                ll len = left - L;
                ans += len * (len + 1) / 2;
            }
            if (right < R) {
                ll len = R - right;
                ans += len * (len + 1) / 2;
            }
        }

        // Update minL and maxR to include the next value
        minL = min(minL, min(px, qx));
        maxR = max(maxR, max(px, qx));
    }

    cout << ans << '\n';
    return 0;
}
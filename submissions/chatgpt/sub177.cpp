#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
using namespace std;

// Segment Tree for Range Maximum Query
class SegmentTree {
    vector<int> tree;
    int n;
public:
    SegmentTree(const vector<int>& data) {
        n = data.size();
        tree.resize(4 * n);
        build(data, 1, 0, n - 1);
    }
    void build(const vector<int>& data, int node, int l, int r) {
        if (l == r) {
            tree[node] = data[l];
        } else {
            int mid = (l + r) / 2;
            build(data, 2 * node, l, mid);
            build(data, 2 * node + 1, mid + 1, r);
            tree[node] = max(tree[2 * node], tree[2 * node + 1]);
        }
    }
    int query(int ql, int qr) {
        return query(1, 0, n - 1, ql, qr);
    }
    int query(int node, int l, int r, int ql, int qr) {
        if (qr < l || r < ql) return -1; // out of range
        if (ql <= l && r <= qr) return tree[node];
        int mid = (l + r) / 2;
        return max(query(2 * node, l, mid, ql, qr),
                   query(2 * node + 1, mid + 1, r, ql, qr));
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<int> b(N);
    for (int i = 0; i < N; ++i) cin >> b[i];

    // Precompute prefix max for left-to-right burning
    vector<int> prefix_max(N);
    prefix_max[0] = b[0];
    for (int i = 1; i < N; ++i)
        prefix_max[i] = max(prefix_max[i - 1], b[i]);

    // Precompute suffix max for right-to-left burning
    vector<int> suffix_max(N);
    suffix_max[N - 1] = b[N - 1];
    for (int i = N - 2; i >= 0; --i)
        suffix_max[i] = max(suffix_max[i + 1], b[i]);

    // Build segment tree for range max query
    SegmentTree seg(b);

    int Q;
    cin >> Q;
    cout << fixed << setprecision(10); // for floating point output

    while (Q--) {
        int L, R;
        cin >> L >> R;

        // Time for the leftmost matchstick to burn from the free end
        int left_burn = b[L];

        // Time for the rightmost matchstick to burn from the free end
        int right_burn = b[R];

        // The time when the fire from the leftmost match reaches the rear end (common point)
        int left_time = left_burn;

        // The time when the fire from the rightmost match reaches the rear end
        int right_time = right_burn;

        // The maximum time to burn any matchstick in [L, R] if only burned from one end
        int max_burn = seg.query(L, R);

        // For each matchstick in [L, R], the time to burn is:
        // - If only burned from one end: b[i]
        // - If burned from both ends: max(time from left, time from right, b[i]/2 + max(left_time, right_time)/2)
        // But since the fire from the rear end starts only after the leftmost or rightmost matchstick burns out,
        // for all matches in [L, R], the rear end fire starts at min(left_time, right_time).
        // For all matches, the time to burn is:
        // max( max_burn, min(left_time, right_time) + (max_burn - min(left_time, right_time))/2 )
        // But the correct way is:
        // For each matchstick i in [L, R]:
        //   - The time when fire from the free end reaches the rear: t1 = b[i]
        //   - The time when fire from the rear end reaches the free end: t2 = (b[i] - (i-L)*left_burn/(R-L)) / 2 + left_time
        // But that's too complex. The correct approach is:
        // The time to burn all matches is max( max_burn, (max_burn + min(left_time, right_time)) / 2 )
        // But let's simulate the process for the range [L, R]:

        // The fire from the free end starts at L and R, and the rear end is at the other side.
        // The time for the fire to reach the rear end from L is b[L], from R is b[R].
        // After that, the rear end is ignited, and the remaining matches (if any) will be burned from both ends.

        // For all matches, the time to burn is:
        // For i in [L, R]:
        //   - If i == L or i == R: time = b[i]
        //   - Else: time = max( b[i]/2 + min(left_burn, right_burn)/2, max(left_burn, right_burn) )
        // But the maximum is always max( max_burn, (max_burn + min(left_burn, right_burn)) / 2 )

        // Actually, the correct way is:
        // For all matches, the time to burn is:
        //   - For the leftmost: b[L]
        //   - For the rightmost: b[R]
        //   - For others: max( b[i]/2 + min(left_burn, right_burn)/2, max(left_burn, right_burn) )
        // The answer is the maximum among these.

        // So, for all matches in [L, R], the time to burn is:
        //   - For i in [L, R]:
        //       - If b[i] <= min(left_burn, right_burn): time = b[i]
        //       - Else: time = (b[i] + min(left_burn, right_burn)) / 2

        // So, we need to find the maximum of:
        //   - b[L]
        //   - b[R]
        //   - For i in [L+1, R-1]: (b[i] + min(left_burn, right_burn)) / 2

        // To do this efficiently, we can:
        //   - For all b[i] in [L, R], if b[i] <= min(left_burn, right_burn), time = min(left_burn, right_burn)
        //   - Else, time = (b[i] + min(left_burn, right_burn)) / 2

        // So, the answer is max( min(left_burn, right_burn), (max_burn + min(left_burn, right_burn)) / 2 )

        double min_burn = min(left_burn, right_burn);
        double ans = min_burn;

        if (max_burn > min_burn) {
            ans = max(ans, (max_burn + min_burn) / 2.0);
        }

        // But also, if b[L] or b[R] > min_burn, their time is b[L] or b[R]
        ans = max(ans, (double)b[L]);
        ans = max(ans, (double)b[R]);

        cout << ans << '\n';
    }
    return 0;
}
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <climits>

using namespace std;

// Segment tree for range maximum query
class SegmentTree {
private:
    vector<int> tree;
    int n;

    void build(const vector<int>& arr, int node, int start, int end) {
        if (start == end) {
            tree[node] = arr[start];
        } else {
            int mid = (start + end) / 2;
            build(arr, 2 * node + 1, start, mid);
            build(arr, 2 * node + 2, mid + 1, end);
            tree[node] = max(tree[2 * node + 1], tree[2 * node + 2]);
        }
    }

    int query(int node, int start, int end, int l, int r) {
        if (r < start || end < l) {
            return INT_MIN;
        }
        if (l <= start && end <= r) {
            return tree[node];
        }
        int mid = (start + end) / 2;
        int left = query(2 * node + 1, start, mid, l, r);
        int right = query(2 * node + 2, mid + 1, end, l, r);
        return max(left, right);
    }

public:
    SegmentTree(const vector<int>& arr) {
        n = arr.size();
        int height = (int)(ceil(log2(n)));
        int size = 2 * (int)pow(2, height) - 1;
        tree.resize(size, INT_MIN);
        build(arr, 0, 0, n - 1);
    }

    int rangeMax(int l, int r) {
        return query(0, 0, n - 1, l, r);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<int> b(N);
    for (int i = 0; i < N; ++i) {
        cin >> b[i];
    }

    // Precompute prefix sums for the left and right parts
    vector<double> prefixLeft(N), prefixRight(N);
    prefixLeft[0] = b[0];
    for (int i = 1; i < N; ++i) {
        prefixLeft[i] = max(prefixLeft[i - 1], (double)b[i]);
    }
    prefixRight[N - 1] = b[N - 1];
    for (int i = N - 2; i >= 0; --i) {
        prefixRight[i] = max(prefixRight[i + 1], (double)b[i]);
    }

    SegmentTree st(b);

    int Q;
    cin >> Q;
    while (Q--) {
        int L, R;
        cin >> L >> R;

        // The maximum b[i] in the range [L, R] is the critical factor
        int maxB = st.rangeMax(L, R);
        double maxTime = maxB;

        // Check if there's a larger b[i] outside [L, R] that could affect the time
        double candidate1 = (L > 0) ? (prefixLeft[L - 1] / 2.0) : 0.0;
        double candidate2 = (R < N - 1) ? (prefixRight[R + 1] / 2.0) : 0.0;
        double maxOutside = max(candidate1, candidate2);

        // The total time is the maximum between the maxB and (maxOutside + maxB/2)
        // But since maxB is the time when lit from one end, and maxOutside is the time from the other end,
        // the actual time is max(maxB, maxOutside + maxB/2)
        // However, the correct formula is max(maxB, maxOutside + maxB/2)
        // But in reality, the matches outside [L, R] can only contribute if their b[i]/2 is greater than maxB - b[i]/2 for some i in [L, R]
        // So the correct answer is max(maxB, maxOutside + maxB/2)
        // But in the sample input 2, maxB is 5, maxOutside is 0, so time is 5.0
        // But in sample input 3, the answer is 9.0, which is maxB (9) and maxOutside is 5/2=2.5, so 9 vs 2.5 + 9/2=6.5 => max is 9.0
        // So the formula seems to be correct.

        double totalTime = max(maxB, maxOutside + maxB / 2.0);
        printf("%.1f\n", totalTime);
    }

    return 0;
}
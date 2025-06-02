#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Segment Tree for Range Maximum Query
struct SegmentTreeMax {
    int n;
    vector<int> tree;
    void build(const vector<int>& a) {
        n = a.size();
        tree.resize(2 * n);
        for (int i = 0; i < n; ++i) tree[n + i] = a[i];
        for (int i = n - 1; i > 0; --i)
            tree[i] = max(tree[i << 1], tree[i << 1 | 1]);
    }
    // Query max in [l, r] (0-based, inclusive)
    int query(int l, int r) {
        int res = INT_MIN;
        l += n; r += n;
        while (l <= r) {
            if (l & 1) res = max(res, tree[l++]);
            if (!(r & 1)) res = max(res, tree[r--]);
            l >>= 1; r >>= 1;
        }
        return res;
    }
};

// Segment Tree for Range Minimum Query
struct SegmentTreeMin {
    int n;
    vector<int> tree;
    void build(const vector<int>& a) {
        n = a.size();
        tree.resize(2 * n);
        for (int i = 0; i < n; ++i) tree[n + i] = a[i];
        for (int i = n - 1; i > 0; --i)
            tree[i] = min(tree[i << 1], tree[i << 1 | 1]);
    }
    // Query min in [l, r] (0-based, inclusive)
    int query(int l, int r) {
        int res = INT_MAX;
        l += n; r += n;
        while (l <= r) {
            if (l & 1) res = min(res, tree[l++]);
            if (!(r & 1)) res = min(res, tree[r--]);
            l >>= 1; r >>= 1;
        }
        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for (int& x : a) cin >> x;
    for (int& x : b) cin >> x;

    // Build segment trees for fast range queries
    SegmentTreeMax st_max;
    SegmentTreeMin st_min;
    st_max.build(a);
    st_min.build(b);

    long long ans = 0;

    // For each l, binary search for r where max(a[l..r]) == min(b[l..r])
    for (int l = 0; l < n; ++l) {
        int lo = l, hi = n - 1, left = -1, right = -1;
        // Find the leftmost r >= l such that max(a[l..r]) == min(b[l..r])
        int low = l, high = n - 1;
        while (low <= high) {
            int mid = (low + high) / 2;
            int mx = st_max.query(l, mid);
            int mn = st_min.query(l, mid);
            if (mx < mn) {
                low = mid + 1;
            } else if (mx > mn) {
                high = mid - 1;
            } else {
                left = mid;
                high = mid - 1;
            }
        }
        // Find the rightmost r >= l such that max(a[l..r]) == min(b[l..r])
        low = l, high = n - 1;
        while (low <= high) {
            int mid = (low + high) / 2;
            int mx = st_max.query(l, mid);
            int mn = st_min.query(l, mid);
            if (mx < mn) {
                low = mid + 1;
            } else if (mx > mn) {
                high = mid - 1;
            } else {
                right = mid;
                low = mid + 1;
            }
        }
        // If such r exists, add the number of valid (l, r) pairs
        if (left != -1 && right != -1 && left <= right) {
            ans += (right - left + 1);
        }
    }

    cout << ans << '\n';
    return 0;
}
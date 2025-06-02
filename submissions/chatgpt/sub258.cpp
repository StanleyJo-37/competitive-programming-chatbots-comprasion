#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

// Segment Tree for range min/max queries
struct SegmentTree {
    int n;
    vector<int> tmin, tmax;
    void build(const vector<int>& a) {
        n = a.size();
        tmin.assign(4 * n, 0);
        tmax.assign(4 * n, 0);
        build(1, 0, n - 1, a);
    }
    void build(int v, int tl, int tr, const vector<int>& a) {
        if (tl == tr) {
            tmin[v] = tmax[v] = a[tl];
        } else {
            int tm = (tl + tr) / 2;
            build(v * 2, tl, tm, a);
            build(v * 2 + 1, tm + 1, tr, a);
            tmin[v] = min(tmin[v * 2], tmin[v * 2 + 1]);
            tmax[v] = max(tmax[v * 2], tmax[v * 2 + 1]);
        }
    }
    int get_min(int l, int r) { return get_min(1, 0, n - 1, l, r); }
    int get_min(int v, int tl, int tr, int l, int r) {
        if (l > r) return 1e9 + 1;
        if (l == tl && r == tr) return tmin[v];
        int tm = (tl + tr) / 2;
        return min(get_min(v * 2, tl, tm, l, min(r, tm)),
                   get_min(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r));
    }
    int get_max(int l, int r) { return get_max(1, 0, n - 1, l, r); }
    int get_max(int v, int tl, int tr, int l, int r) {
        if (l > r) return 0;
        if (l == tl && r == tr) return tmax[v];
        int tm = (tl + tr) / 2;
        return max(get_max(v * 2, tl, tm, l, min(r, tm)),
                   get_max(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r));
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int& x : a) cin >> x;

        // Precompute prefix max and suffix max
        vector<int> pref_max(n), suff_max(n);
        pref_max[0] = a[0];
        for (int i = 1; i < n; ++i)
            pref_max[i] = max(pref_max[i - 1], a[i]);
        suff_max[n - 1] = a[n - 1];
        for (int i = n - 2; i >= 0; --i)
            suff_max[i] = max(suff_max[i + 1], a[i]);

        // Map from value to all positions where it occurs
        map<int, vector<int>> pos;
        for (int i = 0; i < n; ++i)
            pos[a[i]].push_back(i);

        // Build segment tree for range min queries
        SegmentTree st;
        st.build(a);

        bool found = false;
        // Try all possible y = 1 (middle part of length 1)
        for (int mid = 1; mid < n - 1; ++mid) {
            int val = a[mid];
            // Find leftmost position where pref_max == val and rightmost where suff_max == val
            // x = left part length, z = right part length
            // x = left, y = 1, z = n - x - 1
            // We need max(0, x-1) == val, min(mid, mid) == val, max(mid+1, n-1) == val
            // So, pref_max[x-1] == val, a[mid] == val, suff_max[mid+1] == val
            // x = mid, y = 1, z = n - x - y
            int x = mid, y = 1, z = n - x - y;
            if (x < 1 || z < 1) continue;
            if (pref_max[x - 1] != val) continue;
            if (suff_max[mid + 1] != val) continue;
            // Check min in [x, x] == val (trivially true)
            // All conditions satisfied
            cout << "YES\n";
            cout << x << " " << y << " " << z << "\n";
            found = true;
            break;
        }
        if (found) continue;

        // Try all possible y > 1 (middle part of length > 1)
        // For each value, try to find a segment [l, r] where min(l, r) == val
        // and left and right parts have max == val
        for (auto& [val, vpos] : pos) {
            // For each possible segment [l, r] with min == val
            // We can try all possible leftmost and rightmost positions of val
            int first = vpos.front();
            int last = vpos.back();
            // Try all possible splits: x = first, y = last - first + 1, z = n - x - y
            int x = first, y = last - first + 1, z = n - x - y;
            if (x < 1 || y < 1 || z < 1) continue;
            // Check max(0, x-1) == val, min(x, x+y-1) == val, max(x+y, n-1) == val
            if (pref_max[x - 1] != val) continue;
            if (st.get_min(x, x + y - 1) != val) continue;
            if (suff_max[x + y] != val) continue;
            cout << "YES\n";
            cout << x << " " << y << " " << z << "\n";
            found = true;
            break;
        }
        if (!found) cout << "NO\n";
    }
    return 0;
}
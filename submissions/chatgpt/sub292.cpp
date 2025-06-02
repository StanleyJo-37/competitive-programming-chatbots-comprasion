#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Disjoint Set Union (Union-Find) with path compression and union by size
struct DSU {
    vector<int> parent, size;
    vector<long long> sum; // sum of each component

    DSU(int n, const vector<long long>& a) {
        parent.resize(n);
        size.assign(n, 1);
        sum = a;
        for (int i = 0; i < n; ++i) parent[i] = i;
    }

    // Find with path compression
    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    // Union by size, and update sum
    void unite(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) return;
        if (size[x] < size[y]) swap(x, y);
        parent[y] = x;
        size[x] += size[y];
        sum[x] += sum[y];
    }

    // Get sum of the component containing x
    long long get_sum(int x) {
        return sum[find(x)];
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    vector<int> destroy(n);
    for (int i = 0; i < n; ++i) {
        cin >> destroy[i];
        --destroy[i]; // convert to 0-based index
    }

    // We will process in reverse: "restore" elements one by one
    vector<bool> alive(n, false); // alive[i] = true if restored
    vector<long long> ans(n);
    DSU dsu(n, a);
    long long max_sum = 0;

    // Process in reverse order
    for (int i = n - 1; i >= 0; --i) {
        ans[i] = max_sum; // after i removals, before restoring destroy[i]
        int idx = destroy[i];
        alive[idx] = true;
        // Initially, the segment is just a[idx]
        // Try to merge with left and right if they are alive
        if (idx > 0 && alive[idx - 1]) {
            dsu.unite(idx, idx - 1);
        }
        if (idx + 1 < n && alive[idx + 1]) {
            dsu.unite(idx, idx + 1);
        }
        // Update max_sum
        max_sum = max(max_sum, dsu.get_sum(idx));
    }

    // Output answers in order
    for (int i = 0; i < n; ++i) {
        cout << ans[i] << '\n';
    }
    return 0;
}
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

struct DSU {
    vector<int> parent;
    vector<long long> sum;
    DSU(int n) : parent(n + 1), sum(n + 1) {
        for (int i = 1; i <= n; ++i) {
            parent[i] = i;
        }
    }
    int find(int u) {
        if (parent[u] != u) {
            parent[u] = find(parent[u]);
        }
        return parent[u];
    }
    void unite(int u, int v) {
        u = find(u);
        v = find(v);
        if (u != v) {
            parent[v] = u;
            sum[u] += sum[v];
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    vector<int> destroy_order(n);
    for (int i = 0; i < n; ++i) {
        cin >> destroy_order[i];
    }

    DSU dsu(n);
    vector<bool> active(n + 1, false);
    vector<long long> res(n);
    long long current_max = 0;

    // Process in reverse order: start from all destroyed and activate elements one by one
    for (int i = n - 1; i >= 0; --i) {
        int pos = destroy_order[i];
        dsu.sum[pos] = a[pos];
        active[pos] = true;

        // Check left neighbor
        if (pos > 1 && active[pos - 1]) {
            dsu.unite(pos, pos - 1);
        }
        // Check right neighbor
        if (pos < n && active[pos + 1]) {
            dsu.unite(pos, pos + 1);
        }

        int root = dsu.find(pos);
        current_max = max(current_max, dsu.sum[root]);
        res[i] = current_max;
    }

    // The first step (i=0) is after all elements are destroyed, so res[0] is 0
    // But we processed in reverse, so res[n-1] is after first destruction, res[0] is after all destructions
    for (int i = 1; i < n; ++i) {
        cout << res[i] << '\n';
    }
    cout << 0 << '\n';

    return 0;
}
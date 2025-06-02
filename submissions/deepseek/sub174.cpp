#include <bits/stdc++.h>
using namespace std;

// Using a Fenwick Tree (Binary Indexed Tree) to handle range updates and point queries.
// Since n can be up to 1e9, we need to use a coordinate compression technique.
// We'll process all queries and collect all relevant coordinates (u, v, x, etc.) to compress them into a smaller range.

struct FenwickTree {
    vector<int> tree;
    int size;

    FenwickTree(int n) {
        size = n + 2;
        tree.assign(size, 0);
    }

    void update(int idx, int delta) {
        for (; idx < size; idx += idx & -idx)
            tree[idx] += delta;
    }

    int query(int idx) {
        int res = 0;
        for (; idx > 0; idx -= idx & -idx)
            res += tree[idx];
        return res;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<tuple<char, int, int>> queries(m);
    vector<int> coords;

    for (int i = 0; i < m; ++i) {
        char type;
        int a, b = 0;
        cin >> type;
        if (type == 'P') {
            cin >> a >> b;
            queries[i] = {type, a, b};
            coords.push_back(a);
            coords.push_back(b);
        } else if (type == 'M') {
            cin >> a >> b;
            queries[i] = {type, a, b};
        } else if (type == 'B') {
            cin >> a;
            queries[i] = {type, a, b};
            coords.push_back(a);
        }
    }

    // Coordinate compression
    sort(coords.begin(), coords.end());
    coords.erase(unique(coords.begin(), coords.end()), coords.end());
    auto compress = [&](int x) {
        return lower_bound(coords.begin(), coords.end(), x) - coords.begin() + 1;
    };

    FenwickTree ft(coords.size());

    // To handle the systems, we'll store their current [u, v] ranges.
    vector<pair<int, int>> systems;
    systems.reserve(m); // Reserve space for efficiency

    for (auto &q : queries) {
        char type = get<0>(q);
        if (type == 'P') {
            int u = get<1>(q);
            int v = get<2>(q);
            systems.emplace_back(u, v);
            int cu = compress(u);
            int cv = compress(v);
            ft.update(cu, 1);
            ft.update(cv + 1, -1);
        } else if (type == 'M') {
            int i = get<1>(q) - 1; // Convert to 0-based index
            int d = get<2>(q);
            auto &[u, v] = systems[i];
            // Remove old range
            int cu = compress(u);
            int cv = compress(v);
            ft.update(cu, -1);
            ft.update(cv + 1, 1);
            // Update to new range
            u += d;
            v += d;
            cu = compress(u);
            cv = compress(v);
            ft.update(cu, 1);
            ft.update(cv + 1, -1);
        } else if (type == 'B') {
            int x = get<1>(q);
            int cx = compress(x);
            cout << ft.query(cx) << '\n';
        }
    }

    return 0;
}
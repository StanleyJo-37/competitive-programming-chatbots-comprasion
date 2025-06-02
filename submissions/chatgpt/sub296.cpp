#include <bits/stdc++.h>
using namespace std;

// Constants
const int MAXN = 100005;
const int LOGN = 17; // since 2^17 > 1e5
const int MAXA = 10; // a <= 10

// Data structures for the tree
vector<int> tree[MAXN];

// For HLD
int parent[MAXN], depth[MAXN], heavy[MAXN], head[MAXN], pos[MAXN], subsize[MAXN];
int cur_pos = 0;

// For LCA
int up[MAXN][LOGN];

// For people in each city
vector<int> people_in_city[MAXN];

// For segment tree
vector<int> segtree[4 * MAXN];

// DFS to compute sizes and heavy child
void dfs(int v, int p) {
    parent[v] = p;
    subsize[v] = 1;
    heavy[v] = -1;
    for (int u : tree[v]) {
        if (u == p) continue;
        depth[u] = depth[v] + 1;
        dfs(u, v);
        subsize[v] += subsize[u];
        if (heavy[v] == -1 || subsize[u] > subsize[heavy[v]])
            heavy[v] = u;
    }
}

// Decompose the tree and assign positions
void decompose(int v, int h) {
    head[v] = h;
    pos[v] = cur_pos++;
    // Sort people in city and keep only up to MAXA smallest IDs
    sort(people_in_city[v].begin(), people_in_city[v].end());
    if (people_in_city[v].size() > MAXA)
        people_in_city[v].resize(MAXA);
    if (heavy[v] != -1)
        decompose(heavy[v], h);
    for (int u : tree[v]) {
        if (u != parent[v] && u != heavy[v])
            decompose(u, u);
    }
}

// Build segment tree
void build(int node, int l, int r, vector<vector<int>>& city_people) {
    if (l == r) {
        segtree[node] = city_people[l];
        return;
    }
    int mid = (l + r) / 2;
    build(node * 2, l, mid, city_people);
    build(node * 2 + 1, mid + 1, r, city_people);
    // Merge two sorted lists, keep only up to MAXA smallest
    segtree[node].resize(0);
    int i = 0, j = 0;
    while ((i < segtree[node * 2].size() || j < segtree[node * 2 + 1].size()) && segtree[node].size() < MAXA) {
        if (j == segtree[node * 2 + 1].size() || (i < segtree[node * 2].size() && segtree[node * 2][i] < segtree[node * 2 + 1][j])) {
            segtree[node].push_back(segtree[node * 2][i++]);
        } else {
            segtree[node].push_back(segtree[node * 2 + 1][j++]);
        }
    }
}

// Query segment tree for range [ql, qr]
vector<int> query(int node, int l, int r, int ql, int qr) {
    if (qr < l || r < ql) return {};
    if (ql <= l && r <= qr) return segtree[node];
    int mid = (l + r) / 2;
    vector<int> left = query(node * 2, l, mid, ql, qr);
    vector<int> right = query(node * 2 + 1, mid + 1, r, ql, qr);
    // Merge left and right, keep only up to MAXA smallest
    vector<int> res;
    int i = 0, j = 0;
    while ((i < left.size() || j < right.size()) && res.size() < MAXA) {
        if (j == right.size() || (i < left.size() && left[i] < right[j])) {
            res.push_back(left[i++]);
        } else {
            res.push_back(right[j++]);
        }
    }
    return res;
}

// Preprocess for LCA (binary lifting)
void preprocess_lca(int n) {
    for (int v = 1; v <= n; ++v)
        up[v][0] = parent[v];
    for (int k = 1; k < LOGN; ++k) {
        for (int v = 1; v <= n; ++v) {
            if (up[v][k - 1] != -1)
                up[v][k] = up[up[v][k - 1]][k - 1];
            else
                up[v][k] = -1;
        }
    }
}

// LCA query
int lca(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);
    for (int k = LOGN - 1; k >= 0; --k) {
        if (up[u][k] != -1 && depth[up[u][k]] >= depth[v])
            u = up[u][k];
    }
    if (u == v) return u;
    for (int k = LOGN - 1; k >= 0; --k) {
        if (up[u][k] != -1 && up[u][k] != up[v][k]) {
            u = up[u][k];
            v = up[v][k];
        }
    }
    return parent[u];
}

// Query path from u to v (inclusive), collect up to a smallest IDs
vector<int> query_path(int u, int v, int a, int n) {
    vector<int> res;
    while (head[u] != head[v]) {
        if (depth[head[u]] < depth[head[v]]) swap(u, v);
        vector<int> tmp = query(1, 0, n - 1, pos[head[u]], pos[u]);
        // Merge tmp into res, keep only up to a smallest
        vector<int> merged;
        int i = 0, j = 0;
        while ((i < res.size() || j < tmp.size()) && merged.size() < a) {
            if (j == tmp.size() || (i < res.size() && res[i] < tmp[j])) {
                merged.push_back(res[i++]);
            } else {
                merged.push_back(tmp[j++]);
            }
        }
        res = merged;
        u = parent[head[u]];
    }
    if (depth[u] < depth[v]) swap(u, v);
    vector<int> tmp = query(1, 0, n - 1, pos[v], pos[u]);
    // Merge tmp into res, keep only up to a smallest
    vector<int> merged;
    int i = 0, j = 0;
    while ((i < res.size() || j < tmp.size()) && merged.size() < a) {
        if (j == tmp.size() || (i < res.size() && res[i] < tmp[j])) {
            merged.push_back(res[i++]);
        } else {
            merged.push_back(tmp[j++]);
        }
    }
    res = merged;
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m, q;
    cin >> n >> m >> q;

    // Read tree edges
    for (int i = 0; i < n - 1; ++i) {
        int v, u;
        cin >> v >> u;
        tree[v].push_back(u);
        tree[u].push_back(v);
    }

    // Read people and their cities
    for (int i = 1; i <= m; ++i) {
        int c;
        cin >> c;
        people_in_city[c].push_back(i);
    }

    // Prepare for HLD and LCA
    depth[1] = 0;
    dfs(1, -1);
    cur_pos = 0;
    decompose(1, 1);

    // Prepare city_people for segment tree
    vector<vector<int>> city_people(n);
    for (int v = 1; v <= n; ++v) {
        city_people[pos[v]] = people_in_city[v];
    }

    // Build segment tree
    build(1, 0, n - 1, city_people);

    // Preprocess LCA
    preprocess_lca(n);

    // Answer queries
    while (q--) {
        int v, u, a;
        cin >> v >> u >> a;
        int w = lca(v, u);
        // Query path v->w and u->w, but w is included in both, so we need to avoid double counting
        vector<int> res1 = query_path(v, w, a, n);
        vector<int> res2 = query_path(u, w, a, n);
        // Merge res1 and res2, but remove one copy of w's people
        vector<int> w_people = query(1, 0, n - 1, pos[w], pos[w]);
        // Remove w_people from one of the lists
        // Remove w_people from res2
        vector<int> res2_no_w;
        int i = 0, j = 0;
        while (i < res2.size() && j < w_people.size()) {
            if (res2
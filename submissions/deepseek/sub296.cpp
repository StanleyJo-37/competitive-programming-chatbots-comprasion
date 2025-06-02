#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 5;
const int LOG = 20;

vector<int> adj[MAXN];
int parent[MAXN][LOG];
int depth[MAXN];
vector<int> people[MAXN]; // people in each city

// Binary lifting to compute LCA
void dfs(int u, int p) {
    parent[u][0] = p;
    for (int i = 1; i < LOG; ++i) {
        parent[u][i] = parent[parent[u][i-1]][i-1];
    }
    for (int v : adj[u]) {
        if (v != p) {
            depth[v] = depth[u] + 1;
            dfs(v, u);
        }
    }
}

int lca(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);
    for (int i = LOG - 1; i >= 0; --i) {
        if (depth[u] - (1 << i) >= depth[v]) {
            u = parent[u][i];
        }
    }
    if (u == v) return u;
    for (int i = LOG - 1; i >= 0; --i) {
        if (parent[u][i] != parent[v][i]) {
            u = parent[u][i];
            v = parent[v][i];
        }
    }
    return parent[u][0];
}

// Function to collect people along the path from u to v (including LCA)
vector<int> collect_people(int u, int v) {
    int ancestor = lca(u, v);
    vector<int> res;
    // Collect from u to ancestor
    while (u != ancestor) {
        for (int p : people[u]) {
            res.push_back(p);
        }
        u = parent[u][0];
    }
    // Collect from v to ancestor
    while (v != ancestor) {
        for (int p : people[v]) {
            res.push_back(p);
        }
        v = parent[v][0];
    }
    // Collect at ancestor
    for (int p : people[ancestor]) {
        res.push_back(p);
    }
    // Sort and return
    sort(res.begin(), res.end());
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, q;
    cin >> n >> m >> q;

    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Read people's cities
    for (int i = 1; i <= m; ++i) {
        int c;
        cin >> c;
        people[c].push_back(i);
    }

    // Sort people in each city to maintain increasing order
    for (int i = 1; i <= n; ++i) {
        sort(people[i].begin(), people[i].end());
    }

    // Preprocess LCA
    dfs(1, 0);

    // Process queries
    while (q--) {
        int v, u, a;
        cin >> v >> u >> a;
        vector<int> path_people = collect_people(v, u);
        int k = min((int)path_people.size(), a);
        cout << k;
        for (int i = 0; i < k; ++i) {
            cout << " " << path_people[i];
        }
        cout << "\n";
    }

    return 0;
}
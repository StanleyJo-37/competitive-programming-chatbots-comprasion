#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 5;
vector<int> adj[MAXN];
int parent[MAXN], depth[MAXN], size[MAXN];
vector<int> nodes_by_depth[MAXN];
int max_depth;

// Compute parent, depth, and size for each node using DFS
void dfs(int u, int p) {
    parent[u] = p;
    depth[u] = (p == -1) ? 0 : depth[p] + 1;
    size[u] = 1;
    max_depth = max(max_depth, depth[u]);
    nodes_by_depth[depth[u]].push_back(u);
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u);
            size[u] += size[v];
        }
    }
}

int solve() {
    int T;
    cin >> T;
    while (T--) {
        int n, k;
        cin >> n >> k;
        for (int i = 1; i <= n; ++i) {
            adj[i].clear();
            nodes_by_depth[i].clear();
        }
        for (int i = 0; i < n - 1; ++i) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        max_depth = 0;
        dfs(1, -1);

        // The idea is to find the minimal set S such that the smallest subtree containing S has at least k nodes.
        // The minimal size of S is the minimal number of leaves in the tree that when selected, their LCA-based subtree has size >= k.
        // The answer is the minimal number of leaves needed to cover a subtree of size >= k.
        // The optimal solution is to pick nodes from the deepest levels first, as they cover more nodes upwards.

        vector<int> leaves;
        for (int i = 1; i <= n; ++i) {
            if (adj[i].size() == 1 && i != 1) { // Leaf node (degree 1, except root if it's alone)
                leaves.push_back(i);
            }
        }
        if (n == 1) {
            leaves.push_back(1);
        }

        // Sort leaves by depth in descending order
        sort(leaves.begin(), leaves.end(), [&](int a, int b) {
            return depth[a] > depth[b];
        });

        if (k == 1) {
            cout << "1\n";
            continue;
        }

        // We need to find the minimal number of leaves such that the union of their paths to the root covers >= k nodes.
        // The approach is to greedily pick the deepest leaves first.
        int res = 0;
        set<int> covered;
        for (int leaf : leaves) {
            if ((int)covered.size() >= k) break;
            int u = leaf;
            while (u != -1 && covered.count(u) == 0) {
                covered.insert(u);
                u = parent[u];
            }
            res++;
        }
        cout << res << "\n";
    }
    return 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
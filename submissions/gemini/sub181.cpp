#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

vector<vector<int>> adj;
vector<int> depth;
vector<int> parent;
vector<int> sz;
vector<int> heavy;
vector<int> head;
vector<int> pos;
int cur_pos;

void dfs_sz(int v, int p, int d) {
    depth[v] = d;
    parent[v] = p;
    sz[v] = 1;
    int max_sz = 0;
    for (int u : adj[v]) {
        if (u == p) continue;
        dfs_sz(u, v, d + 1);
        sz[v] += sz[u];
        if (sz[u] > max_sz) {
            max_sz = sz[u];
            heavy[v] = u;
        }
    }
}

void dfs_hld(int v, int h) {
    head[v] = h;
    pos[v] = cur_pos++;
    if (heavy[v] != 0) {
        dfs_hld(heavy[v], h);
    }
    for (int u : adj[v]) {
        if (u == parent[v] || u == heavy[v]) continue;
        dfs_hld(u, u);
    }
}

int lca(int u, int v) {
    for (; head[u] != head[v]; v = parent[head[v]]) {
        if (depth[head[u]] > depth[head[v]]) {
            swap(u, v);
        }
    }
    if (depth[u] > depth[v]) {
        swap(u, v);
    }
    return u;
}

int dist(int u, int v) {
    int ancestor = lca(u, v);
    return depth[u] + depth[v] - 2 * depth[ancestor];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    while (T--) {
        int n, k;
        cin >> n >> k;

        adj.assign(n + 1, vector<int>());
        depth.assign(n + 1, 0);
        parent.assign(n + 1, 0);
        sz.assign(n + 1, 0);
        heavy.assign(n + 1, 0);
        head.assign(n + 1, 0);
        pos.assign(n + 1, 0);
        cur_pos = 0;

        for (int i = 0; i < n - 1; ++i) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        dfs_sz(1, 0, 0);
        dfs_hld(1, 1);

        int ans = 0;
        vector<bool> marked(n + 1, false);

        for (int i = n; i >= 1; --i) {
            if (marked[i]) continue;
            
            vector<int> path;
            int curr = i;
            while(curr != 0 && !marked[curr]) {
                path.push_back(curr);
                curr = parent[curr];
            }
            
            int already_marked_ancestor = curr; // This is the first marked node on the path to root, or 0 if none
            
            int start_node = -1;
            for(int j = 0; j < path.size(); ++j) {
                int node_on_path = path[j];
                int d = dist(node_on_path, i);
                if (already_marked_ancestor != 0) {
                    d = dist(node_on_path, i) + dist(already_marked_ancestor, node_on_path);
                }
                
                if (d + 1 >= k) {
                    start_node = node_on_path;
                    break;
                }
            }

            if (start_node == -1) { // No node on path forms a k-subtree with i and its marked ancestors
                ans++;
                marked[i] = true;
            } else {
                ans++;
                int nodes_to_mark = k - 1;
                int current_node = i;
                while (nodes_to_mark > 0 && current_node != start_node) {
                    marked[current_node] = true;
                    current_node = parent[current_node];
                    nodes_to_mark--;
                }
                if (current_node == start_node) {
                    marked[current_node] = true;
                }
            }
        }
        cout << ans << endl;
    }
    return 0;
}
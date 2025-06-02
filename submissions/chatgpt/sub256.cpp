#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
using namespace std;

// Maximum number of cities
const int MAXN = 205;

vector<int> adj[MAXN]; // Adjacency list for the tree
int n; // Number of cities

// For each pair of nodes (u, v), we will compute the maximum path length in the subtree rooted at u, excluding the subtree going towards v
int dp[MAXN][MAXN]; // dp[u][v] = max path length in subtree rooted at u, excluding the edge to v

// Used to avoid recomputation
bool vis[MAXN][MAXN];

// DFS to compute dp[u][p] = max path length in subtree rooted at u, excluding the edge to p
int dfs(int u, int p) {
    if (vis[u][p]) return dp[u][p];
    vis[u][p] = true;
    int res = 0;
    for (int v : adj[u]) {
        if (v == p) continue;
        // For each child, take the max path length from u to the deepest leaf in that subtree
        res = max(res, 1 + dfs(v, u));
    }
    dp[u][p] = res;
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    // Read input
    cin >> n;
    for (int i = 1; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    // Precompute all dp[u][p]
    memset(vis, 0, sizeof(vis));
    for (int u = 1; u <= n; ++u) {
        for (int v : adj[u]) {
            dfs(u, v);
        }
    }

    int ans = 0;

    // For every edge (u, v), consider removing it, and compute the longest path in each of the two resulting trees
    for (int u = 1; u <= n; ++u) {
        for (int v : adj[u]) {
            if (u < v) { // To avoid double counting edges
                // The two trees are:
                // - One rooted at u, excluding v
                // - One rooted at v, excluding u
                int len1 = dfs(u, v);
                int len2 = dfs(v, u);
                ans = max(ans, len1 * len2);
            }
        }
    }

    cout << ans << '\n';
    return 0;
}
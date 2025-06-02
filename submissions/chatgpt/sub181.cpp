#include <bits/stdc++.h>
using namespace std;

// For fast input
ios_base::sync_with_stdio(false);
cin.tie(nullptr);

// Function to find the diameter of the tree and return the path (nodes on the diameter)
vector<int> get_diameter_path(const vector<vector<int>>& adj, int n) {
    // First BFS to find one endpoint of the diameter
    vector<int> dist(n+1, -1);
    queue<int> q;
    q.push(1);
    dist[1] = 0;
    int farthest = 1;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
                if (dist[v] > dist[farthest]) farthest = v;
            }
        }
    }
    // Second BFS from farthest to get the other endpoint and the path
    vector<int> parent(n+1, -1);
    dist.assign(n+1, -1);
    q.push(farthest);
    dist[farthest] = 0;
    int other = farthest;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                parent[v] = u;
                q.push(v);
                if (dist[v] > dist[other]) other = v;
            }
        }
    }
    // Reconstruct the path from 'other' to 'farthest'
    vector<int> path;
    int cur = other;
    while (cur != -1) {
        path.push_back(cur);
        cur = parent[cur];
    }
    reverse(path.begin(), path.end());
    return path;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        int n, k;
        cin >> n >> k;
        vector<vector<int>> adj(n+1);
        for (int i = 0; i < n-1; ++i) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        // If k == 1, any single node is a good subset
        if (k == 1) {
            cout << 1 << '\n';
            continue;
        }
        // If k == n, the only good subset is the whole tree (need all nodes)
        if (k == n) {
            cout << n << '\n';
            continue;
        }
        // Find the diameter path of the tree
        vector<int> diam_path = get_diameter_path(adj, n);
        int diam_len = diam_path.size();
        // The minimal subtree containing any set of m nodes on the diameter path is at least (m-1) + 1 = m nodes
        // But the minimal subtree containing m nodes on the diameter path is the path from the first to the last, which is (pos_last - pos_first + 1)
        // To get a subtree of size at least k, we need to pick m nodes such that the minimal subtree containing them is at least k
        // The best is to pick the two endpoints of a path of length (k-1), i.e., pick two nodes at distance (k-1) on the diameter
        // So, the minimal size of a good subset is the minimal number of nodes such that the minimal subtree containing them is at least k
        // For a path, picking the two endpoints at distance (k-1) gives a subtree of size k
        // So, answer is 2 if the diameter is at least (k-1)
        if (diam_len >= k) {
            cout << 2 << '\n';
            continue;
        }
        // Otherwise, we need to pick more nodes. For a star, for example, we need to pick k nodes.
        // In general, the answer is the minimal number m such that the minimal subtree containing any m nodes is at least k
        // For a tree, the minimal subtree containing m nodes is at least (max distance between any two of them) + 1
        // So, for general trees, the answer is the minimal m such that the minimal subtree containing any m nodes is at least k
        // For a path, m=2 is enough if diameter >= k-1, otherwise m=k
        // For a star, m=k
        // So, in general, answer is k if diameter < k-1, else 2
        cout << k << '\n';
    }
    return 0;
}
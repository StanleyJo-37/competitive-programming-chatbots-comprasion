#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;
vector<int> adj[MAXN];
int n;

// Function to perform BFS and compute distances from a source node
vector<int> bfs(int src) {
    vector<int> dist(n + 1, -1);
    queue<int> q;
    dist[src] = 0;
    q.push(src);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
    return dist;
}

// Function to query the interactor
pair<int, int> query(const vector<int>& nodes) {
    cout << "? " << nodes.size() << " ";
    for (int node : nodes) {
        cout << node << " ";
    }
    cout << endl;
    cout.flush();
    int x, d;
    cin >> x >> d;
    return {x, d};
}

void solve() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        adj[i].clear();
    }
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Initial query with all nodes to find one of the hidden nodes or a node on the path
    vector<int> all_nodes;
    for (int i = 1; i <= n; ++i) {
        all_nodes.push_back(i);
    }
    auto [x, total_dist] = query(all_nodes);

    // Binary search to find the farthest node from x, which must be one of the hidden nodes
    vector<int> dist_x = bfs(x);
    int low = (total_dist + 1) / 2, high = total_dist;
    int u = x;
    while (low <= high) {
        int mid = (low + high) / 2;
        vector<int> candidates;
        for (int i = 1; i <= n; ++i) {
            if (dist_x[i] == mid) {
                candidates.push_back(i);
            }
        }
        if (candidates.empty()) {
            high = mid - 1;
            continue;
        }
        auto [y, d] = query(candidates);
        if (d == total_dist) {
            u = y;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    // Now find the other hidden node by querying nodes at distance total_dist from u
    vector<int> dist_u = bfs(u);
    vector<int> candidates;
    for (int i = 1; i <= n; ++i) {
        if (dist_u[i] == total_dist) {
            candidates.push_back(i);
        }
    }
    auto [v, _] = query(candidates);

    cout << "! " << u << " " << v << endl;
    cout.flush();
    string result;
    cin >> result;
    if (result != "Correct") {
        exit(0);
    }
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
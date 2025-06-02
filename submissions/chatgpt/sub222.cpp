#include <bits/stdc++.h>
using namespace std;

// Fast IO
#define endl '\n'

// Tree structure
vector<vector<int>> tree;
int n;

// Query function: sends a query to the interactor and receives the response
pair<int, int> query(const vector<int>& nodes) {
    cout << "? " << nodes.size();
    for (int x : nodes) cout << " " << x;
    cout << endl;
    cout.flush();
    int x, d;
    cin >> x >> d;
    if (x == -1 && d == -1) exit(0); // Invalid query, terminate
    return {x, d};
}

// BFS to get distances from a source node to all other nodes
vector<int> bfs(int src) {
    vector<int> dist(n + 1, -1);
    queue<int> q;
    dist[src] = 0;
    q.push(src);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : tree[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
    return dist;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        cin >> n;
        tree.assign(n + 1, vector<int>());
        for (int i = 1; i < n; ++i) {
            int u, v;
            cin >> u >> v;
            tree[u].push_back(v);
            tree[v].push_back(u);
        }

        // 1. Query all nodes to get a node x0 and the sum of distances d0
        vector<int> all_nodes;
        for (int i = 1; i <= n; ++i) all_nodes.push_back(i);
        auto [x0, d0] = query(all_nodes);

        // 2. BFS from x0 to get distances to all nodes
        vector<int> dist = bfs(x0);

        // 3. For each possible distance, collect nodes at that distance
        vector<vector<int>> nodes_at_dist(n + 1);
        for (int i = 1; i <= n; ++i) {
            if (dist[i] >= 0) nodes_at_dist[dist[i]].push_back(i);
        }

        // 4. Binary search on distance to find one of the hidden nodes
        int l = 0, r = n;
        int found_dist = -1, found_node = -1;
        while (l <= r) {
            int mid = (l + r) / 2;
            if (nodes_at_dist[mid].empty()) {
                r = mid - 1;
                continue;
            }
            auto [x, d] = query(nodes_at_dist[mid]);
            // If d0 - 2*mid == d, then one of the hidden nodes is at distance mid from x0
            if (d == d0 - 2 * mid) {
                found_dist = mid;
                found_node = x;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }

        // 5. found_node is one of the hidden nodes (let's call it s)
        int s = found_node;

        // 6. BFS from s to get distances
        vector<int> dist_s = bfs(s);

        // 7. The other hidden node f is at distance d0 - found_dist from s
        int target_dist = d0 - found_dist;
        vector<int> candidates;
        for (int i = 1; i <= n; ++i) {
            if (i != s && dist_s[i] == target_dist) candidates.push_back(i);
        }

        // 8. If only one candidate, that's the answer. If multiple, query to find the correct one.
        int f;
        if (candidates.size() == 1) {
            f = candidates[0];
        } else {
            // Query all candidates, the one with sum of distances == d0 is the other hidden node
            auto [x, d] = query(candidates);
            f = x;
        }

        // 9. Output the answer
        cout << "! " << s << " " << f << endl;
        cout.flush();

        // 10. Read verdict
        string verdict;
        cin >> verdict;
        if (verdict != "Correct") exit(0);
    }
    return 0;
}
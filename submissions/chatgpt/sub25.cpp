#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
using namespace std;

// Function to check if u and v are connected in the subgraph of a given color using BFS
bool is_connected(const vector<vector<int>>& adj, int u, int v, int n) {
    vector<bool> visited(n + 1, false);
    queue<int> q;
    q.push(u);
    visited[u] = true;
    while (!q.empty()) {
        int curr = q.front(); q.pop();
        if (curr == v) return true;
        for (int neighbor : adj[curr]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
    return false;
}

int main() {
    int n, m;
    cin >> n >> m;

    // Map from color to adjacency list for that color
    map<int, vector<vector<int>>> color_adj;
    set<int> colors; // To keep track of all colors present

    // Read edges and build adjacency lists for each color
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        colors.insert(c);
        if (color_adj.find(c) == color_adj.end()) {
            color_adj[c] = vector<vector<int>>(n + 1);
        }
        color_adj[c][a].push_back(b);
        color_adj[c][b].push_back(a);
    }

    int q;
    cin >> q;
    vector<pair<int, int>> queries(q);
    for (int i = 0; i < q; ++i) {
        cin >> queries[i].first >> queries[i].second;
    }

    // For each query, count the number of colors for which u and v are connected
    for (int i = 0; i < q; ++i) {
        int u = queries[i].first;
        int v = queries[i].second;
        int count = 0;
        for (int c : colors) {
            // For each color, check if u and v are connected in that color's subgraph
            if (is_connected(color_adj[c], u, v, n)) {
                ++count;
            }
        }
        cout << count << endl;
    }
    return 0;
}
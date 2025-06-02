#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    ios::sync_with_stdio(false); // Fast IO
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    // Adjacency list for the graph
    vector<vector<int>> adj(n + 1);
    // In-degree array
    vector<int> indeg(n + 1, 0);

    // Read edges and build the graph
    for (int i = 0; i < m; ++i) {
        int v, u;
        cin >> v >> u;
        adj[v].push_back(u);
        indeg[u]++;
    }

    // Min-heap to always pick the smallest available node (lex smallest)
    priority_queue<int, vector<int>, greater<int>> pq;

    // Push all nodes with in-degree 0
    for (int i = 1; i <= n; ++i) {
        if (indeg[i] == 0) pq.push(i);
    }

    // Result array: label[i] = label assigned to vertex i
    vector<int> label(n + 1, 0);
    int curr_label = 1;

    // Kahn's algorithm with min-heap for lex smallest topological order
    while (!pq.empty()) {
        int v = pq.top();
        pq.pop();
        label[v] = curr_label++; // Assign the next smallest label

        // Decrease in-degree of all neighbors
        for (int u : adj[v]) {
            indeg[u]--;
            if (indeg[u] == 0) pq.push(u);
        }
    }

    // Output the labels in order of vertices 1..n
    for (int i = 1; i <= n; ++i) {
        cout << label[i] << " ";
    }
    cout << "\n";
    return 0;
}
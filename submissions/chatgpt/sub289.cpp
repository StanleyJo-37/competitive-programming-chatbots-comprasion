#include <iostream>
#include <vector>
#include <queue>
#include <limits>
using namespace std;

int main() {
    int T;
    cin >> T; // Read number of test cases
    while (T--) {
        int N, M;
        cin >> N >> M; // Read number of nodes and edges

        // Adjacency list: each node has a vector of pairs (neighbor, cost)
        vector<vector<pair<int, int>>> adj(N + 1);

        // Read all edges
        for (int i = 0; i < M; ++i) {
            int A, B, C;
            cin >> A >> B >> C;
            adj[A].emplace_back(B, C);
            adj[B].emplace_back(A, C); // Since the roads are two-way
        }

        // Dijkstra's algorithm to find shortest distances and count paths
        vector<int> dist(N + 1, numeric_limits<int>::max()); // Shortest distance to each node
        vector<int> ways(N + 1, 0); // Number of shortest paths to each node

        // Min-heap priority queue: (distance, node)
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        dist[1] = 0; // Start from node 1
        ways[1] = 1; // Only one way to start at node 1
        pq.emplace(0, 1);

        while (!pq.empty()) {
            int d = pq.top().first;
            int u = pq.top().second;
            pq.pop();

            // If we already found a better way, skip
            if (d > dist[u]) continue;

            // Explore neighbors
            for (auto &edge : adj[u]) {
                int v = edge.first;
                int cost = edge.second;
                if (dist[v] > dist[u] + cost) {
                    // Found a shorter path to v
                    dist[v] = dist[u] + cost;
                    ways[v] = ways[u];
                    pq.emplace(dist[v], v);
                } else if (dist[v] == dist[u] + cost) {
                    // Found another shortest path to v
                    ways[v] += ways[u];
                }
            }
        }

        // Output the number of shortest paths from 1 to N
        cout << ways[N] << endl;
    }
    return 0;
}
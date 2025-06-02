#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <cstring>
using namespace std;

void solve() {
    int T;
    cin >> T;
    while (T--) {
        int N, M;
        cin >> N >> M;
        
        // Adjacency list to store the graph
        vector<vector<pair<int, int>>> adj(N + 1);
        for (int i = 0; i < M; ++i) {
            int A, B, C;
            cin >> A >> B >> C;
            adj[A].emplace_back(B, C);
            adj[B].emplace_back(A, C);
        }
        
        // Dijkstra's algorithm to find shortest distances and count paths
        vector<int> dist(N + 1, INT_MAX);
        vector<int> count(N + 1, 0);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        
        dist[1] = 0;
        count[1] = 1;
        pq.push({0, 1});
        
        while (!pq.empty()) {
            int u = pq.top().second;
            int current_dist = pq.top().first;
            pq.pop();
            
            if (current_dist > dist[u]) continue;
            
            for (auto &edge : adj[u]) {
                int v = edge.first;
                int weight = edge.second;
                
                if (dist[v] > dist[u] + weight) {
                    dist[v] = dist[u] + weight;
                    count[v] = count[u];
                    pq.push({dist[v], v});
                } else if (dist[v] == dist[u] + weight) {
                    count[v] += count[u];
                }
            }
        }
        
        cout << count[N] << endl;
    }
}

int main() {
    solve();
    return 0;
}
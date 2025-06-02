#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <limits>

using namespace std;

const long long INF = numeric_limits<long long>::max();

struct State {
    int u;
    long long dist;

    bool operator>(const State& other) const {
        return dist > other.dist;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    while (T--) {
        int N, M;
        cin >> N >> M;

        vector<vector<pair<int, int>>> adj(N + 1);
        for (int i = 0; i < M; ++i) {
            int u, v, c;
            cin >> u >> v >> c;
            adj[u].push_back({v, c});
            adj[v].push_back({u, c});
        }

        vector<long long> dist(N + 1, INF);
        vector<long long> paths(N + 1, 0);
        priority_queue<State, vector<State>, greater<State>> pq;

        dist[1] = 0;
        paths[1] = 1;
        pq.push({1, 0});

        while (!pq.empty()) {
            State current = pq.top();
            pq.pop();

            int u = current.u;
            long long d = current.dist;

            if (d > dist[u]) {
                continue;
            }

            for (auto& edge : adj[u]) {
                int v = edge.first;
                int weight = edge.second;

                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    paths[v] = paths[u];
                    pq.push({v, dist[v]});
                } else if (dist[u] + weight == dist[v]) {
                    paths[v] += paths[u];
                }
            }
        }
        cout << paths[N] << endl;
    }

    return 0;
}
#include <bits/stdc++.h>
using namespace std;

vector<int> solve(int n, int m, vector<pair<int, int>>& edges) {
    vector<vector<int>> adj(n + 1);
    vector<int> outDegree(n + 1, 0);
    for (auto& edge : edges) {
        int v = edge.first, u = edge.second;
        adj[u].push_back(v); // Reverse the edges for topological sort
        outDegree[v]++;
    }

    priority_queue<int> pq; // Max-heap to pick largest available label
    for (int i = 1; i <= n; ++i) {
        if (outDegree[i] == 0) {
            pq.push(i);
        }
    }

    vector<int> label(n + 1);
    int currentLabel = n;
    while (!pq.empty()) {
        int u = pq.top();
        pq.pop();
        label[u] = currentLabel--;
        for (int v : adj[u]) {
            outDegree[v]--;
            if (outDegree[v] == 0) {
                pq.push(v);
            }
        }
    }

    vector<int> result(n);
    for (int i = 1; i <= n; ++i) {
        result[i - 1] = label[i];
    }
    return result;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> edges(m);
    for (int i = 0; i < m; ++i) {
        cin >> edges[i].first >> edges[i].second;
    }

    vector<int> result = solve(n, m, edges);
    for (int num : result) {
        cout << num << " ";
    }
    cout << "\n";

    return 0;
}
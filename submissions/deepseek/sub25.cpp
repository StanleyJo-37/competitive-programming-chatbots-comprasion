#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

// Disjoint Set Union (DSU) data structure with path compression and union by rank
class DSU {
private:
    vector<int> parent;
    vector<int> rank;

public:
    DSU(int n) {
        parent.resize(n + 1);
        rank.resize(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            parent[i] = i;
        }
    }

    int find(int u) {
        if (parent[u] != u) {
            parent[u] = find(parent[u]); // Path compression
        }
        return parent[u];
    }

    void unite(int u, int v) {
        int rootU = find(u);
        int rootV = find(v);
        if (rootU != rootV) {
            // Union by rank
            if (rank[rootU] > rank[rootV]) {
                parent[rootV] = rootU;
            } else if (rank[rootU] < rank[rootV]) {
                parent[rootU] = rootV;
            } else {
                parent[rootV] = rootU;
                rank[rootU]++;
            }
        }
    }
};

int main() {
    int n, m;
    cin >> n >> m;

    // We'll process each color separately. For each color, we'll build a DSU and unite the nodes connected by edges of that color.
    // Then, for each query (u, v), we'll check for how many colors u and v are in the same set in the DSU for that color.

    // First, collect all unique colors and the edges for each color.
    unordered_set<int> colors;
    vector<pair<int, int>> edges_by_color[m + 1]; // 1-based color indexing

    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        colors.insert(c);
        edges_by_color[c].emplace_back(a, b);
    }

    int q;
    cin >> q;

    while (q--) {
        int u, v;
        cin >> u >> v;
        int answer = 0;

        // For each color, check if u and v are connected in the DSU built for that color.
        for (int color : colors) {
            DSU dsu(n);
            // Unite all edges of this color
            for (auto &edge : edges_by_color[color]) {
                dsu.unite(edge.first, edge.second);
            }
            if (dsu.find(u) == dsu.find(v)) {
                answer++;
            }
        }

        cout << answer << endl;
    }

    return 0;
}
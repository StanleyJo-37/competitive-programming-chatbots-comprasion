#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// This problem reduces to finding the size of the largest independent set in a graph
// constructed by the bubble sort process. The graph is a collection of paths (since
// each swap only connects two numbers, and each number is only swapped with its neighbors).
// The maximum independent set in a path of length k is ceil(k/2).
// So, we need to find all connected components (paths) and sum up their max independent set sizes.

// We use Union-Find (Disjoint Set Union) to find connected components efficiently.

const int MAXN = 100005;

int parent[MAXN], sz[MAXN];

// Find with path compression
int find(int x) {
    if (parent[x] != x) parent[x] = find(parent[x]);
    return parent[x];
}

// Union by size
void unite(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) return;
    if (sz[x] < sz[y]) swap(x, y);
    parent[y] = x;
    sz[x] += sz[y];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];

    // Initialize DSU
    for (int i = 1; i <= n; ++i) {
        parent[i] = i;
        sz[i] = 1;
    }

    // Simulate bubble sort and add edges as described
    vector<pair<int, int>> edges; // store edges to add to DSU
    vector<int> b = a; // work on a copy
    bool swapped = true;
    while (swapped) {
        swapped = false;
        for (int i = 0; i < n - 1; ++i) {
            if (b[i] > b[i + 1]) {
                // Add edge between b[i] and b[i+1]
                edges.emplace_back(b[i], b[i + 1]);
                swap(b[i], b[i + 1]);
                swapped = true;
            }
        }
    }

    // Add all edges to DSU
    for (auto &e : edges) {
        unite(e.first, e.second);
    }

    // Count the size of each component
    vector<int> comp_size(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        comp_size[find(i)]++;
    }

    // For each component, add ceil(size/2) to the answer
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        if (parent[i] == i && comp_size[i] > 0) {
            ans += (comp_size[i] + 1) / 2;
        }
    }

    cout << ans << '\n';
    return 0;
}
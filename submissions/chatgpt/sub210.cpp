#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// We need to find the size of the maximum independent set in the graph G
// constructed as described in the problem. The key observation is that
// the graph G is a collection of disjoint chains (paths), because each
// swap in bubble sort only connects two adjacent values, and each value
// is only swapped with its neighbors. Thus, the graph is a forest of paths.
//
// For a path of length L (L vertices), the maximum independent set size is
// ceil(L/2). So, we need to find all connected components (paths) in G,
// and sum up their maximum independent set sizes.
//
// To build G efficiently, we simulate bubble sort, but instead of actually
// sorting, we just record the edges that would be added during swaps.

const int MAXN = 100005;
vector<int> adj[MAXN]; // adjacency list for the graph
int parent[MAXN];      // for DSU (Disjoint Set Union)
int sz[MAXN];          // size of each component

// DSU find
int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);
    return parent[x];
}

// DSU union
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
    for (int &x : a) cin >> x;

    // Initialize DSU
    for (int i = 1; i <= n; ++i) {
        parent[i] = i;
        sz[i] = 1;
    }

    // Simulate bubble sort and build the graph
    bool swapped = true;
    while (swapped) {
        swapped = false;
        for (int i = 0; i < n - 1; ++i) {
            if (a[i] > a[i + 1]) {
                // Add edge between a[i] and a[i+1]
                adj[a[i]].push_back(a[i + 1]);
                adj[a[i + 1]].push_back(a[i]);
                unite(a[i], a[i + 1]);
                swap(a[i], a[i + 1]);
                swapped = true;
            }
        }
    }

    // Now, for each connected component (path), find its size
    // and sum up ceil(size/2) for all components.
    vector<bool> visited(n + 1, false);
    int answer = 0;

    for (int v = 1; v <= n; ++v) {
        if (!visited[v]) {
            // BFS/DFS to count the size of the component
            int cnt = 0;
            vector<int> stack = {v};
            visited[v] = true;
            while (!stack.empty()) {
                int u = stack.back();
                stack.pop_back();
                ++cnt;
                for (int w : adj[u]) {
                    if (!visited[w]) {
                        visited[w] = true;
                        stack.push_back(w);
                    }
                }
            }
            // For a path of length cnt, the max independent set is (cnt+1)/2
            answer += (cnt + 1) / 2;
        }
    }

    cout << answer << '\n';
    return 0;
}
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<vector<int>> tree(n + 1); // adjacency list, 1-based
    vector<int> parent(n + 1, 0); // parent of each node
    for (int i = 2; i <= n; ++i) {
        cin >> parent[i];
        tree[parent[i]].push_back(i);
    }

    vector<ll> s(n + 1); // s_v values, 1-based
    for (int i = 1; i <= n; ++i) {
        cin >> s[i];
    }

    vector<ll> a(n + 1, 0); // a_v values to restore

    // BFS to process nodes by depth (level order)
    queue<pair<int, int>> q; // (node, depth)
    q.push({1, 1});
    vector<int> depth(n + 1, 0);
    depth[1] = 1;

    while (!q.empty()) {
        int v = q.front().first;
        int d = q.front().second;
        q.pop();
        for (int u : tree[v]) {
            depth[u] = d + 1;
            q.push({u, d + 1});
        }
    }

    // For each node, process in BFS order
    queue<int> bfs;
    bfs.push(1);

    // For root
    if (s[1] == -1) {
        // s_1 must be given
        cout << -1 << '\n';
        return 0;
    }
    a[1] = s[1];

    while (!bfs.empty()) {
        int v = bfs.front();
        bfs.pop();

        for (int u : tree[v]) {
            // For even depth (h_u even), s[u] is erased (-1)
            if (s[u] == -1) {
                // We need to assign s[u] as small as possible, but at least s[v]
                // For all children of v at even depth, assign s[u] = min(s[w]) among all children
                // But we process one by one, so for each, assign s[u] = min(s[w]) among all children
                // To minimize sum, for all children at even depth, assign s[u] = min(s[w]) among all children
                // But since we process in BFS, we can process all children of v at once
                // So, we delay assignment for all children at even depth
                continue;
            }
            // For odd depth, s[u] is given
            // a[u] = s[u] - s[v]
            if (s[u] < s[v]) {
                cout << -1 << '\n';
                return 0;
            }
            a[u] = s[u] - s[v];
            bfs.push(u);
        }

        // Now, for all children of v at even depth, assign s[u] = min(s[w]) among all children
        vector<int> even_children;
        for (int u : tree[v]) {
            if (s[u] == -1) {
                even_children.push_back(u);
            }
        }
        if (!even_children.empty()) {
            // For all children at even depth, assign s[u] = min(s[w]) among all children
            // For each such child, its own children may have s[w] given (at odd depth)
            // For each u in even_children, find min_s = min(s[w]) for all children w of u
            for (int u : even_children) {
                ll min_s = 1e18;
                if (tree[u].empty()) {
                    // If u is a leaf, s[u] = s[v]
                    s[u] = s[v];
                } else {
                    // For all children w of u, s[w] must be given (since depth of w is odd)
                    for (int w : tree[u]) {
                        if (s[w] == -1) {
                            // Should not happen, as depth alternates
                            cout << -1 << '\n';
                            return 0;
                        }
                        min_s = min(min_s, s[w]);
                    }
                    if (min_s < s[v]) {
                        // Impossible, as s[u] >= s[v]
                        cout << -1 << '\n';
                        return 0;
                    }
                    s[u] = min_s;
                }
                a[u] = s[u] - s[v];
                if (a[u] < 0) {
                    cout << -1 << '\n';
                    return 0;
                }
                bfs.push(u);
            }
        }
    }

    ll total = 0;
    for (int i = 1; i <= n; ++i) {
        total += a[i];
    }
    cout << total << '\n';
    return 0;
}
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 3e5 + 5;

int parent[MAXN]; // Parent array for DSU
int ans[MAXN];    // Stores the answer for each knight

// Find operation for DSU with path compression
int find(int u) {
    if (parent[u] != u) {
        parent[u] = find(parent[u]);
    }
    return parent[u];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    // Initialize parent array: each knight is their own parent initially
    for (int i = 1; i <= n + 1; ++i) {
        parent[i] = i;
    }

    // Process each fight
    while (m--) {
        int l, r, x;
        cin >> l >> r >> x;

        // Find the first knight in [l, r] that hasn't been processed yet
        int current = find(l);
        while (current <= r) {
            if (current != x) {
                ans[current] = x; // Mark that 'x' defeated 'current'
                parent[current] = current + 1; // Move to next knight
            } else {
                current = find(current + 1); // Skip the winner
            }
            current = find(current); // Find next unprocessed knight
        }
    }

    // Output the results
    for (int i = 1; i <= n; ++i) {
        cout << ans[i] << " ";
    }
    cout << "\n";

    return 0;
}
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    
    vector<int> adj(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        adj[u] |= (1 << v);
        adj[v] |= (1 << u);
    }
    
    // Each node is friend with itself
    for (int i = 0; i < n; ++i) {
        adj[i] |= (1 << i);
    }
    
    // DP[mask] = minimum steps to achieve 'mask' where all bits are connected
    vector<int> dp(1 << n, INT_MAX);
    vector<pair<int, int>> parent(1 << n, {-1, -1}); // {previous mask, selected node}
    
    // Initialize for single nodes
    for (int i = 0; i < n; ++i) {
        dp[1 << i] = 0;
    }
    
    for (int mask = 1; mask < (1 << n); ++mask) {
        if (dp[mask] == INT_MAX) continue;
        
        // For each node in the current mask, try to expand
        for (int i = 0; i < n; ++i) {
            if (!(mask & (1 << i))) continue;
            
            int new_mask = mask | adj[i];
            if (dp[new_mask] > dp[mask] + 1) {
                dp[new_mask] = dp[mask] + 1;
                parent[new_mask] = {mask, i};
            }
        }
    }
    
    int full_mask = (1 << n) - 1;
    cout << dp[full_mask] << endl;
    
    // Reconstruct the sequence
    vector<int> steps;
    int current = full_mask;
    while (parent[current].first != -1) {
        steps.push_back(parent[current].second + 1); // convert to 1-based
        current = parent[current].first;
    }
    reverse(steps.begin(), steps.end());
    
    for (int node : steps) {
        cout << node << " ";
    }
    cout << endl;
    
    return 0;
}
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int>> adj;
vector<bool> visited;
int max_len;

// DFS to find the longest path starting from node u
int dfs(int u) {
    visited[u] = true;
    int first_max = 0, second_max = 0;
    for (int v : adj[u]) {
        if (!visited[v]) {
            int current = dfs(v);
            if (current > first_max) {
                second_max = first_max;
                first_max = current;
            } else if (current > second_max) {
                second_max = current;
            }
        }
    }
    // Update the global maximum path length found so far
    max_len = max(max_len, first_max + second_max);
    return first_max + 1;
}

int main() {
    int n;
    cin >> n;
    adj.resize(n + 1);
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    int result = 0;
    // Iterate over all possible edges to split the tree into two subtrees
    for (int u = 1; u <= n; ++u) {
        for (int v : adj[u]) {
            if (v > u) { // To avoid processing the same edge twice
                // Split the tree by removing edge u-v
                visited.assign(n + 1, false);
                visited[v] = true; // Block the path to v from u
                max_len = 0;
                dfs(u);
                int len1 = max_len;

                visited.assign(n + 1, false);
                visited[u] = true; // Block the path to u from v
                max_len = 0;
                dfs(v);
                int len2 = max_len;

                result = max(result, len1 * len2);
            }
        }
    }
    cout << result << endl;
    return 0;
}
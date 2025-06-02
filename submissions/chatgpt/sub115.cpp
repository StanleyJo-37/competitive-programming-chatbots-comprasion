#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
using namespace std;

// Movement cost matrix: move_cost[from][to]
int move_cost[4][4] = {
    {0, 0, 0, 0}, // 0-index not used
    {0, 0, 1, 2}, // from 1 to 1,2,3
    {0, 2, 0, 1}, // from 2 to 1,2,3
    {0, 1, 2, 0}  // from 3 to 1,2,3
};

int main() {
    int n;
    cin >> n;
    vector<int> c(n); // c[i]: computer for part i (1-based)
    for (int i = 0; i < n; ++i) cin >> c[i];

    // Build dependency graph
    vector<vector<int>> adj(n); // adj[i]: list of parts that depend on i
    vector<int> indeg(n, 0);    // indeg[i]: number of prerequisites for part i
    for (int i = 0; i < n; ++i) {
        int k;
        cin >> k;
        for (int j = 0; j < k; ++j) {
            int a;
            cin >> a;
            --a; // convert to 0-based
            adj[a].push_back(i); // a must be done before i
            indeg[i]++;
        }
    }

    // Topological sort to get a valid order of completion
    vector<int> topo;
    queue<int> q;
    for (int i = 0; i < n; ++i)
        if (indeg[i] == 0) q.push(i);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        topo.push_back(u);
        for (int v : adj[u]) {
            indeg[v]--;
            if (indeg[v] == 0) q.push(v);
        }
    }
    // Now topo contains a valid topological order

    // dp[i][cur]: minimal time to finish all parts from position i in topo, starting at computer cur
    // cur in {1,2,3}
    vector<vector<int>> dp(n+1, vector<int>(4, INT_MAX));
    // Base case: after all parts, cost is 0
    for (int cur = 1; cur <= 3; ++cur) dp[n][cur] = 0;

    // For each position in topo, from last to first
    for (int i = n-1; i >= 0; --i) {
        int part = topo[i];
        int need = c[part]; // computer needed for this part
        // For each possible current computer
        for (int cur = 1; cur <= 3; ++cur) {
            // Move to 'need' computer if not already there, pay move cost
            int move = move_cost[cur][need];
            // 1 hour to complete the part
            // After this, we are at 'need' computer, so next dp[i+1][need]
            if (dp[i+1][need] != INT_MAX)
                dp[i][cur] = min(dp[i][cur], move + 1 + dp[i+1][need]);
        }
    }

    // The answer is the minimal dp[0][cur] for cur in {1,2,3}
    int ans = INT_MAX;
    for (int cur = 1; cur <= 3; ++cur)
        ans = min(ans, dp[0][cur]);
    cout << ans << endl;
    return 0;
}
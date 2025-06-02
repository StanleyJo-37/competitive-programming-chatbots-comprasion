#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

const int INF = INT_MAX;

int main() {
    int n;
    cin >> n;
    vector<int> c(n + 1); // Computer for each part (1-based)
    for (int i = 1; i <= n; ++i) {
        cin >> c[i];
    }

    vector<vector<int>> adj(n + 1); // Adjacency list for dependencies
    for (int i = 1; i <= n; ++i) {
        int k;
        cin >> k;
        adj[i].resize(k);
        for (int j = 0; j < k; ++j) {
            cin >> adj[i][j];
        }
    }

    // The problem is to find the minimal time to complete all parts, considering dependencies and movement costs.
    // We can model this as a topological sort problem where we process nodes in dependency order,
    // and for each node, we compute the minimal time to reach it from any of the three computers,
    // considering the time to move from the previous computer and the time to complete the part.

    // We'll use dynamic programming where dp[i][j] represents the minimal time to complete part i when ending at computer j.
    vector<vector<int>> dp(n + 1, vector<int>(4, INF)); // 1-based for parts, 1-3 for computers

    // The initial position can be any computer, so we need to find the best starting computer.
    // However, we need to process parts in topological order (dependencies first).

    // To process in topological order, we'll use a DFS-based approach to get the order.
    vector<int> order;
    vector<bool> visited(n + 1, false);

    // DFS for topological sort
    function<void(int)> dfs = [&](int u) {
        visited[u] = true;
        for (int v : adj[u]) {
            if (!visited[v]) {
                dfs(v);
            }
        }
        order.push_back(u);
    };

    for (int i = 1; i <= n; ++i) {
        if (!visited[i]) {
            dfs(i);
        }
    }

    // Now, process nodes in reverse order (since dependencies are pushed first)
    reverse(order.begin(), order.end());

    // Initialize dp for the first part in the order (no dependencies)
    for (int part : order) {
        if (adj[part].empty()) {
            // No dependencies, can start at any computer
            for (int comp = 1; comp <= 3; ++comp) {
                int time_to_move = 0; // Initial position can be any computer, no movement cost initially
                if (comp != c[part]) {
                    // Need to move to the correct computer
                    if (comp == 1) {
                        if (c[part] == 2) time_to_move = 1;
                        else if (c[part] == 3) time_to_move = 2;
                    } else if (comp == 2) {
                        if (c[part] == 1) time_to_move = 2;
                        else if (c[part] == 3) time_to_move = 1;
                    } else if (comp == 3) {
                        if (c[part] == 1) time_to_move = 1;
                        else if (c[part] == 2) time_to_move = 2;
                    }
                }
                dp[part][c[part]] = min(dp[part][c[part]], time_to_move + 1); // 1 hour to complete the part
            }
        } else {
            // Has dependencies, need to process them first
            for (int prev_comp = 1; prev_comp <= 3; ++prev_comp) {
                int max_prev_time = 0;
                for (int dep : adj[part]) {
                    int min_time = INF;
                    for (int dep_comp = 1; dep_comp <= 3; ++dep_comp) {
                        if (dp[dep][dep_comp] == INF) continue;
                        int move_time = 0;
                        if (dep_comp != prev_comp) {
                            if (dep_comp == 1) {
                                if (prev_comp == 2) move_time = 2;
                                else if (prev_comp == 3) move_time = 1;
                            } else if (dep_comp == 2) {
                                if (prev_comp == 1) move_time = 1;
                                else if (prev_comp == 3) move_time = 2;
                            } else if (dep_comp == 3) {
                                if (prev_comp == 1) move_time = 2;
                                else if (prev_comp == 2) move_time = 1;
                            }
                        }
                        min_time = min(min_time, dp[dep][dep_comp] + move_time);
                    }
                    max_prev_time = max(max_prev_time, min_time);
                }
                if (max_prev_time == INF) continue;
                int move_time = 0;
                if (prev_comp != c[part]) {
                    if (prev_comp == 1) {
                        if (c[part] == 2) move_time = 1;
                        else if (c[part] == 3) move_time = 2;
                    } else if (prev_comp == 2) {
                        if (c[part] == 1) move_time = 2;
                        else if (c[part] == 3) move_time = 1;
                    } else if (prev_comp == 3) {
                        if (c[part] == 1) move_time = 1;
                        else if (c[part] == 2) move_time = 2;
                    }
                }
                dp[part][c[part]] = min(dp[part][c[part]], max_prev_time + move_time + 1);
            }
        }
    }

    // The answer is the minimal time to complete all parts, ending at any computer
    int result = INF;
    for (int comp = 1; comp <= 3; ++comp) {
        result = min(result, dp[order.back()][comp]);
    }
    cout << result << endl;

    return 0;
}
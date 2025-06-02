#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

const int INF = 1e9;

int main() {
    // Optimize C++ standard streams for faster input/output.
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m; // Read the number of guests (n) and initial friendship pairs (m).

    // Adjacency matrix to represent the friendship graph.
    // adj[i][j] is true if i and j are friends.
    vector<vector<bool>> adj(n, vector<bool>(n, false));
    for (int i = 0; i < n; ++i) {
        adj[i][i] = true; // Everyone is friends with themselves.
    }

    // Read initial friendship pairs and populate the adjacency matrix.
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v; // Convert to 0-indexed.
        adj[u][v] = adj[v][u] = true; // Set friendship in both directions.
    }

    // dp[mask] will store the minimum number of steps to achieve a complete graph
    // where the current friendship graph is represented by the bitmask.
    // Each bit in the mask represents a pair of people (i, j).
    // The total number of pairs is n * (n - 1) / 2.
    // Let's create a mapping for pairs to bit indices.
    vector<pair<int, int>> pairs;
    vector<vector<int>> pair_to_idx(n, vector<int>(n));
    int pair_count = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            pair_to_idx[i][j] = pair_to_idx[j][i] = pair_count;
            pairs.push_back({i, j});
            pair_count++;
        }
    }

    // Calculate the initial state (mask) of friendships.
    // Each bit in the initial_mask corresponds to an existing friendship pair.
    int initial_mask = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (adj[i][j]) {
                initial_mask |= (1 << pair_to_idx[i][j]);
            }
        }
    }

    // The target mask represents a complete graph where all pairs are friends.
    int target_mask = (1 << pair_count) - 1;

    // Initialize DP array.
    // dp[mask] stores the minimum steps to reach the state represented by 'mask'.
    vector<int> dp(1 << pair_count, INF);
    // parent[mask] stores the previous mask in the shortest path to 'mask'.
    vector<int> parent_mask(1 << pair_count, -1);
    // chosen_guest[mask] stores the guest chosen to transition from parent_mask to 'mask'.
    vector<int> chosen_guest(1 << pair_count, -1);

    // BFS queue for state transitions.
    queue<int> q;

    // Start BFS from the initial friendship state.
    dp[initial_mask] = 0;
    q.push(initial_mask);

    int final_mask = -1; // To store the mask of the complete graph state.

    while (!q.empty()) {
        int current_mask = q.front();
        q.pop();

        // If we reached the target mask, we can stop early as BFS guarantees shortest path.
        if (current_mask == target_mask) {
            final_mask = current_mask;
            break;
        }

        // Try selecting each guest to perform introductions.
        for (int i = 0; i < n; ++i) {
            // Calculate the new friendship graph after guest 'i' introduces their friends.
            vector<vector<bool>> next_adj(n, vector<bool>(n, false));
            // Reconstruct the adjacency matrix from the current_mask.
            for (int k = 0; k < pair_count; ++k) {
                if ((current_mask >> k) & 1) {
                    next_adj[pairs[k].first][pairs[k].second] = true;
                    next_adj[pairs[k].second][pairs[k].first] = true;
                }
            }
            for (int k = 0; k < n; ++k) {
                next_adj[k][k] = true;
            }

            // Guest 'i' introduces all their friends to each other.
            // For any two distinct friends j and k of i, make them friends.
            for (int j = 0; j < n; ++j) {
                if (j == i) continue;
                if (next_adj[i][j]) { // If j is a friend of i
                    for (int k = j + 1; k < n; ++k) {
                        if (k == i) continue;
                        if (next_adj[i][k]) { // If k is also a friend of i
                            next_adj[j][k] = next_adj[k][j] = true; // Make j and k friends.
                        }
                    }
                }
            }

            // Convert the new adjacency matrix back to a bitmask.
            int next_mask = 0;
            for (int r = 0; r < n; ++r) {
                for (int c = r + 1; c < n; ++c) {
                    if (next_adj[r][c]) {
                        next_mask |= (1 << pair_to_idx[r][c]);
                    }
                }
            }

            // If we found a shorter path to next_mask, update DP and add to queue.
            if (dp[next_mask] > dp[current_mask] + 1) {
                dp[next_mask] = dp[current_mask] + 1;
                parent_mask[next_mask] = current_mask;
                chosen_guest[next_mask] = i; // Store the guest who made this transition.
                q.push(next_mask);
            }
        }
    }

    // Reconstruct the path (sequence of chosen guests).
    vector<int> path;
    int current_reconstruct_mask = final_mask;
    while (parent_mask[current_reconstruct_mask] != -1) {
        // Add 1 to guest ID because they are 1-indexed in output.
        path.push_back(chosen_guest[current_reconstruct_mask] + 1);
        current_reconstruct_mask = parent_mask[current_reconstruct_mask];
    }
    reverse(path.begin(), path.end()); // Reverse to get the correct order.

    // Output the minimum number of steps.
    cout << dp[target_mask] << endl;
    // Output the sequence of chosen guests.
    for (int i = 0; i < path.size(); ++i) {
        cout << path[i] << (i == path.size() - 1 ? "" : " ");
    }
    cout << endl;

    return 0;
}
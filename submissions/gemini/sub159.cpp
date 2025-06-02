#include <iostream> // Required for input/output operations (cin, cout).
#include <vector>   // Required for using std::vector.
#include <string>   // Required for using std::string.
#include <queue>    // Required for using std::queue for BFS.

// Define the maximum number of vertices.
// The problem states N <= 1000.
// A common construction for K shortest paths using binary representation
// uses about 2 * log2(K) vertices.
// For K = 10^9, log2(10^9) is approximately 29.89.
// So, 2 * 30 = 60 vertices plus source and sink (2) gives 62 vertices.
// This is well within the 1000 limit.
const int MAX_NODES = 62; 

// Adjacency matrix to store the graph.
// adj[i][j] = 'Y' if there's an edge between i and j, 'N' otherwise.
// Using 1-based indexing for vertices (1 to N).
char adj[MAX_NODES + 1][MAX_NODES + 1];

// dp[i] stores the number of shortest paths from vertex 1 to vertex i.
long long dp[MAX_NODES + 1];

// dist[i] stores the shortest distance from vertex 1 to vertex i.
int dist[MAX_NODES + 1];

int main() {
    // Optimize C++ standard streams for competitive programming.
    // Unties cin from cout and disables synchronization with C stdio.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int k; // The target number of shortest paths.
    std::cin >> k;

    // Initialize the adjacency matrix.
    // All cells are 'N' (no edge) by default.
    // Diagonal elements adj[i][i] are also 'N' as it's a simple graph.
    for (int i = 1; i <= MAX_NODES; ++i) {
        for (int j = 1; j <= MAX_NODES; ++j) {
            adj[i][j] = 'N';
        }
    }

    // The graph construction uses two "chains" of vertices, 'v' and 'u'.
    // v_i and u_i represent nodes at a certain 'depth' or 'layer'.
    // v_i is mapped to vertex (i + 3).
    // u_i is mapped to vertex (i + 3 + 30).
    // The maximum depth (number of layers) is 30, corresponding to bits 0 to 29.
    // This means the shortest path length will be 30.

    // Connect vertex 1 (source) to v_0 (vertex 3).
    // This initializes the 'v' chain with 1 path.
    adj[1][3] = adj[3][1] = 'Y';

    // Initialize dp and dist arrays for BFS.
    // All distances are infinity, all path counts are 0, except for source.
    for (int i = 1; i <= MAX_NODES; ++i) {
        dist[i] = -1; // -1 represents infinity (unvisited).
        dp[i] = 0;
    }
    dist[1] = 0;
    dp[1] = 1;

    // Perform a BFS-like traversal to calculate dp and dist values
    // and construct edges based on the binary representation of k.
    // The loop iterates through 'layers' or 'depths' from 0 to 29.
    // 'i' represents the current bit position.
    for (int i = 0; i < 30; ++i) {
        // Calculate vertex indices for current and next layers.
        // v_i is current_v_node, u_i is current_u_node.
        // v_{i+1} is next_v_node, u_{i+1} is next_u_node.
        int current_v_node = i + 3;
        int current_u_node = i + 3 + 30;
        int next_v_node = (i + 1) + 3;
        int next_u_node = (i + 1) + 3 + 30;

        // If current_v_node is reachable from source (dist[current_v_node] != -1):
        if (dist[current_v_node] != -1) {
            // Connect v_i to v_{i+1}.
            // This propagates paths from v_i to v_{i+1}.
            adj[current_v_node][next_v_node] = adj[next_v_node][current_v_node] = 'Y';
            // Update dp and dist for next_v_node.
            // If next_v_node is visited for the first time, set its distance.
            // Otherwise, if it's a shortest path, add the path count.
            if (dist[next_v_node] == -1) {
                dist[next_v_node] = dist[current_v_node] + 1;
            }
            if (dist[next_v_node] == dist[current_v_node] + 1) {
                dp[next_v_node] += dp[current_v_node];
            }

            // Connect v_i to u_i.
            // This propagates paths from v_i to u_i.
            adj[current_v_node][current_u_node] = adj[current_u_node][current_v_node] = 'Y';
            // Update dp and dist for current_u_node.
            if (dist[current_u_node] == -1) {
                dist[current_u_node] = dist[current_v_node] + 1;
            }
            if (dist[current_u_node] == dist[current_v_node] + 1) {
                dp[current_u_node] += dp[current_v_node];
            }
        }

        // If current_u_node is reachable from source (dist[current_u_node] != -1):
        if (dist[current_u_node] != -1) {
            // Connect u_i to u_{i+1}.
            // This propagates paths from u_i to u_{i+1}.
            adj[current_u_node][next_u_node] = adj[next_u_node][current_u_node] = 'Y';
            // Update dp and dist for next_u_node.
            if (dist[next_u_node] == -1) {
                dist[next_u_node] = dist[current_u_node] + 1;
            }
            if (dist[next_u_node] == dist[current_u_node] + 1) {
                dp[next_u_node] += dp[current_u_node];
            }

            // If the i-th bit of k is set (k has a 2^i component):
            if ((k >> i) & 1) {
                // Connect u_i to v_{i+1}.
                // This adds paths corresponding to 2^i to the v-chain.
                adj[current_u_node][next_v_node] = adj[next_v_node][current_u_node] = 'Y';
                // Update dp and dist for next_v_node.
                if (dist[next_v_node] == -1) {
                    dist[next_v_node] = dist[current_u_node] + 1;
                }
                if (dist[next_v_node] == dist[current_u_node] + 1) {
                    dp[next_v_node] += dp[current_u_node];
                }
            }
        }
    }

    // Connect the last v-node (v_{29}, which is vertex 29+3 = 32) to vertex 2 (sink).
    // This completes the paths accumulated in the v-chain.
    adj[32][2] = adj[2][32] = 'Y';

    // Output the number of vertices.
    std::cout << MAX_NODES << std::endl;

    // Output the adjacency matrix.
    for (int i = 1; i <= MAX_NODES; ++i) {
        for (int j = 1; j <= MAX_NODES; ++j) {
            std::cout << adj[i][j];
        }
        std::cout << std::endl;
    }

    return 0;
}

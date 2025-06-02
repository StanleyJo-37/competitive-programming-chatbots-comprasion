#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
#include <utility> // For std::pair

// Function to perform BFS and calculate distances from a source node
std::vector<int> bfs(int start_node, int n, const std::vector<std::vector<int>>& adj) {
    // dist[i] stores distance from start_node to i. Initialized to -1 (unvisited).
    std::vector<int> dist(n + 1, -1); 
    std::queue<int> q;

    dist[start_node] = 0; // Distance from start_node to itself is 0
    q.push(start_node);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        // Iterate over neighbors of u
        for (int v : adj[u]) {
            if (dist[v] == -1) { // If neighbor v has not been visited
                dist[v] = dist[u] + 1; // Distance to v is distance to u + 1
                q.push(v); // Add v to queue for further exploration
            }
        }
    }
    return dist;
}

// Function to make a query to the interactive judge
std::pair<int, int> make_query(const std::vector<int>& nodes_to_query) {
    // Print query format: "? c node1 node2 ... nodeC"
    std::cout << "? " << nodes_to_query.size();
    for (int node : nodes_to_query) {
        std::cout << " " << node;
    }
    std::cout << std::endl; // Flush output buffer to ensure query is sent

    int x, d;
    std::cin >> x >> d; // Read the response from the judge
    if (x == -1 && d == -1) {
        // Error condition: invalid query or exceeded query limit. Terminate.
        exit(0);
    }
    return {x, d};
}

void solve() {
    int n;
    std::cin >> n; // Read number of nodes

    // Adjacency list to represent the tree
    std::vector<std::vector<int>> adj(n + 1);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        std::cin >> u >> v; // Read edges
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Query 1: Find a node x0 on the path s-f and the distance L = d(s,f)
    // Query all nodes to find a node x0 that minimizes d(x0,s) + d(x0,f).
    // This x0 will be on the path s-f, and the sum will be d(s,f).
    std::vector<int> all_nodes(n);
    for (int i = 0; i < n; ++i) {
        all_nodes[i] = i + 1; // Populate vector with all node IDs (1 to n)
    }
    std::pair<int, int> query_result = make_query(all_nodes);
    int x0 = query_result.first;  // Node returned by the query
    int L = query_result.second; // Minimum sum of distances, which is d(s,f)

    // Calculate distances from x0 to all other nodes using BFS
    std::vector<int> dist_x0 = bfs(x0, n, adj);

    // Prepare nodes for binary search: create pairs of {distance_from_x0, node_id}
    // and sort them by distance.
    std::vector<std::pair<int, int>> nodes_by_dist;
    for (int i = 1; i <= n; ++i) {
        nodes_by_dist.push_back({dist_x0[i], i});
    }
    std::sort(nodes_by_dist.begin(), nodes_by_dist.end());

    // Binary search to find one of the secret nodes (S1)
    // S1 will be the endpoint of the s-f path that is further from x0.
    // The binary search finds the largest distance 'k' such that max(d(x0,s), d(x0,f)) >= k.
    // The node returned by the query for this 'k' will be S_far.
    int S1 = -1; // Initialize S1, will be updated during binary search
    int low = 0, high = n - 1; // Indices for nodes_by_dist vector

    while (low <= high) {
        int mid_idx = low + (high - low) / 2;
        int current_dist_threshold = nodes_by_dist[mid_idx].first;

        // Construct query set: all nodes whose distance from x0 is >= current_dist_threshold
        std::vector<int> query_set;
        for (int i = mid_idx; i < n; ++i) {
            query_set.push_back(nodes_by_dist[i].second);
        }

        // The query_set will not be empty for n >= 2, as mid_idx will always be a valid index.
        // However, an empty check doesn't hurt.
        if (query_set.empty()) {
            high = mid_idx - 1; // Should not happen with correct bounds, but for safety
            continue;
        }

        query_result = make_query(query_set);
        int x_A = query_result.first;
        int D_A = query_result.second;

        if (D_A == L) {
            // If D_A == L, it means x_A is on the path s-f.
            // Since x_A is from query_set, dist_x0[x_A] >= current_dist_threshold.
            // This implies that the endpoint of the s-f path that is further from x0
            // (S_far) must have dist_x0[S_far] >= current_dist_threshold.
            // So S_far is in the current query_set.
            // We update S1 to x_A (as x_A is a candidate for S_far) and try to find a larger threshold.
            S1 = x_A;
            low = mid_idx + 1;
        } else { // D_A > L
            // If D_A > L, it means x_A is NOT on the path s-f.
            // This implies that neither s nor f is in the current query_set.
            // So both d(x0,s) and d(x0,f) must be < current_dist_threshold.
            // This means S_far is NOT in the current query_set.
            // We need to look for nodes with smaller distances.
            high = mid_idx - 1;
        }
    }

    // S1 now holds one of the secret nodes (specifically, the one further from x0).
    // Now find the other secret node (S2).
    // S2 is the unique node at distance L from S1.
    std::vector<int> dist_S1 = bfs(S1, n, adj); // Calculate distances from S1
    std::vector<int> query_set_S2;
    for (int i = 1; i <= n; ++i) {
        if (dist_S1[i] == L) { // Collect all nodes at distance L from S1
            query_set_S2.push_back(i);
        }
    }

    // Query the set of nodes at distance L from S1. The returned node will be S2.
    query_result = make_query(query_set_S2);
    int S2 = query_result.first;

    // Output the guessed nodes
    std::cout << "! " << S1 << " " << S2 << std::endl;

    // Read the judge's response ("Correct" or "Incorrect")
    std::string response;
    std::cin >> response;
    if (response == "Incorrect") {
        exit(0); // Terminate if guess was incorrect
    }
}

int main() {
    // Optimize C++ standard streams for competitive programming
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t; // Read number of test cases
    while (t--) {
        solve(); // Solve each test case
    }

    return 0;
}

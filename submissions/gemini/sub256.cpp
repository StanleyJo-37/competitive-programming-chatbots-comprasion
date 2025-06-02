#include <iostream>
#include <vector>
#include <queue>
#include <algorithm> // Required for std::max

// Function to perform Breadth-First Search (BFS) starting from a given node.
// It finds the node farthest from the start_node within a specific component
// of the graph, effectively ignoring a particular edge (excluded_u, excluded_v).
//
// Parameters:
//   start_node: The node from which the BFS traversal begins.
//   n: The total number of nodes in the graph.
//   adj: The adjacency list representing the graph.
//   excluded_u, excluded_v: The two endpoints of the edge to be ignored during traversal.
//
// Returns:
//   A std::pair<int, int> where:
//     - first: The node farthest from start_node.
//     - second: The distance (number of edges) to that farthest node.
std::pair<int, int> bfs(int start_node, int n, const std::vector<std::vector<int>>& adj, int excluded_u, int excluded_v) {
    // Initialize a distance array. `dist[i]` will store the shortest distance
    // from `start_node` to node `i`. -1 indicates unvisited.
    std::vector<int> dist(n + 1, -1);
    // Queue for BFS traversal.
    std::queue<int> q;

    // Start BFS from the start_node.
    q.push(start_node);
    dist[start_node] = 0; // Distance from start_node to itself is 0.

    int farthest_node = start_node; // Initialize farthest node to start_node.
    int max_dist = 0;               // Initialize max distance to 0.

    // Standard BFS loop.
    while (!q.empty()) {
        int curr = q.front(); // Get the current node from the front of the queue.
        q.pop();              // Remove it from the queue.

        // Iterate over all neighbors of the current node.
        for (int neighbor : adj[curr]) {
            // Check if the current edge (curr, neighbor) is the one we need to exclude.
            // The edge can be represented as (excluded_u, excluded_v) or (excluded_v, excluded_u).
            if ((curr == excluded_u && neighbor == excluded_v) || (curr == excluded_v && neighbor == excluded_u)) {
                continue; // If it's the excluded edge, skip it.
            }

            // If the neighbor has not been visited yet (distance is -1).
            if (dist[neighbor] == -1) {
                dist[neighbor] = dist[curr] + 1; // Update its distance.
                q.push(neighbor);                // Add the neighbor to the queue for further exploration.

                // If the newly found distance to this neighbor is greater than max_dist,
                // update max_dist and farthest_node.
                if (dist[neighbor] > max_dist) {
                    max_dist = dist[neighbor];
                    farthest_node = neighbor;
                }
            }
        }
    }
    // Return the farthest node found and its distance from start_node.
    return {farthest_node, max_dist};
}

// Function to calculate the diameter (longest path) of a connected component
// within a graph, given a starting node within that component and an edge to exclude.
// The diameter is found using two BFS traversals:
// 1. Find the node farthest from an arbitrary start_node.
// 2. Find the node farthest from the node found in step 1. The distance found in step 2
//    is the diameter of the component.
//
// Parameters:
//   start_node: A node known to be part of the component whose diameter is to be found.
//   n: The total number of nodes in the graph.
//   adj: The adjacency list representing the graph.
//   excluded_u, excluded_v: The two endpoints of the edge that defines the component boundary.
//
// Returns:
//   The length of the longest path (diameter) in the specified component.
int get_diameter(int start_node, int n, const std::vector<std::vector<int>>& adj, int excluded_u, int excluded_v) {
    // First BFS: Find a node (res1.first) that is farthest from start_node
    // within the component defined by excluding (excluded_u, excluded_v).
    std::pair<int, int> res1 = bfs(start_node, n, adj, excluded_u, excluded_v);
    
    // Second BFS: Find a node (res2.first) that is farthest from res1.first.
    // The distance returned by this BFS (res2.second) is the diameter of the component.
    std::pair<int, int> res2 = bfs(res1.first, n, adj, excluded_u, excluded_v);
    
    return res2.second; // Return the calculated diameter.
}

int main() {
    // Optimize C++ standard streams for faster input/output operations.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    std::cin >> n; // Read the number of cities (nodes).

    // Adjacency list to represent the tree structure.
    // Using 1-based indexing for cities, so vector size is n + 1.
    std::vector<std::vector<int>> adj(n + 1);
    // Store all edges. This allows iterating through them to simulate removal.
    std::vector<std::pair<int, int>> edges;

    // Read the n-1 roads (edges) and populate the adjacency list.
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        std::cin >> u >> v;
        // Add edges to both u and v as roads are two-way.
        adj[u].push_back(v);
        adj[v].push_back(u);
        // Store the edge for later iteration.
        edges.push_back({u, v});
    }

    int max_profit = 0; // Initialize the maximum profit found so far to 0.

    // The core idea: Iterate through each edge in the tree.
    // Conceptually "remove" each edge one by one. Removing an edge splits a tree
    // into two connected components (subtrees).
    // For each pair of resulting subtrees, find the longest path (diameter) in each,
    // and calculate the product of their lengths. Keep track of the maximum product.
    for (const auto& edge : edges) {
        int u_edge = edge.first;  // One endpoint of the current edge being "removed".
        int v_edge = edge.second; // The other endpoint of the current edge being "removed".

        // Calculate the diameter of the component that contains u_edge
        // after the edge (u_edge, v_edge) is removed.
        int diam_u_component = get_diameter(u_edge, n, adj, u_edge, v_edge);

        // Calculate the diameter of the component that contains v_edge
        // after the edge (u_edge, v_edge) is removed.
        int diam_v_component = get_diameter(v_edge, n, adj, u_edge, v_edge);

        // Update max_profit if the product of the current two diameters is greater.
        max_profit = std::max(max_profit, diam_u_component * diam_v_component);
    }

    // Output the maximum possible profit found.
    std::cout << max_profit << std::endl;

    return 0; // Indicate successful execution.
}
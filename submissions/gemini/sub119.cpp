#include <iostream>
#include <vector>
#include <queue>
#include <algorithm> // Required for std::greater

// Define a constant for the maximum number of vertices.
// This is a common practice in competitive programming for array sizing.
const int MAXN = 100005;

// Adjacency list to represent the directed graph.
// adj[u] will store a list of vertices v such that there is a directed edge u -> v.
std::vector<int> adj[MAXN];

// Array to store the in-degree of each vertex.
// in_degree[v] counts the number of incoming edges to vertex v.
int in_degree[MAXN];

// Array to store the final assigned labels for each vertex.
// labels[i] will store the label assigned to vertex i.
int labels[MAXN];

int main() {
    // Optimize C++ standard streams for faster input/output operations.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams.
    // std::cin.tie(NULL) prevents std::cout from flushing before std::cin reads input.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, m; // n: number of vertices, m: number of edges
    std::cin >> n >> m;

    // Read the m edges and build the graph's adjacency list and in-degrees.
    for (int i = 0; i < m; ++i) {
        int u, v; // Edge from u to v
        std::cin >> u >> v;
        adj[u].push_back(v); // Add v to u's adjacency list
        in_degree[v]++;      // Increment the in-degree of v
    }

    // Create a min-priority queue.
    // std::priority_queue by default is a max-heap.
    // To make it a min-heap, we use std::greater<int> as the comparator.
    // This priority queue will store vertices that are "ready" to be processed.
    // A vertex is ready when all its predecessors have been assigned labels.
    std::priority_queue<int, std::vector<int>, std::greater<int>> pq;

    // Initialize the priority queue with all vertices that have an in-degree of 0.
    // These are the initial source vertices in the graph, as they have no predecessors.
    for (int i = 1; i <= n; ++i) {
        if (in_degree[i] == 0) {
            pq.push(i);
        }
    }

    // Assign labels from 1 to n.
    // 'current_label' represents the label we are currently assigning.
    for (int current_label = 1; current_label <= n; ++current_label) {
        // The problem guarantees a DAG, so a topological sort is always possible.
        // This means the priority queue will not be empty until all vertices are processed.
        // Pop the vertex 'u' with the smallest index from the priority queue.
        // This greedy choice (smallest index among ready vertices) is crucial for
        // achieving the lexicographically smallest sequence of labels.
        int u = pq.top();
        pq.pop();

        // Assign the 'current_label' to the chosen vertex 'u'.
        labels[u] = current_label;

        // For each neighbor 'v' of 'u' (i.e., for each edge u -> v):
        // Decrement 'v's in-degree, as 'u' (one of its predecessors) has now been processed.
        // If 'v's in-degree becomes 0, it means all its predecessors have been processed,
        // so 'v' is now ready to be assigned a label. Add 'v' to the priority queue.
        for (int v : adj[u]) {
            in_degree[v]--;
            if (in_degree[v] == 0) {
                pq.push(v);
            }
        }
    }

    // Print the assigned labels for vertices 1 to n, separated by spaces.
    for (int i = 1; i <= n; ++i) {
        std::cout << labels[i] << (i == n ? "" : " ");
    }
    std::cout << std::endl; // Print a newline at the end of the output.

    return 0; // Indicate successful execution.
}

#include <iostream> // Required for input/output operations (std::cin, std::cout)
#include <vector>   // Required for std::vector
#include <numeric>  // Required for std::iota (to initialize DSU parent array)
#include <utility>  // Required for std::pair and std::swap

// DSU (Disjoint Set Union) data structure
// Used to efficiently manage sets of elements and perform union and find operations.
// It helps determine if two elements are in the same connected component.
struct DSU {
    std::vector<int> parent; // parent[i] stores the parent of element i. If parent[i] == i, i is a root.
    std::vector<int> sz;     // sz[i] stores the size of the set rooted at i. Used for union by size optimization.

    // Constructor: Initializes n+1 elements, each in its own set.
    DSU(int n) {
        parent.resize(n + 1); // Vertices are 1-indexed, so size n+1 is used.
        std::iota(parent.begin(), parent.end(), 0); // Initialize parent[i] = i for all i.
        sz.assign(n + 1, 1); // Each set initially has size 1.
    }

    // Find operation: Returns the representative (root) of the set containing element i.
    // Uses path compression for optimization.
    int find(int i) {
        if (parent[i] == i)
            return i; // If i is its own parent, it's the root.
        return parent[i] = find(parent[i]); // Path compression: set parent[i] directly to the root.
    }

    // Unite operation: Merges the sets containing elements i and j.
    // Uses union by size optimization.
    void unite(int i, int j) {
        int root_i = find(i); // Find the root of i's set.
        int root_j = find(j); // Find the root of j's set.

        if (root_i != root_j) { // If they are not already in the same set.
            // Union by size: Attach the smaller tree under the root of the larger tree.
            // This keeps the tree height small, improving find operation efficiency.
            if (sz[root_i] < sz[root_j]) {
                std::swap(root_i, root_j); // Ensure root_i always points to the larger tree.
            }
            parent[root_j] = root_i; // Make root_i the parent of root_j.
            sz[root_i] += sz[root_j]; // Update the size of the merged set.
        }
    }
};

int main() {
    // Optimize C++ standard streams for faster input/output.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams.
    // std::cin.tie(NULL) prevents std::cout from flushing before std::cin reads input.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, m;
    std::cin >> n >> m; // Read number of vertices (n) and edges (m).

    // Store edges grouped by color.
    // `edges_by_color[c]` will store a list of pairs `{u, v}` for all edges of color `c`.
    // The maximum color value is `m`, so a vector of size `m + 1` is used for 1-based indexing.
    std::vector<std::vector<std::pair<int, int>>> edges_by_color(m + 1);

    // Read all m edges and store them by their color.
    for (int i = 0; i < m; ++i) {
        int u, v, c;
        std::cin >> u >> v >> c; // Read edge (u, v) with color c.
        edges_by_color[c].push_back({u, v}); // Add the edge to the list for its color.
    }

    int q;
    std::cin >> q; // Read the number of queries (q).

    // Process each query.
    for (int i = 0; i < q; ++i) {
        int u_query, v_query;
        std::cin >> u_query >> v_query; // Read the two query vertices.

        int distinct_colors_count = 0; // Initialize a counter for colors satisfying the condition.

        // Iterate through all possible colors from 1 to m.
        // For each color, we check if u_query and v_query are connected using only edges of that color.
        for (int color = 1; color <= m; ++color) {
            // Create a new DSU structure for each color.
            // This ensures that the connectivity check is isolated to only edges of the current `color`.
            DSU dsu(n); 

            // For the current `color`, iterate through all edges associated with it.
            for (const auto& edge : edges_by_color[color]) {
                // For each edge `{first, second}` of the current color, unite the two vertices.
                // This effectively builds the connected components for the subgraph of this specific color.
                dsu.unite(edge.first, edge.second);
            }

            // After processing all edges of the current color, check if `u_query` and `v_query` are connected.
            // They are connected if their representatives (roots) in the DSU structure are the same.
            if (dsu.find(u_query) == dsu.find(v_query)) {
                distinct_colors_count++; // If connected, increment the counter.
            }
        }
        std::cout << distinct_colors_count << "\n"; // Print the total count of distinct colors for the current query.
    }

    return 0; // Indicate successful execution.
}
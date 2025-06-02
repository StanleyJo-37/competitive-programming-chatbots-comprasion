#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

// Structure to represent a Disjoint Set Union (DSU)
struct DSU {
    std::vector<int> parent;
    DSU(int n) {
        // Initialize parent array, each element is its own parent
        parent.resize(n);
        std::iota(parent.begin(), parent.end(), 0);
    }

    // Find operation with path compression
    int find(int i) {
        if (parent[i] == i)
            return i;
        return parent[i] = find(parent[i]);
    }

    // Union operation by rank/size (here simple union by setting parent)
    void unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) {
            parent[root_i] = root_j;
        }
    }
};

int main() {
    // Optimize C++ standard streams for faster input/output.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    std::cin >> n; // Read the number of integers

    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i]; // Read the integers
    }

    // A vector to store all possible XOR pairs and their values.
    // Each element is a tuple: {XOR_value, index_a, index_b}
    std::vector<std::tuple<int, int, int>> xor_pairs;
    xor_pairs.reserve(n * (n - 1) / 2); // Reserve space for efficiency

    // Generate all unique XOR pairs between distinct elements.
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            xor_pairs.emplace_back(a[i] ^ a[j], i, j);
        }
    }

    // Sort the XOR pairs in ascending order of their XOR value.
    // This is crucial for Kruskal's-like approach.
    std::sort(xor_pairs.begin(), xor_pairs.end());

    int min_max_xor = 0; // Initialize the minimum possible score

    // If n=2, the only permutation is (a[0], a[1]) or (a[1], a[0]),
    // and the score is simply a[0] ^ a[1].
    if (n == 2) {
        std::cout << (a[0] ^ a[1]) << std::endl;
        return 0;
    }

    // Kruskal's-like algorithm to find the minimum maximum XOR value.
    // We are looking for a spanning path/tree that connects all n elements.
    // The maximum edge in such a path will be our score. We want to minimize this score.
    // By processing edges in increasing order of XOR value, we ensure that
    // when all n nodes are connected (forming a single component), the
    // last edge added to achieve this connection determines the maximum XOR value
    // within the current "minimum spanning path" consideration.

    DSU dsu(n); // Initialize DSU for n elements
    int edges_added = 0; // Counter for edges added to the "spanning path"

    // Iterate through sorted XOR pairs
    for (const auto& edge : xor_pairs) {
        int u = std::get<1>(edge); // Index of first element
        int v = std::get<2>(edge); // Index of second element
        int xor_val = std::get<0>(edge); // XOR value of the pair

        // If u and v are not already in the same component, unite them.
        // This is equivalent to adding an edge to our "spanning path".
        if (dsu.find(u) != dsu.find(v)) {
            dsu.unite(u, v); // Unite the components
            min_max_xor = xor_val; // Update the current maximum XOR value encountered
            edges_added++; // Increment edge count

            // If we have added n-1 edges, it means all n elements are connected
            // into a single component (a spanning tree/path).
            // At this point, the current 'min_max_xor' is the smallest possible
            // maximum XOR value that connects all elements.
            if (edges_added == n - 1) {
                break; // We found our minimum maximum XOR value, so we can stop.
            }
        }
    }

    std::cout << min_max_xor << std::endl; // Print the result

    return 0;
}
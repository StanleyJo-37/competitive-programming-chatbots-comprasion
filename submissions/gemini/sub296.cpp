#include <iostream>
#include <vector>
#include <algorithm> // For std::sort and std::min

// Constants for array sizes and limits
const int MAXN = 100005; // Maximum number of cities (N)
const int MAX_LOG = 18;  // ceil(log2(MAXN)) is about 16.6, so 18 is a safe upper bound for log N
const int MAX_A = 10;    // Maximum value for 'a' in queries

// Adjacency list to represent the tree structure
std::vector<int> adj[MAXN];

// Stores people IDs for each city.
// Each vector will be sorted and capped at MAX_A during preprocessing.
std::vector<int> people_in_city[MAXN];

// Binary lifting parent table: parent[u][k] is the 2^k-th ancestor of node u.
// A value of 0 indicates no such ancestor (e.g., parent of root).
int parent[MAXN][MAX_LOG];

// Depth of each node from the root. Root is at depth 0.
int depth[MAXN];

// dp[u][k] stores the MAX_A smallest unique people IDs on the path from node u
// to its 2^k-th ancestor, EXCLUDING the 2^k-th ancestor itself.
std::vector<int> dp[MAXN][MAX_LOG];

// Merges two sorted vectors of integers, removes duplicates, and caps the result size at MAX_A.
// This function is crucial for combining people IDs along paths efficiently.
std::vector<int> merge_vectors(const std::vector<int>& v1, const std::vector<int>& v2) {
    std::vector<int> res;
    res.reserve(MAX_A); // Pre-allocate memory to avoid reallocations

    int p1 = 0, p2 = 0; // Pointers for v1 and v2
    // Iterate while we haven't reached MAX_A elements and there are still elements in v1 or v2
    while (res.size() < MAX_A && (p1 < v1.size() || p2 < v2.size())) {
        int current_val;
        // Determine the smaller element from v1 or v2
        if (p1 < v1.size() && (p2 == v2.size() || v1[p1] < v2[p2])) {
            current_val = v1[p1++]; // Take from v1 if it's smaller or v2 is exhausted
        } else {
            current_val = v2[p2++]; // Take from v2
        }

        // Add to result only if it's not a duplicate of the last element added
        if (res.empty() || res.back() != current_val) {
            res.push_back(current_val);
        }
    }
    return res;
}

// DFS to precompute depths and direct parents (2^0-th ancestor) for all nodes.
// It also initializes the base case for the dp table (dp[u][0]).
void dfs(int u, int p, int d) {
    depth[u] = d;       // Set depth of current node
    parent[u][0] = p;   // Set direct parent of current node
    
    // Base case for dp table: dp[u][0] contains people in city u itself.
    // people_in_city[u] is already sorted and capped at MAX_A from main.
    dp[u][0] = people_in_city[u]; 

    // Recurse for children
    for (int v : adj[u]) {
        if (v == p) continue; // Avoid going back to parent
        dfs(v, u, d + 1);
    }
}

// Computes the Lowest Common Ancestor (LCA) of two nodes u and v.
int get_lca(int u, int v) {
    // Ensure u is deeper than or at the same depth as v
    if (depth[u] < depth[v]) {
        std::swap(u, v);
    }

    // Lift u up to the same depth as v
    for (int k = MAX_LOG - 1; k >= 0; --k) {
        // Check if parent[u][k] is a valid node (not 0, our sentinel for root's parent)
        // and if lifting u by 2^k steps doesn't go above v's depth
        if (parent[u][k] != 0 && depth[parent[u][k]] >= depth[v]) {
            u = parent[u][k];
        }
    }

    // If u is now v, then v (or u) is the LCA
    if (u == v) {
        return u;
    }

    // Lift u and v simultaneously until their parents are the same.
    // This means they are now children of the LCA.
    for (int k = MAX_LOG - 1; k >= 0; --k) {
        // Check if both parents are valid and different
        if (parent[u][k] != 0 && parent[v][k] != 0 && parent[u][k] != parent[v][k]) {
            u = parent[u][k];
            v = parent[v][k];
        }
    }
    // The parent of u (or v) is the LCA
    return parent[u][0];
}

int main() {
    // Optimize C++ standard streams for faster input/output
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, m, q;
    std::cin >> n >> m >> q;

    // Read tree edges and build adjacency list
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        std::cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Read people's cities and store their IDs.
    // Sort and cap each city's people list to MAX_A smallest IDs.
    for (int i = 1; i <= m; ++i) {
        int c; // City where person i lives
        std::cin >> c;
        people_in_city[c].push_back(i);
    }
    for (int i = 1; i <= n; ++i) {
        std::sort(people_in_city[i].begin(), people_in_city[i].end());
        if (people_in_city[i].size() > MAX_A) {
            people_in_city[i].resize(MAX_A); // Cap the size to MAX_A
        }
    }

    // Perform DFS to initialize depth and parent[u][0] for all nodes.
    // Node 1 is chosen as the root, its parent is 0 (sentinel), and its depth is 0.
    dfs(1, 0, 0);

    // Precompute parent and dp tables for binary lifting.
    // This loop builds the tables for 2^k-th ancestors and their associated people IDs.
    for (int k = 1; k < MAX_LOG; ++k) {
        for (int u = 1; u <= n; ++u) {
            // Compute the 2^k-th parent of u.
            // It's the 2^(k-1)-th parent of the 2^(k-1)-th parent of u.
            parent[u][k] = parent[parent[u][k-1]][k-1];
            
            // Merge people IDs from the two halves of the 2^k path segment.
            // dp[u][k-1] covers path from u to parent[u][k-1] (exclusive parent[u][k-1]).
            // dp[parent[u][k-1]][k-1] covers path from parent[u][k-1] to parent[parent[u][k-1]][k-1]
            // (exclusive parent[parent[u][k-1]][k-1]).
            // Their merge covers the path from u to parent[u][k] (exclusive parent[u][k]).
            if (parent[u][k-1] != 0) { // Check if parent[u][k-1] is a valid node
                dp[u][k] = merge_vectors(dp[u][k-1], dp[parent[u][k-1]][k-1]);
            } else {
                // If parent[u][k-1] is 0 (root's parent), it means there's no further ancestor.
                // The path segment only includes what's already in dp[u][k-1].
                dp[u][k] = dp[u][k-1];
            }
        }
    }

    // Process queries
    for (int i = 0; i < q; ++i) {
        int v_query, u_query, a_query;
        std::cin >> v_query >> u_query >> a_query;

        int lca_node = get_lca(v_query, u_query); // Find the LCA of v_query and u_query
        std::vector<int> final_path_people; // Stores the collected people IDs for the current query

        // Collect people IDs on the path from v_query to lca_node (exclusive lca_node)
        int curr_node = v_query;
        for (int k = MAX_LOG - 1; k >= 0; --k) {
            // If lifting curr_node by 2^k steps does not go above lca_node's depth,
            // meaning parent[curr_node][k] is lca_node or deeper than lca_node.
            if (parent[curr_node][k] != 0 && depth[parent[curr_node][k]] >= depth[lca_node]) {
                final_path_people = merge_vectors(final_path_people, dp[curr_node][k]);
                curr_node = parent[curr_node][k]; // Move curr_node up
            }
        }

        // Collect people IDs on the path from u_query to lca_node (exclusive lca_node)
        curr_node = u_query;
        for (int k = MAX_LOG - 1; k >= 0; --k) {
            // Similar logic as for v_query
            if (parent[curr_node][k] != 0 && depth[parent[curr_node][k]] >= depth[lca_node]) {
                final_path_people = merge_vectors(final_path_people, dp[curr_node][k]);
                curr_node = parent[curr_node][k]; // Move curr_node up
            }
        }
        
        // Add people from the LCA node itself.
        // The previous loops collected people on paths *exclusive* of the LCA node.
        // This ensures the LCA node's people are included exactly once.
        final_path_people = merge_vectors(final_path_people, people_in_city[lca_node]);

        // Print the result: min(total people found, a_query) smallest IDs
        int count = std::min((int)final_path_people.size(), a_query);
        std::cout << count;
        for (int j = 0; j < count; ++j) {
            std::cout << " " << final_path_people[j];
        }
        std::cout << "\n";
    }

    return 0;
}

#include <iostream>
#include <vector>
#include <algorithm> // For std::min
#include <limits>    // For std::numeric_limits

// Using global variables for tree structure and values for competitive programming style.
// This avoids passing large data structures by value and simplifies function signatures.
// MAXN is the maximum number of vertices as per problem constraints (10^5).
const int MAXN = 100005;
std::vector<int> adj[MAXN]; // Adjacency list to store children for each node.
                            // adj[u] contains all direct children of node u.
long long s_given[MAXN];    // Given s_v values. If s_v was erased, it's -1.
                            // Using long long because s_v can be up to 10^9.
int h[MAXN];                 // Depths of vertices. h[1] = 1.
long long s_actual[MAXN];    // Calculated s_v values for all vertices.
                            // These are the actual s_v values that satisfy constraints.
long long total_a_sum = 0;   // Total sum of a_v values. Initialized to 0.
                            // Will be set to -1 if an impossible scenario is detected.
                            // Using long long because total sum can be up to N * 10^9 = 10^14.

// DFS function to compute depths of all nodes.
// This is a standard tree traversal to pre-calculate depths.
// u: current node being visited.
// current_depth: the depth of the current node u.
void dfs_depth(int u, int current_depth) {
    h[u] = current_depth; // Set the depth for the current node.
    // Recursively call dfs_depth for all children of u.
    // Children will have a depth one greater than their parent.
    for (int v : adj[u]) {
        dfs_depth(v, current_depth + 1);
    }
}

// DFS function to determine s_v values for even-depth nodes and calculate the total sum of a_v.
// This function performs a pre-order traversal (parent before children) to determine s_actual[u]
// and then passes this value to its children.
// u: current node being processed.
// parent_s_val: the s_value of the parent of node u. For the root (node 1), this is conceptually 0.
void dfs_solve(int u, long long parent_s_val) {
    // If an inconsistency was found in a previous recursive call,
    // propagate the error by immediately returning.
    if (total_a_sum == -1) {
        return;
    }

    // Determine s_actual[u] based on its depth and given information.
    // Case 1: Current node u has an odd depth.
    // According to the problem, s_v for odd depths are given and not erased.
    if (h[u] % 2 != 0) { // Odd depth (h_u is 1, 3, 5, ...)
        s_actual[u] = s_given[u]; // Use the provided s_v value.

        // Consistency check: a_u = s_u - s_{p_u} must be non-negative (a_u >= 0).
        // This implies s_u must be greater than or equal to s_{p_u}.
        // s_{p_u} is passed as parent_s_val.
        if (s_actual[u] < parent_s_val) {
            total_a_sum = -1; // Inconsistency found: impossible to satisfy a_u >= 0.
            return;
        }
    }
    // Case 2: Current node u has an even depth.
    // According to the problem, s_v for even depths are erased and replaced by -1.
    // We need to determine s_actual[u] to minimize the total sum of a_v.
    else { // Even depth (h_u is 2, 4, 6, ...)
        // If u is a leaf node (it has no children).
        if (adj[u].empty()) {
            // For a leaf node with even depth, s_u is unknown.
            // The only constraint is a_u = s_u - s_{p_u} >= 0, so s_u >= s_{p_u}.
            // To minimize a_u (and thus the total sum), we choose the smallest possible s_u.
            s_actual[u] = parent_s_val; // Set s_u equal to s_{p_u}.
        }
        // If u is not a leaf node (it has children).
        else {
            // For a non-leaf node with even depth, s_u is unknown.
            // Constraints:
            // 1. a_u = s_u - s_{p_u} >= 0  =>  s_u >= s_{p_u}.
            // 2. For any child c of u, h_c is odd, so s_c is given.
            //    a_c = s_c - s_u >= 0  =>  s_u <= s_c for all children c.
            // Combining these, s_u must be in the range [s_{p_u}, min(s_c for all children c)].
            // To minimize the total sum of a_v, we want to minimize s_u.
            // So, we choose s_u = min(s_c for all children c).
            long long min_child_s = std::numeric_limits<long long>::max(); // Initialize with a very large value.
            for (int v : adj[u]) {
                min_child_s = std::min(min_child_s, s_given[v]); // Children of even-depth nodes have odd depths, so their s_values are known.
            }
            s_actual[u] = min_child_s;

            // After determining s_actual[u], we must check the first constraint: s_u >= s_{p_u}.
            if (s_actual[u] < parent_s_val) {
                total_a_sum = -1; // Inconsistency found: impossible to satisfy a_u >= 0.
                return;
            }
        }
    }

    // Now that s_actual[u] is determined, calculate a_u and add it to the total sum.
    // a_u = s_u - s_{p_u}. For the root (u=1), s_{p_u} is 0, so a_1 = s_1.
    total_a_sum += (s_actual[u] - parent_s_val);

    // Recursively call dfs_solve for all children of u.
    // Pass the newly determined s_actual[u] as the parent_s_val for its children.
    for (int v : adj[u]) {
        // Check for error propagation before making recursive call.
        if (total_a_sum == -1) {
            return;
        }
        dfs_solve(v, s_actual[u]);
    }
}

int main() {
    // Optimize C++ standard streams for faster input/output.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    std::cin >> n;

    // Read parent information and build the adjacency list (children list).
    // For each node i from 2 to n, p_i is its parent.
    // So, add i to the list of children for p_i.
    for (int i = 2; i <= n; ++i) {
        int p_i;
        std::cin >> p_i;
        adj[p_i].push_back(i);
    }

    // Read the given s_v values for all nodes.
    for (int i = 1; i <= n; ++i) {
        std::cin >> s_given[i];
    }

    // Step 1: Perform a DFS starting from the root (node 1) to compute depths of all nodes.
    // The root is at depth 1.
    dfs_depth(1, 1);

    // Step 2: Perform another DFS to determine the actual s_v values for even-depth nodes
    // and calculate the total sum of a_v values.
    // For the root (node 1), its conceptual parent's s_value is 0.
    dfs_solve(1, 0);

    // Output the minimum total sum of a_v values, or -1 if no valid tree can be restored.
    std::cout << total_a_sum << std::endl;

    return 0;
}
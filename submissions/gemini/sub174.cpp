#include <iostream> // Required for input/output operations (std::cin, std::cout)
#include <vector>   // Required for dynamic arrays (std::vector)
#include <string>   // Required for string manipulation (not directly used, but good practice for competitive programming)
#include <algorithm> // Required for sorting and lower_bound (std::sort, std::lower_bound)
#include <set>      // Required for storing distinct coordinates efficiently (std::set)

// Using a global vector for compressed coordinates. This avoids passing it as an argument
// to segment tree functions, simplifying function signatures.
std::vector<long long> g_compressed_coords;

// Helper function to map an original coordinate to its compressed 0-based index.
// It uses binary search (std::lower_bound) on the sorted vector of unique coordinates.
int map_coord_to_idx(long long coord) {
    return std::lower_bound(g_compressed_coords.begin(), g_compressed_coords.end(), coord) - g_compressed_coords.begin();
}

// Define the maximum possible number of distinct coordinates.
// In the worst case, each of M operations (P, M, B) can introduce new coordinates.
// P u v: 2 coords. M i d: 2 coords. B x: 1 coord.
// Max distinct coords = 2*M (from P) + 2*M (from M) + M (from B) = 5*M.
// For M = 250,000, MAX_K = 5 * 250,000 = 1,250,000.
const int MAX_K = 1250000;

// Segment tree arrays.
// 'tree' stores the accumulated value for a range. For a point query, this will be the final count at a leaf node.
// 'lazy' stores pending updates (increments/decrements) that need to be propagated down to children.
// The size 4 * MAX_K is a common safe upper bound for segment tree arrays to cover all nodes.
int tree[4 * MAX_K];
int lazy[4 * MAX_K];

// Propagates lazy tag down to children.
// This function ensures that any pending updates at the current node are applied to its
// own 'tree' value and then passed down to its children's 'lazy' tags.
void push(int node, int start, int end) {
    if (lazy[node] != 0) {
        tree[node] += lazy[node]; // Apply lazy value to current node's accumulated sum
        if (start != end) { // If not a leaf node, propagate to children
            lazy[2 * node] += lazy[node];     // Add lazy value to left child's lazy tag
            lazy[2 * node + 1] += lazy[node]; // Add lazy value to right child's lazy tag
        }
        lazy[node] = 0; // Reset lazy tag for current node after propagation
    }
}

// Updates a range [l, r] by adding 'val'.
// 'node' is the current segment tree node index.
// '[start, end]' is the range covered by the current node.
// '[l, r]' is the target range for the update.
// 'val' is the value to add (e.g., +1 for adding a system, -1 for removing).
void update(int node, int start, int end, int l, int r, int val) {
    push(node, start, end); // Apply any pending lazy updates before processing this node
    
    // Case 1: Current segment is completely outside the target range [l, r]
    if (start > end || start > r || end < l) {
        return;
    }
    
    // Case 2: Current segment is completely inside the target range [l, r]
    if (l <= start && end <= r) {
        lazy[node] += val; // Add value to current node's lazy tag
        push(node, start, end); // Apply this new lazy value to current node's sum immediately
                                // and propagate to children if applicable.
        return;
    }
    
    // Case 3: Partial overlap, recurse on children
    int mid = start + (end - start) / 2; // Calculate midpoint to divide the range
    update(2 * node, start, mid, l, r, val);       // Recurse on left child
    update(2 * node + 1, mid + 1, end, l, r, val); // Recurse on right child
    
    // For range add/point query segment trees, the parent node's 'tree' value is not
    // directly derived from its children's 'tree' values. Its value is only affected
    // by lazy tags pushed down from its own parent.
}

// Queries the value at a specific compressed index 'idx'.
// 'node' is the current segment tree node index.
// '[start, end]' is the range covered by the current node.
// 'idx' is the target index for the query.
int query(int node, int start, int end, int idx) {
    push(node, start, end); // Apply any pending lazy updates before querying this node
    
    // Case 1: Reached the leaf node for the queried index
    if (start == end) {
        return tree[node]; // Return the accumulated value at this leaf
    }
    
    // Case 2: Traverse down to the appropriate child
    int mid = start + (end - start) / 2; // Calculate midpoint
    if (idx <= mid) {
        return query(2 * node, start, mid, idx); // Query in the left child's range
    } else {
        return query(2 * node + 1, mid + 1, end, idx); // Query in the right child's range
    }
}

// Structure to store each operation read from input.
// 'type': 'P', 'M', or 'B'.
// 'arg1', 'arg2', 'arg3': Arguments specific to each operation type.
// For 'P u v': arg1=u, arg2=v, arg3=system_idx (0-based index of the system).
// For 'M i d': arg1=i (1-based system index), arg2=d, arg3=0.
// For 'B x': arg1=x, arg2=0, arg3=0.
struct Operation {
    char type;
    long long arg1, arg2, arg3;
};

int main() {
    // Optimize C++ standard streams for faster input/output.
    // This is crucial for competitive programming problems with large I/O.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    long long n; // Max house index
    int m;       // Number of operations
    std::cin >> n >> m;

    // Store all operations as they are read.
    std::vector<Operation> operations(m);
    // Stores the initial (u,v) ranges for each system defined by 'P' operations.
    // System indices are 1-based in input, but 0-based here for vector access.
    std::vector<std::pair<long long, long long>> system_definitions;

    // First pass: Read all operations and populate 'operations' and 'system_definitions'.
    int system_idx_counter = 0; // Counter for assigning 0-based indices to systems
    for (int k = 0; k < m; ++k) {
        char type;
        std::cin >> type;
        operations[k].type = type;
        if (type == 'P') {
            long long u, v;
            std::cin >> u >> v;
            operations[k].arg1 = u;
            operations[k].arg2 = v;
            operations[k].arg3 = system_idx_counter; // Store the 0-based index for this system
            system_definitions.push_back({u, v});    // Store its initial range
            system_idx_counter++;
        } else if (type == 'M') {
            long long i, d;
            std::cin >> i >> d;
            operations[k].arg1 = i; // 1-based system index
            operations[k].arg2 = d;
        } else { // type == 'B'
            long long x;
            std::cin >> x;
            operations[k].arg1 = x;
        }
    }

    // Second pass: Collect all distinct coordinates that will ever be relevant.
    // This includes initial P ranges, all B query points, and all M new ranges.
    std::set<long long> distinct_coords_set; // Use a set to automatically handle uniqueness and sorting
    
    // Create a temporary copy of system definitions to track their current positions
    // during this pass, without altering the original 'system_definitions' needed for Pass 3.
    std::vector<std::pair<long long, long long>> current_system_ranges_temp = system_definitions;

    for (const auto& op : operations) {
        if (op.type == 'P') {
            distinct_coords_set.insert(op.arg1); // u
            distinct_coords_set.insert(op.arg2); // v
        } else if (op.type == 'M') {
            long long i = op.arg1; // 1-based system index
            long long d = op.arg2;
            
            // Get the current range of the system before it moves
            long long old_u = current_system_ranges_temp[i - 1].first;
            long long old_v = current_system_ranges_temp[i - 1].second;
            
            // Calculate the new range after moving
            long long new_u = old_u + d;
            long long new_v = old_v + d;
            
            // Add the new endpoints to the set of distinct coordinates
            distinct_coords_set.insert(new_u);
            distinct_coords_set.insert(new_v);
            
            // Update the temporary current state of the system for subsequent 'M' operations
            current_system_ranges_temp[i - 1] = {new_u, new_v};
        } else { // op.type == 'B'
            distinct_coords_set.insert(op.arg1); // x
        }
    }

    // Convert the set of distinct coordinates to a sorted vector.
    // This vector will be used by 'map_coord_to_idx' for coordinate compression.
    g_compressed_coords.assign(distinct_coords_set.begin(), distinct_coords_set.end());
    int K = g_compressed_coords.size(); // K is the number of unique coordinates

    // Reset 'current_system_ranges' to initial definitions for the third pass.
    // This ensures that the segment tree operations start with the correct initial system states.
    std::vector<std::pair<long long, long long>> current_system_ranges = system_definitions;

    // Third pass: Process operations using the segment tree.
    // The segment tree arrays 'tree' and 'lazy' are global and implicitly initialized to 0.
    // If they were local, they would need explicit initialization (e.g., std::fill or memset).
    for (const auto& op : operations) {
        if (op.type == 'P') {
            long long u = op.arg1;
            long long v = op.arg2;
            // Add the defense system: increment count for all houses in [u, v]
            update(1, 0, K - 1, map_coord_to_idx(u), map_coord_to_idx(v), 1);
        } else if (op.type == 'M') {
            long long i = op.arg1; // 1-based system index
            long long d = op.arg2;

            // Get the current range of the system before it moves
            long long old_u = current_system_ranges[i - 1].first;
            long long old_v = current_system_ranges[i - 1].second;
            
            // Remove the contribution of the old range from the segment tree
            update(1, 0, K - 1, map_coord_to_idx(old_u), map_coord_to_idx(old_v), -1);
            
            // Calculate the new range after moving
            long long new_u = old_u + d;
            long long new_v = old_v + d;
            
            // Update the current state of the system
            current_system_ranges[i - 1] = {new_u, new_v};
            
            // Add the contribution of the new range to the segment tree
            update(1, 0, K - 1, map_coord_to_idx(new_u), map_coord_to_idx(new_v), 1);
        } else { // op.type == 'B'
            long long x = op.arg1;
            // Query the number of systems protecting house x and print the result
            std::cout << query(1, 0, K - 1, map_coord_to_idx(x)) << "\n";
        }
    }

    return 0; // Indicate successful execution
}

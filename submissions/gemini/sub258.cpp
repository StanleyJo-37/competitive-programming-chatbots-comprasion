#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

// Structure for segment tree node
struct Node {
    int min_val;
    int max_val;
};

// Segment tree array
std::vector<Node> tree;
// Original array
std::vector<int> arr;
int N_seg; // Size of the array for segment tree operations

// Builds the segment tree recursively.
// node_idx: current node's index in the tree array.
// start, end: range [start, end] covered by the current node.
void build(int node_idx, int start, int end) {
    if (start == end) {
        // Leaf node: stores the value of the array element.
        tree[node_idx] = {arr[start], arr[start]};
    } else {
        int mid = (start + end) / 2;
        // Recursively build left and right children.
        build(2 * node_idx, start, mid);
        build(2 * node_idx + 1, mid + 1, end);
        // Internal node: stores min/max of its children.
        tree[node_idx].min_val = std::min(tree[2 * node_idx].min_val, tree[2 * node_idx + 1].min_val);
        tree[node_idx].max_val = std::max(tree[2 * node_idx].max_val, tree[2 * node_idx + 1].max_val);
    }
}

// Finds the first (leftmost) index in the query range [query_L, query_R]
// where the element is strictly less than 'value'.
// Returns N_seg if no such element is found.
int find_first_less(int node_idx, int start, int end, int query_L, int query_R, int value) {
    // If the current node's range is completely outside the query range,
    // or if the minimum value in this node's range is already >= 'value',
    // then no element less than 'value' exists in this range.
    if (query_R < start || end < query_L || tree[node_idx].min_val >= value) {
        return N_seg; // Indicate not found
    }
    // If it's a leaf node and its value is less than 'value', this is the first such element.
    if (start == end) {
        return start;
    }
    int mid = (start + end) / 2;
    // Search the left child first.
    int res = find_first_less(2 * node_idx, start, mid, query_L, query_R, value);
    if (res != N_seg) { // If found in the left child, return its index.
        return res;
    }
    // Otherwise, search the right child.
    return find_first_less(2 * node_idx + 1, mid + 1, end, query_L, query_R, value);
}

// Finds the last (rightmost) index in the query range [query_L, query_R]
// where the element is strictly greater than 'value'.
// Returns -1 if no such element is found.
int find_last_greater(int node_idx, int start, int end, int query_L, int query_R, int value) {
    // If the current node's range is completely outside the query range,
    // or if the maximum value in this node's range is already <= 'value',
    // then no element greater than 'value' exists in this range.
    if (query_R < start || end < query_L || tree[node_idx].max_val <= value) {
        return -1; // Indicate not found
    }
    // If it's a leaf node and its value is greater than 'value', this is the last such element.
    if (start == end) {
        return start;
    }
    int mid = (start + end) / 2;
    // Search the right child first.
    int res = find_last_greater(2 * node_idx + 1, mid + 1, end, query_L, query_R, value);
    if (res != -1) { // If found in the right child, return its index.
        return res;
    }
    // Otherwise, search the left child.
    return find_last_greater(2 * node_idx, start, mid, query_L, query_R, value);
}

void solve() {
    int n;
    std::cin >> n;
    arr.resize(n);
    // Store positions of each value in the array. This helps in finding specific values efficiently.
    // map<value, vector_of_indices>
    std::map<int, std::vector<int>> positions;
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
        positions[arr[i]].push_back(i);
    }

    // Precompute prefix maximums. pref_max[i] stores max(a[0...i]).
    std::vector<int> pref_max(n);
    pref_max[0] = arr[0];
    for (int i = 1; i < n; ++i) {
        pref_max[i] = std::max(pref_max[i - 1], arr[i]);
    }

    // Initialize and build the segment tree.
    N_seg = n; // Set the size for segment tree operations.
    tree.assign(4 * n, {0, 0}); // Clear and resize tree for each test case.
    build(1, 0, n - 1); // Build the segment tree starting from root (node_idx 1).

    // Iterate through possible lengths 'x_len' for the first part.
    // 'x_len' is 1-indexed length. In 0-indexed array, first part is a[0...x_len-1].
    // 'x_len' must be at least 1.
    // The second part (length y_len) and third part (length z_len) must also be at least 1.
    // So, x_len + y_len + z_len = n => x_len + 1 + 1 <= n => x_len <= n-2.
    for (int x_len = 1; x_len <= n - 2; ++x_len) {
        int V = pref_max[x_len - 1]; // The common value V is the max of the first part.

        // We need to find 'p' (0-indexed end of the second part).
        // Second part: a[x_len...p].
        // Third part: a[p+1...n-1].
        // Constraints on 'p': p must be at least x_len (for y_len >= 1) and at most n-2 (for z_len >= 1).

        // --- Determine valid range for 'p' based on Condition 1: min(a[x_len...p]) == V ---
        // Condition 1a: All elements in a[x_len...p] must be >= V.
        // This means 'p' must be less than the first index 'k' in [x_len, n-1] where a[k] < V.
        // R_bound_1 is the maximum possible 'p' satisfying this.
        int R_bound_1 = find_first_less(1, 0, n - 1, x_len, n - 1, V) - 1;
        
        // Condition 1b: At least one element in a[x_len...p] must be V.
        // This means 'p' must be greater than or equal to the first index 'k' in [x_len, n-1] where a[k] == V.
        // L_bound_1 is the minimum possible 'p' satisfying this.
        auto it_eq_1 = std::lower_bound(positions[V].begin(), positions[V].end(), x_len);
        int L_bound_1 = (it_eq_1 == positions[V].end()) ? n : *it_eq_1; // If V not found, set to n (invalid index).

        // --- Determine valid range for 'p' based on Condition 2: max(a[p+1...n-1]) == V ---
        // Condition 2a: All elements in a[p+1...n-1] must be <= V.
        // This means 'p+1' must be greater than the last index 'k' in [p+1, n-1] where a[k] > V.
        // We find the last index 'k' in [x_len+1, n-1] where a[k] > V.
        int last_idx_gt_V_in_suffix = find_last_greater(1, 0, n - 1, x_len + 1, n - 1, V);
        int L_bound_2; // This is the lower bound for 'p' based on Condition 2a.
        if (last_idx_gt_V_in_suffix == -1) {
            // If no element > V exists in [x_len+1, n-1], then all elements in this range are <= V.
            // So, p+1 can start from x_len+1, meaning p can be x_len.
            L_bound_2 = x_len; 
        } else {
            // If an element > V exists at 'last_idx_gt_V_in_suffix', then p+1 must be after it.
            // So, p+1 >= last_idx_gt_V_in_suffix + 1, which means p >= last_idx_gt_V_in_suffix.
            L_bound_2 = last_idx_gt_V_in_suffix; 
        }
        
        // Condition 2b: At least one element in a[p+1...n-1] must be V.
        // This means 'p+1' must be less than or equal to the last index 'k' in [p+1, n-1] where a[k] == V.
        // We find the last index 'k' in [0, n-1] where a[k] == V.
        auto it_eq_2 = std::upper_bound(positions[V].begin(), positions[V].end(), n - 1);
        int R_bound_2; // This is the upper bound for 'p' based on Condition 2b.
        if (it_eq_2 == positions[V].begin()) { 
            // If no V exists in the entire array, or all V's are after n-1 (impossible).
            R_bound_2 = x_len - 1; // Effectively no valid p.
        } else {
            it_eq_2--; // 'it_eq_2' now points to the last occurrence of V in [0, n-1].
            // We need this occurrence to be in the third part, i.e., its index must be >= p+1.
            // So, p+1 <= *it_eq_2, which means p <= *it_eq_2 - 1.
            // Also, this occurrence must be at or after x_len+1 (start of the potential third part).
            if (*it_eq_2 < x_len + 1) {
                R_bound_2 = x_len - 1; // No V in the range [x_len+1, n-1].
            } else {
                R_bound_2 = *it_eq_2 - 1;
            }
        }

        // Calculate the overall valid range for 'p' by intersecting all bounds.
        // 'p' must also satisfy the overall constraints: p >= x_len and p <= n-2.
        int p_min_candidate = std::max({x_len, L_bound_1, L_bound_2});
        int p_max_candidate = std::min({n - 2, R_bound_1, R_bound_2});

        // If the calculated range for 'p' is valid (min <= max), we found a solution.
        if (p_min_candidate <= p_max_candidate) {
            int p = p_min_candidate; // Choose the smallest valid 'p'.
            int y_len = p - x_len + 1; // Calculate length of second part.
            int z_len = n - (x_len + y_len); // Calculate length of third part.
            std::cout << "YES\n";
            std::cout << x_len << " " << y_len << " " << z_len << "\n";
            return; // Found a solution, exit function for current test case.
        }
    }

    // If no solution is found after checking all possible x_len values.
    std::cout << "NO\n";
}

int main() {
    // Optimize C++ standard streams for competitive programming.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t;
    while (t--) {
        solve(); // Solve each test case.
    }

    return 0;
}

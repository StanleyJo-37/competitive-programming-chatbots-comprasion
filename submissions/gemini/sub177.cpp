#include <iostream>
#include <vector>
#include <algorithm> // For std::min, std::max, std::merge, std::upper_bound
#include <limits>    // For std::numeric_limits
#include <iomanip>   // For std::fixed, std::setprecision

// Define a large enough constant for array sizes.
// N can be up to 10^5, so 100005 provides a small buffer.
const int MAXN = 100005;

// Array to store the burn times of matchsticks.
// b_i can be up to 10^8, so long long is appropriate.
long long b[MAXN];

// Structure for a segment tree node.
// Each node stores:
// - min_val: The minimum b_i in the node's covered range.
// - max_val: The maximum b_i in the node's covered range.
// - sorted_b_values: A sorted vector of all b_i values in the node's covered range.
//   This vector is crucial for efficiently performing conditional range maximum queries.
struct Node {
    long long min_val;
    long long max_val;
    std::vector<long long> sorted_b_values;
};

// Segment tree array. A size of 4 * MAXN is typical for a segment tree.
Node tree[4 * MAXN];

// Global variable to store the total number of matchsticks (N).
// Used by segment tree functions to determine the full range [0, N-1].
int N_global;

// Function to build the segment tree.
// v: Current node index in the tree array.
// tl, tr: The range [tl, tr] that the current node v covers in the original b array.
void build(int v, int tl, int tr) {
    if (tl == tr) {
        // Base case: If it's a leaf node (covering a single element).
        // Store the b_i value directly.
        tree[v].min_val = b[tl];
        tree[v].max_val = b[tl];
        tree[v].sorted_b_values = {b[tl]}; // Vector contains just this single element.
    } else {
        // Recursive step: For an internal node.
        int tm = (tl + tr) / 2; // Calculate the middle point to split the range.
        build(2 * v, tl, tm);         // Recursively build the left child (2*v).
        build(2 * v + 1, tm + 1, tr); // Recursively build the right child (2*v+1).

        // Combine results from children:
        // The min_val for the current node is the minimum of its children's min_val.
        tree[v].min_val = std::min(tree[2 * v].min_val, tree[2 * v + 1].min_val);
        // The max_val for the current node is the maximum of its children's max_val.
        tree[v].max_val = std::max(tree[2 * v].max_val, tree[2 * v + 1].max_val);

        // Merge the sorted_b_values from children.
        // This creates a single sorted vector for the current node's range.
        tree[v].sorted_b_values.resize(tree[2 * v].sorted_b_values.size() + tree[2 * v + 1].sorted_b_values.size());
        std::merge(tree[2 * v].sorted_b_values.begin(), tree[2 * v].sorted_b_values.end(),
                   tree[2 * v + 1].sorted_b_values.begin(), tree[2 * v + 1].sorted_b_values.end(),
                   tree[v].sorted_b_values.begin());
    }
}

// Function to query the minimum b_i in a specified query range [l, r].
// v: Current node index.
// tl, tr: Range [tl, tr] covered by current node v.
// l, r: The query range [l, r].
long long query_min(int v, int tl, int tr, int l, int r) {
    if (l > r) {
        // If the query range is empty or outside the current node's range,
        // return a value that won't affect the minimum (e.g., max possible long long).
        return std::numeric_limits<long long>::max();
    }
    if (l == tl && r == tr) {
        // If the current node's range exactly matches the query range, return its precomputed min_val.
        return tree[v].min_val;
    }
    // If the query range partially overlaps or is fully contained within children's ranges,
    // recurse on children and combine results.
    int tm = (tl + tr) / 2;
    return std::min(query_min(2 * v, tl, tm, l, std::min(r, tm)), // Query left child
                    query_min(2 * v + 1, tm + 1, tr, std::max(l, tm + 1), r)); // Query right child
}

// Function to query the maximum b_i in a specified query range [l, r].
// v: Current node index.
// tl, tr: Range [tl, tr] covered by current node v.
// l, r: The query range [l, r].
long long query_max(int v, int tl, int tr, int l, int r) {
    if (l > r) {
        // If the query range is empty or outside the current node's range,
        // return a value that won't affect the maximum. Since b_i >= 1, 0 is a safe sentinel.
        return 0;
    }
    if (l == tl && r == tr) {
        // If the current node's range exactly matches the query range, return its precomputed max_val.
        return tree[v].max_val;
    }
    // If the query range partially overlaps or is fully contained within children's ranges,
    // recurse on children and combine results.
    int tm = (tl + tr) / 2;
    return std::max(query_max(2 * v, tl, tm, l, std::min(r, tm)), // Query left child
                    query_max(2 * v + 1, tm + 1, tr, std::max(l, tm + 1), r)); // Query right child
}

// Function to query the maximum of min(b_i, (b_i + T_rear) / 2.0) for matchsticks
// within the query range [l, r]. This is the "M_in" calculation.
// v: Current node index.
// tl, tr: Range [tl, tr] covered by current node v.
// l, r: The query range [l, r].
// T_rear: The minimum burn time among matchsticks [L, R] for the current query.
double query_M_in_val(int v, int tl, int tr, int l, int r, long long T_rear) {
    if (l > r) {
        // If the query range is empty or outside the current node's range,
        // return 0.0 as a neutral value for max operation.
        return 0.0;
    }
    if (l == tl && r == tr) {
        // If the current node's range exactly matches the query range.
        double max_val = 0.0; // Initialize max_val for this node's contribution.

        // Use std::upper_bound to find the first element in sorted_b_values that is strictly greater than T_rear.
        auto it_gt = std::upper_bound(tree[v].sorted_b_values.begin(), tree[v].sorted_b_values.end(), T_rear);

        // Case 1: Handle matchsticks where b_i <= T_rear.
        // If it_gt is not the beginning of the vector, it means there are elements <= T_rear.
        if (it_gt != tree[v].sorted_b_values.begin()) {
            // The element just before it_gt is the maximum b_i that is <= T_rear.
            long long max_le_T_rear = *(it_gt - 1);
            // For these matchsticks, the burn time is b_i. We take the maximum of these.
            max_val = std::max(max_val, (double)max_le_T_rear);
        }

        // Case 2: Handle matchsticks where b_i > T_rear.
        // If it_gt is not the end of the vector, it means there are elements > T_rear.
        if (it_gt != tree[v].sorted_b_values.end()) {
            // Since the vector is sorted, the largest element in the vector (tree[v].sorted_b_values.back())
            // will be the maximum among all b_i in this node's range.
            // If this branch is entered, it implies that this maximum element is > T_rear,
            // making it the relevant max_gt_T_rear.
            long long max_gt_T_rear = tree[v].sorted_b_values.back();
            // For these matchsticks, the burn time is (b_i + T_rear) / 2.0.
            // We take the maximum of these.
            max_val = std::max(max_val, (max_gt_T_rear + T_rear) / 2.0);
        }
        return max_val;
    }
    // If the query range partially overlaps or is fully contained within children's ranges,
    // recurse on children and combine results.
    int tm = (tl + tr) / 2;
    double left_res = query_M_in_val(2 * v, tl, tm, l, std::min(r, tm), T_rear);
    double right_res = query_M_in_val(2 * v + 1, tm + 1, tr, std::max(l, tm + 1), r, T_rear);
    return std::max(left_res, right_res);
}

int main() {
    // Optimize C++ standard streams for faster input/output.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::cin >> N_global; // Read N, the total number of matchsticks.

    // Read the burn times (b_i) for all matchsticks.
    for (int i = 0; i < N_global; ++i) {
        std::cin >> b[i];
    }

    // Build the segment tree covering the entire range of matchsticks [0, N_global - 1].
    build(1, 0, N_global - 1);

    int Q; // Read Q, the number of queries.
    std::cin >> Q;

    // Process each query.
    for (int q = 0; q < Q; ++q) {
        int L, R;
        std::cin >> L >> R; // Read the query range [L, R].

        // Step 1: Calculate T_rear.
        // T_rear is the earliest time any fire reaches the common rear end.
        // This is the minimum burn time among matchsticks [L, R] (those initially lit at free end).
        long long T_rear = query_min(1, 0, N_global - 1, L, R);

        // Step 2: Calculate the maximum burn time for matchsticks OUTSIDE the range [L, R].
        // These matchsticks are only lit from the rear end (at time T_rear).
        // Their total burn time is T_rear + b_i.
        // We need the maximum of these, which is T_rear + max(b_i) for i not in [L, R].
        long long M_out_val = 0; // Initialize with 0, as b_i >= 1.
        if (L > 0) {
            // Query for max b_i in range [0, L-1].
            M_out_val = std::max(M_out_val, query_max(1, 0, N_global - 1, 0, L - 1));
        }
        if (R < N_global - 1) {
            // Query for max b_i in range [R+1, N-1].
            M_out_val = std::max(M_out_val, query_max(1, 0, N_global - 1, R + 1, N_global - 1));
        }
        double ans_out_range = (double)T_rear + M_out_val;

        // Step 3: Calculate the maximum burn time for matchsticks INSIDE the range [L, R].
        // These matchsticks are lit at their free end at time 0 AND at their rear end at time T_rear.
        // Their total burn time is min(b_i, (b_i + T_rear) / 2.0).
        double ans_in_range = query_M_in_val(1, 0, N_global - 1, L, R, T_rear);

        // Step 4: The final answer is the maximum of the times calculated for both categories of matchsticks.
        double final_ans = std::max(ans_out_range, ans_in_range);

        // Print the answer formatted to one decimal place.
        std::cout << std::fixed << std::setprecision(1) << final_ans << "\n";
    }

    return 0;
}
#include <iostream>
#include <vector>
#include <algorithm>

// Define a struct for segment tree nodes.
// Each node stores information required to compute the minimum subarray sum within its range.
struct Node {
    long long total_sum;        // Sum of all elements in the node's range
    long long min_prefix_sum;   // Minimum sum of any prefix in the node's range
    long long min_suffix_sum;   // Minimum sum of any suffix in the node's range
    long long min_subarray_sum; // Minimum sum of any subarray in the node's range

    // Default constructor for an empty node or base case initialization.
    // Used when merging or initializing a node that doesn't represent a single element.
    Node() : total_sum(0), min_prefix_sum(0), min_suffix_sum(0), min_subarray_sum(0) {}

    // Constructor for a leaf node (representing a single element).
    // All sums for a single element are just its value.
    Node(long long val) : total_sum(val), min_prefix_sum(val), min_suffix_sum(val), min_subarray_sum(val) {}
};

// Function to merge two child nodes into a parent node.
// This is the core logic for segment tree operations on subarray sums.
Node merge(const Node& left, const Node& right) {
    Node res;
    // The total sum of the parent is the sum of its children's total sums.
    res.total_sum = left.total_sum + right.total_sum;
    
    // The minimum prefix sum can be either from the left child, or the sum of the left child's
    // total sum plus the right child's minimum prefix sum (if the minimum prefix spans both children).
    res.min_prefix_sum = std::min(left.min_prefix_sum, left.total_sum + right.min_prefix_sum);
    
    // The minimum suffix sum can be either from the right child, or the sum of the right child's
    // total sum plus the left child's minimum suffix sum (if the minimum suffix spans both children).
    res.min_suffix_sum = std::min(right.min_suffix_sum, right.total_sum + left.min_suffix_sum);
    
    // The minimum subarray sum can be:
    // 1. The minimum subarray sum from the left child.
    // 2. The minimum subarray sum from the right child.
    // 3. A subarray that spans across both children, formed by a suffix of the left child
    //    and a prefix of the right child.
    res.min_subarray_sum = std::min({left.min_subarray_sum, right.min_subarray_sum, left.min_suffix_sum + right.min_prefix_sum});
    return res;
}

// Segment Tree class to efficiently query minimum subarray sums and perform point updates.
class SegmentTree {
private:
    int size; // The size of the array (m in the problem)
    std::vector<Node> tree; // The segment tree nodes
    std::vector<int> initial_vals; // Stores the initial values for building the tree

    // Recursive function to build the segment tree.
    // node_idx: current node's index in the tree vector.
    // tl, tr: range [tl, tr] covered by the current node.
    void build(int node_idx, int tl, int tr) {
        if (tl == tr) {
            // Leaf node: initialize with the value of the corresponding element.
            tree[node_idx] = Node(initial_vals[tl]);
        } else {
            int tm = (tl + tr) / 2; // Midpoint
            build(2 * node_idx, tl, tm);         // Build left child (2*node_idx)
            build(2 * node_idx + 1, tm + 1, tr); // Build right child (2*node_idx + 1)
            // Merge results from children to compute current node's values.
            tree[node_idx] = merge(tree[2 * node_idx], tree[2 * node_idx + 1]);
        }
    }

    // Recursive function to update a single element in the segment tree.
    // pos: the index of the element to update.
    // new_val: the new value for the element at 'pos'.
    void update(int node_idx, int tl, int tr, int pos, int new_val) {
        if (tl == tr) {
            // Found the leaf node for 'pos', update its value.
            tree[node_idx] = Node(new_val);
        } else {
            int tm = (tl + tr) / 2;
            if (pos <= tm) {
                update(2 * node_idx, tl, tm, pos, new_val); // Update in left child's subtree
            } else {
                update(2 * node_idx + 1, tm + 1, tr, pos, new_val); // Update in right child's subtree
            }
            // After updating a child, re-merge children to update current node.
            tree[node_idx] = merge(tree[2 * node_idx], tree[2 * node_idx + 1]);
        }
    }

public:
    // Constructor for SegmentTree.
    // m: the maximum coordinate (size of the range [1, m]).
    // vals: initial values for the array elements (1-indexed).
    SegmentTree(int m, const std::vector<int>& vals) : size(m), initial_vals(vals) {
        tree.resize(4 * size); // Allocate memory for the tree (4*size is a safe upper bound for array-based tree).
        build(1, 1, size);     // Build the tree starting from root (node 1) covering range [1, size].
    }

    // Public method to update an element at a given position with a new value.
    void update(int pos, int new_val) {
        update(1, 1, size, pos, new_val);
    }

    // Public method to query the minimum subarray sum for the entire range [1, size].
    // This is simply the min_subarray_sum stored in the root node.
    long long query_min_subarray_sum() {
        return tree[1].min_subarray_sum;
    }
};

int main() {
    // Optimize C++ standard streams for faster input/output.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, m;
    std::cin >> n >> m;

    // Step 1: Compute actual_cnt[x] for x in [1, m] using a sweep line approach.
    // diff array stores changes in segment counts.
    // diff[i]++ means a segment starts at i.
    // diff[i]-- means a segment ends at i-1 (so it doesn't cover i).
    std::vector<int> diff(m + 2, 0); // Size m+2 for 1-based indexing up to m+1
    for (int i = 0; i < n; ++i) {
        int l, r;
        std::cin >> l >> r;
        diff[l]++;
        diff[r + 1]--;
    }

    std::vector<int> actual_cnt(m + 1); // actual_cnt[x] stores the number of segments covering point x.
    int current_count = 0;
    for (int x = 1; x <= m; ++x) {
        current_count += diff[x];
        actual_cnt[x] = current_count;
    }

    // Step 2: Group points by their actual_cnt value.
    // positions_by_count[v] will store a list of indices x such that actual_cnt[x] = v.
    // Max count can be n, so size n+1 for 0-indexed counts.
    std::vector<std::vector<int>> positions_by_count(n + 1); 
    for (int x = 1; x <= m; ++x) {
        positions_by_count[actual_cnt[x]].push_back(x);
    }

    // Step 3: Initialize the segment tree for K=0.
    // For a hypothetical scenario where N_hypothetical segments all contain a point p,
    // the count for points x in the intersection [L,R] of these segments would be N_hypothetical,
    // and for points x outside [L,R], the count would be < N_hypothetical.
    // Sasha can't be sure Teodor isn't lying if there exists such a K (N_hypothetical) and [L,R]
    // that is consistent with the observed actual_cnt values.
    // We want to maximize the number of points x for which (actual_cnt[x] == K AND x in [L,R])
    // OR (actual_cnt[x] < K AND x not in [L,R]).
    // This is equivalent to minimizing "bad" points:
    // (actual_cnt[x] != K AND x in [L,R]) OR (actual_cnt[x] == K AND x not in [L,R]).
    // Let cost[x] = 1 if actual_cnt[x] != K, and 0 if actual_cnt[x] == K.
    // Total bad points = sum_{x=L to R} cost[x] + sum_{x=1 to L-1} (1-cost[x]) + sum_{x=R+1 to M} (1-cost[x])
    // This simplifies to: (sum_{x=1 to M} (1-cost[x])) + (sum_{x=L to R} (2*cost[x] - 1)).
    // The first term is `count_K` (number of points where actual_cnt[x] == K).
    // The second term is `sum_{x=L to R} val[x]`, where val[x] = 2*cost[x] - 1.
    // So, val[x] = -1 if actual_cnt[x] == K, and val[x] = 1 if actual_cnt[x] != K.
    // Wait, the problem statement for val[x] was:
    // val[x] = 2 if actual_cnt[x] != K, val[x] = -1 if actual_cnt[x] = K.
    // This is correct. The formula for bad points is `count_K + min_sum_val_range`.
    // For K=0, val[x] is -1 if actual_cnt[x] == 0, else 2.
    std::vector<int> initial_vals(m + 1); // 1-indexed
    for (int x = 1; x <= m; ++x) {
        initial_vals[x] = (actual_cnt[x] == 0) ? -1 : 2;
    }
    SegmentTree st(m, initial_vals);

    long long max_ans = 0; // Stores the maximum number of points Sasha can ask about.

    // Step 4: Iterate K from 0 to n.
    // K represents the hypothetical number of segments (N_hypothetical) that all contain a common point.
    // The loop goes up to n because N_hypothetical could be n.
    // The problem guarantees that for the actual picture, no point belongs to all n segments.
    // So, actual_cnt[x] will never be n.
    // If K=n, then actual_cnt[x] will never be equal to K. So all val[x] will be 2.
    for (int K = 0; K <= n; ++K) {
        // Query the minimum subarray sum for the current configuration of val[x] values.
        long long min_sum_val_range = st.query_min_subarray_sum();
        
        // count_K is the number of points x where actual_cnt[x] == K.
        long long count_K = positions_by_count[K].size();
        
        // Calculate the total number of "bad" points for this K.
        // This is `count_K` (points that are supposed to be inside [L,R] but are outside)
        // plus `min_sum_val_range` (which accounts for points inside [L,R] that are "bad"
        // and points outside [L,R] that are "bad").
        long long current_bad_points = count_K + min_sum_val_range;
        
        // The number of points Sasha can ask about is M - current_bad_points.
        // We want to maximize this value over all possible K.
        max_ans = std::max(max_ans, m - current_bad_points);

        // Prepare for the next iteration (K+1):
        // For points x where actual_cnt[x] == K, their val[x] was -1 (because actual_cnt[x] == K).
        // For K+1, actual_cnt[x] will be < K+1 (specifically, K), so val[x] becomes 2.
        for (int x_idx : positions_by_count[K]) {
            st.update(x_idx, 2);
        }
        
        // For points x where actual_cnt[x] == K+1, their val[x] was 2 (because actual_cnt[x] != K).
        // For K+1, actual_cnt[x] will be equal to K+1, so val[x] becomes -1.
        // This update only happens if K+1 is a valid count (i.e., K+1 <= n).
        if (K + 1 <= n) {
            for (int x_idx : positions_by_count[K + 1]) {
                st.update(x_idx, -1);
            }
        }
    }

    std::cout << max_ans << std::endl;

    return 0;
}
#include <iostream>
#include <vector>
#include <algorithm> // Required for std::lower_bound and std::max

// Global vector to represent the segment tree.
// It stores the maximum dp value in each segment.
std::vector<int> tree;
// N_SEG_TREE stores the size of the original array for which the segment tree is built.
int N_SEG_TREE;

/**
 * @brief Updates a value in the segment tree.
 *
 * This function updates the dp value at a specific index in the segment tree.
 * The segment tree is used to efficiently query maximum dp values in ranges.
 *
 * @param node The current node index in the `tree` vector.
 * @param start The starting index of the range covered by the current node.
 * @param end The ending index of the range covered by the current node.
 * @param idx The index in the original array whose dp value needs to be updated.
 * @param val The new dp value to set at `idx`.
 */
void update(int node, int start, int end, int idx, int val) {
    // Base case: If the current node represents a single element (leaf node)
    // and it's the target index, update its value.
    if (start == end) {
        tree[node] = val;
    } else {
        // Recursive step: Determine which child node covers the target index.
        int mid = (start + end) / 2;
        if (start <= idx && idx <= mid) {
            // If idx is in the left child's range, recurse on the left child.
            update(2 * node, start, mid, idx, val);
        } else {
            // If idx is in the right child's range, recurse on the right child.
            update(2 * node + 1, mid + 1, end, idx, val);
        }
        // After updating the child, update the current node's value.
        // The current node's value is the maximum of its children's values.
        tree[node] = std::max(tree[2 * node], tree[2 * node + 1]);
    }
}

/**
 * @brief Queries the maximum value in a given range [l, r] from the segment tree.
 *
 * This function efficiently finds the maximum dp value within a specified range
 * of indices in the original array.
 *
 * @param node The current node index in the `tree` vector.
 * @param start The starting index of the range covered by the current node.
 * @param end The ending index of the range covered by the current node.
 * @param l The left boundary of the query range.
 * @param r The right boundary of the query range.
 * @return The maximum dp value found in the query range. Returns 0 if the range
 *         is invalid or outside the current node's coverage, as dp values are
 *         always at least 1.
 */
int query(int node, int start, int end, int l, int r) {
    // Case 1: The current node's range is completely outside the query range.
    // Return 0, as it doesn't contribute to the maximum.
    if (r < start || end < l) {
        return 0;
    }
    // Case 2: The current node's range is completely within the query range.
    // Return the value stored in this node.
    if (l <= start && end <= r) {
        return tree[node];
    }
    // Case 3: The current node's range partially overlaps the query range.
    // Recurse on both children and return the maximum of their results.
    int mid = (start + end) / 2;
    int p1 = query(2 * node, start, mid, l, r);
    int p2 = query(2 * node + 1, mid + 1, end, l, r);
    return std::max(p1, p2);
}

int main() {
    // Optimize C++ standard streams for faster input/output.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    std::cin >> n; // Read the number of problems

    // Handle edge cases for n=0 or n=1 explicitly.
    // A contest with 0 problems is not possible.
    // A contest with 1 problem is always valid.
    if (n == 0) {
        std::cout << 0 << std::endl;
        return 0;
    }
    if (n == 1) {
        std::cout << 1 << std::endl;
        return 0;
    }

    // Use long long for difficulties as they can be up to 10^9.
    std::vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i]; // Read problem difficulties
    }

    // Set the size for the segment tree. A segment tree typically needs 4*N space.
    N_SEG_TREE = n;
    tree.resize(4 * N_SEG_TREE, 0); // Initialize all segment tree nodes to 0.

    int max_overall_len = 0; // Stores the maximum length of a valid contest found so far.

    // Iterate through each problem from left to right (increasing difficulty).
    // For each problem a[i], we calculate the maximum length of a contest ending with it.
    for (int i = 0; i < n; ++i) {
        // Calculate the minimum difficulty 'a_j' a previous problem must have
        // to satisfy the condition: a[i] <= a_j * 2, which implies a_j >= a[i] / 2.
        // (a[i] + 1) / 2 correctly computes ceil(a[i] / 2.0) for positive integers.
        long long target_val = (a[i] + 1) / 2;

        // Find the index 'k' of the first problem 'a[k]' in the sorted array
        // such that a[k] >= target_val. We only search among problems before a[i].
        // std::lower_bound returns an iterator to the first element not less than target_val.
        auto it = std::lower_bound(a.begin(), a.begin() + i, target_val);
        int k = it - a.begin(); // Convert the iterator to an index.

        int max_prev_dp = 0; // Initialize max_prev_dp to 0 (no valid previous problem found yet).

        // If there are problems in the range [k, i-1] (i.e., k is a valid start index
        // and there's at least one problem before a[i]), query the segment tree.
        if (k < i) {
            // Query the segment tree for the maximum dp value in the range [k, i-1].
            // This gives the maximum length of a valid contest ending at some a[j]
            // where a[j] satisfies the condition to precede a[i].
            max_prev_dp = query(1, 0, N_SEG_TREE - 1, k, i - 1);
        }

        // The current problem a[i] extends the longest contest found among valid previous problems.
        // If max_prev_dp is 0, it means no valid previous problem was found, so a[i] starts a new contest of length 1.
        int current_dp_val = 1 + max_prev_dp;

        // Update the segment tree with the calculated dp value for a[i] at its index i.
        update(1, 0, N_SEG_TREE - 1, i, current_dp_val);

        // Update the overall maximum length found so far.
        max_overall_len = std::max(max_overall_len, current_dp_val);
    }

    // Print the final maximum length of a valid contest.
    std::cout << max_overall_len << std::endl;

    return 0;
}

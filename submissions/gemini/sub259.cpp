#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

// Global vector for the segment tree.
// It's declared globally to be easily accessible by segment tree functions
// and reset for each test case.
std::vector<int> tree;
// N_SEG_TREE stores the effective size of the array that the segment tree covers.
int N_SEG_TREE;

// Function to update a value at a specific index in the segment tree.
// node: current node in the segment tree (root is 1).
// start, end: range covered by the current node.
// idx: the index in the original array (0 to N_SEG_TREE-1) to update.
// val: the new value to set at idx.
void update(int node, int start, int end, int idx, int val) {
    // If the current segment is a leaf node (contains a single element)
    if (start == end) {
        // Update the value at this leaf node.
        // We take max because multiple elements in 'a' might map to the same 'b[j]'
        // (e.g., if a[i] and a[k] both map to b[j] and k < i, we want the best result).
        // However, in this specific problem, each a[i] maps to a unique b[j] based on its occurrence count.
        // So, it's effectively a point update, but max ensures correctness if an element
        // could potentially extend a sequence in multiple ways (though not applicable here).
        tree[node] = std::max(tree[node], val);
    } else {
        // If not a leaf node, determine which child to recurse into.
        int mid = (start + end) / 2;
        if (start <= idx && idx <= mid) {
            // If idx is in the left child's range, recurse left.
            update(2 * node, start, mid, idx, val);
        } else {
            // If idx is in the right child's range, recurse right.
            update(2 * node + 1, mid + 1, end, idx, val);
        }
        // After updating the child, update the current node.
        // An internal node stores the maximum value in its range.
        tree[node] = std::max(tree[2 * node], tree[2 * node + 1]);
    }
}

// Function to query the maximum value in a specific range [l, r] in the segment tree.
// node: current node in the segment tree.
// start, end: range covered by the current node.
// l, r: the query range.
int query(int node, int start, int end, int l, int r) {
    // If the current segment is completely outside the query range, return 0.
    // 0 is used as the identity element for max operation (it won't affect the max).
    if (r < start || end < l) {
        return 0;
    }
    // If the current segment is completely within the query range, return its value.
    if (l <= start && end <= r) {
        return tree[node];
    }
    // Otherwise, the query range partially overlaps with the current segment.
    // Recurse on children and return the maximum of their results.
    int mid = (start + end) / 2;
    int p1 = query(2 * node, start, mid, l, r);
    int p2 = query(2 * node + 1, mid + 1, end, l, r);
    return std::max(p1, p2);
}

// Main solve function for each test case.
void solve() {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    std::vector<int> b(n); // 'b' will store the sorted version of 'a'.
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
        b[i] = a[i]; // Copy elements to 'b'.
    }

    // Sort 'b' to get the target sorted array.
    std::sort(b.begin(), b.end());

    // Map to store indices in 'b' for each value.
    // Key: value, Value: vector of indices where this value appears in 'b'.
    // This helps in mapping an element from 'a' to its specific occurrence in 'b'.
    std::map<int, std::vector<int>> b_indices_for_val;
    for (int j = 0; j < n; ++j) {
        b_indices_for_val[b[j]].push_back(j);
    }

    // Map to keep track of how many times each value has been encountered in 'a' so far.
    // This is crucial for correctly picking the 'j' from b_indices_for_val.
    std::map<int, int> current_counts;

    // Initialize segment tree for the current test case.
    // The segment tree will cover indices from 0 to n-1.
    N_SEG_TREE = n;
    // Resize and clear the tree for the new test case. All values become 0.
    tree.assign(4 * N_SEG_TREE, 0); 

    int max_len = 0; // Stores the maximum length of the non-decreasing subsequence found.

    // Iterate through the original array 'a' to build the DP solution.
    for (int i = 0; i < n; ++i) {
        int val = a[i];
        current_counts[val]++; // Increment the count for the current value.
        int occurrence_num = current_counts[val]; // This is the k-th occurrence of 'val'.

        // Check if this k-th occurrence of 'val' actually exists in the sorted array 'b'.
        // If not, it means this 'val' is an "extra" element that cannot be part of the
        // desired sorted subsequence, so we skip it.
        if (occurrence_num > b_indices_for_val[val].size()) {
            continue; 
        }

        // Get the specific index 'j' in 'b' that this 'a[i]' (this occurrence of 'val') corresponds to.
        // We use occurrence_num - 1 because vector indices are 0-based.
        int j = b_indices_for_val[val][occurrence_num - 1];

        // 'current_dp_val' will store the length of the longest valid subsequence ending at b[j]
        // that includes a[i].
        // It can always start a new subsequence of length 1.
        int current_dp_val = 1; 

        // If 'j > 0', this element 'b[j]' could potentially extend a sequence ending at 'b[j-1]'.
        if (j > 0) {
            // Query the segment tree for the maximum length of a subsequence ending at b[j-1].
            // This 'prev_dp_val' represents the longest sequence ending at b[j-1]
            // using elements from a[0...i-1] (due to how segment tree updates work).
            int prev_dp_val = query(1, 0, N_SEG_TREE - 1, j - 1, j - 1);
            // If b[j-1] was successfully matched by an earlier element (prev_dp_val > 0),
            // then a[i] can extend that sequence.
            // We take the maximum of starting a new sequence (1) or extending the previous one.
            current_dp_val = std::max(current_dp_val, prev_dp_val + 1);
        }
        
        // Update the segment tree at index 'j' with the new maximum length found for b[j].
        update(1, 0, N_SEG_TREE - 1, j, current_dp_val);
        
        // Update the overall maximum length found across all possible ending points in 'b'.
        max_len = std::max(max_len, current_dp_val);
    }

    // The minimum number of operations is the total number of elements (n)
    // minus the maximum number of elements that can be kept in place (max_len).
    std::cout << n - max_len << std::endl;
}

int main() {
    // Optimize C++ standard streams for competitive programming.
    // This unties C++ streams from C standard streams and prevents flushing
    // operations, leading to faster I/O.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t; // Read the number of test cases.
    while (t--) {
        solve(); // Solve each test case.
    }

    return 0;
}

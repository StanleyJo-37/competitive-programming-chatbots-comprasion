#include <iostream>
#include <vector>
#include <algorithm>

// Global arrays for segment tree and permutation data
std::vector<int> P; // Stores the permutation
std::vector<int> tree; // Segment tree to store range maximums

// Function to build the segment tree
// node_idx: current node index in the tree array
// tree_l, tree_r: range covered by the current node
void build(int node_idx, int tree_l, int tree_r) {
    // If it's a leaf node, store the value from the permutation array
    if (tree_l == tree_r) {
        tree[node_idx] = P[tree_l];
        return;
    }
    // Recursively build left and right children
    int mid = tree_l + (tree_r - tree_l) / 2;
    build(2 * node_idx, tree_l, mid);
    build(2 * node_idx + 1, mid + 1, tree_r);
    // Current node stores the maximum of its children's ranges
    tree[node_idx] = std::max(tree[2 * node_idx], tree[2 * node_idx + 1]);
}

// Function to query for records in a given range [query_l, query_r]
// node_idx: current node index in the tree array
// tree_l, tree_r: range covered by the current node
// query_l, query_r: range for which we want to count records
// current_max: the maximum value encountered so far before the current segment
// Returns a pair: {new_max_so_far, records_count_in_this_query_range}
std::pair<int, int> count_records_query(int node_idx, int tree_l, int tree_r, int query_l, int query_r, int current_max) {
    // If the current segment is completely outside the query range, return current_max and 0 records
    if (tree_l > query_r || tree_r < query_l) {
        return {current_max, 0};
    }

    // If the maximum value in the current segment is not greater than current_max,
    // no new records can be formed in this segment. Return current_max and 0 records.
    if (tree[node_idx] <= current_max) {
        return {current_max, 0};
    }

    // If it's a leaf node and its value is greater than current_max, it's a new record
    if (tree_l == tree_r) {
        return {P[tree_l], 1};
    }

    // Recursively query left and right children
    int mid = tree_l + (tree_r - tree_l) / 2;
    // Query left child, passing current_max
    std::pair<int, int> left_res = count_records_query(2 * node_idx, tree_l, mid, query_l, query_r, current_max);
    // Query right child, passing the updated max from the left child's result
    std::pair<int, int> right_res = count_records_query(2 * node_idx + 1, mid + 1, tree_r, query_l, query_r, left_res.first);

    // Combine results: new max is the max of left and right results, total records is sum of records
    return {std::max(left_res.first, right_res.first), left_res.second + right_res.second};
}

int main() {
    // Optimize C++ standard streams for faster input/output.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    std::cin >> n;

    P.resize(n);
    // p_val_to_idx[value] stores the 0-based index of 'value' in the permutation P
    std::vector<int> p_val_to_idx(n + 1); 
    for (int i = 0; i < n; ++i) {
        std::cin >> P[i];
        p_val_to_idx[P[i]] = i;
    }

    // Initialize segment tree with size 4*N for safety (standard practice for segment trees)
    tree.resize(4 * n);
    build(1, 0, n - 1); // Build the segment tree starting from root (node 1) covering range [0, n-1]

    // Identify records in the original permutation
    std::vector<int> records_indices; // Stores indices of records
    std::vector<int> records_values;  // Stores values of records
    std::vector<bool> is_record(n, false); // is_record[i] is true if P[i] is a record
    int current_max_val = 0;
    for (int i = 0; i < n; ++i) {
        if (P[i] > current_max_val) {
            records_indices.push_back(i);
            records_values.push_back(P[i]);
            is_record[i] = true;
            current_max_val = P[i];
        }
    }
    int R0 = records_values.size(); // Total records in the original permutation

    // record_rank_by_value[value] stores the rank (0-based index) of 'value' in records_values
    // This is used to quickly find the previous record's value when a record is removed.
    std::vector<int> record_rank_by_value(n + 1);
    for (int j = 0; j < records_values.size(); ++j) {
        record_rank_by_value[records_values[j]] = j;
    }

    int max_overall_records = -1; // Stores the maximum number of records found
    int ans_element = -1;         // Stores the element to remove to achieve max_overall_records (smallest if tie)

    // Iterate through each element of the permutation to consider its removal
    for (int i = 0; i < n; ++i) {
        int removed_val = P[i];
        int current_records_after_removal;

        if (!is_record[i]) {
            // Case 1: The removed element P[i] was NOT a record in the original permutation.
            // Removing a non-record does not change the record status of any other element.
            // So, the number of records remains R0.
            current_records_after_removal = R0;
        } else {
            // Case 2: The removed element P[i] WAS a record in the original permutation.
            // The number of records decreases by 1 (P[i] itself is removed).
            current_records_after_removal = R0 - 1;

            // Find the value of the record immediately preceding P[i] in the original sequence of records.
            // This value becomes the 'current_max' for counting new records in the suffix.
            int j = record_rank_by_value[removed_val]; // Get rank of removed_val among records
            int prev_record_val = (j == 0) ? 0 : records_values[j - 1]; // If P[i] was the first record, prev_max is 0

            // Count new records in the suffix P[i+1 ... n-1]
            // The query range starts from i+1 to n-1.
            // The initial max for this suffix is prev_record_val.
            if (i + 1 < n) { // If there are elements after P[i]
                std::pair<int, int> res = count_records_query(1, 0, n - 1, i + 1, n - 1, prev_record_val);
                current_records_after_removal += res.second; // Add the count of new records
            }
        }

        // Update max_overall_records and ans_element
        if (current_records_after_removal > max_overall_records) {
            max_overall_records = current_records_after_removal;
            ans_element = removed_val;
        } else if (current_records_after_removal == max_overall_records) {
            // If tie in record count, choose the smallest removed element
            ans_element = std::min(ans_element, removed_val);
        }
    }

    std::cout << ans_element << std::endl;

    return 0;
}

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

// Define maximum N for array sizes. MAXN is 10^5, so 100005 provides a small buffer.
const int MAXN = 100005;

// Segment tree node structure
struct Node {
    long long max_val; // Stores the maximum count value in the node's range.
                       // Using long long to accommodate large negative values for "removed" positions.
    long long lazy_C;  // Lazy tag for range updates:
                       // 0: no lazy tag.
                       // -1: indicates that the entire range covered by this node should be considered "removed"
                       //     (i.e., its values are set to a very small number like -2e18).
                       // >0: indicates that for any position 'k' in this node's range, its count value
                       //     should be calculated as 'k - lazy_C'.
};

Node tree[4 * MAXN]; // Segment tree array. Size 4*MAXN is typical for segment trees.
int p_pos[MAXN];     // p_pos[val] stores the 1-indexed position where 'val' is found in the input permutation 'p'.

// Set to store 1-indexed occupied positions. Used to find 'prev_occ' and 'next_occ'.
std::set<int> occupied_positions;

// Function to push lazy tags down to children nodes.
// This ensures that when a query or update operation traverses down the tree,
// the values in child nodes are up-to-date before further processing.
void push(int v, int tl, int tr) {
    if (tree[v].lazy_C != 0) { // If there's a lazy tag to push
        int tm = (tl + tr) / 2; // Midpoint of the current node's range [tl, tr]

        // Apply lazy tag to the left child (node 2*v)
        if (tree[v].lazy_C == -1) { // If the tag means "remove" (set to -infinity)
            tree[2 * v].max_val = -2e18; // Set max_val to a very small number
            tree[2 * v].lazy_C = -1;     // Propagate the -1 lazy tag
        } else { // If the tag means "k - C" update
            // The maximum value in the left child's range [tl, tm] will be tm - lazy_C.
            tree[2 * v].max_val = (long long)tm - tree[v].lazy_C;
            tree[2 * v].lazy_C = tree[v].lazy_C; // Propagate the C lazy tag
        }

        // Apply lazy tag to the right child (node 2*v + 1)
        if (tree[v].lazy_C == -1) { // If the tag means "remove" (set to -infinity)
            tree[2 * v + 1].max_val = -2e18; // Set max_val to a very small number
            tree[2 * v + 1].lazy_C = -1;     // Propagate the -1 lazy tag
        } else { // If the tag means "k - C" update
            // The maximum value in the right child's range [tm+1, tr] will be tr - lazy_C.
            tree[2 * v + 1].max_val = (long long)tr - tree[v].lazy_C;
            tree[2 * v + 1].lazy_C = tree[v].lazy_C; // Propagate the C lazy tag
        }
        
        tree[v].lazy_C = 0; // Clear the lazy tag of the current node after pushing
    }
}

// Builds the segment tree.
// Initially, for any position 'k', the 'last_occupied_before[k]' is 0 (as no positions are occupied).
// So, count[k] = k - 0 = k.
void build(int v, int tl, int tr) {
    tree[v].lazy_C = 0; // Initialize lazy tag to 0 (no pending updates)
    if (tl == tr) { // If it's a leaf node
        tree[v].max_val = tl; // Set its value to 'k' (which is 'tl' for a leaf)
    } else { // If it's an internal node
        int tm = (tl + tr) / 2;
        build(2 * v, tl, tm);         // Recursively build left child
        build(2 * v + 1, tm + 1, tr); // Recursively build right child
        // The max_val of an internal node is the maximum of its children's max_val.
        tree[v].max_val = std::max(tree[2 * v].max_val, tree[2 * v + 1].max_val);
    }
}

// Performs a range update operation on the segment tree.
// If C == -1, it effectively "removes" positions in [L, R] by setting their values to -infinity.
// If C > 0, it updates positions 'k' in [L, R] to 'k - C'.
void update_range(int v, int tl, int tr, int L, int R, long long C) {
    if (L > R) return; // Invalid or empty update range
    if (L == tl && R == tr) { // If the current node's range [tl, tr] is fully contained within [L, R]
        if (C == -1) {
            tree[v].max_val = -2e18; // Set to -infinity
        } else {
            // For a range [tl, tr] with values k - C, the maximum value is tr - C.
            tree[v].max_val = (long long)tr - C;
        }
        tree[v].lazy_C = C; // Apply the lazy tag to this node
    } else { // If the current node's range partially overlaps or contains [L, R]
        push(v, tl, tr); // Push down any existing lazy tags before recursing
        int tm = (tl + tr) / 2;
        // Recursively update the left child
        update_range(2 * v, tl, tm, L, std::min(R, tm), C);
        // Recursively update the right child
        update_range(2 * v + 1, tm + 1, tr, std::max(L, tm + 1), R, C);
        // After children are updated, recalculate the max_val for the current node.
        tree[v].max_val = std::max(tree[2 * v].max_val, tree[2 * v + 1].max_val);
    }
}

// Performs a range query operation on the segment tree to find the maximum value in [L, R].
long long query_range(int v, int tl, int tr, int L, int R) {
    if (L > R) return -2e18; // Return -infinity for an empty or invalid query range
    if (L == tl && R == tr) { // If the current node's range [tl, tr] is fully contained within [L, R]
        return tree[v].max_val; // Return its stored max_val
    }
    push(v, tl, tr); // Push down any existing lazy tags before recursing
    int tm = (tl + tr) / 2;
    // Recursively query left and right children and return the maximum of their results.
    return std::max(query_range(2 * v, tl, tm, L, std::min(R, tm)),
                    query_range(2 * v + 1, tm + 1, tr, std::max(L, tm + 1), R));
}

// Solves a single test case.
void solve() {
    int n;
    std::cin >> n;

    // Read the permutation and store the 1-indexed position for each value.
    // For example, if p = [2, 3, 4, 5, 1], then p_pos[1]=5, p_pos[2]=1, p_pos[3]=2, etc.
    for (int i = 1; i <= n; ++i) {
        int p_val;
        std::cin >> p_val;
        p_pos[p_val] = i;
    }

    // Clear the set of occupied positions for the new test case.
    occupied_positions.clear();

    // Build the segment tree for the current 'n'.
    build(1, 1, n);

    bool possible = true; // Flag to track if the permutation can be generated.
    // Simulate the generator steps for numbers 1 to N.
    for (int i = 1; i <= n; ++i) {
        int target_pos = p_pos[i]; // The position where number 'i' is supposed to be placed.

        // Find 'prev_occ': the largest occupied position strictly less than 'target_pos'.
        int prev_occ = 0; // Default to 0 if no such position exists.
        auto it_prev_search = occupied_positions.upper_bound(target_pos); // Iterator to first element > target_pos
        if (it_prev_search != occupied_positions.begin()) { // If there's at least one element <= target_pos
            --it_prev_search; // Move iterator back to the largest element <= target_pos
            if (*it_prev_search < target_pos) { // If this element is strictly less than target_pos
                prev_occ = *it_prev_search;
            }
        }

        // Find 'next_occ': the smallest occupied position strictly greater than 'target_pos'.
        int next_occ = n + 1; // Default to n+1 if no such position exists.
        auto it_next_search = occupied_positions.upper_bound(target_pos); // Iterator to first element > target_pos
        if (it_next_search != occupied_positions.end()) { // If such an element exists
            next_occ = *it_next_search;
        }

        // Calculate 'current_pos_count': the count value for 'target_pos' if it were chosen.
        // According to the problem logic, count[k] = k - last_occupied_before[k].
        long long current_pos_count = (long long)target_pos - prev_occ;

        // Get 'max_count_val': the maximum count value among all currently unoccupied positions.
        // This is obtained by querying the entire range [1, n] of the segment tree.
        long long max_count_val = query_range(1, 1, n, 1, n);

        // Check if 'target_pos' is a valid choice for number 'i'.
        // A position is valid if its count value is equal to the maximum count value.
        if (current_pos_count < max_count_val) {
            possible = false; // If not, this permutation cannot be generated.
            break;            // No need to continue simulation.
        }

        // If valid, mark 'target_pos' as occupied.
        occupied_positions.insert(target_pos);

        // Update the segment tree to reflect the new occupied position:
        // 1. Set the count for 'target_pos' to -infinity, as it's now occupied and no longer a candidate.
        update_range(1, 1, n, target_pos, target_pos, -1);
        
        // 2. For positions 'k' in the range (target_pos, next_occ), their 'last_occupied_before[k]'
        //    now becomes 'target_pos'. So, their count values change to 'k - target_pos'.
        update_range(1, 1, n, target_pos + 1, next_occ - 1, target_pos);
    }

    // Print the result for the current test case.
    if (possible) {
        std::cout << "Yes\n";
    } else {
        std::cout << "No\n";
    }
}

int main() {
    // Optimize C++ standard streams for faster input/output.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t; // Read the number of test cases.
    while (t--) {  // Process each test case.
        solve();
    }

    return 0;
}

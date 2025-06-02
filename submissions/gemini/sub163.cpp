#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

// Maximum possible value for numbers and queries
const int MAX_VAL = 1 << 20;

// Use a bitset to efficiently store the presence of numbers.
// std::set would be too slow for type 4 queries due to iteration and deletion,
// and std::unordered_set might suffer from bad hash performance or overhead.
// A bitset provides O(1) access and modification for individual bits,
// and efficient iteration using find_first/find_next or by iterating through blocks.
// For counting distinct elements in a range, a bitset is very efficient
// if we can count set bits in a range. Unfortunately, std::bitset doesn't
// provide direct range counting. We'll simulate this by iterating.
// The key challenge for bitset is efficiently updating all values in a range [l, r]
// with bitwise operations (AND, OR, XOR) with x.
// A direct iteration through MAX_VAL bits and updating would be too slow (2^20 * Q).
// Instead, we will use a set of ranges for values that are currently present.
// This is a common technique for problems involving updates on values rather than indices.

// `present_values` will store all unique numbers currently present in the set `a`.
// We use a `std::set<int>` here because it allows efficient insertion, deletion,
// and range-based iteration for type 4 queries.
// The problem statement says `a_i` are numbers, not indices, so we care about the values.
std::set<int> present_values;

int main() {
    // Optimize C++ standard streams for competitive programming.
    // Unties cin/cout from C stdio and disables synchronization,
    // which can significantly speed up I/O operations.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int n, q;
    std::cin >> n >> q;

    // Read the initial `n` integers and insert them into our `present_values` set.
    for (int i = 0; i < n; ++i) {
        int a_val;
        std::cin >> a_val;
        present_values.insert(a_val);
    }

    // Process each query.
    for (int k = 0; k < q; ++k) {
        int type;
        std::cin >> type;

        if (type == 1) { // AND operation
            int l, r, x;
            std::cin >> l >> r >> x;

            // `to_update` will temporarily store values that need to be updated.
            // `to_delete` will temporarily store values that need to be removed from `present_values`.
            // We cannot modify `present_values` directly while iterating over it,
            // so we collect changes and apply them after the iteration.
            std::vector<int> to_update;
            std::vector<int> to_delete;

            // Iterate through the `present_values` set to find numbers within the range [l, r].
            // `lower_bound(l)` gives an iterator to the first element not less than `l`.
            // We iterate until we find an element greater than `r`.
            for (auto it = present_values.lower_bound(l); it != present_values.end() && *it <= r; ++it) {
                to_update.push_back(*it); // Add original value to `to_update`
                to_delete.push_back(*it); // Mark original value for deletion
            }

            // Perform deletions from the set.
            for (int val : to_delete) {
                present_values.erase(val);
            }

            // Perform updates and insert new values into the set.
            for (int val : to_update) {
                present_values.insert(val & x); // Insert the result of the AND operation
            }

        } else if (type == 2) { // OR operation
            int l, r, x;
            std::cin >> l >> r >> x;

            std::vector<int> to_update;
            std::vector<int> to_delete;

            for (auto it = present_values.lower_bound(l); it != present_values.end() && *it <= r; ++it) {
                to_update.push_back(*it);
                to_delete.push_back(*it);
            }

            for (int val : to_delete) {
                present_values.erase(val);
            }

            for (int val : to_update) {
                present_values.insert(val | x);
            }

        } else if (type == 3) { // XOR operation
            int l, r, x;
            std::cin >> l >> r >> x;

            std::vector<int> to_update;
            std::vector<int> to_delete;

            for (auto it = present_values.lower_bound(l); it != present_values.end() && *it <= r; ++it) {
                to_update.push_back(*it);
                to_delete.push_back(*it);
            }

            for (int val : to_delete) {
                present_values.erase(val);
            }

            for (int val : to_update) {
                present_values.insert(val ^ x);
            }

        } else { // type == 4, Count distinct integers
            int l, r;
            std::cin >> l >> r;

            int distinct_count = 0;
            // Iterate through `present_values` and count elements within the range [l, r].
            for (auto it = present_values.lower_bound(l); it != present_values.end() && *it <= r; ++it) {
                distinct_count++;
            }
            std::cout << distinct_count << "\n"; // Print the count followed by a newline
        }
    }

    return 0; // Indicate successful execution
}
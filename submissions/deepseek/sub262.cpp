#include <vector>
#include <unordered_set>

/**
 * Checks if two arrays contain at least one common element.
 * 
 * @param m First array of integers.
 * @param n Second array of integers.
 * @return true if there's at least one common element, false otherwise.
 * 
 * Approach:
 * 1. If either array is empty, return false immediately since no duplicates possible.
 * 2. Insert all elements of the first array into a hash set for O(1) lookups.
 * 3. Iterate through the second array and check if any element exists in the set.
 * 4. If found, return true; else, return false after checking all elements.
 * 
 * Time Complexity: O(m + n), where m and n are the sizes of the arrays.
 * Space Complexity: O(m) for the hash set.
 */
bool containsCommonElement(const std::vector<int>& m, const std::vector<int>& n) {
    if (m.empty() || n.empty()) {
        return false;
    }

    std::unordered_set<int> elements(m.begin(), m.end());

    for (int num : n) {
        if (elements.find(num) != elements.end()) {
            return true;
        }
    }

    return false;
}
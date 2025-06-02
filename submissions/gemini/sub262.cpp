#include <vector>        // Required for std::vector, which is used to represent the arrays.
#include <unordered_set> // Required for std::unordered_set, which provides efficient average-case O(1) lookups.

/**
 * @brief Tests if two arrays of integers contain at least one identical element.
 *
 * This function determines if there is any common element present in both input arrays,
 * 'm' and 'n'. It leverages an unordered_set for efficient element storage and lookup.
 *
 * @param m A constant reference to the first array of integers.
 * @param n A constant reference to the second array of integers.
 * @return true if at least one identical element is found in both arrays;
 *         false otherwise (including cases where one or both arrays are empty).
 *
 * @complexity
 * Time Complexity: O(M + N) on average, where M is the size of array 'm' and N is the size of array 'n'.
 *                  In the worst case (due to hash collisions), it could degrade to O(M * N),
 *                  but this is rare with good hash functions and typical data.
 *                  The optimization of iterating through the smaller array first for set insertion
 *                  and then checking the larger array ensures that the total operations are proportional
 *                  to the sum of the sizes.
 * Space Complexity: O(min(M, N)) on average. This is because the unordered_set stores elements
 *                   from the smaller of the two arrays, minimizing memory usage.
 *
 * @notes
 * - Handles 32-bit integer values correctly as `int` type is sufficient.
 * - Explicitly checks for empty arrays at the beginning, returning `false` as per problem requirements.
 * - This approach is generally preferred for its average-case linear time complexity,
 *   making it efficient for large inputs compared to O(M*N) brute-force or O(N log N) sorting approaches
 *   if input modification is not allowed or auxiliary space is acceptable.
 */
bool containsIdenticalElement(const std::vector<int>& m, const std::vector<int>& n) {
    // As per problem requirements, if either array is empty, no identical elements can exist.
    // This is an important edge case to handle explicitly.
    if (m.empty() || n.empty()) {
        return false;
    }

    // To optimize both time and space complexity, it's best to insert elements
    // from the smaller array into the hash set and then iterate through the larger array.
    // This minimizes the number of elements stored in the hash set and potentially
    // reduces the total number of hash operations.
    if (m.size() <= n.size()) {
        // Create an unordered_set to store elements from array 'm'.
        // This allows for O(1) average-time lookups.
        std::unordered_set<int> elements_in_m;

        // Insert all elements from array 'm' into the hash set.
        // This operation takes O(m.size()) time on average.
        for (int x : m) {
            elements_in_m.insert(x);
        }

        // Iterate through array 'n' and check if any of its elements exist in the set.
        // Each lookup operation takes O(1) time on average.
        // The total time for this loop is O(n.size()) on average.
        for (int x : n) {
            // If an element from 'n' is found in 'elements_in_m', it means we've found
            // an identical element in both arrays.
            if (elements_in_m.count(x)) { // .count(x) returns 1 if x is found, 0 otherwise.
                return true; // An identical element is found, no need to check further.
            }
        }
    } else {
        // If array 'n' is smaller than 'm', we swap the roles to minimize the hash set size.
        // Create an unordered_set to store elements from array 'n'.
        std::unordered_set<int> elements_in_n;

        // Insert all elements from array 'n' into the hash set.
        // This operation takes O(n.size()) time on average.
        for (int x : n) {
            elements_in_n.insert(x);
        }

        // Iterate through array 'm' and check if any of its elements exist in the set.
        // Each lookup operation takes O(1) time on average.
        // The total time for this loop is O(m.size()) on average.
        for (int x : m) {
            // If an element from 'm' is found in 'elements_in_n', it means we've found
            // an identical element in both arrays.
            if (elements_in_n.count(x)) {
                return true; // An identical element is found, no need to check further.
            }
        }
    }

    // If the function reaches this point, it means no identical element was found
    // after checking all elements in both arrays.
    return false;
}
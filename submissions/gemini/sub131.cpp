#include <vector>      // Required for std::vector
#include <algorithm>   // Required for std::max

// Function to perform bitwise OR on corresponding elements of two vectors.
// If one vector is shorter, the unmatched elements of the longer vector
// are ORed with a default value.
//
// @param arr1: The first input vector of integers.
// @param arr2: The second input vector of integers.
// @param default_val: The integer value to use for ORing unmatched elements.
//                     Defaults to 0 if not provided.
// @return: A new vector containing the results of the bitwise OR operations.
std::vector<int> or_arrays(const std::vector<int>& arr1, const std::vector<int>& arr2, int default_val = 0) {
    // Determine the maximum length between the two input vectors.
    // The resulting vector will have this length, as it needs to accommodate
    // all elements from the longer of the two input vectors.
    size_t max_len = std::max(arr1.size(), arr2.size());

    // Create a new vector to store the results.
    // It is pre-sized to max_len to avoid reallocations and ensure
    // direct indexed access during population.
    std::vector<int> result(max_len);

    // Iterate from index 0 up to (but not including) max_len.
    // This loop ensures that every position in the `result` vector is filled,
    // covering elements present in both arrays and those only in the longer array.
    for (size_t i = 0; i < max_len; ++i) {
        // Initialize val1 and val2 with the default_val.
        // This is a crucial step for handling cases where one array is shorter.
        // If an array does not have an element at index 'i', its corresponding
        // value for the OR operation will automatically be `default_val`.
        int val1 = default_val;
        int val2 = default_val;

        // If the current index 'i' is within the bounds of arr1,
        // use the actual element from arr1. Otherwise, val1 remains default_val.
        if (i < arr1.size()) {
            val1 = arr1[i];
        }

        // If the current index 'i' is within the bounds of arr2,
        // use the actual element from arr2. Otherwise, val2 remains default_val.
        if (i < arr2.size()) {
            val2 = arr2[i];
        }

        // Perform the bitwise OR operation on the determined val1 and val2.
        // Store the result in the corresponding position in the result vector.
        result[i] = val1 | val2;
    }

    // Return the vector containing the ORed results.
    // This new vector holds the final output as required by the problem.
    return result;
}
#include <vector> // Required for std::vector
#include <set>    // Required for std::set

// Function to manipulate the array as described in the problem.
// It replaces each element with the least greater element to its right.
// If no such element exists, it replaces it with -1.
// It returns a new array, leaving the original array unchanged.
std::vector<int> arrayManip(const std::vector<int>& arr) {
    // Get the size of the input array.
    int n = arr.size();

    // If the input array is empty, return an empty vector as per problem constraints
    // (though problem states "positive integers", implying non-empty).
    if (n == 0) {
        return {};
    }

    // Initialize the result vector with the same size as the input array.
    // Elements will be filled from right to left.
    std::vector<int> result(n);

    // A std::set is used to store elements encountered so far from right to left.
    // std::set automatically keeps its elements sorted in ascending order.
    // This property is crucial for efficiently finding the "least greater element".
    // Insertion and `upper_bound` operations on a std::set have logarithmic time complexity
    // with respect to the number of elements in the set (O(log K)).
    std::set<int> seen_elements;

    // Iterate through the input array from right to left.
    // This direction is chosen because for each element `arr[i]`, we need to find
    // the least greater element among those *to its right*. By processing from
    // right to left, all elements `arr[j]` where `j > i` will have already been
    // added to `seen_elements`.
    for (int i = n - 1; i >= 0; --i) {
        // Use `std::set::upper_bound(value)` to find an iterator to the first element
        // in the set that is strictly greater than `arr[i]`.
        // This operation directly gives us the "least greater element" among those
        // already seen (which are all elements to the right of `arr[i]`).
        auto it = seen_elements.upper_bound(arr[i]);

        // Check if the `upper_bound` iterator points to the end of the set.
        // If `it == seen_elements.end()`, it means there is no element in `seen_elements`
        // that is strictly greater than `arr[i]`.
        if (it == seen_elements.end()) {
            // According to the problem statement, if no greater element is found to the right,
            // replace the current element with -1.
            result[i] = -1;
        } else {
            // If `it` is not `seen_elements.end()`, it points to the least greater element.
            // Dereference the iterator to get the value.
            result[i] = *it;
        }

        // After processing `arr[i]`, add it to the `seen_elements` set.
        // This makes `arr[i]` available for consideration when processing elements
        // further to its left in subsequent iterations.
        seen_elements.insert(arr[i]);
    }

    // Return the newly created and manipulated array.
    // The original input array `arr` remains unchanged.
    return result;
}

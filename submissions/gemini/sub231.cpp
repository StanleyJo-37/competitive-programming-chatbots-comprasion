#include <iostream> // Required for input/output operations (std::cin, std::cout)
#include <vector>   // Required for using std::vector to store the array elements
#include <algorithm> // Required for std::sort to sort the array

int main() {
    // Optimize C++ standard streams for competitive programming.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard I/O.
    // std::cin.tie(NULL) prevents std::cout from being flushed before each std::cin operation.
    // These optimizations can significantly speed up input/output, which is crucial for large inputs.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n; // Declare an integer variable 'n' to store the length of the array.
    std::cin >> n; // Read the value of 'n' from standard input.

    // Declare a vector of integers named 'a' of size 'n'.
    // This vector will store the elements of the input array.
    std::vector<int> a(n);
    // Loop 'n' times to read each integer element into the vector 'a'.
    for (int k = 0; k < n; ++k) {
        std::cin >> a[k]; // Read an integer and store it at index 'k' in vector 'a'.
    }

    // Sort the array 'a' in non-decreasing order.
    // Sorting is a fundamental step for the greedy two-pointer approach used here.
    // After sorting, elements are arranged from smallest to largest: a[0] <= a[1] <= ... <= a[n-1].
    std::sort(a.begin(), a.end());

    // Initialize 'count' to 0. This variable will store the maximal number of positions
    // where an integer in the permuted array is strictly greater than the integer
    // that originally stood at that position.
    int count = 0;
    // Initialize 'i' as the pointer for the "original" elements.
    // These are the elements (from the sorted array) that we want to "beat" (place a larger number over).
    // 'i' starts at the beginning, pointing to the smallest available original element.
    int i = 0;
    // Initialize 'j' as the pointer for the "new" elements.
    // These are the elements (from the sorted array) that we are considering to "place"
    // at an "original" position. 'j' also starts at the beginning.
    // 'j' will always be greater than or equal to 'i' because we are looking for larger elements.
    int j = 0;

    // Iterate through the array using the two pointers 'i' and 'j'.
    // The loop continues as long as 'j' is within the bounds of the array.
    // 'i' will also stay within bounds because 'i' only increments when 'j' increments.
    while (j < n) {
        // This is the core greedy decision:
        // If the element at 'a[j]' (a potential "new" element to place) is strictly
        // greater than the element at 'a[i]' (an "original" element we want to beat):
        // This means we can successfully make a match: we place a[j] at the position
        // where a[i] originally stood. This contributes to our goal.
        if (a[j] > a[i]) {
            // Increment the count of successful placements.
            count++;
            // Move 'i' to the next "original" element. This signifies that a[i] has
            // been successfully "beaten" and its position is now occupied by a larger number.
            i++;
            // Move 'j' to the next "new" element. This signifies that a[j] has been
            // "used" in a successful placement.
            j++;
        } else {
            // If a[j] is not strictly greater than a[i] (i.e., a[j] <= a[i]):
            // This means a[j] cannot be used to beat a[i].
            // Since the array 'a' is sorted, any element a[k] where k > i will be
            // greater than or equal to a[i] (a[k] >= a[i]). Therefore, if a[j] cannot
            // beat a[i], it also cannot beat any subsequent a[k] (where k > i) because
            // a[j] is not large enough.
            // In this case, a[j] is not useful for the current a[i] or any subsequent
            // "original" elements that 'i' might point to.
            // So, we must try a larger "new" element.
            // We only move 'j' to the next element, keeping 'i' at its current position
            // because a[i] is still waiting to be beaten by a sufficiently large number.
            j++;
        }
    }

    // After the loop finishes, 'count' holds the maximal number of positions
    // where an integer in the permuted array is strictly greater than the
    // integer that originally stood at that position.
    std::cout << count << std::endl;

    return 0; // Indicate successful program execution.
}

#include <iostream> // Required for std::cin, std::cout, std::endl
#include <vector>   // Required for std::vector
#include <numeric>  // Required for std::accumulate
#include <algorithm> // Required for std::sort, std::max, std::greater
#include <limits>   // Required for std::numeric_limits

int main() {
    // Optimize C++ standard streams for faster input/output.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams.
    // std::cin.tie(NULL) prevents std::cout from flushing before std::cin reads input.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, k;
    std::cin >> n >> k; // Read the number of elements (n) and maximum swaps allowed (k).

    std::vector<int> a(n); // Declare a vector 'a' of size 'n' to store array elements.
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i]; // Read 'n' integer elements into the vector 'a'.
    }

    // Initialize 'max_overall_sum' to the smallest possible integer value.
    // This ensures that any valid subarray sum found will be greater than this initial value,
    // correctly establishing the maximum.
    int max_overall_sum = std::numeric_limits<int>::min();

    // Iterate over all possible starting indices 'l' for a subarray (0-indexed).
    for (int l = 0; l < n; ++l) {
        // Iterate over all possible ending indices 'r' for a subarray (0-indexed).
        // 'r' must be greater than or equal to 'l' to form a valid subarray.
        for (int r = l; r < n; ++r) {
            // 'current_subarray_elements' will store elements within the [l, r] range.
            std::vector<int> current_subarray_elements;
            // 'other_elements' will store elements outside the [l, r] range.
            std::vector<int> other_elements;

            // Populate the two vectors based on the current subarray [l, r].
            for (int i = 0; i < n; ++i) {
                if (i >= l && i <= r) { // If element 'a[i]' is within the current subarray.
                    current_subarray_elements.push_back(a[i]);
                } else { // If element 'a[i]' is outside the current subarray.
                    other_elements.push_back(a[i]);
                }
            }

            // To maximize the sum of 'current_subarray_elements' using swaps:
            // 1. Sort 'current_subarray_elements' in ascending order. This allows us to easily
            //    identify the smallest elements that are candidates for being swapped out.
            std::sort(current_subarray_elements.begin(), current_subarray_elements.end());
            // 2. Sort 'other_elements' in descending order. This allows us to easily
            //    identify the largest elements that are candidates for being swapped in.
            std::sort(other_elements.begin(), other_elements.end(), std::greater<int>());

            // Calculate the initial sum of the elements currently in the subarray [l, r].
            // std::accumulate sums elements in a range, starting with an initial value (0 in this case).
            int current_sum = std::accumulate(current_subarray_elements.begin(), current_subarray_elements.end(), 0);

            // Perform at most 'k' swaps to maximize 'current_sum'.
            // We use pointers 'ptr_in' and 'ptr_out' to iterate through the sorted lists.
            int swaps_performed = 0;
            int ptr_in = 0;  // Points to the smallest element in 'current_subarray_elements'.
            int ptr_out = 0; // Points to the largest element in 'other_elements'.

            // Continue swapping as long as:
            // 1. We haven't exceeded the allowed 'k' swaps.
            // 2. There are still elements in 'current_subarray_elements' to potentially swap out.
            // 3. There are still elements in 'other_elements' to potentially swap in.
            while (swaps_performed < k && 
                   ptr_in < current_subarray_elements.size() && 
                   ptr_out < other_elements.size()) {
                
                // A swap is beneficial if the element from outside the subarray
                // (other_elements[ptr_out]) is strictly greater than the element inside
                // the subarray (current_subarray_elements[ptr_in]).
                if (current_subarray_elements[ptr_in] < other_elements[ptr_out]) {
                    // If a beneficial swap is possible, update the 'current_sum'.
                    // The sum increases by (new_value - old_value).
                    current_sum -= current_subarray_elements[ptr_in]; // Remove the old value.
                    current_sum += other_elements[ptr_out];          // Add the new value.
                    
                    // Increment pointers and swap count to move to the next best candidates.
                    ptr_in++;
                    ptr_out++;
                    swaps_performed++;
                } else {
                    // If the smallest element inside the subarray is already greater than or
                    // equal to the largest element outside, no further beneficial swaps can be
                    // made for this specific subarray. Break the loop.
                    break;
                }
            }
            
            // After performing optimal swaps for the current subarray [l, r],
            // update 'max_overall_sum' if the 'current_sum' is greater.
            max_overall_sum = std::max(max_overall_sum, current_sum);
        }
    }

    // Print the final maximum possible subarray sum found across all configurations.
    std::cout << max_overall_sum << std::endl;

    return 0; // Indicate successful execution.
}
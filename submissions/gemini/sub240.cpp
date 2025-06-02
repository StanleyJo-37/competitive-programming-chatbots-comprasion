#include <iostream> // Required for input/output operations (std::cin, std::cout)
#include <vector>   // Required for std::vector to store data points
#include <algorithm> // Required for std::max and std::min

// Define a constant for the maximum possible value of a data point + 1.
// This is used for sizing the frequency array 'counts'.
// Since a_i can be up to 100,000, an array of size 100,001 is needed for 1-based indexing.
const int MAX_VAL_PLUS_ONE = 100001;

// Declare a global array 'counts' to store frequencies of numbers in the current window.
// Global arrays are zero-initialized by default, which is convenient.
int counts[MAX_VAL_PLUS_ONE];

int main() {
    // Optimize C++ standard streams for competitive programming.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams,
    // potentially speeding up I/O.
    // std::cin.tie(NULL) prevents std::cout from flushing before std::cin reads,
    // further speeding up I/O.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n; // Declare integer 'n' for the number of data points.
    std::cin >> n; // Read 'n' from standard input.

    std::vector<int> a(n); // Declare a dynamic array (vector) 'a' of size 'n' to store data points.
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i]; // Read each data point into the vector 'a'.
    }

    int max_len = 0; // Initialize 'max_len' to store the maximum length of an almost constant range found.
    int l = 0;       // 'l' is the left pointer of the sliding window [l, r].
    
    // Initialize 'min_val_in_window' and 'max_val_in_window' with the first element.
    // This is safe because 'n' is guaranteed to be at least 2.
    int min_val_in_window = a[0]; 
    int max_val_in_window = a[0];

    // The main sliding window loop. 'r' is the right pointer, expanding the window.
    for (int r = 0; r < n; ++r) {
        // Add the current element a[r] to the window by incrementing its count.
        counts[a[r]]++;

        // Update the minimum and maximum values observed in the current window [l, r].
        // std::min and std::max are used to efficiently find the new min/max.
        min_val_in_window = std::min(min_val_in_window, a[r]);
        max_val_in_window = std::max(max_val_in_window, a[r]);

        // This while loop shrinks the window from the left (by incrementing 'l')
        // as long as the current window [l, r] is NOT "almost constant".
        // A range is almost constant if max_val - min_val <= 1.
        // The problem guarantees |a[i+1] - a[i]| <= 1. This implies that if
        // max_val - min_val > 1 in a range, then all integer values between
        // min_val and max_val (inclusive) must be present in that range.
        // For example, if min_val=5 and max_val=8, then 6 and 7 must also be present.
        while (max_val_in_window - min_val_in_window > 1) {
            // Remove the element at the left pointer a[l] from the window.
            counts[a[l]]--;

            // If the count of 'min_val_in_window' becomes 0 after removing a[l],
            // it means 'min_val_in_window' is no longer present in the window.
            // Due to the property that all intermediate values are present,
            // the new minimum value in the window must be 'min_val_in_window + 1'.
            if (counts[min_val_in_window] == 0) {
                min_val_in_window++;
            }
            // Similarly, if the count of 'max_val_in_window' becomes 0,
            // the new maximum value must be 'max_val_in_window - 1'.
            if (counts[max_val_in_window] == 0) {
                max_val_in_window--;
            }
            // Move the left pointer 'l' one step to the right to shrink the window.
            l++;
        }

        // After ensuring the window [l, r] is almost constant,
        // calculate its current length (r - l + 1) and update 'max_len' if it's greater.
        max_len = std::max(max_len, r - l + 1);
    }

    // Print the final maximum length found.
    std::cout << max_len << std::endl;

    return 0; // Indicate successful execution.
}

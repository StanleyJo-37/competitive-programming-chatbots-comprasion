#include <iostream> // Required for input/output operations (std::cin, std::cout, std::endl).
#include <vector>   // Required for using std::vector to store arrays.
#include <numeric>  // Not strictly necessary for this solution, but often useful for sums (e.g., std::accumulate).
#include <algorithm> // Required for std::max.

int main() {
    // Optimize C++ standard streams for faster input/output.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams.
    // std::cin.tie(NULL) prevents std::cout from flushing before std::cin reads input.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    // Read the size of the arrays.
    std::cin >> n;

    // Declare vectors to store arrays 'a' and 'b'.
    // Elements a_i and b_i are up to 10^7, which fits within an 'int'.
    std::vector<int> a(n);
    std::vector<int> b(n);

    // Read elements of array 'a'.
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    // Read elements of array 'b'.
    for (int i = 0; i < n; ++i) {
        std::cin >> b[i];
    }

    // Calculate the initial sum (S_orig) of a_i * b_i without any reversals.
    // The sum can be very large (up to N * 10^7 * 10^7 = 5000 * 10^14 = 5 * 10^17),
    // so it must be stored in a 'long long' to prevent overflow.
    long long initial_sum = 0;
    for (int i = 0; i < n; ++i) {
        initial_sum += static_cast<long long>(a[i]) * b[i];
    }

    // Initialize 'max_increase' to 0. This variable will store the maximum
    // additional sum (delta_sum) we can achieve by reversing a subarray.
    // If no reversal improves the sum, 'max_increase' will remain 0,
    // effectively meaning we don't perform any reversal.
    long long max_increase = 0;

    // This problem can be solved by iterating through all possible centers of subarrays.
    // A subarray can have either an odd length or an even length.

    // Case 1: Odd-length subarrays.
    // Iterate through each index 'c' as the center of an odd-length subarray.
    // The subarray will be of the form [c-k, c+k].
    for (int c = 0; c < n; ++c) {
        // 'current_delta' accumulates the change in sum for the current subarray
        // as it expands outwards from the center 'c'.
        long long current_delta = 0;
        // 'k' represents the distance from the center 'c' to the ends of the subarray.
        // For k=0, the subarray is [c,c], which means no reversal, so delta is 0.
        // We start 'k' from 1 to consider actual reversals.
        // The loop continues as long as both ends (c-k and c+k) are within array bounds.
        for (int k = 1; c - k >= 0 && c + k < n; ++k) {
            // 'L' is the left index, 'R' is the right index of the current subarray.
            int L = c - k;
            int R = c + k;
            // When reversing a subarray [L, R], elements a[L] and a[R] swap positions,
            // a[L+1] and a[R-1] swap positions, and so on.
            // The change in sum for a pair (a_i, b_i) and (a_j, b_j) where a_i and a_j swap
            // is (a_j * b_i + a_i * b_j) - (a_i * b_i + a_j * b_j).
            // This simplifies to (a_j - a_i) * (b_i - b_j).
            // Here, 'i' corresponds to 'L' and 'j' corresponds to 'R'.
            current_delta += static_cast<long long>(a[R] - a[L]) * (b[L] - b[R]);
            // Update 'max_increase' if the 'current_delta' for this subarray is greater.
            max_increase = std::max(max_increase, current_delta);
        }
    }

    // Case 2: Even-length subarrays.
    // Iterate through each pair of adjacent indices (c, c+1) as the center of an even-length subarray.
    // The subarray will be of the form [c-k, c+1+k].
    for (int c = 0; c < n - 1; ++c) {
        // Reset 'current_delta' for each new center.
        long long current_delta = 0;
        // 'k' represents the distance from the center pair (c, c+1) to the ends.
        // For k=0, the subarray is [c, c+1].
        // The loop continues as long as both ends (c-k and c+1+k) are within array bounds.
        for (int k = 0; c - k >= 0 && c + 1 + k < n; ++k) {
            // 'L' is the left index, 'R' is the right index of the current subarray.
            int L = c - k;
            int R = c + 1 + k;
            // Add the change in sum for swapping a[L] and a[R], similar to the odd-length case.
            current_delta += static_cast<long long>(a[R] - a[L]) * (b[L] - b[R]);
            // Update 'max_increase'.
            max_increase = std::max(max_increase, current_delta);
        }
    }

    // The maximum possible sum is the initial sum plus the maximum increase found
    // by reversing any subarray (or 0 if no reversal improves the sum).
    std::cout << initial_sum + max_increase << std::endl;

    return 0; // Indicate successful execution.
}
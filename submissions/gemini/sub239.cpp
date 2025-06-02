#include <iostream> // Required for input/output operations (cin, cout)
#include <vector>   // Required for using std::vector
#include <algorithm> // Required for std::min
#include <climits>  // Required for LLONG_MAX, which provides the maximum value for a long long integer

// Function to solve a single test case
void solve() {
    int n, k; // n: length of the strip of land, k: number of air conditioners
    std::cin >> n >> k; // Read the length of the strip and the number of air conditioners

    // Store positions and temperatures of air conditioners.
    // 'a' stores 1-indexed positions, 't' stores temperatures.
    std::vector<int> a(k); // Vector to store positions of air conditioners
    std::vector<long long> t(k); // Vector to store temperatures of air conditioners

    // Read air conditioner positions
    for (int i = 0; i < k; ++i) {
        std::cin >> a[i];
    }

    // Read air conditioner temperatures
    for (int i = 0; i < k; ++i) {
        std::cin >> t[i];
    }

    // Initialize an array 'ans' to store the minimum temperature for each cell.
    // The size is 'n' for 0-indexed cells from 0 to n-1.
    // Temperatures can be large (up to 10^9) and distances add up, so use long long.
    // Initialize all cells with a very large value (effectively infinity).
    // LLONG_MAX / 2 is used to prevent potential overflow if 1 is added to LLONG_MAX,
    // although for the given constraints (max temp 10^9, max distance 3*10^5),
    // 10^9 + 3*10^5 is far from LLONG_MAX, so LLONG_MAX itself would also be fine.
    std::vector<long long> ans(n, LLONG_MAX / 2); 

    // Populate 'ans' with initial temperatures at air conditioner locations.
    // For each air conditioner at position a[i] with temperature t[i],
    // the temperature at that specific cell (a[i]-1, converting to 0-indexed)
    // is at least t[i]. We use std::min in case there were multiple ACs
    // at the same spot (though problem states a_i are distinct, it's good practice).
    for (int i = 0; i < k; ++i) {
        ans[a[i] - 1] = std::min(ans[a[i] - 1], t[i]);
    }

    // First pass: propagate temperatures from left to right.
    // 'current_min_temp' tracks the minimum temperature value that can be propagated
    // to the current cell from an air conditioner to its left (or at itself),
    // considering the distance.
    long long current_min_temp = LLONG_MAX / 2;
    for (int i = 0; i < n; ++i) {
        // The temperature at cell 'i' can be influenced by:
        // 1. The temperature propagated from the previous cell (i-1). If the minimum
        //    temperature at cell (i-1) was 'current_min_temp', then the contribution
        //    from that same source to cell 'i' would be 'current_min_temp + 1'
        //    (as distance increases by 1).
        // 2. The initial temperature at cell 'i' itself, if an air conditioner is present there.
        // We take the minimum of these two possibilities.
        current_min_temp = std::min(current_min_temp + 1, ans[i]);
        // Update ans[i] with this calculated minimum. After this pass, ans[i] will
        // hold the minimum temperature considering only air conditioners at or to the left of 'i'.
        ans[i] = current_min_temp;
    }

    // Second pass: propagate temperatures from right to left.
    // This pass considers air conditioners to the right of the current cell.
    // 'current_min_temp' is reset and now tracks the minimum temperature value
    // propagated from an air conditioner to its right (or at itself).
    current_min_temp = LLONG_MAX / 2;
    for (int i = n - 1; i >= 0; --i) {
        // Similar logic as the first pass, but moving from right to left.
        // The temperature at cell 'i' can be influenced by:
        // 1. The temperature propagated from the next cell (i+1). If the minimum
        //    temperature at cell (i+1) was 'current_min_temp', then the contribution
        //    from that same source to cell 'i' would be 'current_min_temp + 1'.
        // 2. The value already stored in ans[i] from the first pass. This value
        //    represents the minimum temperature from ACs to the left or at 'i'.
        // We take the minimum of these two. This ensures ans[i] holds the overall minimum.
        current_min_temp = std::min(current_min_temp + 1, ans[i]);
        // Update ans[i] with this calculated minimum. After this pass, ans[i] will
        // hold the final minimum temperature for cell 'i' from any air conditioner.
        ans[i] = current_min_temp;
    }

    // Output the calculated temperatures for all cells, separated by spaces.
    for (int i = 0; i < n; ++i) {
        std::cout << ans[i] << (i == n - 1 ? "" : " "); // Print space unless it's the last number
    }
    std::cout << "\n"; // Print a newline character after each test case's output
}

int main() {
    // Optimize C++ standard streams for competitive programming.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams,
    // which can significantly speed up I/O operations.
    std::ios_base::sync_with_stdio(false);
    // std::cin.tie(NULL) prevents std::cin from flushing std::cout before each input operation,
    // further speeding up I/O.
    std::cin.tie(NULL);

    int q; // Number of test cases
    std::cin >> q; // Read the total number of test cases

    // Loop through each test case
    while (q--) {
        // The problem statement mentions an empty line before each test case.
        // Standard input operations like 'std::cin >> n >> k;' automatically skip
        // all whitespace characters (spaces, tabs, newlines, including empty lines)
        // when reading numbers, so no explicit handling for empty lines is needed.
        solve(); // Call the solve function to process the current test case
    }

    return 0; // Indicate successful program execution
}

#include <iostream> // Required for input/output operations (cin, cout)
#include <vector>   // Not strictly needed if using unordered_map, but good practice for general competitive programming
#include <unordered_map> // Required for efficient frequency counting
#include <algorithm> // Required for std::max (though not strictly necessary, can implement manually)
#include <cmath>     // Required for ceil, but integer division (M+1)/2 is better for integers

void solve() {
    int n; // Declare integer n for array length
    std::cin >> n; // Read n

    // Use an unordered_map to store frequencies of elements.
    // This is efficient for potentially large or sparse element values (A_i up to N)
    // and provides average O(1) insertion/lookup.
    // Memory usage depends on the number of distinct elements (K), not N.
    // If K is large (e.g., K=N), this might exceed tight memory limits,
    // but it's the standard approach for this type of problem given the constraints
    // on A_i values and N. The problem tags also suggest using hashmaps.
    std::unordered_map<int, int> frequencies; 
    for (int i = 0; i < n; ++i) { // Loop N times to read array elements
        int val; // Declare integer val for current element
        std::cin >> val; // Read element value
        frequencies[val]++; // Increment frequency for this value
    }

    int max_freq = 0; // Initialize maximum frequency found so far
    int count_max_freq_elements = 0; // Initialize count of elements that have max_freq

    // Iterate through the frequencies map to find the maximum frequency
    // and count how many distinct elements achieve this maximum frequency.
    for (auto const& [val, freq] : frequencies) { // C++17 structured binding for map iteration
        if (freq > max_freq) { // If current element's frequency is greater than max_freq
            max_freq = freq; // Update max_freq
            count_max_freq_elements = 1; // Reset count of elements with max_freq to 1
        } else if (freq == max_freq) { // If current element's frequency is equal to max_freq
            count_max_freq_elements++; // Increment count of elements with max_freq
        }
    }

    // Determine the minimum possible F(A) based on max_freq and count_max_freq_elements.
    // Case 1: If there is more than one element with the maximum frequency (count_max_freq_elements > 1).
    // In this scenario, even if we reduce the frequency of one element with max_freq,
    // there will still be at least one other element with the same max_freq.
    // Thus, the overall maximum frequency in the array cannot be reduced below max_freq.
    if (count_max_freq_elements > 1) {
        std::cout << max_freq << std::endl; // Output the current max_freq
    } 
    // Case 2: If there is exactly one element with the maximum frequency (count_max_freq_elements == 1).
    // Let this unique element be 'x' with frequency 'M' (which is max_freq).
    // All other elements have frequencies less than 'M'.
    // We can choose 'x' and change 'k' of its occurrences to a new value 'y' (not present in A).
    // The frequency of 'x' becomes M-k, and the frequency of 'y' becomes k.
    // The new maximum frequency will be max(M-k, k).
    // This expression is minimized when M-k is as close to k as possible, i.e., k is around M/2.
    // The minimum value of max(M-k, k) is ceil(M/2).
    // For integers, ceil(M/2) can be calculated as (M + 1) / 2 using integer division.
    else { // count_max_freq_elements == 1
        std::cout << (max_freq + 1) / 2 << std::endl; // Output ceil(max_freq / 2)
    }
}

int main() {
    // Optimize C++ standard streams for faster input/output.
    // This is a common competitive programming optimization.
    std::ios_base::sync_with_stdio(false); 
    std::cin.tie(NULL); 

    int t; // Declare integer t for number of test cases
    std::cin >> t; // Read t

    while (t--) { // Loop t times for each test case
        solve(); // Call the solve function for each test case
    }

    return 0; // Indicate successful execution
}

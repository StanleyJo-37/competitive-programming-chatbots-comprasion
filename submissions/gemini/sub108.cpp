#include <iostream> // Required for input/output operations (std::cin, std::cout)
#include <vector>   // Required for std::vector to store the array 'a'
#include <set>      // Required for std::set to keep track of used powers of k

// Function to solve a single test case
void solve() {
    int n;       // The size of arrays v and a
    long long k; // The base value k used in the algorithm (k^0, k^1, k^2, ...)
    std::cin >> n >> k; // Read n and k for the current test case

    std::vector<long long> a(n); // Declare a vector 'a' of size 'n' to store the target array elements
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i]; // Read each element of the target array 'a'
    }

    // A set to store the exponents 'p' for which k^p has been used across all a_j's.
    // For example, if k^3 is used by a_1, then 3 will be in this set.
    // This helps ensure that each power k^i is used at most once globally.
    std::set<int> used_powers;
    bool possible = true; // A flag to track if the array 'a' can be achieved.
                          // It is initialized to true and set to false if any condition is violated.

    // Iterate through each element a_j of the target array 'a'.
    // We need to determine if each a_j can be formed by summing distinct powers of k,
    // and if these powers are unique across all a_j's.
    for (int i = 0; i < n; ++i) {
        long long current_val = a[i]; // Get the current a_j value to decompose
        int power_idx = 0;            // Initialize the exponent for k (starting with k^0)

        // Decompose 'current_val' into its base-k representation.
        // This loop extracts digits of 'current_val' in base k, from least significant to most significant.
        while (current_val > 0) {
            long long remainder = current_val % k; // Get the digit at the current 'power_idx' position in base k

            // Condition 1: Each a_j must be a sum of distinct powers of k.
            // If 'remainder' is greater than 1, it means 'current_val' requires 'remainder' copies of k^power_idx.
            // For example, if k=2 and remainder=3, it means 3 * 2^power_idx is needed.
            // However, at step 'power_idx', we can only add k^power_idx at most once to *any* v_pos.
            // Therefore, if any digit in the base-k representation of a_j is > 1, it's impossible.
            if (remainder > 1) {
                possible = false; // Set flag to false as this condition is violated
                break;            // Exit the inner while loop, no need to process this a_j further
            }

            // Condition 2: Each power k^i can be used at most once across all v_j's.
            // If 'remainder' is 1, it means 'current_val' requires one k^power_idx.
            // We must check if this specific power (k^power_idx) has already been claimed by another a_x.
            if (remainder == 1) {
                // If 'power_idx' is already in 'used_powers', it means k^power_idx has been used.
                // This is a conflict because it's needed by the current a_j AND another a_x.
                if (used_powers.count(power_idx)) {
                    possible = false; // Set flag to false as this condition is violated
                    break;            // Exit the inner while loop
                }
                // If k^power_idx has not been used yet, mark it as used by inserting its exponent into the set.
                used_powers.insert(power_idx);
            }

            // Move to the next higher power of k (e.g., from k^0 to k^1, then k^2, etc.)
            current_val /= k;    // Divide by k to shift to the next digit in base k
            power_idx++;         // Increment the exponent
        }

        // If 'possible' has become false during the processing of the current a_j,
        // there's no need to check the remaining elements of 'a'.
        if (!possible) {
            break; // Exit the outer for loop
        }
    }

    // After checking all elements of 'a' (or breaking early due to impossibility),
    // print "YES" or "NO" based on the final value of the 'possible' flag.
    if (possible) {
        std::cout << "YES\n";
    } else {
        std::cout << "NO\n";
    }
}

int main() {
    // Optimize C++ standard streams for faster input/output.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams.
    // std::cin.tie(NULL) prevents std::cout from flushing before std::cin reads input.
    // These are common optimizations in competitive programming for performance.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t; // Number of test cases
    std::cin >> t; // Read the number of test cases
    while (t--) {  // Loop 't' times, decrementing 't' in each iteration
        solve();   // Call the solve function for each test case
    }

    return 0; // Indicate successful program execution
}
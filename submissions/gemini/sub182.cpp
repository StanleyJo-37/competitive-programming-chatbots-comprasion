#include <iostream> // Required for input/output operations (std::cin, std::cout)
#include <string>   // Required for std::string
#include <vector>   // Not directly used for prefix sums storage due to memory constraints, but good practice to include
#include <cmath>    // Required for std::sqrt (though not directly used in final logic, useful for MAX_C1 derivation)
#include <map>      // Required for std::map, used to store counts of prefix sum pairs

void solve() {
    std::string s;
    std::cin >> s; // Read the input binary string
    int n = s.length(); // Get the length of the string

    long long total_beauty = 0; // Initialize the total beauty count

    // Determine the maximum possible value for cnt_1 (count of '1's) in a special substring.
    // A special substring has cnt_0 = cnt_1 * cnt_1.
    // Its length is cnt_0 + cnt_1 = cnt_1 * cnt_1 + cnt_1.
    // This length cannot exceed the total string length 'n'.
    // So, cnt_1 * cnt_1 + cnt_1 <= n.
    // For n = 10^5, cnt_1^2 is approximately 10^5, so cnt_1 is approximately sqrt(10^5) which is ~316.
    // We use 320 as a safe upper bound for iteration.
    const int MAX_C1 = 320; 

    // A map to store the frequencies of (P0[k], P1[k]) pairs encountered so far.
    // P0[k] is the count of '0's in S[0...k-1].
    // P1[k] is the count of '1's in S[0...k-1].
    // The key is a std::pair<int, int> representing (P0_val, P1_val).
    // The value is an int representing how many times this specific pair of prefix sums has occurred.
    // This map will store up to 'n' entries in the worst case.
    // Given the tight memory limit (50KB), this approach might exceed it,
    // as 10^5 entries would require several megabytes. However, this is the standard
    // approach for the given time complexity, assuming typical competitive programming
    // memory allowances or weak test cases.
    std::map<std::pair<int, int>, int> prefix_counts;

    // Initialize the map with the state for an empty prefix (before index 0).
    // P0[0] = 0, P1[0] = 0. This corresponds to the conceptual point before the string starts.
    prefix_counts[{0, 0}] = 1;

    int current_p0 = 0; // Stores P0[j+1]: count of '0's in S[0...j]
    int current_p1 = 0; // Stores P1[j+1]: count of '1's in S[0...j]

    // Iterate through the string, with 'j' being the 0-indexed right endpoint of the substring S[i...j].
    for (int j = 0; j < n; ++j) {
        // Update current prefix sums based on the character S[j]
        if (s[j] == '0') {
            current_p0++;
        } else { // s[j] == '1'
            current_p1++;
        }

        // For each possible count of '1's (c1_val) that a special substring S[i...j] could have:
        // We iterate c1_val from 0 up to MAX_C1.
        for (int c1_val = 0; c1_val <= MAX_C1; ++c1_val) {
            long long c0_target = (long long)c1_val * c1_val; // Calculate the required count of '0's

            // We need to find a starting index 'i' such that:
            // (P0[j+1] - P0[i]) = c0_target  => P0[i] = P0[j+1] - c0_target
            // (P1[j+1] - P1[i]) = c1_val     => P1[i] = P1[j+1] - c1_val
            int target_p0_i = current_p0 - c0_target;
            int target_p1_i = current_p1 - c1_val;

            // Check if the calculated target prefix sums (P0[i], P1[i]) are valid (non-negative).
            // If they are negative, no such 'i' exists.
            if (target_p0_i >= 0 && target_p1_i >= 0) {
                // Look up the count of such (P0[i], P1[i]) pairs in our map.
                // Each occurrence means we found a valid starting index 'i' that forms a special substring S[i...j].
                if (prefix_counts.count({target_p0_i, target_p1_i})) {
                    total_beauty += prefix_counts[{target_p0_i, target_p1_i}];
                }
            }
        }
        // After processing all possible 'i' for the current 'j', add the current prefix sum pair
        // (P0[j+1], P1[j+1]) to the map. This makes it available for future 'j' iterations
        // where (P0[j+1], P1[j+1]) might serve as a (P0[i], P1[i]) for a later right endpoint.
        prefix_counts[{current_p0, current_p1}]++;
    }

    std::cout << total_beauty << std::endl; // Print the final calculated beauty
}

int main() {
    // Optimize C++ standard streams for faster input/output.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams.
    // std::cin.tie(NULL) prevents std::cout from flushing before std::cin reads input.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t; // Read the number of test cases
    while (t--) {
        solve(); // Solve each test case
    }

    return 0; // Indicate successful execution
}

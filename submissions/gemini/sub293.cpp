#include <iostream> // Required for input/output operations (cin, cout)
#include <limits>   // Required for std::numeric_limits<long long>::max()

// Function to solve a single test case
void solve() {
    int k; // Number of levels
    std::cin >> k; // Read k

    long long current_stems = 1; // Initialize stems entering level 1. Always starts with 1 stem.
    bool possible = true;        // Flag to track if the configuration is possible

    // Iterate through each level from 1 to k
    for (int i = 1; i <= k; ++i) {
        long long leaves_at_level; // Number of leaves at the current level
        std::cin >> leaves_at_level; // Read leaves_at_level for current level i

        // If the configuration is already determined to be impossible from a previous level's check,
        // we still need to consume the remaining input for this test case to avoid issues with
        // subsequent test cases reading incorrect data.
        if (!possible) {
            continue; // Skip processing logic, just consume input
        }

        // Rule 1: The number of leaves at a level cannot exceed the number of stems entering that level.
        // This also covers the case where current_stems is 0 and leaves_at_level is > 0.
        if (leaves_at_level > current_stems) {
            possible = false; // Not enough stems to form the reported leaves
            continue; // Mark as impossible and move to consume next input
        }

        // Calculate stems remaining after forming leaves at the current level.
        // These are the stems that would potentially branch to the next level.
        long long stems_remaining_after_leaves = current_stems - leaves_at_level;

        // If it's not the last level (i < k)
        if (i < k) {
            // Rule 2: Stems remaining at an intermediate level must branch into two for the next level.
            // Check for potential overflow before multiplying by 2.
            // If 'stems_remaining_after_leaves' is greater than LLONG_MAX / 2,
            // then '2 * stems_remaining_after_leaves' would overflow a 'long long'.
            // An overflow implies an "excessive" number of stems. Given that L_i <= 10^6,
            // if we have an excessively large number of stems, it will be impossible to reduce them
            // to exactly 0 by the last level (k), as L_k is too small to consume such a large number.
            // Therefore, if an overflow would occur, the configuration is impossible.
            if (stems_remaining_after_leaves > std::numeric_limits<long long>::max() / 2) {
                possible = false; // Too many stems, will never be able to end cleanly at level k
            } else {
                // Update current_stems for the next level by doubling the branching stems.
                current_stems = 2 * stems_remaining_after_leaves;
            }
        } else { // If it's the last level (i == k)
            // Rule 3: At the last level, all remaining stems must form leaves.
            // This means there should be no stems left over after forming leaves.
            if (stems_remaining_after_leaves > 0) {
                possible = false; // Stems left over at the last level, but nowhere to go
            }
        }
    }

    // Output the result for the current test case
    if (possible) {
        std::cout << "Yes\n";
    } else {
        std::cout << "No\n";
    }
}

// Main function
int main() {
    // Optimize C++ standard streams for competitive programming.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams,
    // potentially speeding up I/O.
    // std::cin.tie(NULL) prevents cin from flushing cout before each input operation,
    // further improving I/O performance.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t; // Number of test cases
    std::cin >> t; // Read t

    // Loop through each test case
    while (t--) {
        solve(); // Call the solve function for each test case
    }

    return 0; // Indicate successful execution
}

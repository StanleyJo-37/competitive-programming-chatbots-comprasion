#include <iostream> // Required for standard input/output operations (std::cin, std::cout, std::endl)
#include <vector>   // Not strictly necessary for this solution as results are printed directly, but often useful.
#include <numeric>  // Not strictly necessary for this solution.

// Function to solve a single test case
void solve() {
    int n; // Declare an integer variable 'n' to store the number of teams
    std::cin >> n; // Read the value of 'n' from standard input

    // The problem requires printing results for games in a specific order:
    // (1,2), (1,3), ..., (1,n), (2,3), ..., (2,n), ..., (n-1,n).
    // This corresponds to iterating 'i' from 1 to n-1, and 'j' from i+1 to n.
    for (int i = 1; i <= n; ++i) { // Loop for the first team in a pair (1-based index)
        for (int j = i + 1; j <= n; ++j) { // Loop for the second team in a pair (1-based index)
            // Convert 1-based team indices to 0-based indices for easier modular arithmetic.
            // This is a common practice in competitive programming when dealing with cyclic structures.
            int team1_idx = i - 1;
            int team2_idx = j - 1;

            // Calculate the difference between the 0-based indices.
            // This 'diff' represents the "distance" between team1_idx and team2_idx
            // in a linear sense, which can be used to infer cyclic relationships.
            int diff = team2_idx - team1_idx;

            // Case 1: 'n' is odd
            // When 'n' is odd, it's possible to have zero ties.
            // Each team plays 'n-1' games. To achieve equal scores with no ties,
            // each team must win (n-1)/2 games and lose (n-1)/2 games.
            // This is because (n-1) is even, so (n-1)/2 is an integer.
            // The construction strategy is to make team 'i' win against the next (n-1)/2 teams
            // in a cyclic order (i.e., i+1, i+2, ..., i+(n-1)/2).
            if (n % 2 != 0) {
                // If the difference 'diff' (j-i) is within the range of wins for team 'i',
                // then team 'i' wins against team 'j'.
                // The range is [1, (n-1)/2].
                if (diff <= (n - 1) / 2) {
                    std::cout << 1 << " "; // Team 'i' wins (represented by 1)
                } else {
                    // Otherwise, team 'j' wins against team 'i'.
                    // This means 'j' is cyclically "further" than the win range for 'i',
                    // implying 'i' is in the win range for 'j' (when viewed from 'j').
                    std::cout << -1 << " "; // Team 'j' wins (represented by -1)
                }
            }
            // Case 2: 'n' is even
            // When 'n' is even, it's not possible to have zero ties while maintaining equal scores.
            // The minimum number of ties required is n/2.
            // This implies each team must be involved in exactly one tie.
            // Additionally, each team will win (n-2)/2 games and lose (n-2)/2 games.
            // The tie is assigned to the team exactly 'n/2' positions away cyclically.
            // For example, team 'i' ties with team '(i + n/2) % n'.
            else {
                // Check if the current game (team1_idx, team2_idx) is one of the designated ties.
                // This occurs when their cyclic distance is exactly n/2.
                if (diff == n / 2) {
                    std::cout << 0 << " "; // It's a tie (represented by 0)
                }
                // If it's not a tie game, determine the winner based on the win/loss pattern.
                // Similar to the odd 'n' case, but now each team wins (n-2)/2 games.
                // The 'diff' (j-i) is compared against (n-2)/2.
                else if (diff < n / 2) {
                    // If 'diff' is within the win range [1, (n-2)/2] for team 'i',
                    // and it's not the tie partner, then team 'i' wins.
                    if (diff <= (n - 2) / 2) {
                        std::cout << 1 << " "; // Team 'i' wins
                    } else {
                        // This 'else' branch covers cases where (n-2)/2 < diff < n/2.
                        // For example, if n=4, (n-2)/2=1, n/2=2. There are no integers 'diff'
                        // such that 1 < diff < 2. So this specific branch is effectively
                        // unreachable for n=4. For larger even n, it means team 'j' wins.
                        std::cout << -1 << " "; // Team 'j' wins
                    }
                } else { // diff > n/2
                    // If 'diff' is greater than n/2, it means team 'j' is cyclically
                    // "far" from team 'i'. In this scenario, team 'j' wins against team 'i'.
                    // This corresponds to team 'i' being in the loss range for team 'j'.
                    std::cout << -1 << " "; // Team 'j' wins
                }
            }
        }
    }
    std::cout << std::endl; // Print a newline character after all results for the current test case
}

// Main function where the program execution begins
int main() {
    // Optimize C++ standard streams for competitive programming.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams.
    // This can significantly speed up I/O operations.
    std::ios_base::sync_with_stdio(false);
    // std::cin.tie(NULL) prevents std::cin from flushing std::cout before reading input.
    // This further speeds up I/O, especially when there's a mix of input and output.
    std::cin.tie(NULL);

    int t; // Declare an integer variable 't' to store the number of test cases
    std::cin >> t; // Read the number of test cases

    // Loop through each test case
    while (t--) {
        solve(); // Call the 'solve' function for each test case
    }

    return 0; // Indicate successful program execution
}

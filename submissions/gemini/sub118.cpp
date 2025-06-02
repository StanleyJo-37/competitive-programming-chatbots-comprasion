#include <iostream> // Required for standard input/output operations (cin, cout).
#include <vector>   // Not strictly necessary if using a global array for counts, but good to include if considering alternatives.
#include <algorithm> // Required for std::min.

// Define the maximum possible rating value.
// Player ratings r_i are up to 10^6.
const int MAX_RATING = 1000000;

// Declare a global array to store the frequency of each rating.
// Global arrays are automatically zero-initialized, which is convenient
// as we start with no players counted. The size is MAX_RATING + 1
// to accommodate ratings from 1 to MAX_RATING (using 1-based indexing for ratings).
int counts[MAX_RATING + 1];

int main() {
    // Optimize C++ standard streams for competitive programming.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams,
    // potentially speeding up I/O.
    // std::cin.tie(NULL) prevents cin from flushing cout before each input operation,
    // further improving I/O performance.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, a, b, k;
    // Read the total number of players (n),
    // the number of players in the first group (a),
    // the number of players in the second group (b),
    // and the rating multiplier (k).
    std::cin >> n >> a >> b >> k;

    // Read each player's rating and increment its count in the 'counts' array.
    for (int i = 0; i < n; ++i) {
        int r;
        std::cin >> r;
        counts[r]++; // Increment the frequency for rating 'r'.
    }

    int total_teams = 0; // Initialize the total number of teams formed.
                         // An 'int' is sufficient here as the maximum number of teams
                         // (n / (a+b)) will not exceed the maximum value of an int (approx 2*10^9).
                         // For n=3e5, a=1, b=1, max teams = 3e5/2 = 1.5e5.

    // Iterate through all possible base ratings (X) for the first group of players.
    // The rating X must be at least 1.
    // The rating for the second group will be k*X. This rating k*X must also be
    // within the valid range of ratings (1 to MAX_RATING).
    // Therefore, X can go up to MAX_RATING / k.
    for (int x = 1; x <= MAX_RATING / k; ++x) {
        // Check if there are enough players with rating X for the first group ('a' players)
        // AND enough players with rating k*X for the second group ('b' players).
        if (counts[x] >= a && counts[x * k] >= b) {
            // Calculate the maximum number of teams that can be formed using
            // rating X as the base and k*X as the second rating.
            // This is limited by:
            // 1. The number of available players with rating X, divided by 'a'.
            // 2. The number of available players with rating k*X, divided by 'b'.
            int teams_from_x = std::min(counts[x] / a, counts[x * k] / b);

            // Add the newly formed teams to the total count.
            total_teams += teams_from_x;

            // Deduct the players used for these teams from the 'counts' array.
            // This is crucial for the greedy approach: once players are used,
            // they cannot be used again for other teams.
            counts[x] -= teams_from_x * a;
            counts[x * k] -= teams_from_x * b;
        }
    }

    // Print the final maximum number of teams that can be composed.
    std::cout << total_teams << std::endl;

    return 0; // Indicate successful execution.
}

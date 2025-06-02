#include <iostream> // Required for input/output operations (cin, cout)
#include <vector>   // Required for std::vector to store team data
#include <algorithm> // Required for std::sort to sort the teams
#include <utility>  // Required for std::pair (though often implicitly included by other headers)

// Custom comparison function for sorting teams.
// Teams are ranked primarily by the number of problems solved (more is better),
// and secondarily by penalty time (less is better).
// This function defines the "less than" relationship for std::sort,
// meaning 'a' comes before 'b' if this function returns true.
bool compareTeams(const std::pair<int, int>& a, const std::pair<int, int>& b) {
    // If the number of problems solved is different:
    // The team with more problems solved gets a higher rank (comes first).
    if (a.first != b.first) {
        return a.first > b.first; // Sort in descending order of problems solved
    }
    // If the number of problems solved is the same:
    // The team with less penalty time gets a higher rank (comes first).
    return a.second < b.second; // Sort in ascending order of penalty time
}

int main() {
    // Optimize C++ standard streams for faster input/output.
    // This is a common practice in competitive programming to disable synchronization
    // with C's stdio and untie cin from cout.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, k;
    // Read the total number of teams (n) and the target rank (k).
    std::cin >> n >> k;

    // Create a vector to store team data. Each team is represented as a pair:
    // first element is problems solved (p), second is penalty time (t).
    std::vector<std::pair<int, int>> teams(n);
    for (int i = 0; i < n; ++i) {
        // Read problems solved (p) and penalty time (t) for each team.
        std::cin >> teams[i].first >> teams[i].second;
    }

    // Sort the teams vector using the custom comparison function.
    // After sorting, teams will be ordered from highest rank to lowest rank
    // according to the contest rules. Teams with identical scores will be
    // adjacent in the sorted list.
    std::sort(teams.begin(), teams.end(), compareTeams);

    // The k-th place (1-indexed) corresponds to the element at index k-1 (0-indexed)
    // in the sorted vector. We need to find the problems solved and penalty time
    // for this specific rank. This team's score defines the score for the k-th place.
    int target_p = teams[k - 1].first;
    int target_t = teams[k - 1].second;

    int count = 0;
    // Iterate through the sorted teams to count how many teams share the
    // exact same problems solved and penalty time as the team at the k-th place.
    // All teams sharing the k-th place will have this identical score.
    for (int i = 0; i < n; ++i) {
        if (teams[i].first == target_p && teams[i].second == target_t) {
            count++;
        }
    }

    // Print the total count of teams sharing the k-th place.
    std::cout << count << std::endl;

    return 0; // Indicate successful execution
}

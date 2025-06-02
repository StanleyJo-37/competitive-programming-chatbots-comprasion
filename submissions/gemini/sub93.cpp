#include <iostream> // Required for input/output operations (cin, cout).
#include <vector>   // Required for using std::vector to store dynamic arrays.
#include <numeric>  // Not strictly needed for this solution, but often useful for algorithms like std::iota.

// Function to solve a single test case.
void solve() {
    int n;
    std::cin >> n; // Read the number of daughters and kingdoms.

    // Store daughters' preferences. g[i] will contain the list of kingdoms daughter i wants.
    // Using 1-based indexing for daughters and kingdoms for convenience, so vectors are sized n+1.
    std::vector<std::vector<int>> g(n + 1);
    for (int i = 1; i <= n; ++i) { // Iterate through each daughter.
        int k;
        std::cin >> k; // Read the number of preferred kingdoms for daughter i.
        g[i].resize(k); // Resize the vector for daughter i's preferences.
        for (int j = 0; j < k; ++j) {
            std::cin >> g[i][j]; // Read each preferred kingdom.
        }
    }

    // Track which daughters are married and which kingdoms are taken.
    // Initialized to false, meaning no daughter is married and no kingdom is taken initially.
    std::vector<bool> daughter_married(n + 1, false);
    std::vector<bool> kingdom_taken(n + 1, false);

    // Simulate the initial greedy marriage process.
    // Daughters are processed in order from 1 to n.
    for (int i = 1; i <= n; ++i) { // Iterate through daughters.
        bool current_daughter_married = false; // Flag to check if daughter i gets married.
        // Iterate through the current daughter's preferred kingdoms.
        // The problem guarantees these lists are already sorted by kingdom number.
        for (int kingdom_pref : g[i]) {
            // If the prince of this preferred kingdom is not yet taken.
            if (!kingdom_taken[kingdom_pref]) {
                // Marry the daughter to this prince.
                kingdom_taken[kingdom_pref] = true; // Mark the kingdom as taken.
                daughter_married[i] = true;         // Mark the daughter as married.
                current_daughter_married = true;    // Set flag.
                break; // Daughter i is married, move to the next daughter.
            }
        }
    }

    // Find the first (lowest indexed) unmarried daughter.
    int unmarried_daughter_idx = -1;
    for (int i = 1; i <= n; ++i) {
        if (!daughter_married[i]) {
            unmarried_daughter_idx = i; // Found an unmarried daughter.
            break; // Stop at the first one.
        }
    }

    // Find the first (lowest indexed) untaken kingdom.
    int untaken_kingdom_idx = -1;
    for (int i = 1; i <= n; ++i) {
        if (!kingdom_taken[i]) {
            untaken_kingdom_idx = i; // Found an untaken kingdom.
            break; // Stop at the first one.
        }
    }

    // Determine if an improvement is possible.
    // An improvement is possible if there is at least one unmarried daughter.
    // If there is an unmarried daughter, there must also be an untaken kingdom.
    // (Proof by contradiction: If all N kingdoms were taken, then N marriages must have occurred,
    // implying all N daughters are married, which contradicts the existence of an unmarried daughter).
    if (unmarried_daughter_idx == -1) {
        // If no unmarried daughter is found, it means all N daughters are married.
        // This is the maximum possible number of couples, so it's optimal.
        std::cout << "OPTIMAL\n";
    } else {
        // If an unmarried daughter exists, an untaken kingdom must also exist.
        // We can improve the number of marriages by adding 'untaken_kingdom_idx'
        // to 'unmarried_daughter_idx''s list.
        // When the greedy process runs again with this change:
        // 1. Daughters before 'unmarried_daughter_idx' will make the exact same choices
        //    because 'untaken_kingdom_idx' was not taken by them in the original simulation.
        // 2. 'unmarried_daughter_idx' will now find 'untaken_kingdom_idx' available
        //    (since it was untaken by previous daughters and is the smallest available option for her
        //    among new choices, and all her original choices were taken). She will marry it.
        // 3. Daughters after 'unmarried_daughter_idx' are not negatively affected.
        //    'untaken_kingdom_idx' was not taken by anyone in the original simulation,
        //    so 'unmarried_daughter_idx' marrying it doesn't "steal" a prince from a later daughter.
        // Thus, the total number of married couples increases by exactly one.
        std::cout << "IMPROVE\n";
        std::cout << unmarried_daughter_idx << " " << untaken_kingdom_idx << "\n";
    }
}

int main() {
    // Optimize C++ standard streams for faster input/output.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams.
    // std::cin.tie(NULL) prevents std::cout from flushing before std::cin reads input.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t; // Read the number of test cases.
    while (t--) {  // Loop through each test case.
        solve();   // Call the solve function for the current test case.
    }

    return 0; // Indicate successful execution.
}

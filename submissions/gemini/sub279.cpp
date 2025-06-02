#include <iostream> // Required for standard input/output operations (std::cin, std::cout)
#include <vector>   // Required for std::vector, used for dynamic arrays
#include <numeric>  // Required for std::iota, used to initialize parent array efficiently

// Global parent vector for Disjoint Set Union (DSU) data structure.
// Using a global variable is a common practice in competitive programming for DSU
// to avoid passing it around to recursive functions.
// The size is n + 2: indices 1 to n represent knights, and n + 1 acts as a sentinel.
std::vector<int> parent;

// The find function with path compression.
// This function determines the representative (root) of the set that 'i' belongs to.
// In this specific DSU application, it finds the smallest active knight
// whose index is greater than or equal to 'i'.
int find(int i) {
    // Base case: If 'i' is its own parent, it is the representative of its set.
    if (parent[i] == i) {
        return i;
    }
    // Recursive step: Otherwise, recursively find the representative of its parent
    // and apply path compression by making 'i' directly point to the root.
    return parent[i] = find(parent[i]);
}

int main() {
    // Optimize C++ standard streams for faster input/output operations.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams.
    // std::cin.tie(NULL) prevents std::cout from flushing before std::cin reads input.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, m; // n: number of knights, m: number of fights
    std::cin >> n >> m;

    // Initialize the parent vector for the DSU structure.
    // Initially, each knight 'i' is its own parent (parent[i] = i), meaning they are all active.
    // parent[n+1] = n+1 serves as a sentinel, indicating the end of the knight range.
    parent.resize(n + 2);
    std::iota(parent.begin(), parent.end(), 0); // Fills parent with 0, 1, 2, ..., n+1

    // 'ans' vector stores the result for each knight.
    // ans[i] will store the knight who defeated knight 'i'.
    // If knight 'i' wins the entire tournament, ans[i] remains 0.
    // Size n+1: indices 1 to n for knights.
    std::vector<int> ans(n + 1, 0);

    // Process each of the 'm' fights.
    for (int k = 0; k < m; ++k) {
        int l, r, x; // l: left boundary, r: right boundary, x: winner of the fight
        std::cin >> l >> r >> x;

        // Start searching for active knights within the range [l, r].
        // 'curr' will represent the current active knight being examined.
        // find(l) returns the smallest active knight whose index is >= l.
        int curr = find(l);

        // Iterate through all active knights found within the range [l, r].
        // The loop continues as long as 'curr' (the current active knight)
        // is within or equal to the right boundary 'r'.
        while (curr <= r) {
            // If the current active knight 'curr' is the winner of this fight ('x').
            if (curr == x) {
                // The winner 'x' remains active and continues in the tournament.
                // We need to find the next active knight *after* the winner 'x'
                // to continue processing the range.
                curr = find(curr + 1);
            } else {
                // If 'curr' is not the winner, it means 'curr' is defeated by 'x'.
                ans[curr] = x; // Record 'x' as the conqueror of 'curr'.

                // Mark 'curr' as defeated by updating its parent in the DSU structure.
                // By setting parent[curr] to find(curr + 1), we effectively "remove"
                // 'curr' from the set of active knights. Any future 'find' operation
                // that would have passed through 'curr' will now directly jump to
                // the next active knight after 'curr', thanks to path compression.
                parent[curr] = find(curr + 1);

                // Move to the next active knight to continue iterating the range.
                // Since parent[curr] has just been updated to point to the next active knight,
                // 'curr' can be directly updated to this new representative.
                // This is equivalent to `curr = find(curr)` after the parent update,
                // as `find(curr)` would now return the new representative.
                curr = parent[curr];
            }
        }
    }

    // Print the final results for each knight from 1 to n.
    for (int i = 1; i <= n; ++i) {
        std::cout << ans[i] << (i == n ? "" : " "); // Print space between numbers, no space after the last one.
    }
    std::cout << std::endl; // Newline at the end of the output.

    return 0; // Indicate successful execution.
}
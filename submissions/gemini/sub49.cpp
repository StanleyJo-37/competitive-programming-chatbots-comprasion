#include <iostream> // Required for input (std::cin) and output (std::cout).
#include <vector>   // Required for using std::vector to store tile destruction days and reachability.

int main() {
    // Optimize C++ standard streams for faster input/output.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams,
    // potentially speeding up I/O operations.
    // std::cin.tie(NULL) prevents std::cout from flushing before each std::cin operation,
    // further improving performance for interactive problems or large I/O.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    std::cin >> n; // Read the number of tiles on the boulevard.

    std::vector<int> a(n);
    // Read the destruction days for each tile.
    // `a[i]` stores the number of days after which tile `(i+1)` is destroyed.
    // This means tile `(i+1)` is available for walking up to and including day `a[i]`.
    // On day `a[i] + 1`, it is destroyed.
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    // The problem asks for the maximum number of days the walk from tile 1 to tile n will be possible.
    // The maximum possible value for any `a_i` is 1000. This implies that the walk
    // cannot be possible for more than 1000 days.
    // We can find the maximum possible days by iterating downwards from the maximum
    // possible `a_i` value (1000) to 1.
    // This approach works because of monotonicity: if a path exists for `D` days,
    // it will also exist for any `D' < D` days (as fewer tiles would be destroyed).
    // The first `current_day` (starting from 1000 and decreasing) for which a path
    // is found will be our answer.
    for (int current_day = 1000; current_day >= 1; --current_day) {
        // `reachable` is a boolean vector where `reachable[i]` will be true if
        // tile `(i+1)` is reachable from tile 1 on the `current_day`.
        // It's 0-indexed to align with the `a` vector (tile 1 is `a[0]`, tile n is `a[n-1]`).
        std::vector<bool> reachable(n, false);

        // Base case: Tile 1 (at index 0) is the starting point.
        // It is reachable if it is not destroyed on `current_day`.
        if (a[0] >= current_day) {
            reachable[0] = true;
        } else {
            // If tile 1 is destroyed on `current_day`, no path can start.
            // Therefore, no path is possible for this `current_day`.
            // We move to check a smaller number of days.
            continue;
        }

        // Dynamic programming approach to determine reachability for subsequent tiles.
        // We iterate from tile 2 (index 1) up to tile n (index n-1).
        for (int i = 1; i < n; ++i) {
            // A tile `(i+1)` (at index `i`) can only be reachable if it itself
            // is not destroyed on `current_day`.
            if (a[i] >= current_day) {
                // Check if tile `(i+1)` can be reached from tile `i` (at index `i-1`).
                // This corresponds to a 1-step move (from `i` to `i+1`).
                if (reachable[i - 1]) {
                    reachable[i] = true;
                }
                // Check if tile `(i+1)` can be reached from tile `(i-1)` (at index `i-2`).
                // This corresponds to a 2-step jump (from `i-1` to `i+1`).
                // We must ensure `i-2` is a valid index (i.e., tile `(i-1)` exists).
                if (i - 2 >= 0 && reachable[i - 2]) {
                    reachable[i] = true;
                }
            }
        }

        // After iterating through all tiles, if tile n (at index `n-1`) is reachable,
        // it means a path exists from tile 1 to tile n for `current_day` days.
        // Since we are iterating `current_day` downwards, this `current_day` is
        // the maximum possible number of days.
        if (reachable[n - 1]) {
            std::cout << current_day << std::endl; // Print the answer.
            return 0; // Terminate the program as we found the maximum days.
        }
    }

    // This part of the code should theoretically not be reached given the problem constraints.
    // Constraints state `1 <= n <= 1000` and `1 <= a_i <= 1000`.
    // This means for `current_day = 1`, all tiles are available (`a_i >= 1`).
    // A path will always exist (e.g., 1 -> 2 -> ... -> n, or 1 -> 3 -> ... if n is large enough).
    // Thus, the loop will always find a valid `current_day` (at least 1) and return.
    return 0;
}

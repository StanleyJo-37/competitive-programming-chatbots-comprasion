#include <iostream> // Required for input/output operations (cin, cout)

int main() {
    // Optimize C++ standard streams for competitive programming.
    // This unties cin/cout from the standard C I/O and disables synchronization
    // with C stdio, which can significantly speed up I/O operations.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t; // Declare an integer variable 't' to store the number of testcases.
    std::cin >> t; // Read the number of testcases from standard input.

    // Loop through each testcase.
    while (t--) {
        int n, m; // Declare integers 'n' for board size and 'm' for number of rooks.
        std::cin >> n >> m; // Read 'n' and 'm' for the current testcase.

        // The problem states that initially, no two rooks attack each other.
        // This implies that all 'm' rooks are in distinct rows and distinct columns.
        // Let R_used be the set of rows occupied by rooks, and C_used be the set of columns occupied by rooks.
        // Initially, |R_used| = m and |C_used| = m.

        // We need to determine if it's possible to move exactly one rook to a *different* cell
        // such that no two rooks still attack each other.
        // This means after moving a rook from (x_k, y_k) to (x_k', y_k'),
        // the new position (x_k', y_k') must not share a row or column with any other rook (x_j, y_j) where j != k.
        // In other words, x_k' must not be in R_used \ {x_k}, and y_k' must not be in C_used \ {y_k}.

        // Let R_free be the set of rows not occupied by any rook: {1, ..., n} \ R_used.
        // Let C_free be the set of columns not occupied by any rook: {1, ..., n} \ C_used.
        // The size of R_free is n - m. The size of C_free is n - m.

        // For a rook at (x_k, y_k) to be moved to (x_k', y_k') such that no rooks attack:
        // 1. The new row x_k' must not be occupied by any other rook. This means x_k' must be in R_free or x_k' == x_k.
        // 2. The new column y_k' must not be occupied by any other rook. This means y_k' must be in C_free or y_k' == y_k.
        // 3. The move must be to a *different* cell, so (x_k', y_k') != (x_k, y_k).
        // 4. A rook can move to any cell in its row or column. So either x_k' == x_k OR y_k' == y_k.

        // Case 1: m < n
        // If m < n, then n - m > 0. This means R_free is not empty and C_free is not empty.
        // We can pick any rook, say the first one at (x_1, y_1).
        // Since R_free is not empty, there exists at least one row x_new such that x_new is not occupied by any rook.
        // We can move the rook from (x_1, y_1) to (x_new, y_1).
        // This is a valid move because:
        // a) It's a move within the same column (y_1), which is allowed.
        // b) x_new != x_1 (since x_new is free and x_1 is occupied, and m < n implies there's at least one free row different from x_1).
        // c) The new row x_new is not occupied by any other rook (by definition of R_free).
        // d) The new column y_1 is still only occupied by this rook (the other rooks are in different columns).
        // Therefore, if m < n, it's always possible to make such a move. Print "YES".

        // Case 2: m = n
        // If m = n, then n - m = 0. This means R_free is empty and C_free is empty.
        // All 'n' rows are occupied, and all 'n' columns are occupied.
        // Consider moving a rook from (x_k, y_k) to (x_k', y_k').
        // For the non-attacking property to hold, x_k' must not be in R_used \ {x_k}.
        // Since R_used = {1, ..., n}, R_used \ {x_k} is the set of all rows except x_k.
        // So, x_k' must be x_k.
        // Similarly, y_k' must not be in C_used \ {y_k}.
        // Since C_used = {1, ..., n}, C_used \ {y_k} is the set of all columns except y_k.
        // So, y_k' must be y_k.
        // This implies that for the non-attacking property to hold, the rook must be moved to (x_k, y_k).
        // However, the problem explicitly states "move exactly one rook into a *different* cell".
        // This creates a contradiction. Thus, if m = n, no such move is possible. Print "NO".

        // The coordinates (x_i, y_i) for each rook are read but not used in this logic,
        // as the solution only depends on 'n' and 'm'. We still need to read them
        // to consume the input correctly for each testcase.
        for (int i = 0; i < m; ++i) {
            int r, c; // Declare variables for rook's row and column.
            std::cin >> r >> c; // Read rook's position.
        }

        // Apply the derived logic:
        if (m < n) {
            std::cout << "YES\n"; // If m is less than n, it's possible.
        } else { // This implies m == n, as m cannot be greater than n given the initial non-attacking condition.
            std::cout << "NO\n"; // If m equals n, it's not possible.
        }
    }

    return 0; // Indicate successful program execution.
}

#include <iostream> // Required for input/output operations (std::cin, std::cout)
#include <vector>   // Not strictly necessary for this problem, but often useful in competitive programming
#include <algorithm> // Not strictly necessary for this problem, but often useful for min/max operations etc.

int main() {
    // Optimize C++ standard streams for faster input/output.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams.
    // std::cin.tie(NULL) prevents std::cout from flushing before std::cin reads input.
    // These are common competitive programming optimizations for performance.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, m;
    // Read the number of rows (n) and columns (m) of the table.
    std::cin >> n >> m;

    // A boolean flag to track if we find any "good" cell that is located on the border
    // (i.e., in the first row, last row, first column, or last column).
    // Initialize to false, as we haven't found such a cell yet.
    bool good_cell_on_border = false;

    // Iterate through each cell of the table.
    // The problem describes rows and columns as 1-indexed, so we use 1-indexed loops
    // to match the problem's coordinate system for clarity.
    for (int i = 1; i <= n; ++i) { // Loop through rows from 1 to n
        for (int j = 1; j <= m; ++j) { // Loop through columns from 1 to m
            int cell_value;
            // Read the value of the current cell (0 if not good, 1 if good).
            std::cin >> cell_value;
            
            // If the current cell is a good cell (its value is 1).
            if (cell_value == 1) {
                // Check if this good cell is on any of the four borders of the table.
                // A cell (i, j) is on the border if its row index 'i' is 1 (first row)
                // OR 'i' is n (last row), OR its column index 'j' is 1 (first column)
                // OR 'j' is m (last column).
                // The problem guarantees that no good cell is a corner (e.g., (1,1), (1,m), (n,1), (n,m)).
                // This means if a good cell is on a border, it's strictly on an edge, not a corner.
                //
                // If a good cell is found on any border, it implies that the entire table
                // can be colored in a minimum of 2 operations.
                // For example, if (1, y) is a good cell (where 1 < y < m, since it's not a corner):
                // 1. Choose good cell (1, y) and table corner (n, 1). This colors the rectangle
                //    from (min(1,n), min(y,1)) to (max(1,n), max(y,1)), which is (1,1) to (n,y).
                //    This covers all cells in columns 1 through y across all rows.
                // 2. Choose good cell (1, y) and table corner (n, m). This colors the rectangle
                //    from (min(1,n), min(y,m)) to (max(1,n), max(y,m)), which is (1,y) to (n,m).
                //    This covers all cells in columns y through m across all rows.
                // The union of these two rectangles covers the entire n x m table.
                // Similar logic applies if the good cell is on row 'n', column '1', or column 'm'.
                if (i == 1 || i == n || j == 1 || j == m) {
                    good_cell_on_border = true;
                    // Once we find such a cell, we know the answer is 2. We can stop searching.
                    // However, for simplicity and given the small constraints (N, M <= 50),
                    // iterating through the rest of the grid doesn't significantly impact performance.
                    // If N, M were much larger, we would break out of loops here.
                }
            }
        }
    }

    // After checking all cells, determine the minimum number of operations.
    if (good_cell_on_border) {
        // If at least one good cell was found on a border, 2 operations are sufficient.
        // As explained above, 2 operations are also necessary because a single operation
        // from a non-corner good cell cannot cover the entire grid (it will always miss
        // at least one of the four table corners).
        std::cout << 2 << std::endl;
    } else {
        // If no good cell was found on any border, it implies that all good cells
        // are located in the interior of the table (i.e., for any good cell (x,y),
        // 1 < x < n and 1 < y < m).
        // In this scenario, 4 operations are needed and sufficient.
        // Let (x, y) be any interior good cell:
        // 1. Choose (x, y) and table corner (1, 1) -> colors rectangle [1, x] x [1, y].
        // 2. Choose (x, y) and table corner (n, 1) -> colors rectangle [x, n] x [1, y].
        // 3. Choose (x, y) and table corner (1, m) -> colors rectangle [1, x] x [y, m].
        // 4. Choose (x, y) and table corner (n, m) -> colors rectangle [x, n] x [y, m].
        // The union of these four rectangles covers the entire n x m table.
        //
        // Why 4 operations are necessary:
        // Each operation using an interior good cell (x, y) and one of the four table corners
        // can cover exactly one of the four table corners (1,1), (n,1), (1,m), (n,m).
        // For example, (x,y) with (1,1) covers (1,1) but not (n,1), (1,m), or (n,m)
        // because x < n and y < m.
        // Since all four table corners must be covered, and each operation from an interior
        // good cell can cover only one of them, a minimum of 4 operations are required.
        std::cout << 4 << std::endl;
    }

    return 0; // Indicate successful program execution.
}
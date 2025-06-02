#include <utility> // Required for std::pair

/**
 * @brief Converts 2D coordinates (x, y) to a 1D zero-based index.
 *        Assumes a row-major order for the 1D representation.
 *
 * @param x The x-coordinate (column index) in the 2D array.
 * @param y The y-coordinate (row index) in the 2D array.
 * @param size A std::pair<int, int> representing the dimensions (width, height) of the 2D array.
 *             size.first is the width, size.second is the height.
 * @return The corresponding zero-based index in the 1D array.
 */
int to_1D(int x, int y, std::pair<int, int> size) {
    // In a row-major order, elements are stored row by row.
    // To find the 1D index for a given (x, y) coordinate:
    // Each full row before 'y' contributes 'width' elements to the 1D index.
    // So, 'y' rows contribute 'y * width' elements.
    // Within the current row 'y', 'x' elements have been passed.
    // Therefore, the total 1D index is (y * width) + x.
    // Example: For a 3x3 array (width=3, height=3):
    // (0,0) -> 0*3 + 0 = 0
    // (1,0) -> 0*3 + 1 = 1
    // (2,0) -> 0*3 + 2 = 2
    // (0,1) -> 1*3 + 0 = 3
    // (1,1) -> 1*3 + 1 = 4
    // (2,1) -> 1*3 + 2 = 5
    // (0,2) -> 2*3 + 0 = 6
    // (1,2) -> 2*3 + 1 = 7
    // (2,2) -> 2*3 + 2 = 8
    int width = size.first;
    return y * width + x;
}

/**
 * @brief Converts a 1D zero-based index to 2D coordinates (x, y).
 *        Assumes a row-major order for the 1D representation.
 *
 * @param n The zero-based index in the 1D array.
 * @param size A std::pair<int, int> representing the dimensions (width, height) of the 2D array.
 *             size.first is the width, size.second is the height.
 * @return A std::pair<int, int> where first is the x-coordinate (column) and second is the y-coordinate (row).
 */
std::pair<int, int> to_2D(int n, std::pair<int, int> size) {
    // To reverse the 1D to 2D mapping (n = y * width + x):
    // The row (y) can be found by integer division of the 1D index 'n' by the 'width'.
    // This is because each row contains 'width' elements.
    // y = n / width (integer division)
    // The column (x) can be found by the remainder of the 1D index 'n' divided by the 'width'.
    // This gives the position within the current row.
    // x = n % width (modulo operation)
    // Example: For a 3x3 array (width=3, height=3):
    // n=5:
    // y = 5 / 3 = 1 (integer division)
    // x = 5 % 3 = 2
    // Returns (2,1)
    // n=3:
    // y = 3 / 3 = 1
    // x = 3 % 3 = 0
    // Returns (0,1)
    int width = size.first;
    int y = n / width; // Calculate row (y)
    int x = n % width; // Calculate column (x)
    return {x, y}; // Return as a pair (x, y)
}

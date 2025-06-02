#include <utility>

// Converts 2D coordinates (x, y) to a 1D index based on the given size (width, height).
// The 2D array is stored in row-major order (i.e., rows are contiguous in memory).
// Formula: index = y * width + x
int to_1D(int x, int y, const std::pair<int, int>& size) {
    return y * size.first + x;
}

// Converts a 1D index 'n' back to 2D coordinates (x, y) based on the given size (width, height).
// The 2D array is stored in row-major order, so:
// x = n % width, y = n / width
std::pair<int, int> to_2D(int n, const std::pair<int, int>& size) {
    return {n % size.first, n / size.first};
}
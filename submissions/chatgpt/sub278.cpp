#include <iostream>
#include <tuple>
using namespace std;

// Converts 2D coordinates (x, y) to 1D index for a 2D array of given size (width, height)
int to_1D(int x, int y, pair<int, int> size) {
    // size.first is width, size.second is height
    // The formula is: index = y * width + x
    return y * size.first + x;
}

// Converts 1D index n to 2D coordinates (x, y) for a 2D array of given size (width, height)
pair<int, int> to_2D(int n, pair<int, int> size) {
    // size.first is width, size.second is height
    // The formula is: y = n / width, x = n % width
    int width = size.first;
    int y = n / width;
    int x = n % width;
    return {x, y};
}

// Test cases to demonstrate correctness
int main() {
    pair<int, int> size = {3, 3}; // width=3, height=3

    // Test to_1D
    cout << to_1D(0, 0, size) << endl; // Expected: 0
    cout << to_1D(1, 1, size) << endl; // Expected: 4
    cout << to_1D(2, 2, size) << endl; // Expected: 8

    // Test to_2D
    pair<int, int> res1 = to_2D(5, size);
    cout << "(" << res1.first << "," << res1.second << ")" << endl; // Expected: (2,1)

    pair<int, int> res2 = to_2D(3, size);
    cout << "(" << res2.first << "," << res2.second << ")" << endl; // Expected: (0,1)

    return 0;
}
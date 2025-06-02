#include <iostream>
using namespace std;

// Function to compute the value at cell (x, y) in the matrix
// The value at (x, y) is given by: value(x, y) = (x + y - 2) * (x + y - 1) / 2 + x
long long cell_value(int x, int y) {
    long long s = x + y - 2;
    return s * (s + 1) / 2 + x;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        long long sum = 0;
        int x = x1, y = y1;
        // Move down from (x1, y1) to (x2, y1)
        for (int i = x1; i <= x2; ++i) {
            sum += cell_value(i, y1);
        }
        // Move right from (x2, y1+1) to (x2, y2)
        for (int j = y1 + 1; j <= y2; ++j) {
            sum += cell_value(x2, j);
        }
        cout << sum << '\n';
    }
    return 0;
}
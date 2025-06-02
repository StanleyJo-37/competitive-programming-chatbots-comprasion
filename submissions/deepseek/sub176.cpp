#include <iostream>
using namespace std;

// Function to calculate the value at position (x, y) in the matrix
long long getValue(long long x, long long y) {
    // The value at (x, y) is determined by the diagonal (x + y - 2)
    // The sum of the first (x + y - 2) terms is (k * (k + 1)) / 2, where k = x + y - 2
    // The value at (x, y) is this sum + x
    long long k = x + y - 2;
    return (k * (k + 1)) / 2 + x;
}

// Function to compute the sum of values from (x1, y1) to (x2, y2) along the optimal path
long long maxPathSum(long long x1, long long y1, long long x2, long long y2) {
    long long sum = 0;
    // Move down first until x reaches x2 (to stay on higher diagonals longer)
    while (x1 < x2) {
        sum += getValue(x1, y1);
        x1++;
    }
    // Then move right until y reaches y2
    while (y1 <= y2) {
        sum += getValue(x1, y1);
        y1++;
    }
    return sum;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    while (T--) {
        long long x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        cout << maxPathSum(x1, y1, x2, y2) << '\n';
    }
    return 0;
}
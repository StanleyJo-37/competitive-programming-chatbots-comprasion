#include <iostream>
using namespace std;

int main() {
    int l, r, x, y, k;
    cin >> l >> r >> x >> y >> k;

    // Iterate through possible costs (b) in the range [x, y]
    // For each b, check if there exists an a in [l, r] such that a = k * b
    // Since a must be integer, k * b must lie within [l, r]
    // To optimize, we can find the smallest b where k * b >= l and largest b where k * b <= r
    // Then check if there's any overlap between [x, y] and [ceil(l/k), floor(r/k)]
    // If yes, then answer is YES, else NO.

    // Calculate the smallest b where k * b >= l => b >= l / k (ceil division)
    long long min_b = (l + k - 1) / k; // Equivalent to ceil(l / k)
    // Calculate the largest b where k * b <= r => b <= r / k (floor division)
    long long max_b = r / k;

    // Check if there's any overlap between [x, y] and [min_b, max_b]
    if (max_b >= x && min_b <= y) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }

    return 0;
}
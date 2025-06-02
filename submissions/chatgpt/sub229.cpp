#include <iostream>
using namespace std;

int main() {
    // Read input values: l, r, x, y, k
    long long l, r, x, y, k;
    cin >> l >> r >> x >> y >> k;

    // We need to find if there exists an integer b in [x, y]
    // such that a = b * k is also integer and l <= a <= r

    // For each possible cost b in [x, y]
    // a = b * k
    // We need l <= b * k <= r
    // => l / k <= b <= r / k (with integer division, careful with bounds)

    // Compute the lower and upper bounds for b
    // ceil(l / k) <= b <= floor(r / k)
    // To avoid floating point, use integer math:
    // ceil(l / k) = (l + k - 1) / k
    // floor(r / k) = r / k

    long long b_min = (l + k - 1) / k; // smallest b such that b*k >= l
    long long b_max = r / k;           // largest b such that b*k <= r

    // The valid b must also be in [x, y]
    // So, the intersection of [b_min, b_max] and [x, y]
    long long left = max(b_min, x);
    long long right = min(b_max, y);

    // If there is at least one integer b in [left, right], answer is YES
    if (left <= right) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }

    return 0;
}
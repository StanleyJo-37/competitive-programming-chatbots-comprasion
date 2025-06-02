#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    // Sort the squares in ascending order of their side lengths
    sort(a.begin(), a.end());

    // If k is 0, the point must be outside all squares. Since all squares include (0,0), no such point exists.
    // If k > n, no point can be in more than n squares.
    if (k == 0 || k > n) {
        cout << -1 << endl;
        return 0;
    }

    // The k-th smallest square (0-indexed) has side length a[k-1].
    // Any point (x, y) where x and y are between 0 and a[k-1] - 1 (inclusive) will be inside exactly k squares.
    // However, if there are duplicates in a, we need to handle them.
    // To ensure the point is in exactly k squares, we can choose x = a[k-1] - 1 and y = a[k-1] - 1.
    // But if a[k-1] == a[k], then the point will be in more than k squares. So we need to check for that.
    if (k < n && a[k-1] == a[k]) {
        cout << -1 << endl;
    } else {
        // The point (a[k-1] - 1, a[k-1] - 1) is inside the first k squares (since a is sorted)
        // and not inside any larger squares (since a[k-1] < a[k] if k < n).
        // Also, ensure the coordinates are non-negative.
        int x = a[k-1] - 1;
        if (x < 0) x = 0; // edge case, though a[i] >= 1 per input constraints
        cout << x << " " << x << endl;
    }

    return 0;
}
#include <iostream>
#include <vector>
#include <algorithm> // Required for std::sort

int main() {
    // Optimize C++ standard streams for competitive programming.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams,
    // which can speed up I/O operations.
    // std::cin.tie(NULL) prevents std::cout from flushing before each std::cin operation,
    // further improving performance for interactive problems or large I/O.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, k;
    std::cin >> n >> k; // Read the number of squares (n) and the target count (k)

    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i]; // Read the side lengths of the squares
    }

    // If k is greater than n, it's impossible to find a point that belongs to exactly k squares,
    // because there are only n squares in total. In this case, no solution exists.
    if (k > n) {
        std::cout << -1 << std::endl;
        return 0;
    }

    // Sort the array 'a' in ascending order.
    // This step is crucial because it allows us to easily identify the k-th largest
    // square side length, which is key to determining the coordinates of our point.
    std::sort(a.begin(), a.end());

    // The problem asks for an integer point (x, y) that belongs to exactly k squares.
    // A square 'i' is defined by corners (0,0) and (a_i, a_i).
    // A point (x, y) belongs to square 'i' if 0 <= x <= a_i and 0 <= y <= a_i.
    // This condition can be simplified to max(x, y) <= a_i, assuming x, y >= 0.
    // We are looking for a point (x, y) such that exactly k values of a_i satisfy a_i >= max(x, y).

    // Let M = max(x, y). We need to find an M such that exactly k values in the sorted array 'a' are >= M.
    // The k largest values in the sorted array 'a' are a[n-k], a[n-k+1], ..., a[n-1] (using 0-based indexing).
    // If we choose M = a[n-k], then all these k values are guaranteed to be >= M.
    // We can construct a point (x, y) such that max(x, y) = M. A simple choice is (M, 0).

    // Case 1: k == n
    // If we need the point to be in all n squares, we should pick M as small as possible
    // while still being greater than or equal to 0.
    // The smallest side length in the sorted array is a[0].
    // If we choose M = a[0], then for any square 'i', a_i >= a[0] (since a[0] is the minimum).
    // Thus, the point (a[0], 0) will belong to all n squares.
    if (k == n) {
        std::cout << a[0] << " " << 0 << std::endl;
    }
    // Case 2: k < n
    // We want exactly k squares.
    // Consider the value a[n-k]. This is the k-th largest value in the sorted array 'a'.
    // If we choose M = a[n-k], then the squares with side lengths a[n-k], a[n-k+1], ..., a[n-1]
    // (which are exactly k squares) will contain the point (M, 0) because their side lengths are all >= M.
    // For this to be *exactly* k squares, we must ensure that squares with side lengths smaller than a[n-k]
    // do NOT contain the point. Specifically, the side length a[n-k-1] (which is the (k+1)-th largest value)
    // must be strictly less than a[n-k].
    // If a[n-k-1] is equal to a[n-k], then choosing M = a[n-k] would mean the point is also in the square
    // corresponding to a[n-k-1], resulting in k+1 squares, not k. In this scenario, no M would work:
    // - Any M' < a[n-k] would include a[n-k-1] and thus more than k squares.
    // - Any M' = a[n-k] would include a[n-k-1] and thus more than k squares.
    // - Any M' > a[n-k] would include fewer than k squares.
    // So, if a[n-k-1] == a[n-k], there is no solution.
    else { // k < n
        int val = a[n - k]; // This is the k-th largest value (0-indexed)
        // Check if the (k+1)-th largest value (a[n-k-1]) is equal to the k-th largest value (a[n-k]).
        // If they are equal, we cannot isolate exactly k squares using a[n-k] as M.
        if (a[n - k - 1] == val) {
            std::cout << -1 << std::endl;
        } else {
            // If a[n-k-1] < a[n-k], then choosing M = a[n-k] works.
            // The point (a[n-k], 0) will be in exactly k squares.
            std::cout << val << " " << 0 << std::endl;
        }
    }

    return 0; // Indicate successful execution
}
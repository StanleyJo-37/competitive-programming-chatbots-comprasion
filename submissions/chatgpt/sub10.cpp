#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false); // Fast IO
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n, q;
        cin >> n >> q; // q is always 0 in this version

        vector<int> a(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }

        // The goal is to select a subsequence with maximal alternating sum:
        // a_{b1} - a_{b2} + a_{b3} - a_{b4} + ...
        // We can use a greedy approach:
        // - Start from the left, always take a local maximum, then a local minimum, then maximum, etc.
        // - The optimal subsequence is to start at a local maximum, then alternate between local minima and maxima.

        long long ans = 0;
        // We keep track of the current sign: +1 for addition, -1 for subtraction
        int sign = 1;
        // We start at the first element
        int i = 0;
        while (i < n) {
            // Find the next local extremum (maximum if sign==1, minimum if sign==-1)
            int j = i;
            // For sign==1, find the next local maximum
            if (sign == 1) {
                // Move forward as long as the next element is greater (strictly increasing)
                while (j + 1 < n && a[j + 1] > a[j]) ++j;
            } else {
                // For sign==-1, find the next local minimum (strictly decreasing)
                while (j + 1 < n && a[j + 1] < a[j]) ++j;
            }
            // Add or subtract the found extremum
            ans += sign * a[j];
            // Flip the sign for the next extremum
            sign *= -1;
            // Continue from the next position
            i = j + 1;
        }

        // Output the answer for this test case (since q=0, only one output per test case)
        cout << ans << '\n';
    }
    return 0;
}
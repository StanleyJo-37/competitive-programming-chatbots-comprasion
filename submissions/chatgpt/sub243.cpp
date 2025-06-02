#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false); // Fast IO
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<long long> a(n), b(n);
        for (int i = 0; i < n; ++i) cin >> a[i];
        for (int i = 0; i < n; ++i) cin >> b[i];

        vector<long long> dmin(n), dmax(n);

        // For dmin: For each a[i], find the first b[j] >= a[i] (since b is sorted)
        // Use a pointer to keep track of the current position in b
        int j = 0;
        for (int i = 0; i < n; ++i) {
            // Move j until b[j] >= a[i]
            while (j < n && b[j] < a[i]) ++j;
            // Since input guarantees a solution, j < n
            dmin[i] = b[j] - a[i];
        }

        // For dmax: For each a[i], find the last b[j] that can be paired with a[i]
        // The last possible b[j] is the one before the next a[i+1] (if any) would force a larger b[j]
        // So, for i < n-1, dmax[i] = b[next_j] - a[i], where next_j = index of first b[j] >= a[i+1], minus 1
        // For i == n-1, dmax[n-1] = b[n-1] - a[n-1]
        j = 0;
        for (int i = 0; i < n; ++i) {
            // For i < n-1, find the first b[j] >= a[i+1]
            int next_j;
            if (i == n - 1) {
                next_j = n - 1;
            } else {
                // Move j until b[j] >= a[i+1]
                while (j < n && b[j] < a[i+1]) ++j;
                next_j = j - 1;
            }
            dmax[i] = b[next_j] - a[i];
        }

        // Output dmin
        for (int i = 0; i < n; ++i) {
            cout << dmin[i] << (i + 1 == n ? '\n' : ' ');
        }
        // Output dmax
        for (int i = 0; i < n; ++i) {
            cout << dmax[i] << (i + 1 == n ? '\n' : ' ');
        }
    }
    return 0;
}
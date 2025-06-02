#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false); // Fast IO
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; ++i) cin >> a[i];

        vector<int> res(n, 0); // Result: 1 if drenched, 0 otherwise

        // We'll process from top to bottom (right to left)
        int cream = 0; // Tracks how many layers from the top will be drenched
        for (int i = n - 1; i >= 0; --i) {
            // At each layer, update cream to be the max of current cream and a[i]
            cream = max(cream, a[i]);
            if (cream > 0) {
                res[i] = 1; // This layer gets drenched
                --cream;    // Cream effect decreases as we go down
            }
            // If cream == 0, this layer is not drenched
        }

        // Output the result for this test case
        for (int i = 0; i < n; ++i) {
            cout << res[i] << (i + 1 == n ? '\n' : ' ');
        }
    }
    return 0;
}
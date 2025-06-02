#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    // Fast IO
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t; // Number of test cases
    while (t--) {
        int n;
        cin >> n; // Number of daughters, necklaces, and bracelets

        vector<int> a(n), b(n);
        for (int i = 0; i < n; ++i) cin >> a[i]; // Read necklace brightness
        for (int i = 0; i < n; ++i) cin >> b[i]; // Read bracelet brightness

        // To guarantee all sums are distinct, sort both arrays.
        // Pair smallest with smallest, second smallest with second smallest, etc.
        // Since all values are distinct, their sums will also be distinct.
        sort(a.begin(), a.end());
        sort(b.begin(), b.end());

        // Output the assignment for necklaces
        for (int i = 0; i < n; ++i) {
            cout << a[i] << (i + 1 == n ? '\n' : ' ');
        }
        // Output the assignment for bracelets
        for (int i = 0; i < n; ++i) {
            cout << b[i] << (i + 1 == n ? '\n' : ' ');
        }
    }
    return 0;
}
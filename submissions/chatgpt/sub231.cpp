#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    // Read input size
    int n;
    cin >> n;
    vector<int> a(n);
    // Read the array
    for (int i = 0; i < n; ++i) cin >> a[i];

    // Sort the original array to facilitate greedy matching
    vector<int> b = a;
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    // Two pointers: i for the original (smaller) array, j for the permuted (larger) array
    int i = 0, j = 0, ans = 0;
    // Try to assign the smallest possible larger number to each position
    while (i < n && j < n) {
        // If b[j] > a[i], we can place b[j] at position i to make it larger
        if (b[j] > a[i]) {
            ++ans;
            ++i;
            ++j;
        } else {
            // Otherwise, try the next b[j]
            ++j;
        }
    }
    // Output the maximal number of positions where the new element is greater than the original
    cout << ans << endl;
    return 0;
}
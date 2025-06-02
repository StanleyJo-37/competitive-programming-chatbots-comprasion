#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n), b(m);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    for (int i = 0; i < m; ++i) {
        cin >> b[i];
    }

    // We use a greedy approach with two pointers:
    // For each required complexity a[i], find the smallest b[j] >= a[i] that hasn't been used yet.
    // If no such b[j] exists, we need to create a new problem.
    int i = 0, j = 0;
    int needed = 0;
    while (i < n && j < m) {
        if (b[j] >= a[i]) {
            // Current problem can be used for a[i]
            i++;
            j++;
        } else {
            // Current problem is too small, skip it
            j++;
        }
    }
    // The number of required problems not covered by existing ones is n - i
    needed = n - i;
    cout << needed << endl;
    return 0;
}
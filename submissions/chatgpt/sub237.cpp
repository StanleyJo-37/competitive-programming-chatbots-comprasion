#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, m;
    // Read n (number of required complexities) and m (number of prepared problems)
    cin >> n >> m;
    vector<int> a(n), b(m);
    // Read required complexities (sorted, strictly increasing)
    for (int i = 0; i < n; ++i) cin >> a[i];
    // Read prepared problem complexities (sorted, non-decreasing)
    for (int i = 0; i < m; ++i) cin >> b[i];

    int i = 0, j = 0, need = 0;
    // Use two pointers to match each required complexity a[i] with a prepared problem b[j]
    while (i < n) {
        // Move j forward until we find a prepared problem with complexity >= a[i]
        while (j < m && b[j] < a[i]) ++j;
        if (j < m) {
            // Found a prepared problem that can be simplified to a[i]
            ++j;
        } else {
            // No prepared problem can be used for a[i], so we need to create a new one
            ++need;
        }
        ++i;
    }
    // Output the minimum number of new problems needed
    cout << need << endl;
    return 0;
}
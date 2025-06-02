#include <iostream>
#include <vector>
using namespace std;

int main() {
    // Read input values
    long long n, m, k;
    cin >> n >> m >> k;
    vector<long long> p(m);
    for (int i = 0; i < m; ++i) {
        cin >> p[i];
    }

    // cnt: number of special items already removed (so far)
    long long cnt = 0;
    int ans = 0; // number of operations
    int i = 0; // pointer to current special item

    // Process all special items
    while (i < m) {
        // Calculate the current page for the first remaining special item
        // After cnt removals, the position of p[i] is p[i] - cnt
        // The page number is ((p[i] - cnt - 1) / k)
        long long page = (p[i] - cnt - 1) / k;

        // Find the last special item that is still on the same page
        int j = i;
        // While next special item is on the same page, include it in this operation
        while (j < m && (p[j] - cnt - 1) / k == page) {
            ++j;
        }

        // All special items from i to j-1 are removed in this operation
        cnt += (j - i);
        ++ans;
        i = j; // Move to the next special item
    }

    // Output the total number of operations
    cout << ans << endl;
    return 0;
}
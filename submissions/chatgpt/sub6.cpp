#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    // Fast IO for large input/output
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n; // Number of shops

    vector<int> prices(n);
    for (int i = 0; i < n; ++i) {
        cin >> prices[i]; // Prices in each shop
    }

    // Sort prices to enable binary search
    sort(prices.begin(), prices.end());

    int q;
    cin >> q; // Number of days

    while (q--) {
        int m;
        cin >> m; // Money Vasiliy can spend on this day

        // upper_bound returns iterator to first element > m
        // So, number of shops where price <= m is (iterator - prices.begin())
        int count = upper_bound(prices.begin(), prices.end(), m) - prices.begin();
        cout << count << '\n';
    }

    return 0;
}
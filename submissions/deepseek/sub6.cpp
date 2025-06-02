#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> prices(n);
    for (int i = 0; i < n; ++i) {
        cin >> prices[i];
    }
    
    // Sort the prices to enable binary search
    sort(prices.begin(), prices.end());
    
    int q;
    cin >> q;
    while (q--) {
        int m;
        cin >> m;
        // Use upper_bound to find the first price > m, then the count is the difference
        auto it = upper_bound(prices.begin(), prices.end(), m);
        cout << (it - prices.begin()) << endl;
    }
    
    return 0;
}
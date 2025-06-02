#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> x(n), y(n);
        for (int i = 0; i < n; ++i) {
            cin >> x[i] >> y[i];
        }

        // The optimal positions for minimal Manhattan distance are the medians of x and y coordinates.
        // The number of optimal positions is the product of the count of median x and y ranges.
        sort(x.begin(), x.end());
        sort(y.begin(), y.end());

        long long x_count, y_count;
        if (n % 2 == 1) {
            // Odd number of houses: single median point.
            x_count = 1;
            y_count = 1;
        } else {
            // Even number of houses: range between two middle points.
            x_count = x[n/2] - x[n/2 - 1] + 1;
            y_count = y[n/2] - y[n/2 - 1] + 1;
        }

        cout << x_count * y_count << '\n';
    }

    return 0;
}
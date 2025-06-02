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
        vector<long long> xs(n), ys(n);
        for (int i = 0; i < n; ++i) {
            cin >> xs[i] >> ys[i];
        }

        // Sort x and y coordinates to find medians
        sort(xs.begin(), xs.end());
        sort(ys.begin(), ys.end());

        // For Manhattan distance, the sum is minimized at the median(s)
        // If n is odd, only one median, so only one optimal point
        // If n is even, any point between the two middle values (inclusive) is optimal
        // So, number of optimal x = xs[n/2] - xs[n/2-1] + 1
        // Same for y

        long long count = 1; // Default for n odd
        if (n % 2 == 0) {
            long long x_choices = xs[n/2] - xs[n/2-1] + 1;
            long long y_choices = ys[n/2] - ys[n/2-1] + 1;
            count = x_choices * y_choices;
        }
        cout << count << '\n';
    }
    return 0;
}
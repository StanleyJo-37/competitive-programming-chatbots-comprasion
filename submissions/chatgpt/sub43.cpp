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
        vector<long long> a(n);
        for (int i = 0; i < n; ++i) cin >> a[i];

        // Sort the array to facilitate greedy partitioning
        sort(a.begin(), a.end());

        // We want to maximize Sum(RED) with minimal Count(RED)
        // and minimize Sum(BLUE) with maximal Count(BLUE)
        // Try all possible splits: RED = k largest, BLUE = k+1 smallest
        // for k = 1 to n-2 (since Count(RED) < Count(BLUE) and both >=1)
        // Precompute prefix sums for efficiency
        vector<long long> prefix(n+1, 0); // prefix[i] = sum of first i elements
        for (int i = 0; i < n; ++i) prefix[i+1] = prefix[i] + a[i];

        bool found = false;
        // k: number of RED elements (from 1 to n-2)
        // BLUE: k+1 smallest elements
        for (int k = 1; k < n-1; ++k) {
            // RED: k largest elements
            long long sum_red = prefix[n] - prefix[n-k];
            // BLUE: k+1 smallest elements
            long long sum_blue = prefix[k+1];
            // Count(RED) = k, Count(BLUE) = k+1, so Count(RED) < Count(BLUE)
            if (sum_red > sum_blue) {
                found = true;
                break;
            }
        }
        cout << (found ? "YES" : "NO") << '\n';
    }
    return 0;
}
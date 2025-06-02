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
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }

        // The idea is to traverse the array and for each contiguous segment of the same sign,
        // pick the maximum element from that segment. This ensures the subsequence alternates in sign
        // and has the maximum possible sum for the maximum possible length.
        long long sum = 0;
        int i = 0;
        while (i < n) {
            // Start of a new segment
            long long curr = a[i];
            int sign = (a[i] > 0) ? 1 : -1;
            // Traverse while the sign is the same
            int j = i + 1;
            while (j < n && ((a[j] > 0) == (curr > 0))) {
                // Keep the maximum in this segment
                curr = max(curr, a[j]);
                ++j;
            }
            // Add the maximum of this segment to the sum
            sum += curr;
            // Move to the next segment
            i = j;
        }
        cout << sum << '\n';
    }
    return 0;
}
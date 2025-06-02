#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    // The maximum subarray sum can be improved by swapping the largest elements into the subarray.
    // We need to consider all possible subarrays and for each, swap the largest remaining elements into it.
    // Since k is small (<=10), we can use a greedy approach to swap the largest elements available.

    int max_sum = -1e9; // Initialize with a very small value.

    // Iterate over all possible subarrays [l, r]
    for (int l = 0; l < n; ++l) {
        for (int r = l; r < n; ++r) {
            vector<int> inside, outside;
            int current_sum = 0;
            // Separate elements inside and outside the subarray [l, r]
            for (int i = 0; i < n; ++i) {
                if (i >= l && i <= r) {
                    inside.push_back(a[i]);
                    current_sum += a[i];
                } else {
                    outside.push_back(a[i]);
                }
            }
            // Sort inside in ascending order to replace smallest elements first.
            sort(inside.begin(), inside.end());
            // Sort outside in descending order to pick largest elements first.
            sort(outside.rbegin(), outside.rend());

            // Try swapping up to k times, but no more than min(k, inside.size(), outside.size())
            int swaps_possible = min(k, (int)min(inside.size(), outside.size()));
            for (int swap = 0; swap < swaps_possible; ++swap) {
                // If the largest outside element is greater than the smallest inside element, swap them.
                if (outside[swap] > inside[swap]) {
                    current_sum += outside[swap] - inside[swap];
                } else {
                    break; // No benefit in further swaps.
                }
            }
            max_sum = max(max_sum, current_sum);
        }
    }

    cout << max_sum << endl;
    return 0;
}
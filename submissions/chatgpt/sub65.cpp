#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    // Read input values
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for(int i=0; i<n; ++i) cin >> a[i];

    int answer = -1000000000; // Initialize answer to a very small value

    // Try all possible subarrays [l, r]
    for(int l=0; l<n; ++l) {
        for(int r=l; r<n; ++r) {
            // Extract the subarray [l, r]
            vector<int> sub;
            for(int i=l; i<=r; ++i) sub.push_back(a[i]);
            // Extract the elements outside the subarray
            vector<int> out;
            for(int i=0; i<l; ++i) out.push_back(a[i]);
            for(int i=r+1; i<n; ++i) out.push_back(a[i]);

            // Sort subarray in ascending order (to find smallest elements to swap out)
            sort(sub.begin(), sub.end());
            // Sort outside elements in descending order (to find largest elements to swap in)
            sort(out.rbegin(), out.rend());

            int sum = 0;
            for(int x : sub) sum += x; // Initial sum of subarray

            int max_sum = sum; // Track the best sum for this subarray

            // Try swapping up to k times
            int max_swaps = min({k, (int)sub.size(), (int)out.size()});
            int cur_sum = sum;
            for(int t=1; t<=max_swaps; ++t) {
                // Remove the smallest in sub, add the largest from out
                cur_sum -= sub[t-1];
                cur_sum += out[t-1];
                if(cur_sum > max_sum) max_sum = cur_sum;
            }

            // Update the global answer if this is the best so far
            if(max_sum > answer) answer = max_sum;
        }
    }

    cout << answer << endl;
    return 0;
}
#include <bits/stdc++.h>
using namespace std;

// Function to compute the largest friend group size in the array
int largestFriendGroup(vector<long long>& a) {
    int n = a.size();
    if (n <= 1) return n;
    
    // The key observation is that for a subarray to be a friend group,
    // the differences between consecutive elements must be divisible by m >= 2.
    // So, the differences must have a common divisor >= 2.
    // We can find the longest contiguous subarray where all adjacent differences
    // share a common divisor >= 2.
    
    // Compute differences between consecutive elements
    vector<long long> diffs;
    for (int i = 1; i < n; ++i) {
        diffs.push_back(abs(a[i] - a[i-1]));
    }
    
    int max_len = 1;
    int current_len = 1;
    long long current_gcd = 0;
    
    // We use a sliding window approach to find the longest subarray of differences
    // where the GCD is >= 2. The length of the friend group is current_len + 1.
    for (int i = 0; i < diffs.size(); ++i) {
        current_gcd = __gcd(current_gcd, diffs[i]);
        if (current_gcd >= 2) {
            current_len++;
            max_len = max(max_len, current_len);
        } else {
            // Reset the window
            current_gcd = 0;
            current_len = 1;
            // We need to recompute the GCD from the current position
            // by going backward until GCD becomes >= 2 or we reach the start.
            int j = i;
            current_gcd = diffs[j];
            while (j >= 0 && current_gcd >= 2) {
                current_len = i - j + 1;
                max_len = max(max_len, current_len);
                j--;
                if (j >= 0) {
                    current_gcd = __gcd(current_gcd, diffs[j]);
                }
            }
            if (current_gcd < 2) {
                current_len = 1;
                current_gcd = 0;
            }
        }
    }
    
    return max_len;
}

int main() {
    ios_base::sync_with_stdio(false);
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
        cout << largestFriendGroup(a) << '\n';
    }
    
    return 0;
}
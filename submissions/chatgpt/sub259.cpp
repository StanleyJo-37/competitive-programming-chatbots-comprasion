#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Function to compute the minimum number of operations to sort the array
int min_operations(const vector<int>& a) {
    int n = a.size();
    // dp[i]: length of the longest non-decreasing subsequence ending at position i
    vector<int> dp;
    // We use lower_bound to maintain the smallest possible last element for each length
    for (int i = 0; i < n; ++i) {
        // For non-decreasing, use upper_bound to allow equal elements
        auto it = upper_bound(dp.begin(), dp.end(), a[i]);
        if (it == dp.end()) {
            dp.push_back(a[i]);
        } else {
            *it = a[i];
        }
    }
    // The minimum number of operations is n - length of the longest non-decreasing subsequence
    return n - dp.size();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    // For each test case
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }
        // Output the answer for this test case
        cout << min_operations(a) << '\n';
    }
    return 0;
}
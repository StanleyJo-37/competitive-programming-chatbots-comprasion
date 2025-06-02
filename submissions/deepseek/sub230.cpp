#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    
    long long res = 0;
    int left = 0;
    for (int right = 0; right < n; ++right) {
        // The condition for the subarray [left..right] to be good is a[i] >= (i - left + 1) for all i in [left..right]
        // Which can be rewritten as a[i] - (i - left + 1) >= 0
        // Or a[i] - i + left - 1 >= 0
        // Or left >= (i + 1 - a[i])
        // So for each right, we need to find the smallest left such that left >= (i + 1 - a[i]) for all i in [left..right]
        // We can maintain the maximum of (i + 1 - a[i]) in the current window [left..right]
        // left must be >= this maximum value
        
        // The current element's constraint is (right + 1 - a[right])
        // left must be >= max of all (i + 1 - a[i]) for i in [left..right]
        // So we can track the maximum constraint in the current window and adjust left accordingly
        
        // The new constraint for the current right is (right + 1 - a[right])
        // left must be >= max of previous max constraint and new constraint
        // So left = max(left, (right + 1 - a[right]))
        
        left = max(left, right + 1 - a[right]);
        // The number of valid subarrays ending at right is (right - left + 1)
        res += (right - left + 1);
    }
    cout << res << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    
    return 0;
}
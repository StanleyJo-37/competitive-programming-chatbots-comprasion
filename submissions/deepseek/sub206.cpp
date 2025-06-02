#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < n; ++i) cin >> b[i];
    
    // We need to find the minimal maximum between:
    // 1. The maximum courier time among selected deliveries.
    // 2. The sum of self-pickup times for the rest.
    // To minimize this, we can sort the dishes based on a[i] and b[i],
    // then find the optimal split where some are delivered and others are picked up.
    
    vector<pair<int, int>> dishes;
    for (int i = 0; i < n; ++i) {
        dishes.emplace_back(a[i], b[i]);
    }
    // Sort dishes in descending order of a[i] to consider the largest a[i] first.
    sort(dishes.begin(), dishes.end(), greater<pair<int, int>>());
    
    long long sum_b = 0;
    long long res = 1e18; // Initialize with a large value.
    
    // The optimal answer is the minimal between:
    // 1. The maximum a[i] among the first k dishes (sorted in descending a[i]).
    // 2. The sum of b[i] of the remaining (n - k) dishes.
    // We iterate to find the point where max(a[k-1], sum_b_remaining) is minimized.
    for (int i = 0; i <= n; ++i) {
        if (i > 0) {
            // The current a[i-1] is the maximum among the first i delivered dishes.
            long long current_max = max((long long)dishes[i-1].first, sum_b);
            res = min(res, current_max);
        }
        if (i < n) {
            sum_b += dishes[i].second;
        }
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
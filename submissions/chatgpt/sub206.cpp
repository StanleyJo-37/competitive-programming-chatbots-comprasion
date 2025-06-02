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
        vector<long long> a(n), b(n);
        for (int i = 0; i < n; ++i) cin >> a[i]; // Delivery times
        for (int i = 0; i < n; ++i) cin >> b[i]; // Pickup times

        // To minimize the time, we need to decide for each dish whether to pick up or use delivery.
        // If we use delivery for some dishes, their times are in parallel (max of their a_i).
        // If we pick up some dishes, their times are summed (sum of their b_i).
        // The total time is max(sum of b_i for picked up, max a_i for delivered).
        // We need to partition the dishes into two groups to minimize max(sum_b, max_a).

        // To do this efficiently, sort the dishes by a_i (delivery time) in increasing order.
        // We'll try all possible splits: first k dishes are picked up, rest are delivered.
        // For each split, sum b_i for picked up, and max a_i for delivered (which is a_i[n-1]..a_i[k]).
        // The answer is the minimum over all splits.

        // Store both a and b together for sorting
        vector<pair<long long, long long>> dishes(n);
        for (int i = 0; i < n; ++i) dishes[i] = {a[i], b[i]};
        sort(dishes.begin(), dishes.end()); // Sort by a_i

        // Precompute prefix sums of b_i
        vector<long long> prefix_b(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            prefix_b[i + 1] = prefix_b[i] + dishes[i].second;
        }

        long long ans = 1e18;
        // Try all splits: pick up first k dishes, deliver the rest
        for (int k = 0; k <= n; ++k) {
            // sum_b = sum of b_i for first k dishes (picked up)
            long long sum_b = prefix_b[k];
            // max_a = max a_i for delivered dishes (from k to n-1)
            long long max_a = 0;
            if (k < n) max_a = dishes[n - 1].first;
            if (k < n) max_a = dishes[k].first; // Since sorted, max a_i among delivered is a_i[k..n-1], which is a_i[n-1]
            // But since we are picking up first k, delivered are k..n-1, so max a_i is a_i[n-1]
            if (k < n) max_a = dishes[n - 1].first;
            else max_a = 0; // If all picked up, no delivery
            // The time is max(sum_b, max_a)
            ans = min(ans, max(sum_b, max_a));
        }

        // The above loop can be optimized: since max_a is always a[n-1] for k < n, and 0 for k == n
        // So, we can do:
        // For k = 0 to n-1: sum_b = prefix_b[k], max_a = a[n-1]
        // For k = n: sum_b = prefix_b[n], max_a = 0
        // But let's do the correct way:
        // For k = 0 to n: sum_b = prefix_b[k], max_a = (k < n ? a[k..n-1].max : 0)
        // Since sorted, a[k..n-1].max = a[n-1]
        // But if we deliver only one dish, it's a[k]
        // Let's do it with a pointer:
        long long res = 1e18;
        for (int k = 0; k <= n; ++k) {
            long long sum_b = prefix_b[k];
            long long max_a = 0;
            if (k < n) max_a = dishes[k].first;
            res = min(res, max(sum_b, max_a));
        }
        cout << res << '\n';
    }
    return 0;
}
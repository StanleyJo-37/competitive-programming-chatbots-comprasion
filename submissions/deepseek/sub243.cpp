#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < n; ++i) cin >> b[i];
    
    vector<int> d_min(n), d_max(n);
    
    // For d_min[i], it's b[j] - a[i] where j is the smallest index such that b[j] >= a[i]
    // We can use binary search to find the smallest j where b[j] >= a[i]
    for (int i = 0; i < n; ++i) {
        auto it = lower_bound(b.begin(), b.end(), a[i]);
        d_min[i] = *it - a[i];
    }
    
    // For d_max[i], it's b[j] - a[i] where j is the largest possible index (n-1) initially,
    // but j can be smaller if a[i] > b[j] for some j. However, since b is sorted and a is sorted,
    // the maximum d_i is b[j] - a[i] where j is the largest possible such that b[j] >= a[i] or j is as large as possible.
    // But since b is sorted and a is sorted, the maximum d_i for a[i] is b[k] - a[i], where k is the largest possible index
    // such that b[k] can be paired with a[i]. This is the largest j >= i in the original pairing.
    // We can use a two-pointer approach to find for each i, the largest j such that b[j] >= a[i] and j >= i.
    int j = 0;
    for (int i = 0; i < n; ++i) {
        while (j < n && b[j] < a[i]) ++j;
        // The maximum j for a[i] is the largest j >= i where b[j] >= a[i], but since b is sorted, it's the last possible j.
        // However, the actual maximum d_i is b[k] - a[i], where k is the largest possible index in the original pairing.
        // To find this, we can track the last j where b[j] >= a[i], but since a is sorted, the maximum j for a[i] is the same or larger than for a[i-1].
    }
    j = n - 1;
    for (int i = n - 1; i >= 0; --i) {
        // The maximum j for a[i] is the largest j >= i where b[j] >= a[i]
        // Since a is non-decreasing and b is non-decreasing, we can find the largest j for each i by moving j left until b[j] >= a[i]
        while (j >= 0 && b[j] >= a[i]) --j;
        d_max[i] = b[j + 1] - a[i];
    }
    
    for (int i = 0; i < n; ++i) cout << d_min[i] << " ";
    cout << "\n";
    for (int i = 0; i < n; ++i) cout << d_max[i] << " ";
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}
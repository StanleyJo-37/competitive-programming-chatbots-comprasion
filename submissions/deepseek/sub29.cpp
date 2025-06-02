#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n, m, k;
    cin >> n >> m >> k;
    long long x, s;
    cin >> x >> s;
    
    vector<long long> a(m), b(m);
    for (int i = 0; i < m; ++i) cin >> a[i];
    for (int i = 0; i < m; ++i) cin >> b[i];
    
    vector<long long> c(k), d(k);
    for (int i = 0; i < k; ++i) cin >> c[i];
    for (int i = 0; i < k; ++i) cin >> d[i];
    
    long long min_time = n * x; // Base case: no spells used
    
    // Pre-process first type spells: find the minimal a_i where b_i <= cost_left
    // We can process first type spells and keep track of the minimal a_i for any budget
    
    // Case 1: Use only second type spell
    // Find the largest c_i where d_i <= s
    auto it = upper_bound(d.begin(), d.end(), s);
    if (it != d.begin()) {
        int idx = prev(it) - d.begin();
        long long potions = c[idx];
        long long remaining = max(0LL, n - potions);
        min_time = min(min_time, remaining * x);
    }
    
    // Case 2: Use only first type spell
    // Find the minimal a_i where b_i <= s
    for (int i = 0; i < m; ++i) {
        if (b[i] <= s) {
            long long time = n * a[i];
            min_time = min(min_time, time);
        }
    }
    
    // Case 3: Use both types of spells
    // For each first type spell (a_i, b_i), find the best second type spell (c_j, d_j) where b_i + d_j <= s
    // Since c and d are sorted, we can binary search for the largest c_j where d_j <= s - b_i
    
    // Pre-process first type spells to have the minimal a_i for any prefix budget
    vector<pair<long long, long long>> first_spells;
    for (int i = 0; i < m; ++i) {
        first_spells.emplace_back(b[i], a[i]);
    }
    sort(first_spells.begin(), first_spells.end());
    
    // Create prefix minima for a_i
    vector<long long> prefix_min_a(m);
    vector<long long> prefix_b(m);
    if (!first_spells.empty()) {
        prefix_min_a[0] = first_spells[0].second;
        prefix_b[0] = first_spells[0].first;
        for (int i = 1; i < m; ++i) {
            prefix_min_a[i] = min(prefix_min_a[i-1], first_spells[i].second);
            prefix_b[i] = first_spells[i].first;
        }
    }
    
    for (int i = 0; i < m; ++i) {
        if (b[i] > s) continue;
        long long cost_left = s - b[i];
        auto it_d = upper_bound(d.begin(), d.end(), cost_left);
        if (it_d != d.begin()) {
            int idx = prev(it_d) - d.begin();
            long long potions = c[idx];
            long long remaining = max(0LL, n - potions);
            min_time = min(min_time, remaining * a[i]);
        } else {
            // Can't use any second spell, but first spell is used
            min_time = min(min_time, n * a[i]);
        }
    }
    
    // Also check the best first spell for any remaining budget after choosing second spell
    for (int j = 0; j < k; ++j) {
        if (d[j] > s) continue;
        long long cost_left = s - d[j];
        auto it_b = upper_bound(prefix_b.begin(), prefix_b.end(), cost_left);
        if (it_b != prefix_b.begin()) {
            int idx = prev(it_b) - prefix_b.begin();
            long long best_a = prefix_min_a[idx];
            long long potions = c[j];
            long long remaining = max(0LL, n - potions);
            min_time = min(min_time, remaining * best_a);
        } else {
            // Can't use any first spell, but second spell is used
            long long potions = c[j];
            long long remaining = max(0LL, n - potions);
            min_time = min(min_time, remaining * x);
        }
    }
    
    cout << min_time << '\n';
    return 0;
}
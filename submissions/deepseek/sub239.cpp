#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(k), t(k);
    for (int i = 0; i < k; ++i) cin >> a[i];
    for (int i = 0; i < k; ++i) cin >> t[i];
    
    vector<pair<int, int>> ac;
    for (int i = 0; i < k; ++i) {
        ac.emplace_back(a[i], t[i]);
    }
    sort(ac.begin(), ac.end()); // Sort ACs by position for processing
    
    vector<int> left(n + 2, INT_MAX); // left[i] is min temp from left up to i
    vector<int> right(n + 2, INT_MAX); // right[i] is min temp from right up to i
    
    // Process left to right
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    for (auto &[pos, temp] : ac) {
        pq.emplace(temp, pos);
    }
    
    while (!pq.empty()) {
        auto [current_temp, pos] = pq.top();
        pq.pop();
        if (left[pos] != INT_MAX) continue; // already processed
        left[pos] = current_temp;
        if (pos - 1 >= 1 && left[pos - 1] == INT_MAX) {
            pq.emplace(current_temp + 1, pos - 1);
        }
        if (pos + 1 <= n && left[pos + 1] == INT_MAX) {
            pq.emplace(current_temp + 1, pos + 1);
        }
    }
    
    // Process right to left
    for (auto &[pos, temp] : ac) {
        pq.emplace(temp, pos);
    }
    
    while (!pq.empty()) {
        auto [current_temp, pos] = pq.top();
        pq.pop();
        if (right[pos] != INT_MAX) continue; // already processed
        right[pos] = current_temp;
        if (pos - 1 >= 1 && right[pos - 1] == INT_MAX) {
            pq.emplace(current_temp + 1, pos - 1);
        }
        if (pos + 1 <= n && right[pos + 1] == INT_MAX) {
            pq.emplace(current_temp + 1, pos + 1);
        }
    }
    
    for (int i = 1; i <= n; ++i) {
        cout << min(left[i], right[i]) << " ";
    }
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int q;
    cin >> q;
    while (q--) {
        solve();
    }
    
    return 0;
}
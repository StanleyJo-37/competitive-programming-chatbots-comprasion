#include <bits/stdc++.h>
using namespace std;

void solve() {
    int t;
    cin >> t;
    while (t--) {
        int n, a, b;
        cin >> n >> a >> b;
        vector<int> x(n);
        for (int i = 0; i < n; ++i) {
            cin >> x[i];
        }
        
        long long total_cost = 0;
        int current_pos = 0; // initial capital at 0
        
        for (int i = 0; i < n; ++i) {
            // Cost to conquer the next kingdom from current capital
            long long conquer_cost = 1LL * b * (x[i] - current_pos);
            // Cost to move capital to x[i] and then conquer remaining from there
            // Compare if moving is better than staying
            if (i < n - 1) {
                long long move_cost = 1LL * a * (x[i] - current_pos);
                long long future_savings = 1LL * b * (x[i] - current_pos) * (n - 1 - i);
                if (move_cost < future_savings) {
                    total_cost += move_cost;
                    current_pos = x[i];
                }
            }
            total_cost += conquer_cost;
        }
        cout << total_cost << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
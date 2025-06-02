#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n), b(n), d(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < n; ++i) cin >> b[i];
    for (int i = 0; i < n; ++i) cin >> d[i];

    // Build a map from value to index in permutation a and b
    vector<int> pos_a(n + 1), pos_b(n + 1);
    for (int i = 0; i < n; ++i) {
        pos_a[a[i]] = i;
        pos_b[b[i]] = i;
    }

    vector<bool> visited(n + 1, false);
    long long result = 1;

    for (int i = 1; i <= n; ++i) {
        if (!visited[i]) {
            // Start traversing the cycle
            int current = i;
            int cycle_length = 0;
            bool has_fixed = false;
            vector<int> cycle_values;

            while (!visited[current]) {
                visited[current] = true;
                cycle_values.push_back(current);
                int a_pos = pos_a[current];
                current = b[a_pos];
                cycle_length++;
            }

            // Check if any element in the cycle is fixed (d_i != 0)
            for (int val : cycle_values) {
                int idx = pos_a[val];
                if (d[idx] != 0) {
                    has_fixed = true;
                    break;
                }
            }

            // If cycle length > 1 and no fixed elements, multiply by 2
            if (cycle_length > 1 && !has_fixed) {
                result = (result * 2) % MOD;
            }
        }
    }

    cout << result << '\n';
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
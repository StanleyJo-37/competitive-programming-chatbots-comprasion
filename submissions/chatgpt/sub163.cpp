#include <bits/stdc++.h>
using namespace std;

// We use 20 bits, so the value range is [0, 2^20)
const int MAXV = 1 << 20;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    // cnt[v] = number of times value v appears in the array
    vector<int> cnt(MAXV, 0);

    // Read initial array and build cnt
    for (int i = 0; i < n; ++i) {
        int a;
        cin >> a;
        cnt[a]++;
    }

    // For each query, process as described
    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            // AND operation: replace all a_i in [l, r] with a_i & x
            int l, r, x;
            cin >> l >> r >> x;
            // To avoid double counting, we process all values in [l, r]
            // and move their counts to (v & x)
            vector<pair<int, int>> changes; // (from, to)
            for (int v = l; v <= r; ++v) {
                if (cnt[v] > 0) {
                    int to = v & x;
                    if (to != v) {
                        changes.emplace_back(v, to);
                    }
                }
            }
            // Apply changes
            for (auto [from, to] : changes) {
                cnt[to] += cnt[from];
                cnt[from] = 0;
            }
        } else if (t == 2) {
            // OR operation: replace all a_i in [l, r] with a_i | x
            int l, r, x;
            cin >> l >> r >> x;
            vector<pair<int, int>> changes;
            for (int v = l; v <= r; ++v) {
                if (cnt[v] > 0) {
                    int to = v | x;
                    if (to != v) {
                        changes.emplace_back(v, to);
                    }
                }
            }
            for (auto [from, to] : changes) {
                cnt[to] += cnt[from];
                cnt[from] = 0;
            }
        } else if (t == 3) {
            // XOR operation: replace all a_i in [l, r] with a_i ^ x
            int l, r, x;
            cin >> l >> r >> x;
            // To avoid double counting, process each pair (v, v^x) only once
            // For v in [l, r], if v^x > v and v^x in [l, r], swap their counts
            vector<int> to_process;
            for (int v = l; v <= r; ++v) {
                if (cnt[v] > 0) to_process.push_back(v);
            }
            set<int> processed;
            for (int v : to_process) {
                int u = v ^ x;
                if (u < l || u > r) continue;
                if (processed.count(v) || processed.count(u)) continue;
                if (v == u) continue;
                swap(cnt[v], cnt[u]);
                processed.insert(v);
                processed.insert(u);
            }
        } else if (t == 4) {
            // Output the number of distinct a_i in [l, r]
            int l, r;
            cin >> l >> r;
            int res = 0;
            for (int v = l; v <= r; ++v) {
                if (cnt[v] > 0) ++res;
            }
            cout << res << '\n';
        }
    }
    return 0;
}
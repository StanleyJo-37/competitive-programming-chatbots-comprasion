#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> parent(n + 1);
    for (int i = 2; i <= n; ++i) {
        cin >> parent[i];
    }

    vector<long long> s(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> s[i];
    }

    vector<vector<int>> children(n + 1);
    for (int i = 2; i <= n; ++i) {
        children[parent[i]].push_back(i);
    }

    bool possible = true;
    vector<long long> a(n + 1, 0);

    // The root's a is s[1]
    a[1] = s[1];

    for (int v = 2; v <= n; ++v) {
        if (s[v] == -1) {
            // Even depth, need to compute based on children or parent
            continue;
        } else {
            // Odd depth, compute a[v] = s[v] - s[parent[v]]
            int p = parent[v];
            if (s[p] == -1) {
                // Parent is even depth, which is invalid since s[parent] is erased
                possible = false;
                break;
            }
            a[v] = s[v] - s[p];
            if (a[v] < 0) {
                possible = false;
                break;
            }
        }
    }

    if (!possible) {
        cout << -1 << '\n';
        return 0;
    }

    // Now handle even depth nodes (s[v] = -1)
    for (int v = 1; v <= n; ++v) {
        if (s[v] != -1) continue; // Skip odd depth nodes

        // For even depth nodes, s[v] is erased. We need to find the minimal a[v] >= 0.
        // s[v] = s[parent] + a[v]
        // But s[v] must be <= minimal s among children (if any), otherwise it's invalid.
        // If no children, a[v] can be 0 (minimal possible).

        if (children[v].empty()) {
            a[v] = 0;
            s[v] = s[parent[v]] + a[v];
        } else {
            long long min_child_s = LLONG_MAX;
            for (int child : children[v]) {
                if (s[child] == -1) continue; // Skip even depth children
                min_child_s = min(min_child_s, s[child]);
            }
            if (min_child_s == LLONG_MAX) {
                // All children are even depth, which is invalid since s[v] is erased
                possible = false;
                break;
            }
            s[v] = min_child_s;
            a[v] = s[v] - s[parent[v]];
            if (a[v] < 0) {
                possible = false;
                break;
            }
        }
    }

    if (!possible) {
        cout << -1 << '\n';
        return 0;
    }

    long long total_sum = 0;
    for (int v = 1; v <= n; ++v) {
        total_sum += a[v];
    }

    cout << total_sum << '\n';
    return 0;
}
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, l, r;
    cin >> n >> l >> r;
    vector<int> a(n), p(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    for (int i = 0; i < n; ++i) {
        cin >> p[i];
    }

    // We need to find b_i = c_i + a_i, where c_i is derived from p_i.
    // Since p_i is the rank of c_i in the sorted list of c's, we can model c_i as follows:
    // c_i = k_i + offset, where k_i is based on p_i (e.g., sorted order).
    // To ensure all c_i are distinct, we can assign c_i in the order of p_i's ranks.
    vector<pair<int, int>> pairs(n);
    for (int i = 0; i < n; ++i) {
        pairs[i] = {p[i], i}; // Store original index along with p_i
    }
    sort(pairs.begin(), pairs.end()); // Sort by p_i to process in order

    vector<int> c(n);
    int prev_c = INT_MIN;
    bool possible = true;

    // Assign c_i in the order of p_i (1..n). To ensure distinctness, c_i must be strictly increasing.
    // The minimal c_i is (p_i - n), and we can adjust to make them distinct.
    for (int i = 0; i < n; ++i) {
        int idx = pairs[i].second;
        int desired_rank = pairs[i].first;
        // To ensure distinctness and correct rank, c_i must be at least (desired_rank - n + i)
        // But since p_i is 1..n, we can set c_i = desired_rank + offset (e.g., i)
        c[idx] = desired_rank + i - n; // This ensures c_i are distinct and in correct order
    }

    // Now, compute b_i = c_i + a_i and check if all b_i are within [l, r]
    vector<int> b(n);
    for (int i = 0; i < n; ++i) {
        b[i] = c[i] + a[i];
        if (b[i] < l || b[i] > r) {
            possible = false;
            break;
        }
    }

    // Additionally, we must ensure that the compressed sequence of c matches the given p.
    // To verify, we can create pairs of (c_i, original index), sort by c_i, and check if the ranks match p.
    if (possible) {
        vector<pair<int, int>> c_with_index(n);
        for (int i = 0; i < n; ++i) {
            c_with_index[i] = {c[i], i};
        }
        sort(c_with_index.begin(), c_with_index.end());
        vector<int> new_p(n);
        for (int rank = 0; rank < n; ++rank) {
            int original_idx = c_with_index[rank].second;
            new_p[original_idx] = rank + 1;
        }
        for (int i = 0; i < n; ++i) {
            if (new_p[i] != p[i]) {
                possible = false;
                break;
            }
        }
    }

    if (!possible) {
        cout << "-1\n";
    } else {
        for (int i = 0; i < n; ++i) {
            cout << b[i] << " ";
        }
        cout << "\n";
    }

    return 0;
}
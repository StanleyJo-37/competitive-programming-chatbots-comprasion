#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q;
    cin >> N >> Q;
    vector<int> roots(N);
    for (int i = 0; i < N; ++i) {
        cin >> roots[i];
    }
    sort(roots.begin(), roots.end()); // Sort roots for binary search

    while (Q--) {
        int x;
        cin >> x;
        // Check if x is a root (P(x) = 0)
        auto it = lower_bound(roots.begin(), roots.end(), x);
        if (it != roots.end() && *it == x) {
            cout << "0\n";
            continue;
        }
        // Number of roots > x determines the sign: if even, positive; else negative
        int cnt = roots.end() - it;
        if (cnt % 2 == 0) {
            cout << "POSITIVE\n";
        } else {
            cout << "NEGATIVE\n";
        }
    }

    return 0;
}
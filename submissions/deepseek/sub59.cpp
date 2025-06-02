#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> p(n);
        for (int i = 0; i < n; ++i) {
            cin >> p[i];
        }

        // The key observation is that the minimum number of operations required
        // is equal to the maximum number of overlapping "chains" in the permutation.
        // A chain is a sequence of numbers where each subsequent number is the next in the sorted order.
        // For example, in [1,5,4,2,3], the chains are:
        // 1,2,3 (length 3)
        // 5 (length 1)
        // 4 (length 1)
        // The answer is the number of chains, minus the length of the longest chain.
        // But a more efficient way is to track the positions of each number and count
        // how many numbers are in the correct order (i.e., x appears before x+1 in the permutation).

        vector<int> pos(n + 1);
        for (int i = 0; i < n; ++i) {
            pos[p[i]] = i;
        }

        int res = 0;
        for (int i = 2; i <= n; ++i) {
            if (pos[i] < pos[i - 1]) {
                res++;
            }
        }

        cout << res << '\n';
    }

    return 0;
}
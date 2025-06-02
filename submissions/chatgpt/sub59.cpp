#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false); // Fast IO
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

        // The key observation:
        // The operation allows us to "move" any two elements to the ends in sorted order.
        // The minimum number of operations needed is:
        //   (n - length of the longest sorted prefix) / 2
        // But actually, the optimal way is to find the length of the longest increasing consecutive subsequence,
        // because those elements are already in order and do not need to be moved.
        // The rest can be paired up and moved in one operation per pair.

        // Find the length of the longest increasing consecutive subsequence
        // For permutation, we can use a map from value to position to find consecutive increasing sequences.
        // But since values are 1..n, we can use an array.

        vector<int> pos(n + 1); // pos[value] = index in p
        for (int i = 0; i < n; ++i) {
            pos[p[i]] = i;
        }

        int max_len = 1, cur_len = 1;
        // For each value from 2 to n, check if its position is after the previous value's position
        for (int i = 2; i <= n; ++i) {
            if (pos[i] > pos[i - 1]) {
                ++cur_len;
            } else {
                cur_len = 1;
            }
            if (cur_len > max_len) max_len = cur_len;
        }

        // The minimum number of operations is (n - max_len + 1) / 2
        // Because in each operation, we can "fix" two elements (move them to the ends)
        // If the number of elements to fix is odd, the last one will need a separate operation
        int to_fix = n - max_len;
        int ans = (to_fix + 1) / 2;

        cout << ans << '\n';
    }
    return 0;
}
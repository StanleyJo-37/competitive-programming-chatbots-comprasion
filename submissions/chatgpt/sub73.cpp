#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        // Read the sequence
        for (int i = 0; i < n; ++i) cin >> a[i];

        // Since a_i in [1,26], we can use 1-based indexing for easier mapping
        // freq[i][j]: number of times value i appears in a[0..j-1]
        int freq[27][2001] = {0}; // 1-based for value, 0-based for position

        // Build prefix sums for each value
        for (int val = 1; val <= 26; ++val) {
            for (int i = 0; i < n; ++i) {
                freq[val][i+1] = freq[val][i] + (a[i] == val ? 1 : 0);
            }
        }

        int ans = 0;

        // Try all possible values for 'a' (the value at the two ends)
        for (int val = 1; val <= 26; ++val) {
            // Find all positions where a[i] == val
            vector<int> pos;
            for (int i = 0; i < n; ++i) {
                if (a[i] == val) pos.push_back(i);
            }
            int total = pos.size();
            // For k = 0 (no outer block), just take the max count of any value
            ans = max(ans, total);

            // Try all possible k (number of elements in each outer block)
            // k from 1 up to total/2
            for (int k = 1; k <= total/2; ++k) {
                int l = pos[k-1] + 1; // left boundary (exclusive)
                int r = pos[total-k] - 1; // right boundary (inclusive)
                if (l > r) break; // no middle block possible

                // For the middle block, try all possible values for 'b'
                int max_mid = 0;
                for (int b = 1; b <= 26; ++b) {
                    // Count of b in [l, r]
                    int cnt = freq[b][r+1] - freq[b][l];
                    max_mid = max(max_mid, cnt);
                }
                // Total length: 2*k (outer blocks) + max_mid (middle block)
                ans = max(ans, 2*k + max_mid);
            }
        }
        cout << ans << '\n';
    }
    return 0;
}
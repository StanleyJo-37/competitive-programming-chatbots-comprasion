#include <bits/stdc++.h>
using namespace std;

void solve() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }

        // Precompute prefix counts for each value (1-26)
        vector<vector<int>> prefix(26, vector<int>(n + 1, 0));
        for (int val = 1; val <= 26; ++val) {
            for (int i = 0; i < n; ++i) {
                prefix[val - 1][i + 1] = prefix[val - 1][i] + (a[i] == val);
            }
        }

        int max_len = 0;
        // Iterate all possible pairs of values (including same values)
        for (int val1 = 1; val1 <= 26; ++val1) {
            for (int val2 = 1; val2 <= 26; ++val2) {
                int left = 0, right = n - 1;
                int cnt_left = 0, cnt_right = 0;
                int max_mid = 0;
                // Two pointers approach to find the maximum middle segment
                while (left <= right) {
                    if (val1 == val2) {
                        // If both values are same, the entire segment is considered
                        max_mid = prefix[val1 - 1][right + 1] - prefix[val1 - 1][left];
                        break;
                    } else {
                        // Move left pointer to next occurrence of val1
                        while (left <= right && a[left] != val1) {
                            left++;
                        }
                        // Move right pointer to previous occurrence of val1
                        while (left <= right && a[right] != val1) {
                            right--;
                        }
                        if (left <= right) {
                            cnt_left++;
                            cnt_right++;
                            // Calculate the middle segment count of val2
                            int mid_count = prefix[val2 - 1][right] - prefix[val2 - 1][left + 1];
                            max_mid = max(max_mid, mid_count);
                            left++;
                            right--;
                        }
                    }
                }
                int total = (cnt_left + cnt_right) + max_mid;
                max_len = max(max_len, total);
            }
        }
        // Edge case: when all elements are the same (val1 == val2)
        for (int val = 1; val <= 26; ++val) {
            max_len = max(max_len, prefix[val - 1][n]);
        }
        cout << max_len << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
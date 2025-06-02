#include <iostream>
#include <vector>
#include <set>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        vector<int> a(n);
        set<int> unique_vals; // To store unique values in a
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
            unique_vals.insert(a[i]);
        }

        // If number of unique values in a > k, it's impossible
        if ((int)unique_vals.size() > k) {
            cout << -1 << '\n';
            continue;
        }

        // Build a pattern of length k using all unique values in a
        vector<int> pattern;
        for (int x : unique_vals) pattern.push_back(x);

        // If pattern size < k, fill with any value from 1..n (not necessarily from a)
        // We can use 1, since 1 <= a_i <= n
        while ((int)pattern.size() < k) pattern.push_back(1);

        // Now, repeat the pattern enough times so that all elements of a appear in order
        // Since we don't need to minimize the length, we can repeat the pattern n times
        // (since n <= 100, n*k <= 10^4)
        vector<int> result;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < k; ++j) {
                result.push_back(pattern[j]);
            }
        }

        // Output the result
        cout << result.size() << '\n';
        for (int i = 0; i < (int)result.size(); ++i) {
            cout << result[i] << (i + 1 == (int)result.size() ? '\n' : ' ');
        }
    }
    return 0;
}
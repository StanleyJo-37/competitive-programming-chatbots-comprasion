#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

// Function to compute the maximum melody subsequence length for every prefix and suffix
int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int &x : a) cin >> x;

    // dp1[i]: the length of the longest melody subsequence ending at i (prefix)
    vector<int> dp1(n, 1);
    // dp2[i]: the length of the longest melody subsequence starting at i (suffix)
    vector<int> dp2(n, 1);

    // For each position, store the best melody ending at that note value and modulo 7
    unordered_map<int, int> last_value1, last_mod1;
    for (int i = 0; i < n; ++i) {
        // Try to extend from previous notes
        for (int j = 0; j < i; ++j) {
            if (abs(a[i] - a[j]) == 1 || a[i] % 7 == a[j] % 7) {
                dp1[i] = max(dp1[i], dp1[j] + 1);
            }
        }
    }

    // Suffix DP: from right to left
    for (int i = n-1; i >= 0; --i) {
        for (int j = n-1; j > i; --j) {
            if (abs(a[i] - a[j]) == 1 || a[i] % 7 == a[j] % 7) {
                dp2[i] = max(dp2[i], dp2[j] + 1);
            }
        }
    }

    // Compute prefix and suffix maximums for fast split calculation
    vector<int> pre_max(n, 0), suf_max(n, 0);
    pre_max[0] = dp1[0];
    for (int i = 1; i < n; ++i) pre_max[i] = max(pre_max[i-1], dp1[i]);
    suf_max[n-1] = dp2[n-1];
    for (int i = n-2; i >= 0; --i) suf_max[i] = max(suf_max[i+1], dp2[i]);

    // Try all possible split points (between i and i+1)
    int ans = 0;
    for (int i = 0; i < n-1; ++i) {
        // pre_max[i]: best melody in [0..i]
        // suf_max[i+1]: best melody in [i+1..n-1]
        ans = max(ans, pre_max[i] + suf_max[i+1]);
    }

    cout << ans << endl;
    return 0;
}
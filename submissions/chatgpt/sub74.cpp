#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>
using namespace std;

// Constants
const int MOD = 1000000007;

int main() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    vector<int> a(26);
    for (int i = 0; i < 26; ++i) cin >> a[i];

    // dp[i]: number of ways to split s[0..i-1]
    vector<int> dp(n + 1, 0);
    dp[0] = 1; // empty string has 1 way

    // maxlen[i]: maximum length of a substring in any valid split of s[0..i-1]
    vector<int> maxlen(n + 1, 0);

    // minparts[i]: minimum number of substrings in any valid split of s[0..i-1]
    vector<int> minparts(n + 1, INT_MAX);
    minparts[0] = 0; // zero substrings for empty string

    // For each position i (end of substring)
    for (int i = 1; i <= n; ++i) {
        int min_a = INT_MAX; // minimum a for current substring
        // Try all possible starting positions j for substring s[j..i-1]
        for (int j = i - 1; j >= 0; --j) {
            // Update min_a to be the minimum a for all characters in s[j..i-1]
            min_a = min(min_a, a[s[j] - 'a']);
            int len = i - j;
            // If current substring s[j..i-1] is valid
            if (len <= min_a) {
                // Update number of ways
                dp[i] = (dp[i] + dp[j]) % MOD;
                // Update maximum length of substring in any valid split
                maxlen[i] = max(maxlen[i], max(maxlen[j], len));
                // Update minimum number of substrings
                minparts[i] = min(minparts[i], minparts[j] + 1);
            } else {
                // If len > min_a, no longer possible to extend further left
                break;
            }
        }
    }

    // Output results
    cout << dp[n] << endl;           // Number of ways to split
    cout << maxlen[n] << endl;       // Maximum length of substring in any valid split
    cout << minparts[n] << endl;     // Minimum number of substrings in any valid split

    return 0;
}
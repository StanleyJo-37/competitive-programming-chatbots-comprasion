#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

int main() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    vector<int> a(26);
    for (int i = 0; i < 26; ++i) {
        cin >> a[i];
    }

    // DP arrays for number of ways, max substring length, and min splits
    vector<long long> ways(n + 1, 0);
    vector<int> max_len(n + 1, 0);
    vector<int> min_splits(n + 1, INT_MAX);

    ways[0] = 1;
    max_len[0] = 0;
    min_splits[0] = 0;

    for (int i = 1; i <= n; ++i) {
        int current_max_len = INT_MAX;
        // Check all possible substring lengths ending at i (1 to i)
        for (int j = 1; j <= i; ++j) {
            int c = s[i - j] - 'a';
            current_max_len = min(current_max_len, a[c]);
            if (j > current_max_len) break; // Invalid substring length

            ways[i] = (ways[i] + ways[i - j]) % MOD;
            max_len[i] = max(max_len[i], max(j, max_len[i - j]));
            min_splits[i] = min(min_splits[i], min_splits[i - j] + 1);
        }
    }

    cout << ways[n] << endl;
    cout << max_len[n] << endl;
    cout << min_splits[n] << endl;

    return 0;
}
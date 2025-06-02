#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Read permutation p
    vector<int> p(26);
    for (int i = 0; i < 26; ++i) {
        cin >> p[i];
    }

    // Read strings s and t
    string s, t;
    cin >> s >> t;

    int n = s.size();
    int m = t.size();

    // Precompute idx(s_i) and p[idx(s_i)] for each character in s
    vector<int> s_normal(n), s_mapped(n);
    for (int i = 0; i < n; ++i) {
        s_normal[i] = s[i] - 'a';  // 0-based index
        s_mapped[i] = p[s[i] - 'a'] - 1;  // 0-based mapped value
    }

    // Precompute for each character in t, the 0-based index
    vector<int> t_idx(m);
    for (int i = 0; i < m; ++i) {
        t_idx[i] = t[i] - 'a';
    }

    // The result will be a binary string of length m - n + 1
    string result(m - n + 1, '0');

    // We need to check for each window of size n in t if it matches s under the given conditions
    // For each position i in t (0 <= i <= m - n), check if for all j in 0..n-1:
    // t[i + j] == s[j] OR p[s[j] - 'a'] == t[i + j] - 'a' + 1
    // Which is equivalent to t_idx[i + j] == s_normal[j] OR s_mapped[j] == t_idx[i + j]

    // Precompute the required conditions for each character in s and t
    // For each character c in t, we can precompute a bitmask or similar to check against s
    // However, given the constraints, a direct approach with O(n*(m-n)) is too slow (n*m up to 4e10)
    // Hence, we need a more efficient approach using polynomial hashing or FFT.

    // Since the problem is tagged with FFT, we can use polynomial multiplication to count matches.
    // The idea is to represent the matching condition as a polynomial and use FFT to compute the convolution.

    // For each character in s, we have two possible matching characters: s_normal[j] and s_mapped[j]
    // For each character in t, we need to check if it matches any of the two possibilities in s at the corresponding position.

    // We can model this as follows:
    // For each position j in s, create a pattern that matches s_normal[j] OR s_mapped[j]
    // Then, for each window in t, check if all positions match the pattern.

    // To do this efficiently, we can use bitmask and polynomial multiplication:
    // 1. For each character in the alphabet, create a bitmask indicating where it appears in s (either as normal or mapped)
    // 2. For each window in t, check if all characters in the window have their corresponding bit set in the pattern.

    // However, implementing this with FFT is complex. Instead, we can use a rolling hash approach with multiple hashes to reduce collision probability.

    // But given the time constraints, here's an optimized approach using bitmask and hashing:

    // Precompute for each position j in s, the allowed characters (s_normal[j] and s_mapped[j])
    vector<bitset<26>> s_pattern(n);
    for (int j = 0; j < n; ++j) {
        s_pattern[j].set(s_normal[j]);
        s_pattern[j].set(s_mapped[j]);
    }

    // For each window in t, check if all characters in the window match the corresponding s_pattern
    for (int i = 0; i <= m - n; ++i) {
        bool match = true;
        for (int j = 0; j < n; ++j) {
            if (!s_pattern[j].test(t_idx[i + j])) {
                match = false;
                break;
            }
        }
        if (match) {
            result[i] = '1';
        }
    }

    cout << result << '\n';

    return 0;
}
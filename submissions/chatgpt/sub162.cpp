#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
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

    // Precompute the mapping from character to its index (0-based)
    // and the reverse mapping from index to character
    vector<int> char_to_idx(26); // 'a' -> 0, ..., 'z' -> 25
    for (int i = 0; i < 26; ++i) char_to_idx[i] = i;

    // For each character c, store the mapped index (0-based) according to p
    vector<int> mapped_idx(26);
    for (int i = 0; i < 26; ++i) {
        mapped_idx[i] = p[i] - 1; // p is 1-based, convert to 0-based
    }

    // Prepare the output string
    string res(m - n + 1, '0');

    // For each substring of t of length n, check if it is an occurrence of s
    for (int i = 0; i <= m - n; ++i) {
        bool ok = true;
        for (int j = 0; j < n; ++j) {
            char sc = s[j];
            char tc = t[i + j];
            if (sc == tc) continue; // direct match
            // Check if mapped index of s[j] equals index of t[i+j]
            int sidx = sc - 'a';
            int tidx = tc - 'a';
            if (mapped_idx[sidx] != tidx) {
                ok = false;
                break;
            }
        }
        if (ok) res[i] = '1';
    }

    // Output the result
    cout << res << endl;
    return 0;
}
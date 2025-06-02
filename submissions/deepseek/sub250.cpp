#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <algorithm>

using namespace std;

int main() {
    string s;
    cin >> s;
    int n;
    cin >> n;
    vector<string> boring(n);
    unordered_set<string> boring_set;
    for (int i = 0; i < n; ++i) {
        cin >> boring[i];
        boring_set.insert(boring[i]);
    }

    int max_len = 0;
    int best_pos = 0;
    int s_len = s.size();

    // Precompute all possible starting positions of boring substrings in s
    vector<bool> is_boring(s_len, false);
    for (int i = 0; i < s_len; ++i) {
        for (int l = 1; l <= 10 && i + l <= s_len; ++l) {
            string sub = s.substr(i, l);
            if (boring_set.find(sub) != boring_set.end()) {
                // Mark all positions in [i, i + l - 1] as part of a boring substring
                for (int j = i; j < i + l; ++j) {
                    if (j < s_len) is_boring[j] = true;
                }
            }
        }
    }

    // Now find the longest contiguous segment without any boring positions
    int current_start = 0;
    for (int i = 0; i < s_len; ++i) {
        if (is_boring[i]) {
            current_start = i + 1;
        } else {
            int current_len = i - current_start + 1;
            if (current_len > max_len) {
                max_len = current_len;
                best_pos = current_start;
            }
        }
    }

    cout << max_len << " " << best_pos << endl;
    return 0;
}
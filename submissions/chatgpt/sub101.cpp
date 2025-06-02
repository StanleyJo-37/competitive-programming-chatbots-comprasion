#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    string s1, s2;
    cin >> s1 >> s2;
    int n = s1.size();
    int m = s2.size();

    // Preprocess: For each character, store all its positions in s1
    vector<vector<int>> pos(26);
    for (int i = 0; i < n; ++i) {
        pos[s1[i] - 'a'].push_back(i);
    }

    // Check if every character in s2 exists in s1
    for (char c : s2) {
        if (pos[c - 'a'].empty()) {
            cout << -1 << endl;
            return 0;
        }
    }

    int ans = 1; // At least one s1 is needed
    int idx = 0; // Current position in s1

    for (int i = 0; i < m; ) {
        char c = s2[i];
        // Binary search for the next occurrence of c in s1 at or after idx
        const vector<int>& v = pos[c - 'a'];
        int l = 0, r = v.size() - 1, found = -1;
        while (l <= r) {
            int mid = (l + r) / 2;
            if (v[mid] >= idx) {
                found = v[mid];
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        if (found != -1) {
            // Found c at position found in s1, move to next character in s2
            idx = found + 1;
            ++i;
            if (idx == n) {
                // If we reach the end of s1, need a new copy
                idx = 0;
                ++ans;
            }
        } else {
            // Need a new copy of s1, reset idx to 0, and increment ans
            idx = 0;
            ++ans;
        }
    }

    cout << ans << endl;
    return 0;
}
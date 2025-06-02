#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    string s1, s2;
    cin >> s1 >> s2;

    // Preprocess s1: for each character, store the positions where it occurs in s1.
    vector<vector<int>> char_positions(26);
    for (int i = 0; i < s1.size(); ++i) {
        char_positions[s1[i] - 'a'].push_back(i);
    }

    // Check if all characters in s2 exist in s1. If not, output -1.
    for (char c : s2) {
        if (char_positions[c - 'a'].empty()) {
            cout << -1 << endl;
            return 0;
        }
    }

    int res = 1;
    int current_pos = -1; // Position in s1 (0-based)

    for (char c : s2) {
        const vector<int>& positions = char_positions[c - 'a'];
        // Find the first position in s1 that is > current_pos.
        auto it = upper_bound(positions.begin(), positions.end(), current_pos);
        if (it != positions.end()) {
            current_pos = *it;
        } else {
            // Need to start a new s1.
            res++;
            current_pos = positions[0];
        }
    }

    cout << res << endl;
    return 0;
}
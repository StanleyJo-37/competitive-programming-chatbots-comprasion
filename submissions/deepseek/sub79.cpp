#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

// Function to check if a candidate string 's' can generate all given strings with exactly one swap each
bool validate(const string &s, const vector<string> &strs) {
    int n = s.size();
    for (const string &str : strs) {
        vector<int> diff_pos;
        for (int i = 0; i < n; ++i) {
            if (s[i] != str[i]) {
                diff_pos.push_back(i);
            }
        }
        // Must have exactly 0 or 2 differences (0 means swapped same characters)
        if (diff_pos.size() != 0 && diff_pos.size() != 2) {
            return false;
        }
        if (diff_pos.size() == 2) {
            int i = diff_pos[0], j = diff_pos[1];
            if (s[i] != str[j] || s[j] != str[i]) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    int k, n;
    cin >> k >> n;
    vector<string> strs(k);
    for (int i = 0; i < k; ++i) {
        cin >> strs[i];
    }

    // The candidate strings are derived from the first string with possible swaps
    string candidate1 = strs[0];
    bool all_same = true;
    for (int i = 1; i < k; ++i) {
        if (strs[i] != strs[0]) {
            all_same = false;
            break;
        }
    }
    if (all_same) {
        // If all strings are same, output any of them (swap same characters)
        cout << strs[0] << endl;
        return 0;
    }

    // Find positions where the first string differs from another string
    int ref_str_idx = -1;
    vector<int> diff_pos;
    for (int i = 1; i < k; ++i) {
        diff_pos.clear();
        for (int j = 0; j < n; ++j) {
            if (strs[0][j] != strs[i][j]) {
                diff_pos.push_back(j);
            }
        }
        if (diff_pos.size() > 0) {
            ref_str_idx = i;
            break;
        }
    }

    if (ref_str_idx == -1) {
        // All strings are same as the first one
        cout << strs[0] << endl;
        return 0;
    }

    // Generate possible candidates based on the first differing string
    vector<string> candidates;
    string &s1 = strs[0];
    string &s2 = strs[ref_str_idx];
    diff_pos.clear();
    for (int i = 0; i < n; ++i) {
        if (s1[i] != s2[i]) {
            diff_pos.push_back(i);
        }
    }

    if (diff_pos.size() > 4) {
        // More than 2 swaps needed, impossible
        cout << -1 << endl;
        return 0;
    }

    // Generate all possible candidates by swapping differing positions in s1
    for (int i = 0; i < diff_pos.size(); ++i) {
        for (int j = i + 1; j < diff_pos.size(); ++j) {
            string candidate = s1;
            swap(candidate[diff_pos[i]], candidate[diff_pos[j]]);
            candidates.push_back(candidate);
        }
    }
    // Also consider the original s1 (if it's valid)
    candidates.push_back(s1);

    // Check each candidate
    for (const string &candidate : candidates) {
        if (validate(candidate, strs)) {
            cout << candidate << endl;
            return 0;
        }
    }

    // If no candidate worked, try s2 (as in second sample)
    if (validate(s2, strs)) {
        cout << s2 << endl;
        return 0;
    }

    // Also check other strings if they can be the original (unlikely but possible)
    for (int i = 1; i < k; ++i) {
        if (validate(strs[i], strs)) {
            cout << strs[i] << endl;
            return 0;
        }
    }

    // No valid candidate found
    cout << -1 << endl;
    return 0;
}
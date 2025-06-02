#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <queue>
using namespace std;

// Function to collect all substrings from the given titles
void collect_substrings(const vector<string>& titles, unordered_set<string>& substrings) {
    for (const string& s : titles) {
        int len = s.size();
        // For each possible substring length
        for (int l = 1; l <= len; ++l) {
            // For each starting position
            for (int i = 0; i + l <= len; ++i) {
                substrings.insert(s.substr(i, l));
            }
        }
    }
}

int main() {
    int n;
    cin >> n;
    vector<string> titles(n);
    for (int i = 0; i < n; ++i) {
        cin >> titles[i];
    }

    // Store all substrings of all titles in a set for O(1) lookup
    unordered_set<string> substrings;
    collect_substrings(titles, substrings);

    // BFS to generate all possible strings in lexicographical order, shortest first
    queue<string> q;
    // Start with all single letters
    for (char c = 'a'; c <= 'z'; ++c) {
        string s(1, c);
        q.push(s);
    }

    while (!q.empty()) {
        string cur = q.front();
        q.pop();
        // If current string is not a substring of any title, it's the answer
        if (substrings.find(cur) == substrings.end()) {
            cout << cur << endl;
            return 0;
        }
        // If length is less than 20 (max title length), append next letter and continue
        if (cur.size() < 20) {
            for (char c = 'a'; c <= 'z'; ++c) {
                q.push(cur + c);
            }
        }
    }
    // The problem guarantees a solution exists, so this should never be reached
    return 0;
}
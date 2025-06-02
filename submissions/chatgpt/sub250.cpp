#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
using namespace std;

// Aho-Corasick automaton node
struct Node {
    vector<int> next; // transitions for each character
    int fail; // failure link
    vector<int> output; // indices of patterns ending at this node

    Node() : next(128, -1), fail(0) {}
};

class AhoCorasick {
public:
    vector<Node> trie;
    vector<int> patLens; // length of each pattern

    AhoCorasick() {
        trie.emplace_back(); // root node
    }

    // Insert pattern into trie
    void insert(const string& pat, int idx) {
        int node = 0;
        for (char c : pat) {
            if (trie[node].next[c] == -1) {
                trie[node].next[c] = trie.size();
                trie.emplace_back();
            }
            node = trie[node].next[c];
        }
        trie[node].output.push_back(idx);
    }

    // Build failure links
    void build() {
        queue<int> q;
        for (int c = 0; c < 128; ++c) {
            if (trie[0].next[c] != -1) {
                trie[trie[0].next[c]].fail = 0;
                q.push(trie[0].next[c]);
            } else {
                trie[0].next[c] = 0; // link missing transitions to root
            }
        }
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int c = 0; c < 128; ++c) {
                int v = trie[u].next[c];
                if (v != -1) {
                    int f = trie[u].fail;
                    while (trie[f].next[c] == -1) f = trie[f].fail;
                    trie[v].fail = trie[f].next[c];
                    // Merge output links
                    for (int idx : trie[trie[v].fail].output)
                        trie[v].output.push_back(idx);
                    q.push(v);
                }
            }
        }
    }

    // Find all occurrences of patterns in text
    // Returns a vector of (end position, pattern index)
    vector<pair<int, int>> findAll(const string& text) {
        vector<pair<int, int>> res;
        int node = 0;
        for (int i = 0; i < (int)text.size(); ++i) {
            char c = text[i];
            while (trie[node].next[c] == -1) node = trie[node].fail;
            node = trie[node].next[c];
            for (int idx : trie[node].output) {
                res.emplace_back(i, idx);
            }
        }
        return res;
    }
};

int main() {
    string s;
    cin >> s;
    int n;
    cin >> n;
    vector<string> b(n);
    for (int i = 0; i < n; ++i) cin >> b[i];

    // Build Aho-Corasick automaton for all boring substrings
    AhoCorasick ac;
    for (int i = 0; i < n; ++i) {
        ac.insert(b[i], i);
    }
    ac.patLens.resize(n);
    for (int i = 0; i < n; ++i) ac.patLens[i] = b[i].size();
    ac.build();

    // Mark all positions in s that are inside any boring substring
    int lenS = s.size();
    vector<int> bad(lenS, 0); // bad[i] == 1 if s[i] is inside any boring substring

    // For each occurrence, mark the range as bad
    vector<pair<int, int>> occ = ac.findAll(s);
    for (auto& p : occ) {
        int end = p.first;
        int idx = p.second;
        int l = end - ac.patLens[idx] + 1;
        int r = end;
        if (l < 0) l = 0;
        for (int i = l; i <= r; ++i) bad[i] = 1;
    }

    // Find the longest contiguous substring of s with no bad positions
    int maxLen = 0, maxPos = 0;
    int curLen = 0, curPos = 0;
    for (int i = 0; i < lenS; ++i) {
        if (bad[i] == 0) {
            if (curLen == 0) curPos = i;
            ++curLen;
            if (curLen > maxLen) {
                maxLen = curLen;
                maxPos = curPos;
            }
        } else {
            curLen = 0;
        }
    }

    // Output the result
    cout << maxLen << " " << maxPos << endl;
    return 0;
}
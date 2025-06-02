#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    // Compute prefix and suffix XOR arrays
    vector<long long> prefix(n + 1, 0), suffix(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        prefix[i + 1] = prefix[i] ^ a[i];
    }
    for (int i = n - 1; i >= 0; --i) {
        suffix[i] = suffix[i + 1] ^ a[i];
    }

    // Build a binary trie for all possible suffix XOR values
    struct TrieNode {
        TrieNode* children[2];
        TrieNode() {
            children[0] = children[1] = nullptr;
        }
    };
    TrieNode* root = new TrieNode();

    // Insert all suffix XOR values into the trie
    for (int i = 0; i <= n; ++i) {
        long long num = suffix[i];
        TrieNode* curr = root;
        for (int j = 40; j >= 0; --j) {
            int bit = (num >> j) & 1;
            if (curr->children[bit] == nullptr) {
                curr->children[bit] = new TrieNode();
            }
            curr = curr->children[bit];
        }
    }

    long long max_pleasure = 0;
    // For each prefix XOR, find the best suffix XOR to maximize XOR
    for (int i = 0; i <= n; ++i) {
        long long num = prefix[i];
        TrieNode* curr = root;
        long long res = 0;
        for (int j = 40; j >= 0; --j) {
            int bit = (num >> j) & 1;
            int desired_bit = 1 - bit;
            if (curr->children[desired_bit] != nullptr) {
                res += (1LL << j);
                curr = curr->children[desired_bit];
            } else {
                curr = curr->children[bit];
            }
        }
        max_pleasure = max(max_pleasure, res);
    }

    cout << max_pleasure << endl;

    return 0;
}
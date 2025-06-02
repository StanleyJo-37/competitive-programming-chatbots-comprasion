#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Trie node for storing binary representation of numbers
struct TrieNode {
    TrieNode* child[2];
    TrieNode() {
        child[0] = child[1] = nullptr;
    }
};

class Trie {
public:
    TrieNode* root;
    Trie() {
        root = new TrieNode();
    }
    // Insert a number into the trie
    void insert(long long num) {
        TrieNode* node = root;
        for (int i = 40; i >= 0; --i) { // 2^40 > 1e12, so 41 bits are enough
            int bit = (num >> i) & 1;
            if (!node->child[bit])
                node->child[bit] = new TrieNode();
            node = node->child[bit];
        }
    }
    // Find the maximum xor of num with any number in the trie
    long long maxXor(long long num) {
        TrieNode* node = root;
        long long res = 0;
        for (int i = 40; i >= 0; --i) {
            int bit = (num >> i) & 1;
            if (node->child[1 - bit]) {
                res |= (1LL << i);
                node = node->child[1 - bit];
            } else {
                node = node->child[bit];
            }
        }
        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; ++i)
        cin >> a[i];

    // Compute prefix xors: prefixXor[i] = a[0] ^ ... ^ a[i-1]
    vector<long long> prefixXor(n + 1, 0);
    for (int i = 1; i <= n; ++i)
        prefixXor[i] = prefixXor[i - 1] ^ a[i - 1];

    // Compute suffix xors: suffixXor[i] = a[i] ^ ... ^ a[n-1]
    vector<long long> suffixXor(n + 1, 0);
    for (int i = n - 1; i >= 0; --i)
        suffixXor[i] = suffixXor[i + 1] ^ a[i];

    // Build a trie of all possible suffix xors (including 0 for empty postfix)
    Trie trie;
    for (int i = 0; i <= n; ++i)
        trie.insert(suffixXor[i]);

    long long result = 0;
    // For each possible prefix (including empty), maximize prefixXor[i] ^ suffixXor[j]
    // where j >= i (no overlap)
    for (int i = 0; i <= n; ++i) {
        // For prefixXor[i], find the suffixXor[j] (j >= i) that maximizes xor
        // Since all suffixXor are in the trie, just query
        result = max(result, trie.maxXor(prefixXor[i]));
    }

    cout << result << '\n';
    return 0;
}
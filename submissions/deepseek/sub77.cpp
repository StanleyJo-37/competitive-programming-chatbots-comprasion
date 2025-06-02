#include <bits/stdc++.h>
using namespace std;

// Function to calculate the number of inversions (minimum adjacent swaps) required to transform s into target
long long countInversions(const string &s, const string &target) {
    map<char, vector<int>> pos;
    for (int i = 0; i < s.size(); ++i) {
        pos[s[i]].push_back(i);
    }
    vector<int> a;
    map<char, int> ptr;
    for (char c : target) {
        a.push_back(pos[c][ptr[c]++]);
    }
    // Count inversions using Fenwick Tree (BIT)
    long long inv = 0;
    vector<int> fenwick(s.size() + 2, 0);
    for (int i = (int)a.size() - 1; i >= 0; --i) {
        int x = a[i] + 1;
        for (int j = x - 1; j > 0; j -= j & -j) {
            inv += fenwick[j];
        }
        for (; x <= s.size(); x += x & -x) {
            fenwick[x]++;
        }
    }
    return inv;
}

// Function to generate all possible permutations of the unique characters in the string
vector<string> generatePermutations(const string &unique_chars) {
    vector<string> permutations;
    string chars = unique_chars;
    sort(chars.begin(), chars.end());
    do {
        permutations.push_back(chars);
    } while (next_permutation(chars.begin(), chars.end()));
    return permutations;
}

// Function to solve each test case
string solve(const string &a) {
    map<char, int> freq;
    for (char c : a) {
        freq[c]++;
    }
    string unique_chars;
    for (auto &p : freq) {
        unique_chars += p.first;
    }
    vector<string> permutations = generatePermutations(unique_chars);
    string best_b;
    long long max_inv = -1;
    for (const string &perm : permutations) {
        string candidate;
        for (char c : perm) {
            candidate += string(freq[c], c);
        }
        long long inv = countInversions(a, candidate);
        if (inv > max_inv) {
            max_inv = inv;
            best_b = candidate;
        }
    }
    return best_b;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        string a;
        cin >> a;
        cout << solve(a) << '\n';
    }
    return 0;
}
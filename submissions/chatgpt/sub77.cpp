#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// For each test case, we want to construct a permutation of the input string
// that maximizes the number of adjacent swaps needed to restore the original string.
// This is equivalent to maximizing the number of inversions with respect to the original string.

// Since there are only 4 possible characters: 'A', 'N', 'O', 'T',
// we can try all 24 (4!) possible orders of these characters and for each,
// construct the string by grouping all same characters together in that order.
// For each such permutation, we compute the number of inversions with respect to the original string.
// The permutation with the maximum inversions is the answer.

typedef long long ll;

// Fenwick Tree (Binary Indexed Tree) for inversion counting
struct Fenwick {
    vector<int> bit;
    int n;
    Fenwick(int n): n(n), bit(n+1, 0) {}
    void add(int i, int x) {
        for (++i; i <= n; i += i&-i) bit[i] += x;
    }
    int sum(int i) {
        int res = 0;
        for (++i; i > 0; i -= i&-i) res += bit[i];
        return res;
    }
    int range(int l, int r) { // sum [l, r]
        return sum(r) - sum(l-1);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    vector<string> results;
    while (t--) {
        string a;
        cin >> a;
        int n = a.size();

        // Count occurrences of each character
        int cnt[4] = {0, 0, 0, 0}; // A, N, O, T
        for (char c : a) {
            if (c == 'A') cnt[0]++;
            else if (c == 'N') cnt[1]++;
            else if (c == 'O') cnt[2]++;
            else if (c == 'T') cnt[3]++;
        }

        // All possible orders of 'A', 'N', 'O', 'T'
        string chars = "ANOT";
        vector<int> perm = {0, 1, 2, 3};
        ll max_inv = -1;
        string best_b;

        do {
            // Build string b by grouping all same characters together in this order
            string b;
            for (int i = 0; i < 4; ++i) {
                b += string(cnt[perm[i]], chars[perm[i]]);
            }

            // To count inversions, map each character in b to its position in a
            // For each character in b, find its next occurrence in a (using a pointer for each char)
            vector<vector<int>> pos(4); // positions of each char in a
            for (int i = 0; i < n; ++i) {
                if (a[i] == 'A') pos[0].push_back(i);
                else if (a[i] == 'N') pos[1].push_back(i);
                else if (a[i] == 'O') pos[2].push_back(i);
                else if (a[i] == 'T') pos[3].push_back(i);
            }
            vector<int> ptr(4, 0);
            vector<int> mapped_pos;
            for (char c : b) {
                int idx = (c == 'A' ? 0 : c == 'N' ? 1 : c == 'O' ? 2 : 3);
                mapped_pos.push_back(pos[idx][ptr[idx]++]);
            }

            // Count inversions in mapped_pos
            Fenwick fen(n);
            ll inv = 0;
            for (int i = n-1; i >= 0; --i) {
                inv += fen.sum(mapped_pos[i]-1);
                fen.add(mapped_pos[i], 1);
            }

            if (inv > max_inv) {
                max_inv = inv;
                best_b = b;
            }
        } while (next_permutation(perm.begin(), perm.end()));

        results.push_back(best_b);
    }

    for (const string& res : results) {
        cout << res << '\n';
    }
}
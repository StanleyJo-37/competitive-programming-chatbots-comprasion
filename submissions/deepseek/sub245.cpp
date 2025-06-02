#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, l, r;
    cin >> n >> l >> r;
    vector<int> c(n);
    for (int i = 0; i < n; ++i) {
        cin >> c[i];
    }

    // Separate left and right socks
    vector<int> left(c.begin(), c.begin() + l);
    vector<int> right(c.begin() + l, c.end());

    // Count frequencies of colors in left and right
    unordered_map<int, int> left_freq, right_freq;
    for (int color : left) {
        left_freq[color]++;
    }
    for (int color : right) {
        right_freq[color]++;
    }

    // First, match as many pairs as possible without any cost
    int cost = 0;
    for (auto& [color, cnt] : left_freq) {
        int matched = min(cnt, right_freq[color]);
        left_freq[color] -= matched;
        right_freq[color] -= matched;
        l -= matched;
        r -= matched;
    }

    // Now, handle the remaining left and right socks
    // For left socks: if there are pairs of same color, flipping one to right reduces cost
    int left_pairs = 0;
    for (auto& [color, cnt] : left_freq) {
        left_pairs += cnt / 2;
    }
    int right_pairs = 0;
    for (auto& [color, cnt] : right_freq) {
        right_pairs += cnt / 2;
    }

    // The number of socks that can be matched by flipping (changing type) is min(left_pairs, right_pairs)
    // But we need to match (abs(l - r) / 2) socks by flipping type, and the rest by recoloring
    int type_flips = abs(l - r) / 2;
    int matched_by_flips = min({type_flips, left_pairs, right_pairs});
    cost += matched_by_flips;
    if (l > r) {
        l -= 2 * matched_by_flips;
    } else {
        r -= 2 * matched_by_flips;
    }

    // The remaining unmatched socks must be recolored or flipped (but flipping now costs 1, same as recoloring)
    // Each remaining sock will cost 1 (either flip or recolor)
    cost += (l + r) / 2;

    cout << cost << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
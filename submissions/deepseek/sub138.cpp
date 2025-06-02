#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<vector<int>> bits(n);
    for (int i = 0; i < n; ++i) {
        int k;
        cin >> k;
        bits[i].resize(k);
        for (int j = 0; j < k; ++j) {
            cin >> bits[i][j];
        }
    }

    // We need to find if there exists two different subsets of elements whose OR is the same.
    // The key observation is that if there exists any bit position that is set in only one element,
    // then that element must be included in any subset that has that bit set. Otherwise, if all bits
    // are covered by at least two elements, then we can always find two different subsets with the same OR.

    // To implement this, we can check for each bit whether it appears in only one element.
    // If any such bit exists, the answer is "No" because that element must be included in any subset
    // that has that bit set, making it impossible to have two different subsets with the same OR.
    // Otherwise, the answer is "Yes".

    unordered_map<int, int> bitCount;
    for (auto &v : bits) {
        for (int bit : v) {
            bitCount[bit]++;
        }
    }

    bool possible = false;
    for (auto &v : bits) {
        bool allBitsMultiple = true;
        for (int bit : v) {
            if (bitCount[bit] == 1) {
                allBitsMultiple = false;
                break;
            }
        }
        if (allBitsMultiple) {
            possible = true;
            break;
        }
    }

    cout << (possible ? "Yes" : "No") << '\n';
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
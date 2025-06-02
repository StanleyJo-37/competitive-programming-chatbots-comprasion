#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<vector<int>> daughters(n);
    vector<bool> married_kingdoms(n + 1, false); // 1-based
    vector<bool> married_daughters(n + 1, false); // 1-based
    int married_count = 0;

    for (int i = 0; i < n; ++i) {
        int k;
        cin >> k;
        daughters[i].resize(k);
        for (int j = 0; j < k; ++j) {
            cin >> daughters[i][j];
        }
    }

    // First pass: assign the lowest available kingdom to each daughter
    for (int i = 0; i < n; ++i) {
        for (int kingdom : daughters[i]) {
            if (!married_kingdoms[kingdom]) {
                married_kingdoms[kingdom] = true;
                married_daughters[i + 1] = true; // daughters are 1-based
                married_count++;
                break;
            }
        }
    }

    if (married_count == n) {
        cout << "OPTIMAL\n";
        return;
    }

    // Find an unmarried daughter and an unmarried kingdom
    int free_daughter = -1;
    for (int i = 1; i <= n; ++i) {
        if (!married_daughters[i]) {
            free_daughter = i;
            break;
        }
    }

    int free_kingdom = -1;
    for (int i = 1; i <= n; ++i) {
        if (!married_kingdoms[i]) {
            free_kingdom = i;
            break;
        }
    }

    if (free_daughter != -1 && free_kingdom != -1) {
        cout << "IMPROVE\n";
        cout << free_daughter << " " << free_kingdom << "\n";
    } else {
        cout << "OPTIMAL\n";
    }
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
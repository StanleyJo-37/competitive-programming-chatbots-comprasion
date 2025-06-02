#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int k;
        cin >> k;
        vector<int> leaves(k);
        for (int i = 0; i < k; ++i) {
            cin >> leaves[i];
        }

        // The last level must have at least one leaf (since stems can't branch beyond the last level)
        if (leaves.back() == 0) {
            cout << "No\n";
            continue;
        }

        bool valid = true;
        long long stems = 0; // Tracks the number of stems at the current level

        // We process levels from bottom to top
        for (int i = k - 1; i >= 0; --i) {
            stems += leaves[i];
            if (i > 0) {
                // Stems at level i must be even because each stem branches into 2 stems at the next level
                if (stems % 2 != 0) {
                    valid = false;
                    break;
                }
                stems /= 2; // Each pair of stems comes from one stem in the previous level
            }
        }

        // At the top (level 1), there must be exactly one stem (the initial stem)
        if (stems != 1) {
            valid = false;
        }

        cout << (valid ? "Yes" : "No") << '\n';
    }

    return 0;
}
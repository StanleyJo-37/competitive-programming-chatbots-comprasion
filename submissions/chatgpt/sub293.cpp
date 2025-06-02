#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false); // Fast IO
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

        // At level 0 (before any level), there is exactly 1 stem.
        long long stems = 1;
        bool possible = true;

        for (int i = 0; i < k; ++i) {
            // If there are more leaves than stems, it's impossible.
            if (leaves[i] > stems) {
                possible = false;
                break;
            }
            // Each stem can either end (become a leaf) or branch into 2 stems at next level.
            // The number of stems that branch = stems - leaves[i]
            // Each branching stem produces 2 stems at next level.
            // So, next level stems = (stems - leaves[i]) * 2
            stems = (stems - leaves[i]) * 2;

            // If at any point, stems become negative, it's impossible.
            if (stems < 0) {
                possible = false;
                break;
            }

            // To avoid overflow, clamp stems to a reasonable upper bound.
            // Since leaves[i] <= 1e6 and k <= 1e6, stems can't exceed 2e6 in any valid scenario.
            if (stems > 2000000) stems = 2000000;
        }

        // At the end, all stems must have ended as leaves (i.e., no stems left unaccounted for).
        if (possible && stems == 0) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }
    return 0;
}
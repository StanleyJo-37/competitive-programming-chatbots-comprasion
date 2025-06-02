#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// For each test case, we simulate the game, greedily pressing "Reset" only when necessary.
// We want to minimize the number of resets, so we only reset when, in the next round, either
// the human or the computer would reach or exceed k points, and we cannot finish the game
// before that happens. We always try to go as far as possible without resetting.

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        long long k;
        cin >> n >> k;
        vector<long long> a(n), b(n);
        for (int i = 0; i < n; ++i) cin >> a[i];
        for (int i = 0; i < n; ++i) cin >> b[i];

        // Current points for human and computer
        long long human = 0, comp = 0;
        // Store the rounds after which we press "Reset"
        vector<int> resets;
        // Whether the game is already lost
        bool lost = false;

        // We process each round
        for (int i = 0; i < n; ++i) {
            // Add points for this round
            human += a[i];
            comp += b[i];

            // If both reach k or more, both lose
            if (human >= k && comp >= k) {
                lost = true;
                break;
            }
            // If human reaches k or more, human loses
            if (human >= k) {
                lost = true;
                break;
            }
            // If computer reaches k or more, human wins
            if (comp >= k) {
                // No need to reset, human wins
                break;
            }

            // If not last round, check if in the next round, either will lose
            if (i + 1 < n) {
                // If after next round, human or computer will reach k or more, and neither is at k yet
                if (human + a[i + 1] >= k || comp + b[i + 1] >= k) {
                    // We need to reset now, after this round, to avoid losing in the next round
                    // Only reset if both are currently less than k
                    if (human < k && comp < k) {
                        // Record the round (1-based index)
                        resets.push_back(i + 1);
                        // Apply the reset transformation
                        long long new_human = max(0LL, human - comp);
                        long long new_comp = max(0LL, comp - human);
                        human = new_human;
                        comp = new_comp;
                    }
                }
            }
        }

        // If lost, print -1
        if (lost) {
            cout << -1 << '\n';
            continue;
        }

        // Otherwise, print the number of resets and the rounds
        cout << resets.size() << '\n';
        if (!resets.empty()) {
            for (int i = 0; i < (int)resets.size(); ++i) {
                cout << resets[i];
                if (i + 1 < (int)resets.size()) cout << ' ';
            }
            cout << '\n';
        }
    }
    return 0;
}
#include <iostream>
#include <vector>
#include <set>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        // For each daughter, store her list of kingdoms
        vector<vector<int>> daughters(n + 1);
        // To check if a kingdom is already in a daughter's list
        vector<set<int>> daughter_sets(n + 1);

        for (int i = 1; i <= n; ++i) {
            int k;
            cin >> k;
            daughters[i].resize(k);
            for (int j = 0; j < k; ++j) {
                cin >> daughters[i][j];
                daughter_sets[i].insert(daughters[i][j]);
            }
        }

        // Track which kingdoms are already taken
        vector<bool> kingdom_taken(n + 1, false);
        // Track which daughters are married
        vector<bool> daughter_married(n + 1, false);

        // Greedily assign marriages
        for (int i = 1; i <= n; ++i) {
            bool married = false;
            for (int kingdom : daughters[i]) {
                if (!kingdom_taken[kingdom]) {
                    kingdom_taken[kingdom] = true;
                    daughter_married[i] = true;
                    married = true;
                    break;
                }
            }
            // If not married, daughter_married[i] remains false
        }

        // Find an unmatched daughter and an unmatched kingdom
        int unmatched_daughter = -1;
        for (int i = 1; i <= n; ++i) {
            if (!daughter_married[i]) {
                unmatched_daughter = i;
                break;
            }
        }

        if (unmatched_daughter == -1) {
            // All daughters are married, marriages are optimal
            cout << "OPTIMAL\n";
        } else {
            // Find an unmatched kingdom not in the unmatched daughter's list
            int unmatched_kingdom = -1;
            for (int k = 1; k <= n; ++k) {
                if (!kingdom_taken[k] && daughter_sets[unmatched_daughter].find(k) == daughter_sets[unmatched_daughter].end()) {
                    unmatched_kingdom = k;
                    break;
                }
            }
            if (unmatched_kingdom != -1) {
                // We can improve by adding this kingdom to this daughter's list
                cout << "IMPROVE\n";
                cout << unmatched_daughter << " " << unmatched_kingdom << "\n";
            } else {
                // No way to improve
                cout << "OPTIMAL\n";
            }
        }
    }
    return 0;
}
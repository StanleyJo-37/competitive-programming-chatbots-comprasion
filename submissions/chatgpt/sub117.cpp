#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    string s;
    cin >> s;
    int n = s.size();

    // Each zebra sequence will be stored as a vector of indices (1-based)
    vector<vector<int>> zebras;

    // For each zebra sequence, we need to know if it currently ends with 0 or 1
    // We use two queues to store the indices of zebra sequences that are waiting for a 1 or a 0
    // zebra_ends_with_0: zebra sequences that currently end with 0, waiting for a 1
    // zebra_ends_with_1: zebra sequences that currently end with 1, waiting for a 0
    queue<int> zebra_ends_with_0, zebra_ends_with_1;

    // Process each day
    for (int i = 0; i < n; ++i) {
        if (s[i] == '0') {
            // If there is a zebra sequence that ends with 1, append this 0 to it
            if (!zebra_ends_with_1.empty()) {
                int idx = zebra_ends_with_1.front();
                zebra_ends_with_1.pop();
                zebras[idx].push_back(i + 1);
                // Now this zebra ends with 0, so push it to zebra_ends_with_0
                zebra_ends_with_0.push(idx);
            } else {
                // Start a new zebra sequence with this 0
                zebras.push_back({i + 1});
                // This new zebra ends with 0, so push its index to zebra_ends_with_0
                zebra_ends_with_0.push(zebras.size() - 1);
            }
        } else { // s[i] == '1'
            // If there is a zebra sequence that ends with 0, append this 1 to it
            if (!zebra_ends_with_0.empty()) {
                int idx = zebra_ends_with_0.front();
                zebra_ends_with_0.pop();
                zebras[idx].push_back(i + 1);
                // Now this zebra ends with 1, so push it to zebra_ends_with_1
                zebra_ends_with_1.push(idx);
            } else {
                // No zebra sequence is waiting for a 1, so it's impossible
                cout << -1 << endl;
                return 0;
            }
        }
    }

    // At the end, all zebra sequences must end with 0 (i.e., zebra_ends_with_1 must be empty)
    if (!zebra_ends_with_1.empty()) {
        cout << -1 << endl;
        return 0;
    }

    // Output the result
    cout << zebras.size() << endl;
    for (const auto& zebra : zebras) {
        cout << zebra.size();
        for (int idx : zebra) cout << " " << idx;
        cout << endl;
    }
    return 0;
}
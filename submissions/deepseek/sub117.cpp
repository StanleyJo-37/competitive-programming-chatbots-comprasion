#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;
    int n = s.size();
    vector<vector<int>> zebras;
    queue<int> q0, q1; // q0 stores indices of zebras ending with 0, q1 with 1

    for (int i = 0; i < n; ++i) {
        char c = s[i];
        if (c == '0') {
            if (!q1.empty()) {
                // Append to a zebra ending with 1 (alternating)
                int zebra_idx = q1.front();
                q1.pop();
                zebras[zebra_idx].push_back(i + 1); // +1 for 1-based index
                q0.push(zebra_idx);
            } else {
                // Create a new zebra
                zebras.push_back({i + 1});
                q0.push(zebras.size() - 1);
            }
        } else { // c == '1'
            if (!q0.empty()) {
                // Append to a zebra ending with 0 (alternating)
                int zebra_idx = q0.front();
                q0.pop();
                zebras[zebra_idx].push_back(i + 1);
                q1.push(zebra_idx);
            } else {
                // No zebra ending with 0 to append to, invalid
                cout << -1 << endl;
                return 0;
            }
        }
    }

    // Check if any zebra ends with 1 (invalid)
    if (!q1.empty()) {
        cout << -1 << endl;
        return 0;
    }

    // Output the result
    cout << zebras.size() << endl;
    for (auto &zebra : zebras) {
        cout << zebra.size() << " ";
        for (int idx : zebra) {
            cout << idx << " ";
        }
        cout << endl;
    }

    return 0;
}
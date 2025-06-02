#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < n; ++i) cin >> b[i];
    
    int human = 0, computer = 0;
    vector<int> resets;
    
    for (int i = 0; i < n; ++i) {
        human += a[i];
        computer += b[i];
        
        // Check if any player has lost
        if (human >= k && computer >= k) {
            cout << "-1\n";
            return;
        }
        if (human >= k) {
            cout << "-1\n";
            return;
        }
        if (computer >= k) {
            // Output the resets if any
            cout << resets.size() << "\n";
            if (!resets.empty()) {
                for (int r : resets) cout << r << " ";
                cout << "\n";
            }
            return;
        }
        
        // Decide whether to reset
        if (human > 0 && computer > 0) {
            // Reset if it helps to minimize future resets or prevent human from losing
            // Greedy approach: reset when human's points are positive and computer's points are positive
            resets.push_back(i + 1); // 1-based index
            int new_human = max(0, human - computer);
            int new_computer = max(0, computer - human);
            human = new_human;
            computer = new_computer;
        }
    }
    
    // After all rounds, check if computer has lost
    if (computer >= k) {
        cout << resets.size() << "\n";
        if (!resets.empty()) {
            for (int r : resets) cout << r << " ";
            cout << "\n";
        }
    } else {
        cout << "-1\n";
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
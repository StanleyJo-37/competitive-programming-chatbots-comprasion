#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

void solve() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> x(n);
        for (int i = 0; i < n; ++i) {
            cin >> x[i];
        }
        
        unordered_set<int> used;
        // Process notes in reverse to prioritize larger values first
        for (int i = n - 1; i >= 0; --i) {
            if (used.find(x[i] + 1) == used.end()) {
                // Prefer to use x[i]+1 if not already used
                used.insert(x[i] + 1);
            } else {
                // Otherwise, use x[i] if not already used
                used.insert(x[i]);
            }
        }
        cout << used.size() << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
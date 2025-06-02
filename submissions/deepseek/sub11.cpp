#include <bits/stdc++.h>
using namespace std;

void solve() {
    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        vector<int> e(N);
        for (int i = 0; i < N; ++i) {
            cin >> e[i];
        }
        sort(e.begin(), e.end()); // Sorting helps in greedy approach
        
        int groups = 0;
        int current = 0; // Tracks the current group size being formed
        
        for (int i = 0; i < N; ++i) {
            current++; // Add current explorer to the potential group
            if (current >= e[i]) { // If group size meets the inexperience requirement
                groups++; // Form a group
                current = 0; // Reset for next group
            }
        }
        cout << groups << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
#include <bits/stdc++.h>
using namespace std;

void solve() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        char c;
        cin >> n >> c;
        string s;
        cin >> s;
        
        if (c == 'g') {
            cout << 0 << '\n';
            continue;
        }
        
        vector<int> green_positions;
        for (int i = 0; i < n; ++i) {
            if (s[i] == 'g') {
                green_positions.push_back(i);
            }
        }
        
        int max_wait = 0;
        for (int i = 0; i < n; ++i) {
            if (s[i] == c) {
                // Find the next 'g' after i (circular)
                auto it = upper_bound(green_positions.begin(), green_positions.end(), i);
                int next_g;
                if (it != green_positions.end()) {
                    next_g = *it;
                } else {
                    next_g = green_positions[0] + n;
                }
                int wait = next_g - i;
                if (wait > max_wait) {
                    max_wait = wait;
                }
            }
        }
        cout << max_wait << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
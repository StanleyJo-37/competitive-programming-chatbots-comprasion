#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false); // Fast IO
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        char c;
        cin >> n >> c;
        string s;
        cin >> s;

        // If current color is green, we can cross immediately
        if (c == 'g') {
            cout << 0 << '\n';
            continue;
        }

        // Precompute the next 'g' position for each index in s (circularly)
        vector<int> next_g(n, -1);
        int last_g = -1;

        // We process 2n to handle circularity
        vector<int> g_pos;
        for (int i = 0; i < n; ++i) {
            if (s[i] == 'g') g_pos.push_back(i);
        }
        // For each position, find the next 'g' position (circular)
        // We'll use a pointer to the next 'g' in the doubled string
        int m = g_pos.size();
        int ptr = 0;
        for (int i = 0; i < n; ++i) {
            // Find the first g_pos >= i
            while (ptr < m && g_pos[ptr] < i) ++ptr;
            if (ptr < m) {
                next_g[i] = g_pos[ptr];
            } else {
                // Wrap around: next 'g' is at g_pos[0] + n
                next_g[i] = g_pos[0] + n;
            }
        }

        // For every position where s[i] == c, calculate the time to next 'g'
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            if (s[i] == c) {
                int wait = next_g[i] - i;
                if (wait > ans) ans = wait;
            }
        }
        cout << ans << '\n';
    }
    return 0;
}
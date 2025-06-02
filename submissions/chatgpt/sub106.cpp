#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false); // Fast IO
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        string s;
        cin >> s;

        vector<int> sheep_positions;
        // Collect all positions of sheep ('*')
        for (int i = 0; i < n; ++i) {
            if (s[i] == '*') {
                sheep_positions.push_back(i);
            }
        }

        // If there are 0 or 1 sheep, no moves needed
        if (sheep_positions.size() <= 1) {
            cout << 0 << '\n';
            continue;
        }

        // The optimal way is to "gather" all sheep around the median sheep
        // This minimizes the total moves (sum of absolute differences)
        int m = sheep_positions.size();
        int median_index = m / 2;
        int median_pos = sheep_positions[median_index];

        // The target positions for the sheep to be consecutive are:
        // [median_pos - median_index, median_pos - median_index + 1, ..., median_pos + (m-1) - median_index]
        // So, sheep_positions[i] should move to (median_pos - median_index + i)
        long long moves = 0;
        for (int i = 0; i < m; ++i) {
            moves += abs(sheep_positions[i] - (median_pos - median_index + i));
        }

        cout << moves << '\n';
    }
    return 0;
}
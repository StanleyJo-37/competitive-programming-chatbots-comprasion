#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        string s;
        cin >> s;

        vector<int> sheep_positions;
        for (int i = 0; i < n; ++i) {
            if (s[i] == '*') {
                sheep_positions.push_back(i);
            }
        }

        if (sheep_positions.empty()) {
            cout << "0\n";
            continue;
        }

        // The median position minimizes the total distance
        int median_pos = sheep_positions[sheep_positions.size() / 2];
        long long moves = 0;

        // Calculate the expected positions for each sheep after alignment
        // The first sheep should be at median_pos - (m), where m is the number of sheep to the left of median
        int left_count = sheep_positions.size() / 2;
        int expected_pos = median_pos - left_count;

        for (int pos : sheep_positions) {
            moves += abs(pos - expected_pos);
            expected_pos++;
        }

        cout << moves << '\n';
    }

    return 0;
}
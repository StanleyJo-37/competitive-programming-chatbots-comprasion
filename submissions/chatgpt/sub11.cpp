#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false); // Fast IO
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        vector<int> e(N);
        for (int i = 0; i < N; ++i) {
            cin >> e[i];
        }

        // Sort inexperience values to process smallest first
        sort(e.begin(), e.end());

        int groups = 0; // Number of groups formed
        int cnt = 0;    // Current group size

        // Greedily form groups as soon as possible
        for (int i = 0; i < N; ++i) {
            ++cnt; // Add current explorer to the current group
            // If current group size is at least as large as the inexperience of the last added explorer,
            // we can form a group
            if (cnt >= e[i]) {
                ++groups; // Form a group
                cnt = 0;  // Reset group size for next group
            }
        }

        cout << groups << '\n';
    }
    return 0;
}
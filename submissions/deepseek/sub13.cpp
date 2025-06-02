#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> res;

    // The optimal strategy is to place the turning points spaced by 2k+1 units.
    // This ensures that each turning covers a maximal non-overlapping segment.
    // The first turning point is at position min(1 + k, n), but we adjust to cover from the start.
    // Then, subsequent points are placed every (2k + 1) units.
    int step = 2 * k + 1;
    int pos = 0;

    // We start placing turning points from the leftmost possible position that covers the first skewer.
    // Then, each next turning point is placed step units away, ensuring coverage without gaps.
    while (pos < n) {
        // The current position to turn is pos + k + 1 (1-based), but we need to ensure it's within bounds.
        int turn_pos = min(pos + k + 1, n);
        res.push_back(turn_pos);
        pos = turn_pos + k; // Move to the end of the current coverage.
    }

    // Output the results.
    cout << res.size() << endl;
    for (int i = 0; i < res.size(); ++i) {
        if (i > 0) cout << " ";
        cout << res[i];
    }
    cout << endl;

    return 0;
}
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> angles(n);
    for (int i = 0; i < n; ++i) {
        cin >> angles[i];
    }

    // We can use bitmask to represent all possible combinations of directions (0 or 1 for each angle)
    // Since n is up to 15, 2^15 = 32768 iterations is feasible.
    bool possible = false;
    for (int mask = 0; mask < (1 << n); ++mask) {
        int total = 0;
        for (int i = 0; i < n; ++i) {
            // Check if the i-th bit is set (1 means clockwise, 0 means counter-clockwise)
            if (mask & (1 << i)) {
                total += angles[i];
            } else {
                total -= angles[i];
            }
        }
        // Check if total is congruent to 0 mod 360 (since 360 degrees is a full rotation)
        if (total % 360 == 0) {
            possible = true;
            break;
        }
    }

    cout << (possible ? "YES" : "NO") << endl;
    return 0;
}
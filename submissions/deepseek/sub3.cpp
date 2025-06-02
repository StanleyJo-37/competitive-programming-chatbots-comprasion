#include <iostream>
#include <string>

using namespace std;

int main() {
    int l, w;
    cin >> l >> w;

    // The minimum possible weight is l (all 'a's) and maximum is 26*l (all 'z's)
    if (w < l || w > 26 * l) {
        cout << "impossible" << endl;
        return 0;
    }

    string result(l, 'a'); // Start with all 'a's (weight = l)
    int remaining = w - l;  // Remaining weight to distribute

    // Distribute the remaining weight from the end to the beginning
    for (int i = l - 1; i >= 0 && remaining > 0; --i) {
        // The maximum we can add to this position is min(25, remaining) (since 'a' is 1, max is 'z' = 26)
        int add = min(25, remaining);
        result[i] += add;
        remaining -= add;
    }

    // If remaining is zero, we have a valid string; otherwise, it's impossible
    if (remaining == 0) {
        cout << result << endl;
    } else {
        cout << "impossible" << endl;
    }

    return 0;
}
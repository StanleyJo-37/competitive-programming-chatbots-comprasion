#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    // The range of skewers affected by one operation is 2*k+1 (center + k on each side)
    int range = 2 * k + 1;

    // If k >= n, one operation is enough (turn any skewer, all will be affected)
    if (k >= n) {
        cout << 1 << endl;
        cout << 1 << endl;
        return 0;
    }

    vector<int> ops; // To store the positions to turn

    // We want to cover all skewers [1, n] with minimum number of operations.
    // Place the first operation as far to the left as possible, but so that the last operation covers the end.
    // The last operation must cover skewer n, so its center is at least n-k.
    // Place operations every 'range' skewers, starting from the leftmost possible.

    // Find the first position to turn:
    // The last operation's center is at least n-k, so we can start at position s,
    // where s = max(1, n - k - (l-1)*range), and l is the number of operations.
    // But it's easier to just greedily place operations every 'range' skewers.

    int pos = 1 + k; // First operation center
    if (pos > n) pos = n; // If k >= n, just use n

    // To ensure the last operation covers n, we may need to shift the starting position
    // Calculate the minimal number of operations needed
    int l = (n + range - 1) / range; // ceil(n / range)
    // The last operation's center should be at most n-k
    int last_center = n - k;
    // The first operation's center is at: first_center = 1 + k + (i * range)
    // So, to have the last operation at last_center, we can start at:
    int first_center = 1 + k;
    if (first_center + (l - 1) * range > last_center) {
        // Shift the first_center to the left
        first_center = last_center - (l - 1) * range;
    }
    pos = first_center;

    // Place l operations, each at pos + i*range
    for (int i = 0; i < l; ++i) {
        ops.push_back(pos + i * range);
    }

    // Output the result
    cout << ops.size() << endl;
    for (int i = 0; i < ops.size(); ++i) {
        cout << ops[i] << (i + 1 == ops.size() ? '\n' : ' ');
    }
    return 0;
}
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n; // Read number of rotations
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i]; // Read each rotation angle
    }

    // There are 2^n possible ways to assign + or - to each rotation
    // We'll use bitmasking to try all possibilities
    // For each bitmask, if bit i is 1, add a[i], else subtract a[i]
    for (int mask = 0; mask < (1 << n); ++mask) {
        int sum = 0;
        for (int i = 0; i < n; ++i) {
            if (mask & (1 << i)) {
                sum += a[i]; // Clockwise
            } else {
                sum -= a[i]; // Counterclockwise
            }
        }
        // If the sum is divisible by 360, the pointer returns to zero
        if ((sum % 360 + 360) % 360 == 0) {
            cout << "YES" << endl;
            return 0;
        }
    }
    // If no combination works, print NO
    cout << "NO" << endl;
    return 0;
}
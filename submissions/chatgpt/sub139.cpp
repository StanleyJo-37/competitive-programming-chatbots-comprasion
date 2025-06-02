#include <iostream>
#include <vector>
using namespace std;

int main() {
    int t;
    cin >> t; // Read number of test cases
    while (t--) {
        int n, l;
        cin >> n >> l; // Read number of forms and word length
        vector<int> x(n);
        for (int i = 0; i < n; ++i) {
            cin >> x[i]; // Read each form as integer
        }

        // For each bit position, count how many forms have 1 at that position
        vector<int> cnt1(l, 0);
        for (int i = 0; i < n; ++i) {
            for (int bit = 0; bit < l; ++bit) {
                if (x[i] & (1 << bit)) {
                    cnt1[bit]++;
                }
            }
        }

        // To minimize the sum of Hamming distances, for each bit position,
        // choose 1 if more than half of the forms have 1 at that position,
        // otherwise choose 0. If exactly half, either is fine.
        int y = 0;
        for (int bit = 0; bit < l; ++bit) {
            if (cnt1[bit] > n / 2) {
                y |= (1 << bit);
            }
            // If cnt1[bit] == n/2, either 0 or 1 is fine, so we can leave it as 0
        }

        cout << y << '\n'; // Output the result for this test case
    }
    return 0;
}
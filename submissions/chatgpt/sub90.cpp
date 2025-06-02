#include <iostream>
#include <string>
using namespace std;

int main() {
    int t;
    cin >> t; // Read number of test cases
    while (t--) {
        int n, k;
        string s;
        cin >> n >> k >> s; // Read n, k, and string s

        // The structure of s must be:
        // s = a1 + a2 + ... + ak + a_{k+1} + R(ak) + ... + R(a1)
        // That means:
        // - The first k characters (prefix) must match the last k characters (suffix) in reverse order.
        // - The middle part (a_{k+1}) can be any non-empty string (at least 1 character).
        // - The total length must be at least 2*k + 1.

        bool possible = true;

        // If 2*k >= n, then there is no room for a non-empty a_{k+1}
        if (2 * k >= n) {
            possible = false;
        } else {
            // Check if the prefix of length k matches the suffix of length k in reverse
            for (int i = 0; i < k; ++i) {
                if (s[i] != s[n - 1 - i]) {
                    possible = false;
                    break;
                }
            }
        }

        // Output result for this test case
        cout << (possible ? "YES" : "NO") << endl;
    }
    return 0;
}
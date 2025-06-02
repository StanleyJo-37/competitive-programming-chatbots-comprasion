#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false); // Fast IO
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        string a, b;
        cin >> a >> b;

        vector<int> ops; // To store the sequence of operations

        // We process from the end of the string to the beginning
        // At each step, we want a[i] == b[i]
        // We simulate the effect of all previous operations using two pointers and a flip flag
        int l = 0, r = n - 1; // Two pointers for the current "ends" of the string
        bool rev = false; // Whether the current string is reversed
        bool flip = false; // Whether the current string is flipped

        // We process from the last character to the first
        for (int i = n - 1; i >= 0; --i) {
            // Determine the current character at position i in a, after all previous operations
            char cur;
            if (!rev) {
                cur = a[r];
            } else {
                cur = a[l];
            }
            // If flip is true, invert the bit
            if (flip) {
                cur = (cur == '0' ? '1' : '0');
            }
            // If the current character matches b[i], just move the pointer
            if (cur == b[i]) {
                if (!rev) --r;
                else ++l;
                continue;
            }
            // Otherwise, we may need to flip the first character first
            // Check what the first character is (after all previous operations)
            char first;
            if (!rev) {
                first = a[l];
            } else {
                first = a[r];
            }
            if (flip) {
                first = (first == '0' ? '1' : '0');
            }
            // If first != b[i], we can flip the prefix of length i+1 directly
            if (first != b[i]) {
                ops.push_back(i + 1);
                // After this operation, the prefix is reversed and flipped
                rev = !rev;
                flip = !flip;
                // Move the pointer accordingly
                if (!rev) --r;
                else ++l;
            } else {
                // Otherwise, flip the first character, then the prefix
                ops.push_back(1);
                // Flipping the first character: just flip the bit at the current "first" position
                // This is simulated by toggling flip
                flip = !flip;
                // Now, flip the prefix of length i+1
                ops.push_back(i + 1);
                rev = !rev;
                flip = !flip;
                // Move the pointer accordingly
                if (!rev) --r;
                else ++l;
            }
        }

        // Output the result for this test case
        cout << ops.size();
        for (int x : ops) cout << " " << x;
        cout << "\n";
    }
    return 0;
}
#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;

int main() {
    int q;
    cin >> q;
    while (q--) {
        ll n;
        cin >> n;

        // Store base-3 digits of n (least significant digit first)
        vector<int> digits;
        ll temp = n;
        while (temp > 0) {
            digits.push_back(temp % 3);
            temp /= 3;
        }

        // Find the first position where digit >= 2
        int sz = digits.size();
        int pos = -1;
        for (int i = 0; i < sz; ++i) {
            if (digits[i] >= 2) {
                pos = i;
                break;
            }
        }

        if (pos == -1) {
            // n is already a good number (all digits are 0 or 1)
            cout << n << endl;
            continue;
        }

        // Find the first zero after pos (or append one if needed)
        int carry_pos = pos;
        while (carry_pos < sz && digits[carry_pos] != 0) {
            ++carry_pos;
        }
        if (carry_pos == sz) {
            // Need to add a new digit
            digits.push_back(0);
            sz++;
        }

        // Set this position to 1, and all lower positions to 0
        digits[carry_pos] = 1;
        for (int i = 0; i < carry_pos; ++i) {
            digits[i] = 0;
        }

        // Convert back to decimal
        ll res = 0, pow3 = 1;
        for (int i = 0; i < sz; ++i) {
            res += digits[i] * pow3;
            pow3 *= 3;
        }
        cout << res << endl;
    }
    return 0;
}
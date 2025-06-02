#include <iostream>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    string s;
    cin >> s;

    // Count number of '+' and '-' in the string
    int cnt_plus = 0, cnt_minus = 0;
    for (char c : s) {
        if (c == '+') cnt_plus++;
        else cnt_minus++;
    }

    int q;
    cin >> q;
    while (q--) {
        long long a, b;
        cin >> a >> b;

        // Let x = number of times we use button a for '+'
        //     y = number of times we use button a for '-'
        //     (cnt_plus - x) = number of times we use button b for '+'
        //     (cnt_minus - y) = number of times we use button b for '-'
        //
        // The total score is:
        //   S = x*a + (cnt_plus-x)*b - (y*a + (cnt_minus-y)*b)
        //     = x*a + cnt_plus*b - x*b - y*a - cnt_minus*b + y*b
        //     = (x-y)*(a-b) + (cnt_plus - cnt_minus)*b
        //
        // We want S == 0, so:
        //   (x-y)*(a-b) + (cnt_plus - cnt_minus)*b == 0
        //   (x-y)*(a-b) == (cnt_minus - cnt_plus)*b
        //
        // Let d = x-y
        //   d*(a-b) == (cnt_minus - cnt_plus)*b
        //
        // d must be integer, and x, y must be in [0, cnt_plus] and [0, cnt_minus] respectively
        // So, d in [-(cnt_minus), cnt_plus]
        //
        // If a == b, then (a-b) == 0, so the only way is (cnt_minus - cnt_plus)*b == 0
        //   i.e., cnt_plus == cnt_minus (number of + and - equal)
        // Otherwise, (a-b) != 0, so (cnt_minus - cnt_plus)*b must be divisible by (a-b)
        //   and d in [-(cnt_minus), cnt_plus]

        if (a == b) {
            if (cnt_plus == cnt_minus) {
                cout << "YES\n";
            } else {
                cout << "NO\n";
            }
        } else {
            long long num = (long long)(cnt_minus - cnt_plus) * b;
            long long den = a - b;
            // Check if num is divisible by den
            if (den == 0) {
                cout << "NO\n";
                continue;
            }
            // To avoid negative division issues, check sign
            if (num % den != 0) {
                cout << "NO\n";
                continue;
            }
            long long d = num / den;
            // d = x - y, so x = y + d
            // y in [0, cnt_minus], x in [0, cnt_plus]
            // So d in [-(cnt_minus), cnt_plus]
            if (d >= -cnt_minus && d <= cnt_plus) {
                cout << "YES\n";
            } else {
                cout << "NO\n";
            }
        }
    }
    return 0;
}
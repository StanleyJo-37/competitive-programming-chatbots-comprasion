#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int q;
    cin >> q;
    while (q--) {
        long long n;
        cin >> n;

        // The smallest composite number is 4.
        // If n < 4, it's impossible to split.
        if (n < 4) {
            cout << -1 << '\n';
            continue;
        }

        // For n == 4, 6, 8, 9, 10, 12, 14, 15, 16, etc., we need to check how to split.
        // The idea is to use as many 4's as possible, since 4 is the smallest composite.
        // But for some remainders, we need to use 6, 8, or 9 to make up the rest.

        // If n is odd, we cannot use only 4's (since 4 is even).
        // The only odd composite less than 10 is 9 and 15.
        // But 9 is the only small odd composite we can use for small remainders.

        // Let's handle the cases for n % 4:
        // n % 4 == 0: use all 4's
        // n % 4 == 1: need to use one 9 (since 9 is composite), then the rest is divisible by 4
        // n % 4 == 2: need to use one 6 (since 6 is composite), then the rest is divisible by 4
        // n % 4 == 3: need to use one 9 and one 6 (since 9+6=15, composite), then the rest is divisible by 4

        // But let's check for each case:

        if (n % 4 == 0) {
            // All 4's
            cout << n / 4 << '\n';
        } else if (n % 4 == 1) {
            // Need at least one 9, so n >= 9
            if (n < 9) {
                cout << -1 << '\n';
            } else {
                // Use one 9, rest is (n-9), which must be divisible by 4
                cout << 1 + (n - 9) / 4 << '\n';
            }
        } else if (n % 4 == 2) {
            // Need at least one 6, so n >= 6
            if (n < 6) {
                cout << -1 << '\n';
            } else {
                // Use one 6, rest is (n-6), which must be divisible by 4
                cout << 1 + (n - 6) / 4 << '\n';
            }
        } else if (n % 4 == 3) {
            // Need at least one 9 and one 6, so n >= 15
            if (n < 15) {
                cout << -1 << '\n';
            } else {
                // Use one 9 and one 6, rest is (n-15), which must be divisible by 4
                cout << 2 + (n - 15) / 4 << '\n';
            }
        }
    }
    return 0;
}
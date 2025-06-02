#include <iostream>
using namespace std;

// For each test case, we need to find three distinct positive integers a, b, c such that:
// 1. a + b + c = n
// 2. gcd(a, b) = c
// 3. a, b, c are all distinct and positive

// We can always construct such a triple as follows:
// - If n is odd, let c = 1, a = n/2, b = n/2
//   But a and b would be equal, so we need to adjust to make them distinct.
//   Instead, for odd n, let c = 1, a = n/2, b = n/2 + 1 (since n is odd, n/2 and n/2+1 are distinct).
//   gcd(a, b) = gcd(n/2, n/2+1) = 1, so c = 1, and a, b, c are all distinct if n/2 != 1.
//   For n >= 10, this is always true.
// - If n is even, and n is not divisible by 4, let c = 2, a = (n-2)/2, b = (n-2)/2 + 2
//   gcd(a, b) = gcd((n-2)/2, (n-2)/2+2) = 2, so c = 2, and a, b, c are all distinct for n >= 10.
// - If n is divisible by 4, let c = n/4, a = n/2 - 1, b = n/4 + 1
//   gcd(a, b) = gcd(n/2-1, n/4+1). For n >= 12, this is always possible and c is distinct.

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        long long n;
        cin >> n;

        // If n is odd
        if (n % 2 == 1) {
            // c = 1, a = n/2, b = n/2 + 1
            long long a = n / 2;
            long long b = n / 2 + 1;
            long long c = 1;
            // Ensure all are distinct and positive
            if (a != b && b != c && a != c && a > 0 && b > 0 && c > 0) {
                cout << a << " " << b << " " << c << "\n";
            } else {
                // This should not happen for n >= 10
                cout << "1 2 " << n-3 << "\n";
            }
        } else {
            // n is even
            if ((n / 2) % 2 == 1) {
                // n/2 is odd, so n is even but not divisible by 4
                // c = 2, a = n/2 - 1, b = n/2 + 1
                long long a = n / 2 - 1;
                long long b = n / 2 + 1;
                long long c = 2;
                // Ensure all are distinct and positive
                if (a != b && b != c && a != c && a > 0 && b > 0 && c > 0) {
                    cout << a << " " << b << " " << c << "\n";
                } else {
                    // This should not happen for n >= 10
                    cout << "1 2 " << n-3 << "\n";
                }
            } else {
                // n is divisible by 4
                // c = n/4, a = n/2 - 1, b = n/4 + 1
                long long c = n / 4;
                long long a = n / 2 - 1;
                long long b = c + 1;
                // Ensure all are distinct and positive
                if (a != b && b != c && a != c && a > 0 && b > 0 && c > 0) {
                    cout << a << " " << b << " " << c << "\n";
                } else {
                    // This should not happen for n >= 10
                    cout << "1 2 " << n-3 << "\n";
                }
            }
        }
    }
    return 0;
}
#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        // The approach is to find a, b, c such that c = gcd(a, b) and a + b + c = n.
        // We can choose c to be 1 if n-1 is even, then a = (n-1)/2, b = (n-1)/2 + 1.
        // But to ensure distinctness, we need to handle cases where (n-1)/2 is even.
        // Alternatively, if n is even, we can choose c = n/2 - 1, but that might not always work.
        // A better approach is to set c = 1 if n is odd, and c = 2 if n is even.
        // Then, a + b = n - c, and gcd(a, b) = c.
        // For c = 1, any two consecutive integers (a, b) will have gcd 1.
        // For c = 2, choose a = 2 and b = n - c - a, ensuring gcd(a, b) = 2.
        // But we need to ensure a, b, c are distinct and positive.

        int c;
        if (n % 2 == 1) {
            // If n is odd, set c = 1, then a and b can be (n-1)/2 and (n-1)/2 + 1.
            c = 1;
            int half = (n - 1) / 2;
            cout << half << " " << half + 1 << " " << c << "\n";
        } else {
            // If n is even, set c = 2, then a = 2 and b = n - c - a = n - 4.
            // Check if gcd(2, n-4) = 2, which is true since n-4 is even.
            // Ensure n-4 != 2 (i.e., n != 6), but n >= 10, so it's safe.
            c = 2;
            int a = 2;
            int b = n - c - a;
            cout << a << " " << b << " " << c << "\n";
        }
    }
    return 0;
}
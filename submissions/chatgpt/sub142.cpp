#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false); // Fast IO
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        long long N, A;
        cin >> N >> A;

        // If N == 1, the only element is A, so sum is A
        if (N == 1) {
            if (A % 2 == 0)
                cout << "Even\n";
            else
                cout << "Odd\n";
            continue;
        }

        // For N > 1, analyze the parity:
        // The AND of all elements is A.
        // Each element must have all bits set that are set in A.
        // But other bits can be 0 or 1, so elements can be A, A+1, A+2, etc., as long as (element & A) == A.

        // The parity of A (A % 2) tells us if all elements are odd or even:
        // - If A is even, all elements are even (since LSB is 0 in all).
        //   So sum is even.
        // - If A is odd, all elements are odd (since LSB is 1 in all).
        //   Sum of N odd numbers is odd if N is odd, even if N is even.
        //   But since elements can be A, A+2, etc., but always odd, so sum is N*odd = odd if N is odd, even if N is even.

        // BUT, for N > 1 and A is odd, is it possible to have all elements odd and their AND is odd?
        // Yes, but the sum's parity depends on N.

        // For N > 1 and A is even, sum is always even.
        if (A % 2 == 0) {
            cout << "Even\n";
        } else {
            // For N > 1 and A is odd, sum is odd if N is odd, even if N is even.
            if (N % 2 == 0)
                cout << "Even\n";
            else
                cout << "Odd\n";
        }
    }
    return 0;
}
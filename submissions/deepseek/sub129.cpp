#include <iostream>
using namespace std;

int main() {
    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        int operations = 0;
        // The minimum operations required is equal to the number of set bits in N minus 1.
        // Because each set bit (except the highest one) represents a part that needs to be broken down.
        while (N) {
            operations += N & 1; // Count each set bit.
            N >>= 1;             // Right shift to check next bit.
        }
        // Subtract 1 because the highest set bit doesn't need to be broken down.
        cout << operations - 1 << endl;
    }
    return 0;
}
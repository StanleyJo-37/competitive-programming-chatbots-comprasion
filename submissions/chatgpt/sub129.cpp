#include <iostream>
using namespace std;

int main() {
    int T;
    cin >> T; // Read number of test cases
    while (T--) {
        int N;
        cin >> N; // Read the integer N for this test case

        // Count the number of set bits (1s) in the binary representation of N
        // Each set bit represents a power of 2 needed to sum up to N
        // To split N into k powers of 2, we need (k-1) splits (operations)
        int count = 0;
        int temp = N;
        while (temp) {
            count += (temp & 1); // Increment count if the least significant bit is 1
            temp >>= 1; // Shift right to check the next bit
        }

        // The minimum number of operations is (number of set bits - 1)
        // If N is already a power of 2, count == 1, so 0 operations needed
        cout << (count - 1) << endl;
    }
    return 0;
}
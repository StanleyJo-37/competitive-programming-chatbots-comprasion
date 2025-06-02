#include <iostream>
using namespace std;

// Function to reverse the bits of a non-negative integer
int reverseBits(int n) {
    int rev = 0; // This will store the reversed bits
    while (n > 0) {
        // Shift rev to the left to make space for the next bit
        rev <<= 1;
        // If the least significant bit of n is 1, set the least significant bit of rev
        if (n & 1)
            rev |= 1;
        // Shift n to the right to process the next bit
        n >>= 1;
    }
    return rev;
}

int main() {
    int n;
    // Read input integer
    cin >> n;
    // Output the integer with its bits reversed
    cout << reverseBits(n) << endl;
    return 0;
}
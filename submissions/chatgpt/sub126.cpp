#include <iostream>
#include <string>
using namespace std;

// Function to generate the first n digits of the Thue-Morse sequence
string thue_morse(int n) {
    // Initialize an empty string to store the sequence
    string result;
    result.reserve(n); // Reserve memory for efficiency

    // For each position i (0-based), the value is the parity of the number of 1s in binary representation of i
    for (int i = 0; i < n; ++i) {
        int x = i;
        int count = 0;
        // Count the number of 1s in the binary representation of i
        while (x) {
            count ^= (x & 1); // XOR accumulates parity (0 for even, 1 for odd)
            x >>= 1;
        }
        // If count is 0, append '0', else append '1'
        result += (count ? '1' : '0');
    }
    return result;
}

// For testing purposes
int main() {
    // Example test cases
    cout << thue_morse(1) << endl;    // Output: 0
    cout << thue_morse(2) << endl;    // Output: 01
    cout << thue_morse(5) << endl;    // Output: 01101
    cout << thue_morse(10) << endl;   // Output: 0110100110
    return 0;
}
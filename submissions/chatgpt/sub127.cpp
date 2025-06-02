#include <iostream>
using namespace std;

// Function to count the number of bits to flip to convert A to B
int countBitsToConvert(int A, int B) {
    // XOR will give bits that are different between A and B
    int xorResult = A ^ B;
    int count = 0;
    // Count the number of set bits in xorResult
    while (xorResult) {
        // Remove the lowest set bit
        xorResult = xorResult & (xorResult - 1);
        count++;
    }
    return count;
}

int main() {
    int A, B;
    // Read two integers from input
    cin >> A >> B;
    // Output the number of bits to flip
    cout << countBitsToConvert(A, B) << endl;
    return 0;
}
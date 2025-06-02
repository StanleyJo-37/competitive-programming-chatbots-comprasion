#include <iostream>

int bitFlipRequired(int A, int B) {
    // XOR A and B to get a number where bits are set to 1 where A and B differ
    int xorResult = A ^ B;
    int count = 0;
    
    // Count the number of set bits in xorResult
    while (xorResult != 0) {
        // Increment count if the least significant bit is 1
        count += xorResult & 1;
        // Right shift xorResult to check the next bit
        xorResult >>= 1;
    }
    
    return count;
}

int main() {
    // Example usage
    int A = 31, B = 14;
    std::cout << bitFlipRequired(A, B) << std::endl; // Output: 2
    return 0;
}
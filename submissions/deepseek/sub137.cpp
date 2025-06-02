#include <iostream>

/**
 * Computes the XOR from 0 to n efficiently using bitwise properties.
 * 
 * Observation:
 * - XOR from 0 to n follows a pattern based on n modulo 4:
 *   - If n % 4 == 0, result is n.
 *   - If n % 4 == 1, result is 1.
 *   - If n % 4 == 2, result is n + 1.
 *   - If n % 4 == 3, result is 0.
 * 
 * This pattern arises because XOR operations cancel out pairs of numbers,
 * leaving a predictable remainder based on the position of n.
 */
int sXORe(int n) {
    switch (n % 4) {
        case 0: return n;
        case 1: return 1;
        case 2: return n + 1;
        default: return 0;
    }
}

int main() {
    // Test cases
    std::cout << sXORe(0) << std::endl;       // Output: 0
    std::cout << sXORe(1) << std::endl;       // Output: 1
    std::cout << sXORe(50) << std::endl;      // Output: 51
    std::cout << sXORe(1000000) << std::endl; // Output: 1000000
    return 0;
}
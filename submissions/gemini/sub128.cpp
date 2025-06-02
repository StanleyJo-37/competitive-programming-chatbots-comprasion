#include <cstdint> // Required for fixed-width integer types like uint32_t if needed, though unsigned int is generally sufficient.

// Function to reverse the bits of a non-negative integer.
// The problem example (417 -> 267) implies reversing only the significant bits
// of the number, not within a fixed-size integer (e.g., 32-bit).
// For example, 417 is 110100001 (9 bits). Reversing these 9 bits gives 100001011 (267).
// If it were a fixed 32-bit reversal, 417 (0...0110100001) would reverse to a much larger number.
// This implementation follows the interpretation of reversing only the effective bits.
unsigned int reverseBits(unsigned int n) {
    // Initialize 'reversed_num' to 0. This variable will store the result
    // as bits are extracted from 'n' and placed in reverse order.
    unsigned int reversed_num = 0;

    // Loop continues as long as there are bits left to process in 'n'.
    // Each iteration processes one bit from 'n', starting from its least significant bit (LSB).
    while (n > 0) {
        // Shift 'reversed_num' left by one position.
        // This makes space for the next bit from 'n' at the least significant position
        // of 'reversed_num'. It also effectively moves existing bits in 'reversed_num'
        // to higher significance, preparing for the reversal.
        reversed_num <<= 1;

        // Check the least significant bit (LSB) of 'n'.
        // The bitwise AND operation (n & 1) will be 1 if the LSB of 'n' is 1, and 0 otherwise.
        if (n & 1) {
            // If the LSB of 'n' is 1, set the LSB of 'reversed_num' to 1.
            // The bitwise OR operation (reversed_num |= 1) achieves this.
            // If the LSB of 'n' was 0, 'reversed_num' would remain unchanged at its LSB (which is 0 after the left shift).
            reversed_num |= 1;
        }

        // Right shift 'n' by one position.
        // This effectively discards the LSB of 'n' that was just processed and
        // brings the next bit to the LSB position for the next iteration.
        n >>= 1;
    }

    // After the loop completes (when 'n' becomes 0, meaning all its bits have been processed),
    // 'reversed_num' holds the integer with its original bits reversed.
    return reversed_num;
}

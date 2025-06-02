#include <cstdint>

uint32_t reverseBits(uint32_t n) {
    uint32_t result = 0;
    for (int i = 0; i < 32; ++i) {
        // Shift result left to make space for the next bit
        result <<= 1;
        // Add the least significant bit of n to result
        result |= (n & 1);
        // Shift n right to process the next bit
        n >>= 1;
    }
    return result;
}
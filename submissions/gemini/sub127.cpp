// Function to count the number of set bits (1s) in a non-negative integer.
// This helper function uses Brian Kernighan's algorithm, which is efficient
// as it runs in time proportional to the number of set bits, not the total
// number of bits in the integer.
//
// Parameters:
//   n: The integer for which to count set bits. Assumed to be non-negative.
//
// Returns:
//   The number of set bits in 'n'.
int countSetBits(int n) {
    int count = 0;
    // Loop continues as long as 'n' has at least one set bit.
    while (n > 0) {
        // The operation `n &= (n - 1)` clears the least significant set bit of 'n'.
        // For example:
        // If n = 12 (binary 1100)
        // n - 1 = 11 (binary 1011)
        // n & (n - 1) = 1100 & 1011 = 1000 (decimal 8)
        // The least significant '1' bit (at position 2) is cleared.
        //
        // If n = 8 (binary 1000)
        // n - 1 = 7 (binary 0111)
        // n & (n - 1) = 1000 & 0111 = 0000 (decimal 0)
        // The least significant '1' bit (at position 3) is cleared.
        //
        // Each time a bit is cleared, we increment the count.
        n &= (n - 1);
        count++;
    }
    return count;
}

// Function to determine the number of bits required to convert integer A to integer B.
// This is equivalent to finding the Hamming distance between A and B.
// The Hamming distance is the number of positions at which the corresponding bits are different.
//
// Parameters:
//   A: The first non-negative integer.
//   B: The second non-negative integer.
//      Both A and B are guaranteed to be >= 0 and up to 2^16 or int.MaxValue.
//      Using 'int' type is sufficient for these constraints.
//
// Returns:
//   The number of bits that need to be flipped to transform A into B.
int solve(int A, int B) {
    // The XOR operation (A ^ B) produces a result where each bit is 1
    // if the corresponding bits in A and B are different, and 0 if they are the same.
    // For example:
    // A = 31 (00011111 in binary)
    // B = 14 (00001110 in binary)
    // A ^ B = (00011111 ^ 00001110) = 00010001 in binary (decimal 17)
    //
    // The bits that are '1' in `xor_result` are precisely the bits that need to be flipped
    // to convert A to B (or vice versa).
    int xor_result = A ^ B;

    // Therefore, the problem reduces to counting the number of set bits (1s)
    // in the `xor_result`.
    return countSetBits(xor_result);
}
// Function to calculate the sXORe of a number n.
// sXORe(n) is defined as 0 XOR 1 XOR 2 ... XOR n.
// This function leverages a pattern observed in the XOR sum of consecutive integers.
// The pattern repeats every 4 numbers:
// sXORe(n) = n, if n % 4 == 0
// sXORe(n) = 1, if n % 4 == 1
// sXORe(n) = n + 1, if n % 4 == 2
// sXORe(n) = 0, if n % 4 == 3
int sXORe(int n) {
    // Calculate the remainder when n is divided by 4.
    int remainder = n % 4;

    // Apply the pattern based on the remainder.
    if (remainder == 0) {
        // If n % 4 is 0, the sXORe is n itself.
        // Example: sXORe(0) = 0, sXORe(4) = 4, sXORe(8) = 8.
        // This is because the XOR sum of any 4 consecutive numbers (k ^ (k+1) ^ (k+2) ^ (k+3)) is 0.
        // For instance, 0^1^2^3 = 0, 4^5^6^7 = 0, etc.
        // If n is a multiple of 4, all numbers up to n-1 form complete blocks of 4 that XOR to 0.
        // Thus, sXORe(n) = (0^...^3) ^ ... ^ ((n-4)^...^(n-1)) ^ n = 0 ^ ... ^ 0 ^ n = n.
        return n;
    } else if (remainder == 1) {
        // If n % 4 is 1, the sXORe is 1.
        // Example: sXORe(1) = 1, sXORe(5) = 1.
        // For n = 4k + 1:
        // sXORe(n) = (0^...^3) ^ ... ^ ((4k-4)^...^(4k-1)) ^ 4k ^ (4k+1)
        // All full blocks (0^...^3), (4^...^7), etc., XOR to 0.
        // So, sXORe(n) = 4k ^ (4k+1).
        // Since 4k is a multiple of 4, its binary representation ends in '00'.
        // 4k+1 will then end in '01'.
        // XORing a number ending in '00' with a number ending in '01' results in a number ending in '01'.
        // For example, 4 (0100) ^ 5 (0101) = 1 (0001).
        // The higher bits of 4k and 4k+1 are identical.
        // Thus, 4k ^ (4k+1) = 1.
        return 1;
    } else if (remainder == 2) {
        // If n % 4 is 2, the sXORe is n + 1.
        // Example: sXORe(2) = 3, sXORe(6) = 7.
        // For n = 4k + 2:
        // sXORe(n) = (0^...^3) ^ ... ^ ((4k-4)^...^(4k-1)) ^ 4k ^ (4k+1) ^ (4k+2)
        // All full blocks XOR to 0.
        // So, sXORe(n) = (4k ^ (4k+1)) ^ (4k+2).
        // From the previous case, we know that 4k ^ (4k+1) = 1.
        // So, sXORe(n) = 1 ^ (4k+2).
        // Since 4k+2 is an even number, its binary representation ends in '0'.
        // XORing with 1 (which is '...01' in binary) flips the last bit of 4k+2 from '0' to '1'.
        // This operation is equivalent to adding 1 to an even number.
        // So, 1 ^ (4k+2) = (4k+2) + 1 = n + 1.
        return n + 1;
    } else { // remainder == 3
        // If n % 4 is 3, the sXORe is 0.
        // Example: sXORe(3) = 0, sXORe(7) = 0.
        // For n = 4k + 3:
        // sXORe(n) = (0^...^3) ^ ... ^ ((4k-4)^...^(4k-1)) ^ (4k ^ (4k+1) ^ (4k+2) ^ (4k+3))
        // All blocks, including the last one (4k ^ (4k+1) ^ (4k+2) ^ (4k+3)), are complete blocks of 4 consecutive numbers.
        // As established, the XOR sum of any 4 consecutive numbers is 0.
        // Thus, sXORe(n) = 0 ^ ... ^ 0 = 0.
        return 0;
    }
}
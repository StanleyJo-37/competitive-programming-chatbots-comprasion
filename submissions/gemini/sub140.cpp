#include <vector> // Required for std::vector
#include <string>   // Required for std::string

// Function to count set bits (1s) in the significant binary representation of a positive integer.
// For example, for n=5 (binary 101), it returns 2.
// For n=0, it returns 0 (though the problem states 0 is neutral and won't be processed here).
int countSetBits(int n) {
    int count = 0;
    // Loop continues as long as n is greater than 0.
    // This ensures we only count bits within the significant representation (e.g., for 5, we consider 101, not 00...0101).
    while (n > 0) {
        // Check the least significant bit (LSB). If it's 1, increment count.
        if ((n & 1) == 1) {
            count++;
        }
        // Right-shift n by 1 to move to the next bit (effectively dividing by 2).
        n >>= 1;
    }
    return count;
}

// Function to count zero bits in the significant binary representation of a positive integer.
// For example, for n=14 (binary 1110), it returns 1.
// For n=4 (binary 100), it returns 2.
// For n=0, it returns 0 (as 0 is neutral and has no significant bits for this context).
int countZeroBits(int n) {
    // If n is 0, it has no significant bits to count zeros from in this context.
    if (n == 0) {
        return 0;
    }

    int total_bits = 0; // Stores the total number of significant bits.
    int ones_count = 0; // Stores the number of 1s in the significant bits.
    int temp_n = n;     // Use a temporary variable to avoid modifying the original 'n'.

    // Loop continues as long as temp_n is greater than 0.
    // This loop determines the length of the significant binary representation and counts 1s.
    while (temp_n > 0) {
        total_bits++; // Increment total_bits for each bit processed.
        // Check the least significant bit. If it's 1, increment ones_count.
        if ((temp_n & 1) == 1) {
            ones_count++;
        }
        // Right-shift temp_n by 1 to move to the next bit.
        temp_n >>= 1;
    }
    // The number of zero bits is the total significant bits minus the number of one bits.
    return total_bits - ones_count;
}

// The main function that solves the "Bits War" problem.
// It takes a constant reference to a vector of integers.
std::string bitsWar(const std::vector<int>& numbers) {
    long long odd_ones_total = 0;   // Accumulator for the total count of '1' bits from odd numbers.
                                    // Using long long to safely handle potentially large sums, though int might suffice.
    long long even_zeros_total = 0; // Accumulator for the total count of '0' bits from even numbers.

    // Iterate through each number in the input vector.
    for (int num : numbers) {
        // According to the problem statement, number 0 is neutral and does not fight.
        if (num == 0) {
            continue; // Skip processing for 0.
        }

        // Determine if the number is odd or even.
        // An odd number has its least significant bit set to 1 (num % 2 != 0).
        // An even number has its least significant bit set to 0 (num % 2 == 0).
        if (num % 2 != 0) { // If the number is odd
            // Odd numbers fight using their '1' bits.
            odd_ones_total += countSetBits(num);
        } else { // If the number is even
            // Even numbers fight using their '0' bits.
            even_zeros_total += countZeroBits(num);
        }
    }

    // Compare the accumulated totals to determine the winner.
    if (odd_ones_total > even_zeros_total) {
        return "odds win";
    } else if (odd_ones_total < even_zeros_total) {
        return "evens win";
    } else {
        // If the totals are equal, or if the input list was empty (both totals remain 0).
        return "tie";
    }
}
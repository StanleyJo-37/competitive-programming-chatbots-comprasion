#include <string>   // Required for std::string to return the result.
#include <vector>   // Required for std::vector to accept the input array of numbers.
#include <cmath>    // Required for std::abs to get the absolute value of numbers.

// Function to determine the winner of the "Bits War".
// It calculates scores for odd and even numbers based on the count of set bits (1s)
// in their binary representation. Negative numbers contribute negatively to their score.
//
// Parameters:
//   numbers: A constant reference to a std::vector of integers.
//
// Returns:
//   A std::string indicating the winner: "odds win", "evens win", or "tie".
std::string bits_war(const std::vector<int>& numbers) {
    // Initialize scores for odd and even numbers.
    // These variables will accumulate the total contribution from numbers of each parity.
    int odd_score = 0;
    int even_score = 0;

    // Iterate through each number in the input vector.
    // Using a range-based for loop for conciseness and readability.
    for (int num : numbers) {
        // Calculate the absolute value of the current number.
        // The problem implies that the count of '1's (set bits) is derived from the
        // magnitude of the number, and then its original sign determines if this count
        // is added positively or negatively to the score.
        // For example, for -3, we consider the bits of 3 (11_2, which has 2 set bits),
        // and then apply the negative sign, resulting in a contribution of -2.
        int abs_num = std::abs(num);

        // Count the number of set bits (1s) in the binary representation of `abs_num`.
        // `__builtin_popcount` is a GCC/Clang compiler intrinsic that efficiently
        // counts the number of set bits in an unsigned integer.
        // We cast `abs_num` to `unsigned int` to ensure `__builtin_popcount`
        // operates on its bit pattern correctly, as it expects unsigned types.
        // Since `abs_num` is guaranteed to be non-negative, this cast is safe.
        int set_bits_count = __builtin_popcount(static_cast<unsigned int>(abs_num));

        // Determine the contribution of the current number to its respective score.
        // If the original number `num` was negative, its contribution is the negative
        // of its set bit count. Otherwise (if `num` was positive or zero), its
        // contribution is simply its set bit count.
        int contribution = (num < 0) ? -set_bits_count : set_bits_count;

        // Check the parity of the original number `num` to add the calculated
        // `contribution` to the correct score (either `odd_score` or `even_score`).
        // The modulo operator (`%`) in C++ correctly determines parity for both
        // positive and negative integers:
        // - An odd number (e.g., 7, -3) will result in `num % 2 != 0`.
        // - An even number (e.g., 12, -2, 0) will result in `num % 2 == 0`.
        if (num % 2 != 0) { // If the number is odd
            odd_score += contribution;
        } else { // If the number is even (including 0)
            even_score += contribution;
        }
    }

    // After processing all numbers, compare the final scores to determine the winner.
    if (odd_score > even_score) {
        return "odds win";
    } else if (even_score > odd_score) {
        return "evens win";
    } else {
        // If scores are equal, it's a tie.
        return "tie";
    }
}
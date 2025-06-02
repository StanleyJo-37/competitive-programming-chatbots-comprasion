#include <iostream> // Required for input/output operations (std::cin, std::cout)
#include <string>   // Required for string manipulation (std::string)

// The problem asks to determine the winner of a game based on an initial number 'n'.
// Louise always starts.
// Game rules:
// 1. If 'n' is a power of 2, divide it by 2.
// 2. If 'n' is not a power of 2, reduce it by the next lower number which is a power of 2.
// The player who reduces the number to 1 wins.

// The core idea is to count the total number of moves made in the game.
// If the total number of moves is odd, Louise (the first player) wins.
// If the total number of moves is even, Richard (the second player) wins.

// Let's analyze the two types of moves in terms of binary representation:

// Type 1: 'n' is a power of 2 (e.g., 8 = 1000_2, 4 = 100_2, 2 = 10_2, 1 = 1_2).
// A power of 2 has exactly one '1' bit in its binary representation.
// The move is to divide 'n' by 2. This effectively shifts the single '1' bit to the right.
// Example: 8 (1000_2) -> 4 (0100_2) -> 2 (0010_2) -> 1 (0001_2).
// If 'n' is 2^k, it takes 'k' such moves to reach 1.
// The value 'k' is equivalent to the position of the '1' bit (0-indexed from the right),
// which is also the number of trailing zeros in the binary representation of 'n'.
// In C++, `__builtin_ctzll(n)` (count trailing zeros for unsigned long long) gives this value.

// Type 2: 'n' is not a power of 2 (e.g., 132 = 10000100_2, 6 = 110_2).
// A number that is not a power of 2 has multiple '1' bits in its binary representation.
// The move is to reduce 'n' by the largest power of 2 less than 'n'.
// This largest power of 2 corresponds to the most significant bit (MSB) of 'n'.
// Subtracting this value effectively clears the MSB of 'n'.
// Example: 132 (10000100_2). The largest power of 2 less than 132 is 128 (10000000_2).
// 132 - 128 = 4 (00000100_2). The MSB (at position 7) is cleared.
// This operation reduces the number of set bits (population count) by 1.
// In C++, `__builtin_popcountll(n)` (population count for unsigned long long) counts set bits.

// The game proceeds in a sequence of these moves until 'n' becomes 1.
// Let's trace the total number of moves:
// 1. Moves of Type 2 (clearing MSBs):
//    If 'n' is not a power of 2, it has `popcount(n)` set bits.
//    Each Type 2 move clears one set bit (the MSB).
//    This continues until 'n' becomes a power of 2 (i.e., has only one set bit).
//    The number of such moves is `popcount(initial_n) - 1`.
//    After these `popcount(initial_n) - 1` moves, the number 'n' will be reduced to its least significant bit (LSB) value from the original number.
//    For example, if initial_n = 132 (10000100_2), popcount = 2.
//    132 -> 4 (1 move). Now n = 4 (00000100_2). This is the LSB of 132.
//    If initial_n = 13 (1101_2), popcount = 3.
//    13 -> 5 (1 move). 5 -> 1 (1 move). Now n = 1 (0001_2). This is the LSB of 13.

// 2. Moves of Type 1 (dividing by 2):
//    Once 'n' has become a power of 2 (which is the LSB of the original 'n'), say 2^j,
//    the game proceeds by repeatedly dividing 'n' by 2 until it reaches 1.
//    This takes 'j' moves.
//    The value 'j' is exactly the number of trailing zeros in the original 'n', which is `__builtin_ctzll(initial_n)`.

// Therefore, the total number of moves is the sum of moves from Phase 1 and Phase 2:
// `total_moves = (popcount(initial_n) - 1) + (__builtin_ctzll(initial_n))`

// Example: n = 132
// popcount(132) = 2 (10000100_2 has two '1's)
// __builtin_ctzll(132) = 2 (10000100_2 has two trailing zeros)
// total_moves = (2 - 1) + 2 = 1 + 2 = 3.
// Since 3 is odd, Louise wins.

// Example: n = 6
// popcount(6) = 2 (110_2 has two '1's)
// __builtin_ctzll(6) = 1 (110_2 has one trailing zero)
// total_moves = (2 - 1) + 1 = 1 + 1 = 2.
// Since 2 is even, Richard wins.

// Edge case: n = 1
// popcount(1) = 1
// __builtin_ctzll(1) = 0
// total_moves = (1 - 1) + 0 = 0.
// Since 0 is even, Richard wins. This matches the problem statement's update.

std::string counterGame(unsigned long long n) {
    // Calculate the total number of moves using the derived formula.
    // __builtin_popcountll(n) counts the number of set bits in 'n'.
    // __builtin_ctzll(n) counts the number of trailing zeros in 'n' (position of LSB).
    long long total_moves = (__builtin_popcountll(n) - 1) + __builtin_ctzll(n);

    // Determine the winner based on the parity of total_moves.
    // Louise wins if total_moves is odd.
    // Richard wins if total_moves is even.
    if (total_moves % 2 == 1) {
        return "Louise";
    } else {
        return "Richard";
    }
}

int main() {
    // Optimize C++ standard streams for faster input/output.
    // This is a common practice in competitive programming to prevent TLE (Time Limit Exceeded)
    // on problems with large I/O.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t; // Number of testcases
    std::cin >> t; // Read the number of testcases

    // Loop through each testcase
    while (t--) {
        unsigned long long n; // Initial game counter value
        std::cin >> n; // Read the initial value for the current game
        std::cout << counterGame(n) << "\n"; // Call the function and print the winner, followed by a newline
    }

    return 0; // Indicate successful execution
}

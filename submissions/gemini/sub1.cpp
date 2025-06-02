#include <iostream> // Required for input/output operations (std::cin, std::cout, std::endl)
#include <vector>   // Not strictly needed for this solution, but often useful
#include <string>   // Required for string manipulation (std::string)
#include <numeric>  // Not strictly needed for this solution, but often useful (e.g., std::accumulate)
#include <algorithm> // Not strictly needed for this solution, but often useful (e.g., std::sort)
#include <cstring>  // Required for std::memset

// Using a 3D array for memoization.
// memo[r][g][b] stores a bitmask representing the set of possible final colors.
// The bitmask uses:
//   1 (binary 001) for Red ('R')
//   2 (binary 010) for Green ('G')
//   4 (binary 100) for Blue ('B')
// A value of -1 indicates that the state has not been computed yet.
int memo[201][201][201]; // Max N is 200, so indices 0-200 are needed.

// Recursive function to determine the possible final colors from a given state.
// r: current count of Red cards
// g: current count of Green cards
// b: current count of Blue cards
int solve(int r, int g, int b) {
    // Base case: If only one card is left, that card's color is the final color.
    // The sum of counts (r + g + b) will be 1.
    if (r + g + b == 1) {
        if (r == 1) return 1; // If the single card is Red, return its bitmask.
        if (g == 1) return 2; // If the single card is Green, return its bitmask.
        if (b == 1) return 4; // If the single card is Blue, return its bitmask.
    }

    // Check if this state has already been computed.
    // If memo[r][g][b] is not -1, it means we've computed it before, so return the stored result.
    if (memo[r][g][b] != -1) {
        return memo[r][g][b];
    }

    // Initialize a bitmask to accumulate all possible final colors from this state.
    int possible_colors_mask = 0;

    // Explore operations that reduce the number of cards by one.
    // Each operation takes two cards and replaces them with one, reducing total count by 1.

    // Operation 1: Take two cards of the same color and exchange them for a new card of that color.
    // This operation reduces the count of one color by 1.
    // Example: R + R -> R (r becomes r-1)
    if (r >= 2) {
        // Recursively call solve for the new state (r-1, g, b) and combine its results
        // using bitwise OR to accumulate all possibilities.
        possible_colors_mask |= solve(r - 1, g, b);
    }
    // G + G -> G (g becomes g-1)
    if (g >= 2) {
        possible_colors_mask |= solve(r, g - 1, b);
    }
    // B + B -> B (b becomes b-1)
    if (b >= 2) {
        possible_colors_mask |= solve(r, g, b - 1);
    }

    // Operation 2: Take two cards of different colors and exchange them for a new card of the third color.
    // This operation reduces the counts of two colors by 1 and increases the count of the third by 1.
    // Example: R + G -> B (r becomes r-1, g becomes g-1, b becomes b+1)
    if (r >= 1 && g >= 1) {
        possible_colors_mask |= solve(r - 1, g - 1, b + 1);
    }
    // R + B -> G (r becomes r-1, b becomes b-1, g becomes g+1)
    if (r >= 1 && b >= 1) {
        possible_colors_mask |= solve(r - 1, g + 1, b - 1);
    }
    // G + B -> R (g becomes g-1, b becomes b-1, r becomes r+1)
    if (g >= 1 && b >= 1) {
        possible_colors_mask |= solve(r + 1, g - 1, b - 1);
    }

    // Memoize the computed result for the current state before returning.
    memo[r][g][b] = possible_colors_mask;
    return possible_colors_mask;
}

int main() {
    // Optimize C++ standard streams for faster input/output operations.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams.
    // std::cin.tie(NULL) prevents std::cout from flushing before each std::cin operation.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n; // Total number of cards.
    std::cin >> n;
    std::string s; // String representing the colors of the cards.
    std::cin >> s;

    // Count the initial number of Red, Green, and Blue cards.
    int initial_r = 0, initial_g = 0, initial_b = 0;
    for (char c : s) {
        if (c == 'R') {
            initial_r++;
        } else if (c == 'G') {
            initial_g++;
        } else { // c == 'B'
            initial_b++;
        }
    }

    // Initialize the memoization table.
    // std::memset sets all bytes in a block of memory to a specified value.
    // Here, it sets all elements of `memo` to -1, indicating they are uncomputed.
    // sizeof(memo) calculates the total size in bytes of the memo array.
    std::memset(memo, -1, sizeof(memo));

    // Call the recursive function with the initial card counts to find all possible final colors.
    int final_mask = solve(initial_r, initial_g, initial_b);

    // Construct the output string based on the `final_mask`.
    // The problem requires the output colors to be in alphabetical order (B, G, R).
    std::string result = "";
    if (final_mask & 4) { // Check if Blue (bit 4) is possible.
        result += 'B';
    }
    if (final_mask & 2) { // Check if Green (bit 2) is possible.
        result += 'G';
    }
    if (final_mask & 1) { // Check if Red (bit 1) is possible.
        result += 'R';
    }
    
    // Print the resulting string of possible final colors.
    std::cout << result << std::endl;

    return 0; // Indicate successful execution.
}
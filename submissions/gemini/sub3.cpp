#include <iostream> // Required for input/output operations (std::cin, std::cout)
#include <string>   // Required for using std::string to build the word
#include <algorithm> // Required for std::min and std::max functions

int main() {
    // Optimize C++ standard streams for competitive programming.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams,
    // which can speed up I/O operations.
    // std::cin.tie(NULL) prevents std::cout from being flushed before each std::cin operation,
    // further improving performance.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int l, w; // Declare integer variables for word length (l) and total weight (w)
    std::cin >> l >> w; // Read the values of l and w from standard input

    // Calculate the minimum possible total weight for a word of length 'l'.
    // This occurs if all 'l' characters are 'a' (weight 1 each).
    // Using long long for calculations involving products to prevent potential overflow,
    // although for given constraints (l <= 40, 26*l <= 1040), int would suffice.
    long long min_possible_w = (long long)l * 1;

    // Calculate the maximum possible total weight for a word of length 'l'.
    // This occurs if all 'l' characters are 'z' (weight 26 each).
    long long max_possible_w = (long long)l * 26;

    // Check if the target weight 'w' is outside the valid range.
    // If 'w' is less than the minimum possible weight or greater than the maximum possible weight,
    // it's impossible to form such a word.
    if (w < min_possible_w || w > max_possible_w) {
        std::cout << "impossible\n"; // Output "impossible" followed by a newline
        return 0; // Terminate the program as no solution exists
    }

    std::string result = ""; // Initialize an empty string to store the constructed word

    // Iterate 'l' times, once for each character position in the word.
    // In each iteration, we determine the character for the current position.
    for (int i = 0; i < l; ++i) {
        // 'chars_left' represents the number of characters remaining to be placed,
        // including the current character being decided.
        int chars_left = l - i;

        // Determine the valid range of weights for the current character.
        // A character's weight must be between 1 ('a') and 26 ('z').
        // Additionally, the remaining weight (w - current_char_weight) must be achievable
        // by the remaining (chars_left - 1) characters.

        // 1. Calculate the maximum possible weight for the current character:
        // The sum of the current character's weight and the minimum possible weight
        // of the remaining (chars_left - 1) characters must not exceed the total remaining weight 'w'.
        // current_char_weight + (chars_left - 1) * 1 <= w
        // current_char_weight <= w - (chars_left - 1) * 1
        // We also cap this at 26 (max weight for 'z').
        int upper_bound_for_current_char = std::min(26, w - (chars_left - 1) * 1);

        // 2. Calculate the minimum possible weight for the current character:
        // The sum of the current character's weight and the maximum possible weight
        // of the remaining (chars_left - 1) characters must be at least the total remaining weight 'w'.
        // current_char_weight + (chars_left - 1) * 26 >= w
        // current_char_weight >= w - (chars_left - 1) * 26
        // We also ensure this is at least 1 (min weight for 'a').
        int lower_bound_for_current_char = std::max(1, w - (chars_left - 1) * 26);

        // To find *any* valid string, we can use a greedy approach.
        // Picking the largest possible character (upper_bound_for_current_char)
        // that satisfies the constraints is a valid greedy strategy.
        // This strategy tends to use up the weight faster, leading to 'z's first,
        // then gradually smaller characters, and finally 'a's if excess weight is used up.
        int char_val = upper_bound_for_current_char;

        // Convert the chosen weight 'char_val' back to its corresponding character.
        // 'a' has a weight of 1, so 'a' + (char_val - 1) gives the correct character.
        result += (char)('a' + char_val - 1);

        // Subtract the weight of the chosen character from the total remaining weight 'w'.
        w -= char_val;
    }

    // After the loop completes, 'result' string contains a word of length 'l'
    // with the target total weight 'w'. Print this result.
    std::cout << result << "\n";

    return 0; // Indicate successful program execution
}
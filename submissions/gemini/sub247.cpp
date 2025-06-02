#include <iostream> // Required for input/output operations (std::cin, std::cout, std::endl)
#include <string>   // Required for std::string
#include <algorithm> // Required for std::max

/**
 * @brief Finds the maximum length of a substring that can be made entirely of 'target_char'
 *        by changing at most 'k' characters.
 *
 * This function uses the two-pointers (sliding window) technique. It expands the window
 * from the right and shrinks it from the left when the condition (flips_needed <= k)
 * is violated.
 *
 * @param n The length of the input string.
 * @param k The maximum number of characters allowed to change.
 * @param s The input string consisting of 'a' and 'b'.
 * @param target_char The character ('a' or 'b') that the substring should consist of.
 * @return The maximum possible length of such a substring.
 */
int solve_for_char(int n, int k, const std::string& s, char target_char) {
    int max_len = 0;      // Stores the maximum length found so far.
    int left = 0;         // The left pointer of the sliding window.
    int flips_needed = 0; // Counts characters within the current window [left, right]
                          // that are not 'target_char' and thus need to be flipped.

    // The right pointer iterates through the string, expanding the window.
    for (int right = 0; right < n; ++right) {
        // If the character at the right pointer is not the target character,
        // it means we need to flip it to make the window uniform.
        if (s[right] != target_char) {
            flips_needed++;
        }

        // If the number of flips required for the current window exceeds 'k',
        // we must shrink the window from the left until the condition is met.
        while (flips_needed > k) {
            // If the character at the left pointer was one that needed a flip,
            // then removing it from the window reduces the 'flips_needed' count.
            if (s[left] != target_char) {
                flips_needed--;
            }
            left++; // Move the left pointer to shrink the window.
        }

        // At this point, the window [left, right] is valid:
        // the number of characters to flip within it is <= k.
        // We update the maximum length found so far.
        max_len = std::max(max_len, right - left + 1);
    }

    return max_len;
}

int main() {
    // Optimize C++ standard streams for faster input/output.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams.
    // std::cin.tie(NULL) prevents std::cout from flushing before std::cin reads input.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, k;
    std::cin >> n >> k; // Read the length of the string (n) and max changes (k).

    std::string s;
    std::cin >> s; // Read the input string.

    // Calculate the maximum beauty if we aim to make a substring of all 'a's.
    int max_beauty_for_a = solve_for_char(n, k, s, 'a');

    // Calculate the maximum beauty if we aim to make a substring of all 'b's.
    int max_beauty_for_b = solve_for_char(n, k, s, 'b');

    // The overall maximum beauty is the greater of the two possibilities.
    std::cout << std::max(max_beauty_for_a, max_beauty_for_b) << std::endl;

    return 0; // Indicate successful execution.
}

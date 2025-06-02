#include <iostream> // Required for input/output operations (std::cin, std::cout)
#include <string>   // Required for string manipulation (std::string)
#include <vector>   // Required for dynamic arrays (std::vector)
#include <algorithm> // Required for std::min
#include <cctype>   // Required for toupper, tolower

int main() {
    // Optimize C++ standard streams for competitive programming.
    // This unties cin/cout from C's stdio and prevents flushing cout before cin.
    std::ios_base::sync_with_stdio(false);
    // This disables synchronization with C's stdio.
    std::cin.tie(NULL);
    // This unties cin from cout, meaning cin will not flush cout before reading input.

    std::string s, t; // Declare strings s and t to store input messages.
    std::cin >> s >> t; // Read the two input strings.

    // Use arrays to store character frequencies.
    // An array of size 256 is sufficient to cover all possible ASCII character values (0-255).
    // Initialize all counts to 0.
    std::vector<int> s_counts(256, 0); // Frequency map for characters in string s.
    std::vector<int> t_counts(256, 0); // Frequency map for characters in string t.

    // Populate s_counts: Iterate through string s and increment count for each character.
    for (char c : s) {
        s_counts[static_cast<unsigned char>(c)]++; // Use static_cast<unsigned char> to ensure character value is treated as a positive index.
    }

    // Populate t_counts: Iterate through string t and increment count for each character.
    for (char c : t) {
        t_counts[static_cast<unsigned char>(c)]++; // Use static_cast<unsigned char> for consistent indexing.
    }

    int yay_count = 0;    // Counter for "YAY!" matches (exact character and case).
    int whoops_count = 0; // Counter for "WHOOPS" matches (correct character, wrong case).

    // First pass: Maximize "YAY!" matches.
    // Iterate through all possible ASCII character values (0 to 255).
    // This ensures we cover both uppercase and lowercase English letters, and any other characters if present (though problem states only English letters).
    for (int i = 0; i < 256; ++i) {
        // The number of exact matches for character 'i' is limited by the minimum of its occurrences in s and t.
        int matches = std::min(s_counts[i], t_counts[i]);
        yay_count += matches; // Add these matches to the total YAY count.
        s_counts[i] -= matches; // Decrement counts in both s_counts and t_counts as these characters are now "used".
        t_counts[i] -= matches;
    }

    // Second pass: Maximize "WHOOPS" matches using remaining characters.
    // Iterate through lowercase English letters ('a' to 'z').
    // For each lowercase letter, check for a match with its uppercase counterpart.
    for (char c = 'a'; c <= 'z'; ++c) {
        // Get the ASCII values for the lowercase and uppercase versions of the current character.
        int lower_idx = static_cast<unsigned char>(c);
        int upper_idx = static_cast<unsigned char>(std::toupper(c)); // std::toupper converts to uppercase.

        // Check for WHOOPS matches where s needs lowercase and t has uppercase.
        // The number of such matches is limited by the minimum of remaining lowercase 'c' in s and remaining uppercase 'C' in t.
        int matches_lower_s_upper_t = std::min(s_counts[lower_idx], t_counts[upper_idx]);
        whoops_count += matches_lower_s_upper_t; // Add to WHOOPS count.
        s_counts[lower_idx] -= matches_lower_s_upper_t; // Decrement counts.
        t_counts[upper_idx] -= matches_lower_s_upper_t;

        // Check for WHOOPS matches where s needs uppercase and t has lowercase.
        // This handles cases like s needs 'A' and t has 'a'.
        // Note: s_counts[upper_idx] might be non-zero if s originally had uppercase characters that weren't YAY-matched.
        // t_counts[lower_idx] might be non-zero if t originally had lowercase characters that weren't YAY-matched.
        int matches_upper_s_lower_t = std::min(s_counts[upper_idx], t_counts[lower_idx]);
        whoops_count += matches_upper_s_lower_t; // Add to WHOOPS count.
        s_counts[upper_idx] -= matches_upper_s_lower_t; // Decrement counts.
        t_counts[lower_idx] -= matches_upper_s_lower_t;
    }

    // Print the final counts of "YAY!" and "WHOOPS".
    std::cout << yay_count << " " << whoops_count << std::endl;

    return 0; // Indicate successful execution.
}
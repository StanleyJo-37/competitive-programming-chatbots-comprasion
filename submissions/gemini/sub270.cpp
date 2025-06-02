#include <string>       // Required for std::string
#include <vector>       // Required for std::vector
#include <algorithm>    // Required for std::sort
#include <cmath>        // Required for std::abs

// Helper function to determine if a character is a vowel.
// Vowels are defined as 'a', 'e', 'i', 'o', 'u'.
bool is_vowel(char c) {
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

// Main function to solve the problem.
std::string solve(const std::string& s) {
    // Step 1: Separate the input string characters into vowels and consonants.
    // Use std::vector<char> to store them, as they can be easily sorted.
    std::vector<char> vowels;
    std::vector<char> consonants;
    for (char c : s) {
        if (is_vowel(c)) {
            vowels.push_back(c);
        } else {
            consonants.push_back(c);
        }
    }

    // Step 2: Sort both lists alphabetically.
    // This is crucial for constructing the lexicographically lowest string.
    std::sort(vowels.begin(), vowels.end());
    std::sort(consonants.begin(), consonants.end());

    // Get the counts of vowels and consonants.
    int num_vowels = vowels.size();
    int num_consonants = consonants.size();

    // Step 3: Check if it's possible to alternate vowels and consonants.
    // Alternation is only possible if the absolute difference between the
    // number of vowels and consonants is 0 or 1. If not, return "failed".
    if (std::abs(num_vowels - num_consonants) > 1) {
        return "failed";
    }

    // Step 4: Determine the starting character type for the alternating string.
    // This depends on the counts of vowels and consonants, and a specific rule.
    bool start_with_vowel;
    if (num_vowels == num_consonants) {
        // Problem rule: if counts are equal, the result must start with a vowel.
        start_with_vowel = true;
    } else if (num_vowels == num_consonants + 1) {
        // If there's one more vowel than consonants, the string must start
        // and end with a vowel to maintain alternation (e.g., V C V C V).
        start_with_vowel = true;
    } else { // This implies num_consonants == num_vowels + 1
        // If there's one more consonant than vowels, the string must start
        // and end with a consonant (e.g., C V C V C).
        start_with_vowel = false;
    }

    // Step 5: Construct the result string by alternating characters.
    std::string result = "";
    // Pre-allocate memory for the result string to improve performance,
    // though not strictly necessary given typical string lengths.
    result.reserve(s.length());

    // Pointers to keep track of the next available vowel and consonant from their sorted lists.
    int v_idx = 0;
    int c_idx = 0;
    // Flag to track whether the current character to be appended should be a vowel.
    bool current_char_is_vowel = start_with_vowel;

    // Iterate through the length of the original string to build the new string.
    for (int i = 0; i < s.length(); ++i) {
        if (current_char_is_vowel) {
            // Append the smallest available vowel.
            result += vowels[v_idx++];
        } else {
            // Append the smallest available consonant.
            result += consonants[c_idx++];
        }
        // Toggle the flag for the next character to ensure alternation.
        current_char_is_vowel = !current_char_is_vowel;
    }

    // Return the constructed lexicographically lowest alternating string.
    return result;
}
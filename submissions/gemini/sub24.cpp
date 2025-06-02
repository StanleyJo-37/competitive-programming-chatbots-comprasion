#include <iostream> // Required for input/output operations (std::cin, std::cout, std::endl)
#include <string>   // Required for using std::string
#include <vector>   // Not strictly necessary for this problem, but often useful in competitive programming
#include <algorithm> // Required for std::fill

// Helper function to determine if a character is a vowel.
// Vowels are defined as 'a', 'e', 'i', 'o', 'u'. All other letters are consonants.
bool is_vowel(char c) {
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

int main() {
    // Optimize C++ standard streams for faster input/output.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams.
    // std::cin.tie(NULL) prevents std::cout from flushing before std::cin reads input.
    // These are common competitive programming optimizations for performance.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::string s; // Declare a string to store the input word.
    std::cin >> s; // Read the input word from standard input.

    std::string result = ""; // Initialize an empty string to build the modified word(s).

    int consonant_count = 0; // Tracks the number of consecutive consonants in the current block.
    
    // `seen_consonants` is a boolean array to keep track of distinct consonants
    // encountered in the current consecutive consonant block.
    // `seen_consonants[0]` corresponds to 'a', `seen_consonants[1]` to 'b', and so on.
    bool seen_consonants[26]; 
    int distinct_consonant_count = 0; // Counts how many unique consonants are in the current block.

    // Initialize the `seen_consonants` array to all false.
    // This ensures a clean state for the first consonant block.
    std::fill(seen_consonants, seen_consonants + 26, false);

    // Iterate through each character of the input string.
    // This loop processes the string character by character to identify and fix typos.
    for (int i = 0; i < s.length(); ++i) {
        char current_char = s[i]; // Get the current character.

        if (is_vowel(current_char)) {
            // If the current character is a vowel, it breaks any ongoing consonant sequence.
            // Therefore, reset the consonant count and distinct consonant tracking.
            consonant_count = 0;
            distinct_consonant_count = 0;
            // Reset the `seen_consonants` array for the new (or continued) word segment.
            std::fill(seen_consonants, seen_consonants + 26, false); 
            
            // Append the vowel to the result string.
            result += current_char;
        } else {
            // If the current character is a consonant.
            consonant_count++; // Increment the count of consecutive consonants.

            // Check if this consonant has been seen in the current block.
            // If not, mark it as seen and increment the distinct consonant count.
            if (!seen_consonants[current_char - 'a']) {
                seen_consonants[current_char - 'a'] = true;
                distinct_consonant_count++;
            }

            // Check for a typo condition based on the problem definition:
            // 1. `consonant_count >= 3`: There are three or more consecutive consonants.
            // 2. `distinct_consonant_count >= 2`: There are at least two different letters in this consonant block.
            //    This condition handles the exception: if all letters are the same, it's not a typo.
            if (consonant_count >= 3 && distinct_consonant_count >= 2) {
                // A typo is detected.
                // To fix it with the minimum number of spaces, we insert a space
                // just before the current character `s[i]`. This means the word
                // segment ending at `s[i-1]` is considered a valid word, and
                // a new word starts with `s[i]`. This is a greedy approach.
                result += ' '; // Add a space to the result string.
                
                // Reset consonant tracking for the new word segment starting with `current_char`.
                // The `current_char` is now the first consonant of this new block.
                consonant_count = 1; 
                distinct_consonant_count = 0;
                // Clear the `seen_consonants` array for the new block.
                std::fill(seen_consonants, seen_consonants + 26, false); 
                // Mark `current_char` as seen in the new block and update its distinct count.
                seen_consonants[current_char - 'a'] = true; 
                distinct_consonant_count = 1; 
            }
            // Append the current consonant to the result string, whether a space was inserted or not.
            result += current_char;
        }
    }

    // Print the final result string, followed by a newline.
    std::cout << result << std::endl;

    return 0; // Indicate successful execution.
}

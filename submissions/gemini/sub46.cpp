#include <iostream> // Required for input/output operations (std::cin, std::cout, std::endl)
#include <string>   // Required for string manipulation (std::string)
#include <vector>   // Not strictly necessary for this solution, but often useful
#include <algorithm> // Required for std::reverse (used in isPalindrome)

// Function to check if a given string is a palindrome.
// A palindrome reads the same forwards and backwards.
bool isPalindrome(const std::string& s) {
    // Create a reversed copy of the input string.
    std::string reversed_s = s;
    std::reverse(reversed_s.begin(), reversed_s.end()); // Reverse the copy in-place.
    // Compare the original string with its reversed copy.
    // If they are identical, the string is a palindrome.
    return s == reversed_s;
}

int main() {
    // Optimize C++ standard streams for competitive programming.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams,
    // which can speed up I/O operations.
    // std::cin.tie(NULL) prevents std::cout from being flushed before each std::cin operation,
    // further improving I/O performance.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::string s;
    std::cin >> s; // Read the input string from standard input.

    int n = s.length(); // Get the length of the input string.
    // Initialize the string to store the lexicographically largest palindromic subsequence found so far.
    // It's initialized to an empty string, which is lexicographically smaller than any non-empty string.
    std::string max_palindromic_subsequence = "";

    // Iterate through all possible non-empty subsequences of the input string.
    // This is done using a bitmask approach. Each integer 'i' from 1 to (2^n - 1)
    // represents a unique combination of characters to form a subsequence.
    // If the j-th bit of 'i' is set (1), it means the character s[j] is included in the subsequence.
    // The loop starts from 1 to ensure that only non-empty subsequences are considered.
    for (int i = 1; i < (1 << n); ++i) {
        std::string current_subsequence = ""; // String to build the current subsequence.

        // Iterate through each character of the original string 's'.
        for (int j = 0; j < n; ++j) {
            // Check if the j-th bit is set in the current bitmask 'i'.
            // (i >> j) shifts the bits of 'i' to the right by 'j' positions,
            // bringing the j-th bit to the least significant position.
            // & 1 then checks if this bit is 1.
            if ((i >> j) & 1) {
                current_subsequence += s[j]; // If the bit is set, append s[j] to the subsequence.
            }
        }

        // After building the current subsequence, check if it is a palindrome.
        if (isPalindrome(current_subsequence)) {
            // If it is a palindrome, compare it lexicographically with the
            // 'max_palindromic_subsequence' found so far.
            // std::string::operator> performs lexicographical comparison.
            // A string 'x' is lexicographically larger than 'y' if:
            // 1. 'y' is a prefix of 'x' and 'x' is longer (e.g., "poster" > "post").
            // 2. At the first differing character position, 'x' has a character
            //    with a greater ASCII value than 'y' (e.g., "ranger" > "racecar" because 'n' > 'c').
            if (current_subsequence > max_palindromic_subsequence) {
                max_palindromic_subsequence = current_subsequence; // Update if the current subsequence is larger.
            }
        }
    }

    // Print the lexicographically largest palindromic subsequence found.
    std::cout << max_palindromic_subsequence << std::endl;

    return 0; // Indicate successful execution.
}
#include <string> // Required for std::string

// Function to check if a given string represents an 8-bit signed integer
// in its canonical representation.
// An 8-bit signed integer ranges from -128 to 127.
// Canonical representation means:
// - No leading '+' (e.g., "+1" is false).
// - No extra '0's (e.g., "01", "-007" are false; "0" is true).
// - No spaces or other non-digit characters (except for an optional leading '-').
bool isSignedEightBitNumber(const std::string& s) {
    // 1. Handle empty string: An empty string cannot represent a number.
    if (s.empty()) {
        return false;
    }

    // 2. Check for leading '+': Canonical representation does not allow a leading '+'.
    if (s[0] == '+') {
        return false;
    }

    // 3. Determine the sign and the starting index for parsing digits.
    long long sign = 1; // Default to positive
    int startIndex = 0; // Default start index for digits

    // If the first character is '-', it indicates a negative number.
    if (s[0] == '-') {
        sign = -1; // Set the sign to negative
        startIndex = 1; // Start parsing digits from the second character

        // If the string is just "-", it's not a valid number.
        if (s.length() == 1) {
            return false;
        }
    }

    // 4. Handle leading zeros for non-zero numbers (canonical check).
    // If the first digit character is '0' and there are more characters after it,
    // it's a non-canonical leading zero (e.g., "01", "-01", "00").
    // "0" and "-0" are considered canonical and are handled correctly by subsequent logic.
    if (s[startIndex] == '0' && s.length() > startIndex + 1) {
        return false;
    }

    // 5. Parse the absolute value of the number.
    long long num = 0; // Stores the absolute value of the parsed number

    // Iterate through the string from the determined startIndex to the end.
    for (int i = startIndex; i < s.length(); ++i) {
        char c = s[i];

        // Check if the current character is a digit ('0' through '9').
        // If not, it's an invalid character (e.g., space, letter, punctuation).
        if (c < '0' || c > '9') {
            return false;
        }

        int digit = c - '0'; // Convert the character digit to its integer value

        // Early check for potential overflow of the absolute value.
        // An 8-bit signed integer has a maximum absolute value of 128 (for -128).
        // If `num` (the absolute value being built) is already greater than 12,
        // then `num * 10` will be at least 130, which is already too large.
        // If `num` is exactly 12, and the current `digit` is greater than 8,
        // then `12 * 10 + digit` will be `120 + digit`, which will exceed 128.
        // For example, if `num` is 12 and `digit` is 9, `num` would become 129.
        // This check prevents `num` from exceeding 128 during parsing, optimizing early exit.
        if (num > 12 || (num == 12 && digit > 8)) {
            return false; // The absolute value will exceed 128
        }

        // Accumulate the digit to form the number.
        num = num * 10 + digit;
    }

    // 6. Calculate the final signed number.
    long long final_num = sign * num;

    // 7. Final range check: Ensure the number is within the valid range for an 8-bit signed integer.
    // The range is from -128 to 127, inclusive.
    return final_num >= -128 && final_num <= 127;
}
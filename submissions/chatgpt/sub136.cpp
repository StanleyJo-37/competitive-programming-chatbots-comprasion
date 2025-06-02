#include <iostream>
#include <string>
#include <cctype>

// Returns true if the input string is a canonical 8-bit signed integer representation (-128 to 127)
bool isSignedEightBitNumber(const std::string& s) {
    // Empty string is not valid
    if (s.empty()) return false;

    // Check for leading or trailing spaces (not allowed)
    if (s.front() == ' ' || s.back() == ' ') return false;

    // Only '-' is allowed as a sign, and only at the first position
    size_t i = 0;
    bool negative = false;
    if (s[0] == '-') {
        negative = true;
        i = 1;
        // String must have at least one digit after '-'
        if (s.size() == 1) return false;
    }

    // No leading '+'
    if (s[0] == '+') return false;

    // No leading zeros allowed (except for "0" itself or "-0")
    if (i < s.size() && s[i] == '0') {
        // "0" is allowed, "-0" is not canonical
        if (s.size() - i > 1) return false;
        if (negative) return false;
    }

    // All remaining characters must be digits
    for (; i < s.size(); ++i) {
        if (!isdigit(s[i])) return false;
    }

    // Convert string to integer safely
    // We do not use stoi directly to avoid exceptions and to check for overflow
    int num = 0;
    i = negative ? 1 : 0;
    for (; i < s.size(); ++i) {
        int digit = s[i] - '0';
        // Check for overflow before multiplying/adding
        if (negative) {
            if (num < (INT_MIN + digit) / 10) return false;
            num = num * 10 - digit;
        } else {
            if (num > (INT_MAX - digit) / 10) return false;
            num = num * 10 + digit;
        }
    }

    // Check 8-bit signed integer range
    if (num < -128 || num > 127) return false;

    return true;
}

// For testing
int main() {
    std::string test_cases[] = {
        "0", "127", "-128", "128", "-129", "001", "+1", " 1", "1 ", "-0", "-01", "42", "-42", "000", "12a", "", "-", "1.0"
    };
    for (const auto& s : test_cases) {
        std::cout << "\"" << s << "\": " << (isSignedEightBitNumber(s) ? "true" : "false") << std::endl;
    }
    return 0;
}
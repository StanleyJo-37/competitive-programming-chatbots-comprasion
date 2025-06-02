#include <string>
#include <regex>

class StringUtils {
public:
    static bool isSignedEightBitNumber(const std::string &s) {
        // The regex checks for:
        // 1. Optional '-' followed by a digit (1-9) and optional more digits (0-9)
        // 2. Or just '0' (no leading zeros allowed)
        // The entire string must match the pattern (no extra characters)
        // The value must be within -128 to 127
        std::regex pattern("^-?(12[0-7]|1[01][0-9]|[1-9][0-9]?|0)$|^-(128|1[0-2][0-9]|[1-9][0-9]?)$");
        
        if (!std::regex_match(s, pattern)) {
            return false;
        }
        
        // If the string passes regex, parse it to ensure it's within the 8-bit signed range
        try {
            int num = std::stoi(s);
            return num >= -128 && num <= 127;
        } catch (...) {
            // stoi can throw for very large numbers (though regex should prevent this)
            return false;
        }
    }
};
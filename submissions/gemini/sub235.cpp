#include <iostream> // Required for input/output operations (cin, cout).
#include <string>   // Required for string manipulation.

int main() {
    // Optimize C++ standard streams for competitive programming.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams,
    // which can speed up I/O operations.
    // std::cin.tie(NULL) prevents cin from flushing cout before each input operation,
    // further improving I/O performance.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::string s; // Declare a string variable to store the input text.
    std::cin >> s; // Read the entire input string.

    // Use long long for the total count of powerful substrings.
    // The maximum possible count can be (N/5) * (N/5) for N=10^6,
    // which is (10^6/5)^2 = (2*10^5)^2 = 4*10^10.
    // This value exceeds the maximum capacity of a 32-bit integer (approx 2*10^9),
    // but fits within a 64-bit integer (long long, approx 9*10^18).
    long long total_powerful_substrings = 0;

    // This variable keeps track of the number of "heavy" occurrences encountered so far.
    // It is also of type long long because it can grow up to N/5 (2*10^5),
    // which is then added to total_powerful_substrings.
    long long current_heavy_count = 0;

    int n = s.length(); // Get the length of the input string.

    // Iterate through the string to find occurrences of "heavy" and "metal".
    // The loop runs up to `n - 5` because we are checking substrings of length 5.
    // If `i` is the starting index, the substring ends at `i+4`.
    // So, `i+4` must be less than `n`. This means `i < n-4`, or `i <= n-5`.
    for (int i = 0; i <= n - 5; ++i) {
        // Check if the substring starting at `i` is "heavy".
        // Direct character comparison `s[i] == 'h' && s[i+1] == 'e' ...` is used
        // instead of `s.substr(i, 5) == "heavy"` for performance reasons,
        // as it avoids creating temporary string objects.
        if (s[i] == 'h' && s[i+1] == 'e' && s[i+2] == 'a' && s[i+3] == 'v' && s[i+4] == 'y') {
            current_heavy_count++; // If "heavy" is found, increment its count.
        }

        // Check if the substring starting at `i` is "metal".
        if (s[i] == 'm' && s[i+1] == 'e' && s[i+2] == 't' && s[i+3] == 'a' && s[i+4] == 'l') {
            // If "metal" is found, it means we have a potential ending for powerful substrings.
            // Any "heavy" occurrence found *before* this "metal" (i.e., counted in `current_heavy_count`)
            // can form a powerful substring with this "metal" occurrence.
            // The problem defines a powerful substring as starting with "heavy" and ending with "metal".
            // This implies that the "heavy" part must entirely precede the "metal" part.
            // For example, if "heavy" starts at `h_idx` and "metal" starts at `m_idx`,
            // then `h_idx + 4` (end of "heavy") must be less than `m_idx` (start of "metal").
            // Since "heavy" and "metal" are distinct 5-character words, they cannot overlap
            // in a way that `h_idx + 4 >= m_idx` while both are present.
            // The minimum `m_idx` for a "metal" to follow a "heavy" at `h_idx` is `h_idx + 5`.
            // In this case, `h_idx + 4 < h_idx + 5` is true.
            // Therefore, `current_heavy_count` correctly represents the number of valid "heavy" prefixes
            // that can pair with the current "metal" suffix to form a powerful substring.
            total_powerful_substrings += current_heavy_count;
        }
    }

    // Print the final calculated count of powerful substrings.
    std::cout << total_powerful_substrings << std::endl;

    return 0; // Indicate successful program execution.
}
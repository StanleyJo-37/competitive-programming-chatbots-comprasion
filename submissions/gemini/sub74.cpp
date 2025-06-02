#include <iostream> // Required for input/output operations (std::cin, std::cout, std::endl).
#include <vector>   // Required for std::vector, a dynamic array.
#include <string>   // Required for std::string.
#include <algorithm> // Required for std::min and std::max.

// Define a constant for the modulo operation.
// This is used for counting the number of ways to prevent integer overflow.
const int MOD = 1e9 + 7;

// Define a constant for infinity.
// Used to initialize dp_min_count values to a very large number,
// ensuring that any valid path will result in a smaller count.
// N can be up to 1000, so N+1 is a safe upper bound for min substrings.
const int INF_COUNT = 1001; // N_max + 1

int main() {
    // Optimize C++ standard streams for faster input/output.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams.
    // std::cin.tie(NULL) prevents std::cout from flushing before std::cin reads input.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n; // Length of the message string.
    std::cin >> n;
    std::string s; // The message string.
    std::cin >> s;
    std::vector<int> a(26); // Array storing max allowed length for each character ('a' through 'z').
    for (int i = 0; i < 26; ++i) {
        std::cin >> a[i];
    }

    // dp_ways[i] stores the number of ways to split the prefix s[0...i-1]
    // into valid substrings.
    std::vector<int> dp_ways(n + 1, 0);
    // dp_min_count[i] stores the minimum number of substrings required to split
    // the prefix s[0...i-1] into valid substrings.
    std::vector<int> dp_min_count(n + 1, INF_COUNT);

    // Base cases:
    // An empty prefix (length 0) has one way to be split (no substrings),
    // and requires 0 substrings.
    dp_ways[0] = 1;
    dp_min_count[0] = 0;

    // max_overall_len stores the maximum length of any valid substring
    // that can appear in *any* valid splitting of the entire string s.
    int max_overall_len = 0;

    // Iterate through all possible end positions for the current prefix.
    // 'i' represents the length of the current prefix s[0...i-1].
    // It also represents the current index in the dp arrays.
    for (int i = 1; i <= n; ++i) {
        // current_min_allowed_len_for_suffix tracks the minimum allowed length
        // for any character encountered in the current suffix s[j...i-1].
        // Initialize with a large value (n + 1 is safe as max length is n).
        int current_min_allowed_len_for_suffix = n + 1;

        // Iterate backwards from j = i-1 down to 0.
        // This loop considers s[j...i-1] as the last substring of the current prefix.
        // 'j' represents the starting index of this last substring.
        for (int j = i - 1; j >= 0; --j) {
            // Update the minimum allowed length based on the character s[j].
            // s[j] is the character at the current starting position of the substring.
            current_min_allowed_len_for_suffix = std::min(current_min_allowed_len_for_suffix, a[s[j] - 'a']);
            
            // Calculate the length of the current substring s[j...i-1].
            int current_substring_length = i - j;

            // Check if the current substring s[j...i-1] is valid.
            // A substring is valid if its length is less than or equal to
            // the minimum allowed length for all characters within it.
            if (current_substring_length > current_min_allowed_len_for_suffix) {
                // If the current substring s[j...i-1] is invalid,
                // any longer substring ending at i-1 (i.e., s[k...i-1] where k < j)
                // will also contain s[j...i-1] and be even longer.
                // Thus, it will also be invalid. So, we can stop checking
                // further substrings ending at i-1 for this 'i'.
                break;
            }

            // If s[j...i-1] is a valid substring, we can potentially form
            // a valid splitting of s[0...i-1] by appending s[j...i-1]
            // to a valid splitting of s[0...j-1].
            // We only consider paths from valid previous states (dp_ways[j] > 0).
            // If dp_ways[j] is 0, it means s[0...j-1] cannot be validly split,
            // so s[j...i-1] cannot extend a valid split to s[0...i-1].
            if (dp_ways[j] > 0) {
                // Update the number of ways:
                // Add the ways to split s[0...j-1] (dp_ways[j]) to dp_ways[i].
                dp_ways[i] = (dp_ways[i] + dp_ways[j]) % MOD;

                // Update the maximum length of a substring:
                // The current substring s[j...i-1] is valid and is part of a valid splitting
                // (since dp_ways[j] > 0 implies s[0...j-1] can be split).
                // So, its length is a candidate for the overall maximum.
                max_overall_len = std::max(max_overall_len, current_substring_length);

                // Update the minimum number of substrings:
                // If we split s[0...j-1] into dp_min_count[j] substrings,
                // and then add s[j...i-1] as one more substring,
                // we get dp_min_count[j] + 1 substrings for s[0...i-1].
                // We take the minimum over all valid choices of j.
                dp_min_count[i] = std::min(dp_min_count[i], dp_min_count[j] + 1);
            }
        }
    }

    // Print the final results for the entire string s (length n).
    // 1. Number of ways to split the message.
    std::cout << dp_ways[n] << std::endl;
    // 2. Maximum length of a substring that can appear in some valid splitting.
    std::cout << max_overall_len << std::endl;
    // 3. Minimum number of substrings the message can be split into.
    std::cout << dp_min_count[n] << std::endl;

    return 0; // Indicate successful execution.
}

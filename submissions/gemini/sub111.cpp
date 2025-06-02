#include <iostream> // Required for input/output operations (std::cin, std::cout)
#include <vector>   // Required for std::vector to store hashtags
#include <string>   // Required for std::string to handle hashtags
#include <algorithm> // Required for std::min function

int main() {
    // Optimize C++ standard streams for competitive programming.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams,
    // which can significantly speed up I/O operations.
    std::ios_base::sync_with_stdio(false);
    // std::cin.tie(NULL) unties std::cin from std::cout. By default, std::cin flushes std::cout
    // before each input operation. Untying them prevents this, further speeding up I/O.
    std::cin.tie(NULL);

    int n;
    std::cin >> n; // Read the number of hashtags.

    // Declare a vector of strings to store all hashtags.
    // Each string will include the leading '#' character.
    std::vector<std::string> hashtags(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> hashtags[i]; // Read each hashtag from input.
    }

    // Iterate through the hashtags from right to left (from n-2 down to 0).
    // This backward iteration is crucial because the decision for hashtags[i]
    // depends on the already processed (and potentially modified) hashtags[i+1].
    // The last hashtag (hashtags[n-1]) does not need to be modified as there's
    // no subsequent hashtag to compare it with.
    for (int i = n - 2; i >= 0; --i) {
        // Get references to the current hashtag and the next hashtag.
        // Using const references avoids unnecessary copying and improves performance.
        const std::string& current_hashtag = hashtags[i];
        const std::string& next_hashtag = hashtags[i+1];

        // Calculate the effective lengths of the string parts (excluding '#').
        // The actual string content starts from index 1.
        int current_len = current_hashtag.length() - 1; // Length of string part of current_hashtag
        int next_len = next_hashtag.length() - 1;       // Length of string part of next_hashtag

        // `new_string_part_len` will store the desired length of the string part
        // for `current_hashtag` after potential truncation.
        // Initialize it to its original length, assuming no truncation is needed initially.
        int new_string_part_len = current_len;

        // Compare characters of the string parts from left to right.
        // `k` represents the 0-indexed position within the string part (after '#').
        // The loop runs up to the length of the shorter string part.
        for (int k = 0; k < std::min(current_len, next_len); ++k) {
            // Compare characters at actual index `k+1` in the full hashtag string.
            if (current_hashtag[k+1] < next_hashtag[k+1]) {
                // If the current hashtag's character is lexicographically smaller,
                // then `current_hashtag` is already lexicographically smaller than `next_hashtag`.
                // No truncation is needed for `current_hashtag` to satisfy the order.
                // `new_string_part_len` remains `current_len`.
                break; // Exit the loop as the order is already satisfied.
            } else if (current_hashtag[k+1] > next_hashtag[k+1]) {
                // If the current hashtag's character is lexicographically larger,
                // then `current_hashtag` is currently lexicographically greater than `next_hashtag`.
                // To satisfy the lexicographical order (current_hashtag <= next_hashtag),
                // `current_hashtag` must be truncated. The longest possible prefix that
                // satisfies the condition is the prefix up to position `k`.
                // So, the new length of the string part will be `k`.
                new_string_part_len = k;
                break; // Truncation length determined, exit the loop.
            }
            // If `current_hashtag[k+1] == next_hashtag[k+1]`, characters are equal.
            // Continue to the next character to find a difference or reach end of string.
        }

        // After the loop, if no `break` occurred, it means the common prefix
        // of `current_hashtag` and `next_hashtag` (up to the length of the shorter string)
        // is identical.
        // In this scenario, `new_string_part_len` would still be `current_len`.
        // We need to handle the case where `next_hashtag` is a prefix of `current_hashtag`
        // and `current_hashtag` is longer (e.g., #bigtown vs #big).
        // In such a case, `current_hashtag` is lexicographically greater and must be
        // truncated to match `next_hashtag`'s length.
        if (new_string_part_len == current_len && current_len > next_len) {
            new_string_part_len = next_len;
        }
        // If `new_string_part_len` is still `current_len` and `current_len <= next_len`,
        // it means `current_hashtag` is a prefix of `next_hashtag` or they are equal.
        // In this case, `current_hashtag` is already lexicographically not greater,
        // so no truncation is needed, and `new_string_part_len` correctly remains `current_len`.

        // Apply the determined truncation to the current hashtag.
        // `substr(0, new_string_part_len + 1)` creates a new string starting from index 0
        // (to include '#') and having a total length of `new_string_part_len + 1`.
        hashtags[i] = current_hashtag.substr(0, new_string_part_len + 1);
    }

    // Print all the modified hashtags, each on a new line.
    for (int i = 0; i < n; ++i) {
        std::cout << hashtags[i] << "\n";
    }

    return 0; // Indicate successful program execution.
}
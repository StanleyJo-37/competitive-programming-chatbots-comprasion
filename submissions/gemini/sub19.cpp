#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // For std::reverse

// Function to check if a character is a lowercase Latin letter.
// This function is not strictly needed as the problem statement implies
// characters are either lowercase letters or periods.
// The prefix sum approach for dots implicitly handles this.
/*
bool is_lowercase_letter(char c) {
    return c >= 'a' && c <= 'z';
}
*/

int main() {
    // Optimize C++ standard streams for competitive programming.
    // This unties cin/cout from C standard streams and disables synchronization,
    // leading to faster input/output operations.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::string s;
    std::cin >> s;

    int n = s.length();

    // dp[i] will be true if the prefix s[0...i-1] can be partitioned into valid filenames.
    // The dp array is of size n+1, where dp[0] serves as the base case for an empty prefix,
    // indicating that an empty string can be "partitioned" (trivially).
    std::vector<bool> dp(n + 1, false);
    dp[0] = true;

    // parent[i] stores the starting index 'j' of the last filename s[j...i-1]
    // if dp[i] is true. This array is used to reconstruct the sequence of filenames
    // once a valid partition is found. Initialized to -1 to indicate no parent yet.
    std::vector<int> parent(n + 1, -1);

    // is_dot_prefix_sum[k] stores the count of '.' characters in the prefix s[0...k-1].
    // This array allows for O(1) checks to determine if a substring s[A...B] contains any dots.
    // If is_dot_prefix_sum[B+1] - is_dot_prefix_sum[A] == 0, it means there are no dots
    // in s[A...B]. Since the input string only contains lowercase letters and periods,
    // this implies s[A...B] consists solely of lowercase letters.
    std::vector<int> is_dot_prefix_sum(n + 1, 0);
    for (int k = 0; k < n; ++k) {
        is_dot_prefix_sum[k + 1] = is_dot_prefix_sum[k] + (s[k] == '.' ? 1 : 0);
    }

    // Iterate through all possible ending positions 'i' for a filename.
    // 'i' represents the length of the prefix s[0...i-1] that we are trying to partition.
    for (int i = 1; i <= n; ++i) {
        // Iterate through all possible lengths 'len' for the current filename.
        // A valid BerFS filename has a total length between 3 (e.g., "a.b") and 12 (e.g., "aaaaaaaa.bbb") characters.
        for (int len = 3; len <= 12; ++len) {
            // Calculate the starting index 'j' of the current candidate filename.
            // The candidate filename is the substring s[j...i-1].
            int j = i - len;

            // If 'j' is less than 0, it means the current length 'len' is too large
            // to form a filename ending at index i-1 (i.e., the filename would start before index 0).
            // Also, if dp[j] is false, it means the prefix s[0...j-1] cannot be partitioned into valid filenames,
            // so we cannot extend a valid partition from this point.
            if (j < 0 || !dp[j]) {
                continue;
            }

            // The current candidate filename is s[j...i-1].
            // We need to find a dot within this substring that satisfies the filename rules.
            // The dot must be at s[dot_pos].
            // The 'name' part (s[j...dot_pos-1]) must have length 1 to 8.
            // This implies j+1 <= dot_pos <= j+8.
            // The 'extension' part (s[dot_pos+1...i-1]) must have length 1 to 3.
            // This implies (i-1)-3 <= dot_pos <= (i-1)-1, which simplifies to i-4 <= dot_pos <= i-2.
            // Combining these, dot_pos must be in the range [max(j+1, i-4), min(j+8, i-2)].
            // This loop iterates at most 3 times, making the check very efficient.
            for (int dot_pos = std::max(j + 1, i - 4); dot_pos <= std::min(j + 8, i - 2); ++dot_pos) {
                // Check if the character at the current dot_pos is indeed a period.
                if (s[dot_pos] == '.') {
                    int name_len = dot_pos - j; // Length of the 'name' part
                    int ext_len = (i - 1) - dot_pos; // Length of the 'extension' part

                    // Check if both name_len and ext_len are within their specified valid ranges.
                    if (name_len >= 1 && name_len <= 8 && ext_len >= 1 && ext_len <= 3) {
                        // Use the precomputed prefix sums to check if the 'name' part
                        // (s[j...dot_pos-1]) contains only lowercase letters (i.e., no dots).
                        bool name_all_lower = (is_dot_prefix_sum[dot_pos] - is_dot_prefix_sum[j] == 0);

                        // Use prefix sums to check if the 'extension' part
                        // (s[dot_pos+1...i-1]) contains only lowercase letters (i.e., no dots).
                        bool ext_all_lower = (is_dot_prefix_sum[i] - is_dot_prefix_sum[dot_pos + 1] == 0);

                        if (name_all_lower && ext_all_lower) {
                            // If all conditions are met, s[j...i-1] is a valid filename.
                            // Mark dp[i] as true, indicating that the prefix s[0...i-1] can be partitioned.
                            // Store 'j' in parent[i] to record the start of this valid filename for reconstruction.
                            dp[i] = true;
                            parent[i] = j;
                            // Since we found a valid partition for dp[i], we can stop searching for other
                            // filenames ending at i-1 and move to the next 'i'. Any valid partition is acceptable.
                            goto next_i_loop; // Use goto to break out of both inner loops.
                        }
                    }
                }
            }
        }
        next_i_loop:; // Label for the goto statement.
    }

    // After filling the DP table, check if the entire string s (up to index n-1) can be partitioned.
    if (dp[n]) {
        std::cout << "YES\n";
        std::vector<std::string> result_filenames;
        int current_idx = n;
        // Reconstruct the path by backtracking from dp[n] to dp[0] using the parent array.
        while (current_idx > 0) {
            int prev_idx = parent[current_idx];
            // Extract the filename substring s[prev_idx...current_idx-1]
            result_filenames.push_back(s.substr(prev_idx, current_idx - prev_idx));
            current_idx = prev_idx; // Move to the start of the current filename for the next iteration.
        }
        // The filenames were added to the vector in reverse order of their appearance in 's'.
        // Reverse the vector to get them in the correct chronological order.
        std::reverse(result_filenames.begin(), result_filenames.end());
        // Print each filename on a new line.
        for (const std::string& filename : result_filenames) {
            std::cout << filename << "\n";
        }
    } else {
        // If dp[n] is false, no valid partition exists for the entire string.
        std::cout << "NO\n";
    }

    return 0;
}

#include <iostream> // Required for input/output operations (cin, cout)
#include <string>   // Required for string manipulation (std::string)
#include <vector>   // Required for dynamic arrays (std::vector)

int main() {
    // Optimize C++ standard streams for competitive programming.
    // This unties cin from cout and disables synchronization with C's stdio,
    // which can significantly speed up I/O operations.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::string s1, s2;
    std::cin >> s1 >> s2; // Read the two input strings

    int n1 = s1.length(); // Length of the heading string s1
    int n2 = s2.length(); // Length of the target word s2

    // Pre-check: Determine if all characters in s2 are present in s1.
    // If s2 contains a character not found in s1, it's impossible to form s2.
    // Use a boolean array for quick lookup of character presence.
    std::vector<bool> s1_has_char(26, false); // Initialize all to false
    for (char c : s1) {
        s1_has_char[c - 'a'] = true; // Mark character as present in s1
    }

    for (char c : s2) {
        if (!s1_has_char[c - 'a']) {
            // If any character in s2 is not in s1, print -1 and exit.
            std::cout << -1 << std::endl;
            return 0;
        }
    }

    // Precompute `next_pos` table:
    // `next_pos[char_code][s1_idx]` stores the smallest index `k >= s1_idx`
    // such that `s1[k]` is the character corresponding to `char_code`.
    // `char_code` is `0` for 'a', `1` for 'b', ..., `25` for 'z'.
    // The table size is 26 (for characters) by `n1 + 1` (for indices 0 to n1).
    // `n1` as a value in the table indicates that the character is not found
    // from that `s1_idx` onwards within the current `s1` copy.
    std::vector<std::vector<int>> next_pos(26, std::vector<int>(n1 + 1, n1));

    // Populate `next_pos` table by iterating backwards through s1.
    // This allows us to easily inherit values from `i+1`.
    for (int i = n1 - 1; i >= 0; --i) {
        // For each character 'a' through 'z':
        for (int char_code = 0; char_code < 26; ++char_code) {
            // Inherit the next position from the index `i+1`.
            // This means if char_code is not found at `s1[i]`, its next occurrence
            // from `i` is the same as its next occurrence from `i+1`.
            next_pos[char_code][i] = next_pos[char_code][i + 1];
        }
        // Update the entry for the character actually at `s1[i]`.
        // Its next occurrence from `i` is `i` itself.
        next_pos[s1[i] - 'a'][i] = i;
    }

    // Main logic: Greedily match characters of s2.
    int copies = 1;     // Start with 1 copy of s1
    int s1_ptr = 0;     // Current index in the virtual concatenated s1 string (within current copy)
    int s2_ptr = 0;     // Current index in s2

    while (s2_ptr < n2) {
        // Get the character code for the current character in s2.
        int char_to_find = s2[s2_ptr] - 'a';

        // Find the next occurrence of `char_to_find` in s1, starting from `s1_ptr`.
        int found_idx = next_pos[char_to_find][s1_ptr];

        if (found_idx == n1) {
            // If `found_idx` is `n1`, it means the character `s2[s2_ptr]`
            // is not found in the current `s1` copy from `s1_ptr` onwards.
            // We need to use a new copy of s1.
            copies++;           // Increment the count of s1 copies
            s1_ptr = 0;         // Reset s1_ptr to the beginning of the new s1 copy
            
            // Now, find the character from the beginning of the new s1 copy.
            // Based on the initial `s1_has_char` check, this will always find a valid index.
            found_idx = next_pos[char_to_find][s1_ptr];
            // No need to check found_idx == n1 again here, as it's guaranteed to be found.
        }

        // Move `s1_ptr` past the found character.
        // `found_idx` is the index in s1 where `s2[s2_ptr]` was matched.
        // The next search in s1 should start from `found_idx + 1`.
        s1_ptr = found_idx + 1;
        
        // Move to the next character in s2.
        s2_ptr++;
    }

    // After matching all characters of s2, print the total number of s1 copies used.
    std::cout << copies << std::endl;

    return 0; // Indicate successful execution
}
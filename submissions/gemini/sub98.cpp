#include <iostream> // Required for input/output operations (cin, cout)
#include <string>   // Required for string manipulation
#include <vector>   // Required for dynamic arrays (vector)
#include <numeric>  // Required for iota (though not strictly necessary, can use a loop)

// Function to solve a single test case
void solve() {
    std::string s, t; // Declare initial word s and target word t
    std::cin >> s >> t; // Read s and t from input

    // Step 1: Check if t is a subsequence of s using a greedy approach.
    // This also identifies the specific characters in s that form t,
    // choosing the leftmost possible characters for each match.
    std::vector<bool> is_kept(s.length(), false); // Boolean array to mark characters in s that are part of t
    int s_ptr = 0; // Pointer for string s
    int t_ptr = 0; // Pointer for string t

    while (s_ptr < s.length() && t_ptr < t.length()) {
        if (s[s_ptr] == t[t_ptr]) {
            is_kept[s_ptr] = true; // Mark s[s_ptr] as kept
            t_ptr++; // Move to the next character in t
        }
        s_ptr++; // Always move to the next character in s
    }

    // If t_ptr has not reached the end of t, it means t is not a subsequence of s.
    // In this case, it's impossible to obtain t.
    if (t_ptr < t.length()) {
        std::cout << "NO\n";
        return;
    }

    // Step 2: Check the deletability condition for characters not part of t.
    // A character s[k] can only be removed if it is the first occurrence of its letter
    // in the current word. If there's an earlier occurrence of the same letter that is *kept*
    // (i.e., part of the target word t), then s[k] can never become the first occurrence
    // and thus can never be removed.
    std::vector<int> last_kept_char_idx(26, -1); // Stores the index of the last encountered kept character for each letter 'A'-'Z'

    for (int k = 0; k < s.length(); ++k) {
        char current_char = s[k];
        int char_code = current_char - 'A'; // Convert character to 0-25 index

        if (is_kept[k]) {
            // If s[k] is a character that is kept (part of t), update its last_kept_char_idx.
            last_kept_char_idx[char_code] = k;
        } else {
            // If s[k] is a character that must be deleted:
            // Check if there was an earlier occurrence of the same character that was kept.
            if (last_kept_char_idx[char_code] != -1) {
                // If last_kept_char_idx[char_code] is not -1, it means a character 'C' (s[k])
                // was encountered earlier at index `last_kept_char_idx[char_code]` and was kept.
                // Since that earlier 'C' is kept, it will never be removed.
                // Therefore, s[k] (which is also 'C' and appears after the kept 'C')
                // can never become the first 'C' in the word to be removed.
                std::cout << "NO\n";
                return;
            }
        }
    }

    // If all checks pass, it is possible to obtain t from s.
    std::cout << "YES\n";
}

int main() {
    // Optimize C++ standard streams for competitive programming.
    // This unties cin/cout from C's stdio and prevents flushing cout before cin.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n; // Number of test cases
    std::cin >> n; // Read the number of test cases

    // Loop through each test case and solve it
    while (n--) {
        solve();
    }

    return 0; // Indicate successful execution
}

#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // Required for std::swap, though not explicitly used in final logic, good practice.

// Function to solve a single test case
void solve() {
    int n;
    std::cin >> n; // Read the length of the binary strings
    std::string a, b;
    std::cin >> a >> b; // Read the two binary strings

    // L and R are pointers to the current effective boundaries of the string 'a'.
    // They represent indices in the original string 'a'.
    // Initially, L points to the first character (index 0) and R points to the last character (index n-1).
    int L = 0;
    int R = n - 1;

    // is_reversed indicates if the current active segment of 'a' is conceptually reversed.
    // If false, we read characters from L towards R.
    // If true, we read characters from R towards L.
    bool is_reversed = false;

    // is_flipped indicates if all characters in the current active segment are conceptually flipped.
    // If true, a '0' is read as '1' and a '1' as '0'.
    bool is_flipped = false;

    // Vector to store the lengths of prefixes for operations performed.
    std::vector<int> operations;

    // We process the string from right to left, matching characters with string 'b'.
    // 'i' represents the current target index in string 'b' that we want to match.
    // The loop runs 'n' times, from the last character (index n-1) down to the first (index 0).
    for (int i = n - 1; i >= 0; --i) {
        // Determine the actual indices in the original string 'a' that correspond
        // to the first and last characters of the current conceptual prefix.
        int char_at_start_original_idx;
        int char_at_end_original_idx;

        if (!is_reversed) {
            // If the string is not reversed, the conceptual prefix is a[L], a[L+1], ..., a[R].
            // So, the first character is at original index L, and the last is at original index R.
            char_at_start_original_idx = L;
            char_at_end_original_idx = R;
        } else {
            // If the string is reversed, the conceptual prefix is a[R], a[R-1], ..., a[L].
            // So, the first character is at original index R, and the last is at original index L.
            char_at_start_original_idx = R;
            char_at_end_original_idx = L;
        }

        // Get the actual character values from string 'a' (converted to int 0 or 1).
        int val_at_start = a[char_at_start_original_idx] - '0';
        int val_at_end = a[char_at_end_original_idx] - '0';

        // Apply the global 'is_flipped' state to get the effective values of these characters.
        // XORing with true (1) flips the bit, XORing with false (0) leaves it unchanged.
        int effective_val_at_start = val_at_start ^ is_flipped;
        int effective_val_at_end = val_at_end ^ is_flipped;

        // Get the target character value from string 'b' at the current position 'i'.
        int target_val = b[i] - '0';

        // Case 1: The effective last character of the current conceptual prefix already matches the target.
        if (effective_val_at_end == target_val) {
            // No operation is needed to change this character.
            // We simply conceptually "remove" this character by shrinking the active prefix.
            // The operation P(current_len) would flip it, which is not desired here.
        } else {
            // Case 2: The effective last character does not match the target.
            // We need to perform operations to make it match.

            // Check if the effective first character of the current conceptual prefix matches the target.
            if (effective_val_at_start == target_val) {
                // If the first character, after considering 'is_flipped', matches the target,
                // we can use two operations:
                // 1. P(1): Flip the first character. This operation only flips the bit at the
                //    current first position (a[char_at_start_original_idx]) and does not affect
                //    the global 'is_flipped' or 'is_reversed' state.
                operations.push_back(1);
                // Directly modify the character in string 'a' to reflect this flip.
                a[char_at_start_original_idx] = (a[char_at_start_original_idx] == '0' ? '1' : '0');
            }
            // Now, the character at the first position (a[char_at_start_original_idx])
            // is conceptually correct (matches target_val).
            // We apply P(i+1) (an operation on the entire current prefix of length i+1)
            // to move this correct character to the end (which is position 'i' in the final string)
            // and simultaneously flip and reverse the entire prefix.
            operations.push_back(i + 1);
            is_flipped = !is_flipped;   // The global flip state toggles
            is_reversed = !is_reversed; // The global reverse state toggles
        }

        // After processing the current character (whether it matched initially or after operations),
        // we shrink the active prefix by moving the appropriate pointer.
        if (!is_reversed) {
            // If the string is currently not reversed, we were processing from L to R.
            // The character at R was the last one, so we move R inwards.
            R--;
        } else {
            // If the string is currently reversed, we were processing from R to L.
            // The character at L was the last one, so we move L inwards.
            L++;
        }
    }

    // Output the total number of operations.
    std::cout << operations.size();
    // Output the lengths of prefixes for each operation.
    for (int p : operations) {
        std::cout << " " << p;
    }
    std::cout << "\n"; // Newline after each test case output
}

int main() {
    // Optimize C++ standard streams for competitive programming.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams.
    // std::cin.tie(NULL) prevents std::cout from flushing before std::cin reads input.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t; // Read the number of test cases
    while (t--) {
        solve(); // Solve each test case
    }

    return 0;
}

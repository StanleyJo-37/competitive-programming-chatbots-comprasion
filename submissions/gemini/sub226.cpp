#include <iostream> // Required for input/output operations (cin, cout)
#include <string>   // Required for string manipulation
#include <algorithm> // Required for std::min

// Function to solve a single test case
void solve() {
    int n; // Declare integer n for string length
    std::cin >> n; // Read the length of the string
    std::string s; // Declare string s
    std::cin >> s; // Read the string

    int min_erased_symbols = -1; // Initialize minimum erased symbols to -1, indicating no solution found yet

    // Iterate through all possible lowercase English letters ('a' to 'z')
    // Each character 'ch' is considered as the one allowed to be erased
    for (char ch = 'a'; ch <= 'z'; ++ch) {
        int current_erased_symbols = 0; // Counter for symbols erased for the current 'ch'
        int left = 0; // Left pointer, starting at the beginning of the string
        int right = n - 1; // Right pointer, starting at the end of the string
        bool possible_for_this_char = true; // Flag to check if it's possible to make a palindrome with current 'ch'

        // Use two pointers to check for palindrome property
        while (left < right) {
            if (s[left] == s[right]) {
                // If characters at current pointers match, they can stay.
                // Move both pointers inwards to check the next pair.
                left++;
                right--;
            } else {
                // If characters do not match, one of them must be 'ch' to be erased.
                if (s[left] == ch) {
                    // If the left character is 'ch', erase it (conceptually) and move left pointer.
                    current_erased_symbols++;
                    left++;
                } else if (s[right] == ch) {
                    // If the right character is 'ch', erase it (conceptually) and move right pointer.
                    current_erased_symbols++;
                    right--;
                } else {
                    // If neither s[left] nor s[right] is 'ch', and they don't match,
                    // it's impossible to form a palindrome by only erasing 'ch'.
                    possible_for_this_char = false;
                    break; // Exit the while loop as this 'ch' cannot form a palindrome
                }
            }
        }

        // If it was possible to form a palindrome with the current 'ch'
        if (possible_for_this_char) {
            // If this is the first valid solution found (min_erased_symbols is still -1),
            // or if the current solution requires fewer erasures than previous ones,
            // update the minimum.
            if (min_erased_symbols == -1 || current_erased_symbols < min_erased_symbols) {
                min_erased_symbols = current_erased_symbols; // Update the minimum
            }
        }
    }

    // Print the result for the current test case
    std::cout << min_erased_symbols << std::endl;
}

int main() {
    // Optimize C++ standard streams for competitive programming.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams,
    // which can speed up I/O operations.
    std::ios_base::sync_with_stdio(false);
    // std::cin.tie(NULL) prevents std::cin from flushing std::cout before reading input,
    // further speeding up I/O.
    std::cin.tie(NULL);

    int t; // Declare integer t for the number of test cases
    std::cin >> t; // Read the number of test cases

    // Loop through each test case
    while (t--) {
        solve(); // Call the solve function for each test case
    }

    return 0; // Indicate successful execution
}

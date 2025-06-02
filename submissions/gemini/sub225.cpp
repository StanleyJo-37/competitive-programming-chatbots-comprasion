#include <iostream> // Required for standard input/output operations (cin, cout)
#include <string>   // Required for using std::string to handle input strings
#include <vector>   // Required for using std::vector to store boolean flags

// Function to solve a single test case
void solve() {
    std::string s;
    std::cin >> s; // Read the input string for the current test case

    // Create a boolean vector to keep track of which characters' buttons
    // are determined to be working correctly.
    // The size is 26 for 'a' through 'z'.
    // is_working_correctly[0] corresponds to 'a', is_working_correctly[1] to 'b', and so on.
    // Initialize all to false, meaning we initially assume no button is necessarily working correctly.
    std::vector<bool> is_working_correctly(26, false);

    // Iterate through the input string 's' using an index 'i'.
    // This loop simulates Polycarp's button presses and how they form the string 's'.
    // We process the string by identifying segments that correspond to a single button press.
    int i = 0;
    while (i < s.length()) {
        char current_char = s[i]; // Get the character at the current position 'i'

        // Check if the current character 'current_char' is followed by an identical character.
        // This condition (i + 1 < s.length() && s[i+1] == current_char)
        // checks if we are not at the end of the string AND the next character is the same.
        if (i + 1 < s.length() && s[i+1] == current_char) {
            // If 'current_char' is followed by itself (e.g., "aa", "bb"),
            // this sequence 'cc' *could* have been produced by a malfunctioning button.
            // Since it *could* be malfunctioning, we cannot definitively say it *must* be working correctly.
            // Therefore, we do not mark this character as 'is_working_correctly'.
            // We consume both characters of this pair and advance the index 'i' by 2.
            i += 2;
        } else {
            // If 'current_char' is NOT followed by an identical character (e.g., "a" followed by "b", or "a" at the end of string),
            // this means 'current_char' appeared as a single character.
            // A single character 'c' can only be produced if the button for 'c' was working correctly.
            // If it were malfunctioning, it would produce 'cc'.
            // Therefore, the button for 'current_char' *must* have been working correctly.
            // We mark this character's button as working correctly.
            is_working_correctly[current_char - 'a'] = true;
            // We consume this single character and advance the index 'i' by 1.
            i += 1;
        }
    }

    // After processing the entire string, construct the result string.
    // This string will contain all characters whose buttons were determined
    // to be working correctly, in alphabetical order.
    std::string result_str = "";
    for (int j = 0; j < 26; ++j) {
        // Iterate from 'a' to 'z' (represented by indices 0 to 25).
        if (is_working_correctly[j]) {
            // If the button for the character 'a' + j was marked as working correctly,
            // append it to the result string.
            result_str += (char)('a' + j);
        }
    }

    std::cout << result_str << std::endl; // Print the final result for the current test case
}

int main() {
    // Optimize C++ standard streams for faster input/output operations.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams.
    // std::cin.tie(NULL) prevents std::cout from flushing before std::cin reads input.
    // These are common optimizations in competitive programming.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t; // Read the number of test cases

    while (t--) { // Loop 't' times, calling solve() for each test case
        solve();
    }

    return 0; // Indicate successful program execution
}

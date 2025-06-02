#include <iostream> // Required for input/output operations (std::cin, std::cout)
#include <string>   // Required for string manipulation (std::string)
// No other headers like <vector> or <algorithm> are strictly necessary for this optimized solution,
// as we process strings one by one and don't need complex data structures or algorithms.

int main() {
    // Optimize C++ standard streams for faster input/output.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard I/O.
    // This can significantly speed up I/O operations.
    std::ios_base::sync_with_stdio(false);
    // std::cin.tie(NULL) prevents std::cout from being flushed before each std::cin operation.
    // This further optimizes I/O, especially when there's a mix of input and output.
    std::cin.tie(NULL);

    int n; // Declare an integer variable 'n' to store the number of Polycarpus's friends.
    std::cin >> n; // Read the value of 'n' from standard input.

    std::string s1; // Declare a string variable 's1' to store the first phone number.
    std::cin >> s1; // Read the first phone number into 's1'. This string will serve as our reference.

    // Initialize 'common_prefix_length' with the length of the first string.
    // The problem guarantees all strings have the same length, so s1.length()
    // is the maximum possible length for the common prefix.
    int common_prefix_length = s1.length();

    // Loop through the remaining n-1 phone numbers.
    // We already read the first string, so we start from the second one (i = 1).
    for (int i = 1; i < n; ++i) {
        std::string current_s; // Declare a string variable to store the current phone number being read.
        std::cin >> current_s; // Read the current phone number into 'current_s'.

        // Iterate through characters from the beginning (index 0) up to the current
        // 'common_prefix_length'. We only need to compare characters within
        // the already established common prefix. If a mismatch occurs earlier,
        // the common prefix shrinks.
        for (int j = 0; j < common_prefix_length; ++j) {
            // If characters at position 'j' in 's1' and 'current_s' do not match,
            // it means the common prefix among all strings processed so far ends
            // before or at this position 'j'.
            if (s1[j] != current_s[j]) {
                // Update 'common_prefix_length' to 'j'. This means the common prefix
                // is now only 'j' characters long (from index 0 to j-1).
                common_prefix_length = j;
                // Since we found a mismatch, there's no need to compare further
                // characters for this 'current_s'. The common prefix cannot extend
                // beyond 'j' characters with this string. Break out of the inner loop.
                break;
            }
        }

        // Optimization: If 'common_prefix_length' becomes 0 at any point,
        // it means there is no common prefix among all strings (or an empty prefix).
        // In this case, the length cannot become negative and will remain 0.
        // We can stop processing further strings as the result is already determined.
        if (common_prefix_length == 0) {
            break;
        }
    }

    // After checking all strings, 'common_prefix_length' will hold the length
    // of the longest common prefix among all phone numbers.
    std::cout << common_prefix_length << std::endl; // Print the result to standard output.

    return 0; // Indicate successful execution of the program.
}
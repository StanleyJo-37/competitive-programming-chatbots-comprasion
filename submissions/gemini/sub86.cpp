#include <iostream> // Required for input/output operations (std::cin, std::cout)
#include <string>   // Required for using std::string

int main() {
    // Optimize C++ standard streams for faster input/output.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams,
    // which can speed up I/O operations.
    // std::cin.tie(NULL) prevents std::cout from flushing before each std::cin operation,
    // further speeding up I/O. These are common competitive programming optimizations.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::string s; // Declare a string variable to store the input word typed by Vasya.
    std::cin >> s; // Read the input word 's' from standard input.

    std::string target = "hello"; // Define the target word "hello" that we need to find as a subsequence.
    int target_idx = 0;           // Initialize an index for the 'target' word.
                                  // This index will keep track of which character of "hello" we are currently
                                  // trying to match in the input string 's'. It starts at 0, meaning we are
                                  // looking for 'h' (target[0]).

    // Iterate through each character of the input string 's'.
    // The loop continues as long as 'i' is within the bounds of 's'.
    for (int i = 0; i < s.length(); ++i) {
        // Before attempting a match, check if we have already found all characters of "hello".
        // If 'target_idx' has reached the length of 'target' (which is 5), it means we have
        // successfully matched 'h', 'e', 'l', 'l', 'o' in order.
        if (target_idx == target.length()) {
            break; // If "hello" is already found, there's no need to process the rest of 's'.
                   // We can exit the loop early.
        }

        // Compare the current character of 's' (s[i]) with the character we are currently looking for
        // in 'target' (target[target_idx]).
        if (s[i] == target[target_idx]) {
            // If they match, it means we found the next character of "hello".
            // Increment 'target_idx' to move to the next character in "hello" for the subsequent match.
            target_idx++;
        }
    }

    // After iterating through the entire input string 's' (or breaking early),
    // check if 'target_idx' has reached the length of "hello".
    // If it has, it means "hello" was successfully formed as a subsequence.
    if (target_idx == target.length()) {
        std::cout << "YES\n"; // Print "YES" followed by a newline character.
    } else {
        // If 'target_idx' is less than the length of "hello", it means not all characters
        // of "hello" were found in the correct order as a subsequence.
        std::cout << "NO\n";  // Print "NO" followed by a newline character.
    }

    return 0; // Indicate that the program executed successfully.
}

#include <iostream> // Required for input/output operations (cin, cout)
#include <vector>   // Required for std::vector to store problem titles
#include <string>   // Required for std::string to handle problem titles and candidate strings

int main() {
    // Optimize C++ standard streams for competitive programming.
    // This unties cin/cout from C's stdio and disables synchronization with C's stdio,
    // potentially speeding up I/O operations.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n; // Declare an integer variable 'n' to store the number of problem titles.
    std::cin >> n; // Read the value of 'n' from standard input.

    std::vector<std::string> titles(n); // Declare a vector of strings to store 'n' problem titles.
    for (int i = 0; i < n; ++i) { // Loop 'n' times to read each title.
        std::cin >> titles[i]; // Read each problem title into the vector.
    }

    // First, try to find a shortest original title of length 1.
    // Iterate through all lowercase English letters from 'a' to 'z'.
    for (char c = 'a'; c <= 'z'; ++c) {
        std::string candidate_title(1, c); // Create a string of length 1 with the current character 'c'.
        bool is_original = true; // Assume the candidate title is original until proven otherwise.

        // Check if this candidate title is a substring of any of the given problem titles.
        for (const std::string& title : titles) { // Iterate through each problem title.
            // std::string::find returns std::string::npos if the substring is not found.
            if (title.find(candidate_title) != std::string::npos) {
                is_original = false; // If found, it's not original.
                break; // No need to check other titles for this candidate; move to the next character.
            }
        }

        if (is_original) {
            // If the candidate title was not found as a substring in any problem title,
            // it is the shortest (length 1) and lexicographically smallest (due to iteration order).
            std::cout << candidate_title << std::endl; // Print the found title.
            return 0; // Exit the program as the answer has been found.
        }
    }

    // If no original title of length 1 was found (meaning all single letters 'a' through 'z'
    // are substrings of some problem title), then try to find an original title of length 2.
    // Iterate through all possible two-letter combinations in lexicographical order.
    for (char c1 = 'a'; c1 <= 'z'; ++c1) { // First character of the two-letter title.
        for (char c2 = 'a'; c2 <= 'z'; ++c2) { // Second character of the two-letter title.
            std::string candidate_title = ""; // Initialize an empty string.
            candidate_title += c1; // Append the first character.
            candidate_title += c2; // Append the second character.
            
            bool is_original = true; // Assume the candidate title is original.

            // Check if this two-letter candidate title is a substring of any problem title.
            for (const std::string& title : titles) { // Iterate through each problem title.
                if (title.find(candidate_title) != std::string::npos) {
                    is_original = false; // If found, it's not original.
                    break; // No need to check other titles for this candidate.
                }
            }

            if (is_original) {
                // If the candidate title was not found as a substring, it is the shortest
                // (since length 1 failed) and lexicographically smallest (due to iteration order).
                std::cout << candidate_title << std::endl; // Print the found title.
                return 0; // Exit the program.
            }
        }
    }

    // Based on the problem constraints (N <= 30, title length <= 20),
    // it's mathematically guaranteed that an original title of length 1 or 2 will always exist.
    // (There are 26 length-1 strings, and at most 26 distinct length-1 substrings in total.
    // There are 26*26 = 676 length-2 strings, and at most 30 * (20-2+1) = 30 * 19 = 570 distinct length-2 substrings in total.)
    // Therefore, the program will always find an answer and exit before reaching this point.
    return 0; // This line should theoretically not be reached given the problem constraints.
}
#include <iostream> // Required for input/output operations (std::cin, std::cout)
#include <string>   // Required for string manipulation (std::string)

// Function to solve a single test case
void solve() {
    int N, K; // N: length of the string, K: minimum consecutive '*' for strong language
    std::cin >> N >> K; // Read the length of the string N and the threshold K

    std::string S; // The input string
    std::cin >> S; // Read the string S

    int current_consecutive_stars = 0; // Counter to keep track of the current sequence of consecutive '*' characters
    bool found_strong_language = false; // A boolean flag to indicate if a sequence of K or more '*' is found

    // Iterate through the string character by character from left to right
    for (int i = 0; i < N; ++i) {
        if (S[i] == '*') {
            // If the current character is an asterisk, increment the consecutive stars counter
            current_consecutive_stars++;
        } else {
            // If the current character is not an asterisk, the sequence of '*' is broken.
            // Reset the counter to 0.
            current_consecutive_stars = 0;
        }

        // After updating the counter, check if the current sequence length meets or exceeds K
        if (current_consecutive_stars >= K) {
            // If it does, then the string uses strong language
            found_strong_language = true;
            // Since we only need to find *at least* K consecutive stars,
            // we can stop checking the rest of the string and break the loop.
            break;
        }
    }

    // After the loop finishes (either by finding strong language and breaking, or by reaching the end of the string)
    if (found_strong_language) {
        // If the flag is true, print "YES"
        std::cout << "YES\n";
    } else {
        // Otherwise, print "NO"
        std::cout << "NO\n";
    }
}

int main() {
    // Optimize C++ standard streams for faster input/output operations.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams,
    // which can significantly speed up I/O.
    std::ios_base::sync_with_stdio(false);
    // std::cin.tie(NULL) prevents std::cout from flushing before std::cin reads input,
    // further optimizing I/O performance.
    std::cin.tie(NULL);

    int T; // Variable to store the number of test cases
    std::cin >> T; // Read the number of test cases

    // Loop T times, once for each test case
    while (T--) {
        solve(); // Call the solve function to handle the current test case
    }

    return 0; // Indicate successful program execution
}

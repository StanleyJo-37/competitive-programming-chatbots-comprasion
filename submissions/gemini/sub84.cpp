#include <iostream> // Required for input/output operations (std::cin, std::cout)
#include <string>   // Required for string manipulation (std::string)
#include <algorithm> // Required for std::sort

// Function to solve a single test case
void solve() {
    int n, m, k; // Declare integers for lengths of strings a, b and max consecutive operations k
    std::cin >> n >> m >> k; // Read n, m, k from input
    std::string a, b; // Declare strings a and b
    std::cin >> a >> b; // Read strings a and b from input

    // Sort strings a and b in lexicographical (alphabetical) order.
    // This is crucial for the greedy approach: by sorting, the smallest available
    // character from each string is always at its beginning (index 0).
    std::sort(a.begin(), a.end());
    std::sort(b.begin(), b.end());

    std::string c = ""; // Initialize an empty string c to build the result
    int ptr_a = 0; // Pointer for string a, initialized to the first character
    int ptr_b = 0; // Pointer for string b, initialized to the first character
    int consecutive_a = 0; // Counter for consecutive characters taken from string a
    int consecutive_b = 0; // Counter for consecutive characters taken from string b

    // The loop continues as long as both strings a and b have characters remaining.
    // The problem states operations must be performed until either a or b becomes empty.
    while (ptr_a < n && ptr_b < m) {
        bool take_from_a; // A boolean flag to decide whether to take the next character from string 'a'

        // Determine which string to take from based on lexicographical order and the 'k' constraint.
        // Since it's guaranteed that no character appears in both strings, a[ptr_a] will never equal b[ptr_b].
        if (a[ptr_a] < b[ptr_b]) {
            // If the current smallest character in 'a' is lexicographically smaller than in 'b'.
            if (consecutive_a < k) {
                // If we haven't reached 'k' consecutive operations from 'a', it's optimal to take from 'a'
                // to keep 'c' lexicographically smallest.
                take_from_a = true;
            } else {
                // If we have already taken 'k' characters consecutively from 'a', we are forced
                // to take a character from 'b' to satisfy the constraint.
                take_from_a = false;
            }
        } else { // This implies b[ptr_b] < a[ptr_a]
            // If the current smallest character in 'b' is lexicographically smaller than in 'a'.
            if (consecutive_b < k) {
                // If we haven't reached 'k' consecutive operations from 'b', it's optimal to take from 'b'.
                take_from_a = false;
            } else {
                // If we have already taken 'k' characters consecutively from 'b', we are forced
                // to take a character from 'a' to satisfy the constraint.
                take_from_a = true;
            }
        }

        // Perform the chosen operation: append the character to 'c' and update pointers/counters.
        if (take_from_a) {
            c.push_back(a[ptr_a]); // Append the character from 'a' to 'c'
            ptr_a++; // Move 'a' pointer to the next character
            consecutive_a++; // Increment consecutive count for 'a'
            consecutive_b = 0; // Reset consecutive count for 'b' as we just took from 'a'
        } else {
            c.push_back(b[ptr_b]); // Append the character from 'b' to 'c'
            ptr_b++; // Move 'b' pointer to the next character
            consecutive_b++; // Increment consecutive count for 'b'
            consecutive_a = 0; // Reset consecutive count for 'a' as we just took from 'b'
        }
    }

    std::cout << c << std::endl; // Output the final lexicographically smallest string 'c'
}

int main() {
    // Optimize C++ standard streams for faster input/output.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams.
    // std::cin.tie(NULL) prevents std::cout from flushing before std::cin reads input.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t; // Declare integer for the number of test cases
    std::cin >> t; // Read the number of test cases
    while (t--) { // Loop through each test case
        solve(); // Call the solve function for the current test case
    }

    return 0; // Indicate successful program execution
}
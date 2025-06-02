#include <iostream> // Required for input/output operations (std::cin, std::cout)
#include <string>   // Required for using std::string
#include <vector>   // Not strictly needed for this problem, but often useful in competitive programming

// Function to solve a single test case
void solve() {
    int n; // Declare an integer variable 'n' to store the length of the bracket sequence
    std::cin >> n; // Read the length 'n' from standard input

    std::string s; // Declare a string variable 's' to store the bracket sequence
    std::cin >> s; // Read the string 's' from standard input

    int balance = 0; // Initialize 'balance' to 0. This variable tracks the current balance
                     // of opening brackets minus closing brackets encountered so far.
                     // For a regular bracket sequence, this balance must never drop below zero.
    int moves = 0;   // Initialize 'moves' to 0. This variable will count the minimum
                     // number of moves required to make the sequence regular.

    // Iterate through each character of the input string 's'
    for (char c : s) {
        if (c == '(') {
            balance++; // If an opening bracket is encountered, increment the balance.
        } else { // If a closing bracket is encountered
            balance--; // Decrement the balance.
        }

        // A key property of a regular bracket sequence is that its balance must never
        // drop below zero at any point. If 'balance' becomes negative, it means we have
        // encountered more closing brackets than opening brackets in the current prefix.
        // This specific closing bracket that caused the balance to go negative is
        // "problematic" and must be moved to satisfy the regular bracket sequence property.
        if (balance < 0) {
            moves++;       // Increment the 'moves' counter because this bracket needs to be moved.
            balance = 0;   // Reset the balance to 0. This conceptually "removes" the problematic
                           // closing bracket from its current position. By resetting to 0,
                           // we are effectively saying that this bracket is moved (e.g., to the end
                           // of the string), and the subsequent part of the string can be evaluated
                           // as if starting with a fresh balance. This greedy choice is optimal
                           // because any ')' that causes a negative balance *must* be moved.
        }
    }

    // After iterating through the entire string, 'moves' will contain the minimum number
    // of problematic closing brackets that needed to be moved. These moved brackets can
    // be placed at the end of the string. The remaining characters, along with the
    // non-problematic closing brackets, will form a sequence where the balance never
    // drops below zero. Since the total number of '(' and ')' is guaranteed to be n/2 each,
    // the final sequence will be a regular bracket sequence.
    std::cout << moves << std::endl; // Print the minimum number of moves for the current test case
}

int main() {
    // Optimize C++ standard streams for competitive programming.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from the C standard I/O library,
    // which can speed up I/O operations.
    // std::cin.tie(NULL) prevents std::cout from being flushed before each std::cin operation,
    // further improving I/O performance.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t; // Declare an integer variable 't' to store the number of test cases
    std::cin >> t; // Read the number of test cases from standard input

    // Loop 't' times, calling the 'solve' function for each test case
    while (t--) {
        solve();
    }

    return 0; // Indicate successful program execution
}

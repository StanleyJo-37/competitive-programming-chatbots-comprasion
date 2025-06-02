#include <iostream> // Required for input and output operations (std::cin, std::cout, std::endl)

// Function to solve a single test case
void solve() {
    int L, R; // Declare two integer variables, L and R, to store the range limits
    std::cin >> L >> R; // Read the values of L and R from standard input

    int pretty_count = 0; // Initialize a counter to store the number of pretty numbers found in the range

    // Iterate through each number from L to R (inclusive)
    for (int i = L; i <= R; ++i) {
        // Calculate the last digit of the current number 'i' using the modulo operator
        int last_digit = i % 10;

        // Check if the last digit is 2, 3, or 9.
        // These are the conditions for a number to be considered "pretty".
        if (last_digit == 2 || last_digit == 3 || last_digit == 9) {
            pretty_count++; // If the number is pretty, increment the counter
        }
    }

    // Print the total count of pretty numbers for the current test case, followed by a newline
    std::cout << pretty_count << std::endl;
}

int main() {
    // Optimize C++ standard streams for faster input/output.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams.
    // std::cin.tie(NULL) prevents std::cout from flushing before std::cin reads input.
    // These optimizations are common in competitive programming to speed up I/O operations.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int T; // Declare an integer variable T to store the number of test cases
    std::cin >> T; // Read the number of test cases from standard input

    // Loop T times, calling the 'solve' function for each test case.
    // The 'T--' decrements T after each iteration until it becomes 0.
    while (T--) {
        solve(); // Call the function to process one test case
    }

    return 0; // Indicate successful program execution
}

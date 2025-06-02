#include <iostream> // Required for input/output operations (std::cin, std::cout)

// Function to check if a given integer is a palindrome
bool isPalindrome(int n) {
    // Store the original number to compare it with the reversed number later.
    // We need to preserve the original value of 'n' because 'n' will be modified
    // during the reversal process.
    int original_n = n;
    
    // Initialize 'reversed_n' to 0. This variable will store the number
    // formed by reversing the digits of 'n'.
    int reversed_n = 0;

    // Loop continues as long as 'n' is greater than 0.
    // In each iteration, we extract the last digit of 'n',
    // append it to 'reversed_n', and then remove it from 'n'.
    while (n > 0) {
        // Get the last digit of 'n' using the modulo operator (%).
        // For example, if n = 331, digit = 1.
        int digit = n % 10;
        
        // Build the reversed number.
        // Multiply 'reversed_n' by 10 to shift its existing digits one position to the left,
        // then add the newly extracted 'digit' to the rightmost position.
        // For example:
        // If reversed_n = 0, digit = 1 -> reversed_n = 0*10 + 1 = 1
        // If reversed_n = 1, digit = 3 -> reversed_n = 1*10 + 3 = 13
        // If reversed_n = 13, digit = 3 -> reversed_n = 13*10 + 3 = 133
        reversed_n = reversed_n * 10 + digit;
        
        // Remove the last digit from 'n' using integer division (/).
        // For example, if n = 331, n becomes 33.
        // If n = 33, n becomes 3.
        // If n = 3, n becomes 0, which terminates the loop.
        n /= 10;
    }

    // After the loop, 'reversed_n' holds the reversed version of the 'original_n'.
    // Compare 'original_n' with 'reversed_n'.
    // If they are equal, the number is a palindrome, and the function returns true.
    // Otherwise, it returns false.
    return original_n == reversed_n;
}

int main() {
    // Optimize C++ standard streams for faster input/output.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams,
    // which can speed up I/O operations significantly.
    std::ios_base::sync_with_stdio(false);
    
    // std::cin.tie(NULL) prevents std::cout from flushing before std::cin reads input.
    // This is useful in competitive programming to avoid unnecessary flushes and improve performance.
    std::cin.tie(NULL);

    // Declare an integer variable 'T' to store the number of test cases.
    int T;
    // Read the number of test cases from the standard input.
    std::cin >> T;

    // Loop 'T' times, once for each test case.
    // The 'T--' decrements T after each iteration until it becomes 0.
    while (T--) {
        // Declare an integer variable 'N' to store the number for the current test case.
        int N;
        // Read the number 'N' from the standard input.
        std::cin >> N;

        // Call the 'isPalindrome' function to check if 'N' is a palindrome.
        if (isPalindrome(N)) {
            // If 'isPalindrome' returns true, print "wins" followed by a newline character.
            std::cout << "wins\n";
        } else {
            // If 'isPalindrome' returns false, print "loses" followed by a newline character.
            std::cout << "loses\n";
        }
    }

    // Return 0 to indicate successful program execution.
    return 0;
}

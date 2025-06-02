#include <iostream> // Required for input/output operations (cin, cout).
#include <string>   // Required for using std::string.
#include <vector>   // Required for using std::vector to store word mappings.

int main() {
    // Optimize C++ standard streams for competitive programming.
    // This unties cin from cout and disables synchronization with C's stdio.
    // It can speed up I/O operations, though for small inputs like this, it's not strictly necessary.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int s; // Declare an integer variable 's' to store Tavas's score.
    std::cin >> s; // Read the integer score from standard input.

    // Define an array of strings for numbers 0 through 19.
    // These numbers have unique word representations.
    std::vector<std::string> units = {
        "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine",
        "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"
    };

    // Define an array of strings for the tens part of numbers (20, 30, ..., 90).
    // The indices correspond to the tens digit (e.g., tens[2] for "twenty", tens[3] for "thirty").
    // Indices 0 and 1 are unused as numbers 0-19 are handled by the 'units' array.
    std::vector<std::string> tens = {
        "", "", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"
    };

    // Check if the score 's' is less than 20.
    // Numbers 0-19 are directly looked up in the 'units' array.
    if (s < 20) {
        std::cout << units[s] << std::endl; // Print the word representation and a newline.
    } else {
        // If 's' is 20 or greater, it falls into the tens category (20-99).
        int tens_digit = s / 10; // Get the tens digit (e.g., for 99, tens_digit is 9).
        int units_digit = s % 10; // Get the units digit (e.g., for 99, units_digit is 9).

        // Check if the units digit is 0.
        // This means the number is a multiple of 10 (e.g., 20, 30, 90).
        if (units_digit == 0) {
            std::cout << tens[tens_digit] << std::endl; // Print only the tens word.
        } else {
            // If the units digit is not 0 (e.g., 21, 35, 99).
            // The word is formed by combining the tens word, a hyphen, and the units word.
            std::cout << tens[tens_digit] << "-" << units[units_digit] << std::endl;
        }
    }

    return 0; // Indicate successful program execution.
}

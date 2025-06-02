#include <iostream> // Required for standard input/output operations (std::cin, std::cout, std::endl).
#include <string>   // Required for using std::string to handle time input and output.
// #include <algorithm> // Not strictly necessary for this solution, as min/max are handled manually.

int main() {
    // Optimize C++ standard streams for faster input/output.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams,
    // which can improve performance by preventing synchronization overhead.
    // std::cin.tie(NULL) unties std::cin from std::cout, meaning std::cin will not flush std::cout
    // before reading input, further speeding up I/O operations.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int format; // Declare an integer variable to store the clock format (12 or 24 hours).
    std::cin >> format; // Read the clock format from standard input.

    std::string s; // Declare a string variable to store the input time in HH:MM format.
    std::cin >> s; // Read the time string from standard input.

    // Initialize 'min_diff' to a value greater than the maximum possible digit changes.
    // There are 4 digits (HHMM) that can change, so 5 is a safe initial maximum.
    int min_diff = 5;
    // Initialize 'best_time_str' to an empty string. This will store the valid time
    // that has the minimum number of differing digits from the input.
    std::string best_time_str = "";

    // Determine the maximum and minimum hour values based on the specified format.
    // For 24-hour format, hours range from 0 to 23.
    // For 12-hour format, hours range from 1 to 12.
    int max_h = (format == 24) ? 23 : 12;
    int min_h = (format == 24) ? 0 : 1;

    // Loop through all possible valid hour values.
    for (int h = min_h; h <= max_h; ++h) {
        // Convert the current integer hour 'h' into its two-digit character representation.
        // For example, if h=7, hh_char1 becomes '0' and hh_char2 becomes '7'.
        char hh_char1 = (h / 10) + '0'; // Get the tens digit of the hour.
        char hh_char2 = (h % 10) + '0'; // Get the units digit of the hour.

        // Loop through all possible valid minute values (0 to 59).
        for (int m = 0; m <= 59; ++m) {
            // Convert the current integer minute 'm' into its two-digit character representation.
            // For example, if m=9, mm_char1 becomes '0' and mm_char2 becomes '9'.
            char mm_char1 = (m / 10) + '0'; // Get the tens digit of the minute.
            char mm_char2 = (m % 10) + '0'; // Get the units digit of the minute.

            int current_diff = 0; // Initialize a counter for differences for the current (h, m) pair.

            // Compare the first digit of the current valid hour with the first digit of the input hour.
            // The input hour's first digit is at s[0].
            if (s[0] != hh_char1) {
                current_diff++; // Increment if they are different.
            }
            // Compare the second digit of the current valid hour with the second digit of the input hour.
            // The input hour's second digit is at s[1].
            if (s[1] != hh_char2) {
                current_diff++; // Increment if they are different.
            }

            // Compare the first digit of the current valid minute with the first digit of the input minute.
            // The input minute's first digit is at s[3] (after the colon).
            if (s[3] != mm_char1) {
                current_diff++; // Increment if they are different.
            }
            // Compare the second digit of the current valid minute with the second digit of the input minute.
            // The input minute's second digit is at s[4].
            if (s[4] != mm_char2) {
                current_diff++; // Increment if they are different.
            }

            // If the current valid time (h:m) has fewer differing digits than the best found so far,
            // update 'min_diff' and 'best_time_str'.
            if (current_diff < min_diff) {
                min_diff = current_diff; // Update the minimum difference.
                // Construct the new best time string.
                best_time_str = ""; // Clear the previous best string.
                best_time_str += hh_char1; // Append first hour digit.
                best_time_str += hh_char2; // Append second hour digit.
                best_time_str += ':';      // Append the colon separator.
                best_time_str += mm_char1; // Append first minute digit.
                best_time_str += mm_char2; // Append second minute digit.
            }
        }
    }

    // Print the 'best_time_str' to standard output, followed by a newline.
    std::cout << best_time_str << std::endl;

    return 0; // Indicate successful program execution.
}

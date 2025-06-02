#include <iostream> // Required for input/output operations (std::cin, std::cout)
#include <string>   // Required for string manipulation (std::string, std::to_string)
#include <vector>   // Not strictly necessary for this solution, but often useful in competitive programming
#include <algorithm> // Required for std::min

int main() {
    // Optimize C++ standard streams for competitive programming.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams,
    // potentially speeding up I/O operations.
    std::ios_base::sync_with_stdio(false);
    // std::cin.tie(NULL) prevents std::cout from being flushed before each std::cin operation,
    // which can further speed up I/O.
    std::cin.tie(NULL);

    int m, s; // Declare variables for length (m) and sum of digits (s)
    std::cin >> m >> s; // Read m and s from standard input

    // --- Handle invalid cases and special case ---

    // Case 1: Sum is 0.
    // If m=1 and s=0, the only number is 0. This is a valid single-digit number.
    // If m>1 and s=0, it's impossible to form a number of length m with sum 0 without leading zeroes.
    // The first digit must be at least 1, making the sum at least 1.
    if (s == 0) {
        if (m == 1) {
            std::cout << "0 0\n"; // Output "0 0" for this special valid case
        } else {
            std::cout << "-1 -1\n"; // Output "-1 -1" for invalid case
        }
        return 0; // Exit the program
    }

    // Case 2: Sum is too large.
    // The maximum possible sum for m digits is m * 9 (e.g., for m=2, max sum is 99 -> 9+9=18).
    // If the given sum 's' exceeds this maximum, no such number exists.
    if (s > m * 9) {
        std::cout << "-1 -1\n"; // Output "-1 -1" for invalid case
        return 0; // Exit the program
    }

    // --- Construct Smallest Number ---
    // To construct the smallest number, we want to place the smallest possible digits
    // at the most significant positions (leftmost).
    std::string min_num_str = ""; // String to build the smallest number
    int temp_s_min = s;           // Temporary sum for constructing the smallest number

    // Iterate through each digit position from left to right (most significant to least significant)
    for (int i = 0; i < m; ++i) {
        // Determine the starting digit for the current position.
        // For the first digit (i=0), it cannot be 0 (to avoid leading zeroes), so start from 1.
        // For subsequent digits (i>0), 0 is allowed.
        int start_digit = (i == 0) ? 1 : 0;

        // Iterate through possible digits from 'start_digit' up to 9
        for (int d = start_digit; d <= 9; ++d) {
            // Calculate the number of digits remaining to be filled after the current position.
            // If current position is 'i', then 'm - 1 - i' digits remain.
            int remaining_digits_count = m - 1 - i;
            // Calculate the maximum possible sum that can be formed by the 'remaining_digits_count'.
            // This is achieved by filling all remaining digits with 9s.
            int max_sum_for_remaining = remaining_digits_count * 9;

            // Check if placing digit 'd' at the current position is valid:
            // 1. (temp_s_min - d >= 0): The remaining sum after placing 'd' must be non-negative.
            //    This ensures we don't use more sum than available.
            // 2. (temp_s_min - d <= max_sum_for_remaining): The remaining sum must be achievable
            //    by the 'remaining_digits_count'. If it's greater, it means we placed too small
            //    a digit 'd' at the current position, and the remaining digits cannot sum up to the required value.
            if (temp_s_min - d >= 0 && temp_s_min - d <= max_sum_for_remaining) {
                min_num_str += std::to_string(d); // Append the chosen digit to the string
                temp_s_min -= d;                   // Subtract the digit's value from the remaining sum
                break;                             // Move to the next digit position (found the smallest valid digit for current pos)
            }
        }
    }

    // --- Construct Largest Number ---
    // To construct the largest number, we want to place the largest possible digits
    // at the most significant positions (leftmost).
    std::string max_num_str = ""; // String to build the largest number
    int temp_s_max = s;           // Temporary sum for constructing the largest number

    // Iterate through each digit position from left to right
    for (int i = 0; i < m; ++i) {
        // The largest digit we can place at the current position is limited by:
        // 1. 9 (maximum single digit value).
        // 2. temp_s_max (the remaining sum available).
        // So, the digit 'd' must be <= std::min(9, temp_s_max).
        //
        // Additionally, we must ensure that after placing 'd', the remaining sum
        // (temp_s_max - d) can be formed by the remaining digits (m - 1 - i).
        // The minimum sum for remaining digits is 0 (all zeros).
        // The maximum sum for remaining digits is (m - 1 - i) * 9 (all nines).
        // So, 0 <= temp_s_max - d <= (m - 1 - i) * 9.
        // This implies:
        // a) d <= temp_s_max (from temp_s_max - d >= 0)
        // b) d >= temp_s_max - (m - 1 - i) * 9 (from temp_s_max - d <= (m - 1 - i) * 9)
        //
        // Combining all constraints:
        // d must be in the range [max(0, temp_s_max - (m - 1 - i) * 9), min(9, temp_s_max)].
        // To maximize 'd', we pick the upper bound of this range: min(9, temp_s_max).
        // It can be mathematically proven that this choice is always valid given the initial check `s <= m * 9`.
        // The first digit cannot be 0, but since we are trying to maximize, it will always be >=1 if s>0.
        // If s=0, m=1, it's handled. If s=0, m>1, it's handled.
        // So, temp_s_max will always be > 0 for the first digit if m>1.
        int digit = std::min(9, temp_s_max);
        max_num_str += std::to_string(digit); // Append the chosen digit
        temp_s_max -= digit;                   // Subtract the digit's value from the remaining sum
    }

    // --- Print Results ---
    std::cout << min_num_str << " " << max_num_str << "\n";

    return 0; // Indicate successful execution
}
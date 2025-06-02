#include <iostream> // Required for input/output operations (cin, cout)
#include <string>   // Required for string manipulation
#include <numeric>  // Required for std::gcd (available from C++17)
#include <cmath>    // Required for std::abs

int main() {
    // Optimize C++ standard streams for faster input/output.
    // This unties cin/cout from C's stdio and prevents flushing cout before cin.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int T; // Declare variable for the number of test cases
    std::cin >> T; // Read the number of test cases

    while (T--) { // Loop through each test case
        int N; // Declare variable for the length of the string
        long long K; // Declare variable for the integer K (using long long for safety, though int is sufficient based on constraints)
        std::cin >> N >> K; // Read N and K

        std::string S; // Declare string variable
        std::cin >> S; // Read the string S

        // Initialize variables to track the state of the array A
        long long count_letters = N; // Initially, all N characters are letters
        long long count_numbers = 0; // Initially, no characters are numbers
        long long sum_numbers = 0;   // Initially, sum of numbers is 0

        // Iterate through each character in the string S
        for (char c : S) {
            // Calculate the numerical value of the character
            // 'a' -> 1, 'b' -> 2, ..., 'z' -> 26
            int char_val = c - 'a' + 1;

            // The decision to convert a character to a number is based on maximizing power P.
            // Power P is defined as: (count of letters) - (count of numbers) + (sum of numbers / K)
            // Let L = count of letters, M = count of numbers, S_num = sum of numbers.
            // P = L - M + S_num / K
            // We know that L + M = N (total characters in the original string). So, L = N - M.
            // Substituting L into the power formula:
            // P = (N - M) - M + S_num / K = N - 2M + S_num / K
            //
            // Consider a single character 'c' with numerical value 'char_val'.
            // If we keep 'c' as a letter:
            //   L increases by 1, M and S_num remain unchanged.
            //   The contribution to P from this character (relative to its absence) is +1 (from L).
            // If we convert 'c' to a number:
            //   M increases by 1, L remains unchanged, S_num increases by 'char_val'.
            //   The contribution to P from this character (relative to its absence) is -1 (from M) + char_val / K.
            //
            // The net change in P if we convert 'c' (which would otherwise be a letter) to a number is:
            // (Contribution if converted) - (Contribution if kept as letter)
            // = (-1 + char_val / K) - (+1)
            // = -2 + char_val / K
            //
            // To maximize P, we should convert 'c' to a number if this net change is positive, i.e., -2 + char_val / K > 0.
            // This inequality simplifies to:
            // char_val / K > 2
            // char_val > 2 * K
            //
            // If char_val <= 2 * K, it's not beneficial or neutral to convert, so we keep it as a letter.
            if (char_val > 2 * K) {
                // If converting is beneficial, update counts and sum
                count_letters--;    // One less letter
                count_numbers++;    // One more number
                sum_numbers += char_val; // Add its value to the sum
            }
        }

        // Calculate the numerator for the final power P_max
        // P_max = count_letters - count_numbers + sum_numbers / K
        // To express this as a single fraction a/b, we find a common denominator K:
        // P_max = ( (count_letters - count_numbers) * K / K ) + ( sum_numbers / K )
        // P_max = ( (count_letters - count_numbers) * K + sum_numbers ) / K
        long long numerator = (count_letters - count_numbers) * K + sum_numbers;
        long long denominator = K;

        // Find the greatest common divisor (GCD) of the numerator and denominator
        // std::gcd requires non-negative arguments. The 'numerator' can be negative, so use std::abs.
        // The 'denominator' (K) is always positive (1 <= K <= 1000).
        long long common_divisor = std::gcd(std::abs(numerator), denominator);

        // Simplify the fraction by dividing both numerator and denominator by their GCD
        long long a = numerator / common_divisor;
        long long b = denominator / common_divisor;

        // Output the simplified fraction a/b, space-separated
        std::cout << a << " " << b << std::endl;
    }

    return 0; // Indicate successful execution
}
#include <cstdio> // Required for scanf and printf
#include <cstring> // Required for strlen

int main() {
    // Use fast I/O. For C++, scanf/printf are generally faster than cin/cout
    // without explicit synchronization disabling.
    // However, for competitive programming, it's common to use:
    // std::ios_base::sync_with_stdio(false);
    // std::cin.tie(NULL);
    // with cin/cout. Since the problem explicitly recommends scanf/printf,
    // we will stick to them.

    // Declare a character array to store the input string.
    // Max length is 3 * 10^5, plus 1 for null terminator.
    char s[300005]; 
    
    // Read the input string.
    scanf("%s", s);
    
    // Get the length of the string.
    int n = strlen(s);
    
    // Declare a long long variable to store the total count of divisible substrings.
    // The answer can be large (up to ~4.5 * 10^10), so long long is necessary.
    long long count = 0;
    
    // Iterate through each character of the string.
    // 'i' represents the current ending index of potential substrings.
    for (int i = 0; i < n; ++i) {
        // Get the integer value of the current digit.
        int current_digit = s[i] - '0';
        
        // Check for single-digit substrings ending at 'i'.
        // A single-digit number is divisible by 4 if the digit itself is 0, 4, or 8.
        if (current_digit % 4 == 0) {
            // If divisible, this single-digit substring contributes 1 to the total count.
            count += 1;
        }
        
        // Check for multi-digit substrings ending at 'i'.
        // These substrings must have at least two digits.
        // Divisibility by 4 for numbers with two or more digits depends only on the
        // number formed by their last two digits.
        // So, we check the number formed by s[i-1]s[i].
        if (i > 0) { // Ensure there is a previous digit (s[i-1])
            // Get the integer value of the previous digit.
            int previous_digit = s[i-1] - '0';
            
            // Form the two-digit number.
            int two_digits_num = previous_digit * 10 + current_digit;
            
            // Check if this two-digit number is divisible by 4.
            if (two_digits_num % 4 == 0) {
                // If it is, then all substrings ending at 'i' and starting at or before 'i-1'
                // are divisible by 4.
                // The possible starting indices for such substrings are 0, 1, ..., i-1.
                // The number of such starting indices is 'i' (since indices are 0-based).
                // For example, if i=1, s[0]s[1] is checked. There is 1 such substring (s[0...1]).
                // If i=2, s[1]s[2] is checked. There are 2 such substrings (s[0...2], s[1...2]).
                // So, we add 'i' to the total count.
                count += i;
            }
        }
    }
    
    // Print the final count.
    printf("%lld\n", count);
    
    return 0;
}

#include <iostream> // Required for input/output operations (std::cin, std::cout, std::endl).
#include <string>   // Required for using std::string to store the input.
#include <vector>   // Not strictly necessary for this solution, but often useful in competitive programming.

int main() {
    // Optimize C++ standard streams for competitive programming.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams,
    // which can significantly speed up I/O operations.
    std::ios_base::sync_with_stdio(false);
    // std::cin.tie(NULL) prevents std::cout from being flushed before each std::cin operation.
    // This further optimizes I/O, especially when there's a lot of interleaved input and output.
    std::cin.tie(NULL);

    std::string s; // Declare a string variable to store the input.
    std::cin >> s; // Read the input string from standard input.

    // We use a dynamic programming approach to count the subsequences.
    // dp[0] will store the count of 'w's encountered so far. A 'w' is represented by "vv".
    // dp[1] will store the count of "wo" subsequences encountered so far.
    // dp[2] will store the count of "wow" subsequences encountered so far. This will be our final answer.
    // We use 'long long' for the counts because the maximum possible value can be up to 10^18
    // (e.g., if the string has 10^6 'v's and one 'o' in the middle, the number of 'w's can be ~10^6,
    // 'wo's can be ~10^6 * 10^6 = 10^12, and 'wow's can be ~10^12 * 10^6 = 10^18),
    // which exceeds the capacity of a 32-bit integer ('int').
    long long dp[3] = {0, 0, 0};

    // Iterate through the input string character by character.
    for (int i = 0; i < s.length(); ++i) {
        if (s[i] == 'o') {
            // If the current character is 'o':
            // This 'o' can form a "wo" subsequence with any 'w' ("vv") that appeared before it.
            // The number of new "wo" subsequences formed by this 'o' is equal to the total
            // number of 'w's (dp[0]) found up to the character just before this 'o'.
            dp[1] += dp[0];
        } else { // s[i] == 'v'
            // If the current character is 'v':
            // We need to check if it forms a "vv" pair (a 'w') with the previous character.
            // This check is only possible if 'i' is greater than 0 (i.e., there is a previous character).
            if (i > 0 && s[i-1] == 'v') {
                // If s[i-1] is also 'v', then s[i-1]s[i] forms a "vv" pair, which is a 'w'.

                // This newly formed 'w' (s[i-1]s[i]) can complete any "wo" subsequence
                // that appeared before it, forming a "wow" subsequence.
                // The number of new "wow" subsequences formed is equal to the total number of
                // "wo" subsequences (dp[1]) found up to the character just before this 'w'.
                dp[2] += dp[1];
                
                // This "vv" pair itself is a new 'w'. So, we increment the total count of 'w's.
                dp[0]++;
            }
        }
    }

    // After iterating through the entire string, dp[2] will hold the total count
    // of "wow" subsequences.
    std::cout << dp[2] << std::endl;

    return 0; // Indicate successful execution.
}

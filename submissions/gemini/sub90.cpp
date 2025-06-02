#include <iostream> // Required for input/output operations (cin, cout)
#include <string>   // Required for string manipulation

void solve() {
    int n, k; // Declare integers n and k for string length and parameter
    std::cin >> n >> k; // Read n and k from standard input
    std::string s; // Declare string s
    std::cin >> s; // Read string s from standard input

    // Initialize a boolean flag to track if a solution is possible.
    // We assume it's possible until a condition proves otherwise.
    bool possible = true;

    // The problem requires the string s to be formed as:
    // s = a_1 + a_2 + ... + a_k + a_{k+1} + R(a_k) + R(a_{k-1}) + ... + R(a_1).
    // Here, '+' denotes concatenation and R(x) is the reversed string x.
    // All a_i must be non-empty strings.

    // This structure implies a palindrome-like property.
    // The first character of s (s[0]) must be the first character of a_1.
    // The last character of s (s[n-1]) must be the first character of R(a_1),
    // which is the last character of a_1.
    // For the structure to hold, s[0] must be equal to s[n-1].
    // Similarly, s[1] must be equal to s[n-2], and so on, up to s[k-1] and s[n-k].
    // This is because the prefix a_1 + ... + a_k must be the reverse of the suffix R(a_k) + ... + R(a_1).
    // Since each a_i must be non-empty, the combined length of a_1 + ... + a_k is at least k.
    // Therefore, we must check if s[i] == s[n - 1 - i] for all i from 0 to k-1.
    for (int i = 0; i < k; ++i) {
        if (s[i] != s[n - 1 - i]) { // Compare character at index i with its symmetric counterpart from the end
            possible = false; // If they don't match, it's impossible to form the string as required
            break; // No need to check further, exit the loop
        }
    }

    // If the palindrome-like property holds for the first k characters,
    // we still need to ensure that a_{k+1} can be a non-empty string.
    // The total length of the parts a_1 + ... + a_k and R(a_k) + ... + R(a_1) is 2 * (sum of lengths of a_1 to a_k).
    // To satisfy the non-empty condition for all a_i, we can choose the simplest case:
    // a_1 = s[0], a_2 = s[1], ..., a_k = s[k-1]. Each of these has length 1.
    // Then R(a_1) = s[0], R(a_2) = s[1], ..., R(a_k) = s[k-1].
    // Because s[i] == s[n-1-i], these reversed parts match s[n-1], s[n-2], ..., s[n-k] respectively.
    // The total length consumed by these 2k characters is 2*k.
    // The remaining part of the string s, which would be a_{k+1}, has length n - 2*k.
    // For a_{k+1} to be non-empty, its length must be at least 1.
    // So, we must have n - 2*k >= 1.
    // If n - 2*k < 1, it means there isn't enough string left for a non-empty a_{k+1},
    // or k is too large such that the "outer" parts overlap or exceed the string length.
    if (possible) { // This check is only relevant if the previous palindrome check passed
        if (n - 2 * k < 1) { // Check if the length of the middle part (a_{k+1}) is less than 1
            possible = false; // If it is, a solution is not possible
        }
    }

    // Print "YES" if a solution is possible, otherwise print "NO".
    if (possible) {
        std::cout << "YES\n";
    } else {
        std::cout << "NO\n";
    }
}

int main() {
    // Optimize C++ standard streams for faster input/output.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams,
    // potentially speeding up I/O operations.
    // std::cin.tie(NULL) prevents std::cout from flushing before std::cin reads input,
    // which can also improve performance in competitive programming.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t; // Declare integer t for the number of test cases
    std::cin >> t; // Read the number of test cases
    while (t--) { // Loop t times, decrementing t each iteration
        solve(); // Call the solve function for each test case
    }

    return 0; // Indicate successful program execution
}
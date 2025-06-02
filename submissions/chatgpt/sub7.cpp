#include <cstdio>
#include <cstring>

// The problem asks for the number of substrings of a given string of digits
// that are divisible by 4. A substring can start with zero and must be contiguous.

// Key observation:
// - A number is divisible by 4 if its last two digits form a number divisible by 4.
// - For single-digit substrings, only '0', '4', and '8' are divisible by 4.

// We will iterate through the string and for each position, check:
// 1. The single digit at that position.
// 2. The two-digit number ending at that position (if possible).

int main() {
    char s[300005];
    // Fast input using scanf
    scanf("%s", s);
    int n = strlen(s);
    long long ans = 0;

    for (int i = 0; i < n; ++i) {
        // Check single digit substrings
        // If the digit itself is divisible by 4, count it
        if ((s[i] - '0') % 4 == 0) {
            ans++;
        }
        // Check two-digit substrings ending at position i (if i > 0)
        if (i > 0) {
            // Form the two-digit number from s[i-1] and s[i]
            int num = (s[i-1] - '0') * 10 + (s[i] - '0');
            if (num % 4 == 0) {
                // For each such substring, it starts at position i-1 and ends at i
                // So, for each such occurrence, we count one substring
                ans++;
            }
        }
    }

    // Output the answer using printf for fast output
    printf("%lld\n", ans);
    return 0;
}
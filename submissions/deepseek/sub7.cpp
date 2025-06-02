#include <cstdio>
#include <cstring>

int main() {
    char s[300001];
    scanf("%s", s);
    int len = strlen(s);
    long long count = 0;

    // A number is divisible by 4 if its last two digits form a number divisible by 4.
    // Single-digit substrings divisible by 4 are '0', '4', '8'.
    // For substrings of length >= 2, check the last two digits.
    for (int i = 0; i < len; ++i) {
        int digit = s[i] - '0';
        if (digit % 4 == 0) {
            count++;
        }
        if (i > 0) {
            int prev_digit = s[i-1] - '0';
            int num = prev_digit * 10 + digit;
            if (num % 4 == 0) {
                count += i; // All substrings ending at i with length >=2 contribute i times (0..i-1)
            }
        }
    }
    printf("%lld\n", count);
    return 0;
}
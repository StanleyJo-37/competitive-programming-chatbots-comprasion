#include <string>
#include <algorithm>

using namespace std;

int binaryDigitSum(long long n) {
    int sum = 0;
    while (n > 0) {
        sum += n % 2;
        n /= 2;
    }
    return sum;
}

int singleDigit(int n) {
    while (n >= 10) {
        n = binaryDigitSum(n);
    }
    return n;
}

int reduceToSingleDigitBinarySum(string nStr) {
    // Handle very large numbers (up to 10^20) by processing as a string to avoid overflow
    long long num = 0;
    for (char c : nStr) {
        num = num * 10 + (c - '0');
        // Early exit if num is already large enough to have a multi-digit sum
        if (num > 1e18) {
            break;
        }
    }
    
    // If the number is already a single digit, return it
    if (nStr.size() == 1) {
        return nStr[0] - '0';
    }
    
    // Compute the binary digit sum of the original number
    int sum = 0;
    for (char c : nStr) {
        int digit = c - '0';
        // Convert each digit to binary and add to sum
        while (digit > 0) {
            sum += digit % 2;
            digit /= 2;
        }
    }
    
    // Reduce the sum to a single digit if necessary
    return singleDigit(sum);
}
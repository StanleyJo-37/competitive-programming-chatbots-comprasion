#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Function to check if a number is a good number (can be represented as sum of distinct powers of 3)
bool isGood(long long n) {
    while (n > 0) {
        if (n % 3 == 2) {
            return false; // If any digit in base-3 is 2, it's not a good number
        }
        n /= 3;
    }
    return true;
}

// Function to find the smallest good number >= n
long long findSmallestGoodNumber(long long n) {
    while (true) {
        if (isGood(n)) {
            return n;
        }
        // Find the leftmost '2' in the base-3 representation of n
        long long m = n;
        long long power = 1;
        while (m > 0) {
            if (m % 3 == 2) {
                // To eliminate this '2', we need to round up to the next power of 3
                // For example, if n=2 (base3: 2), next good number is 3 (base3: 10)
                n = ((n / power) + 1) * power;
                break;
            }
            m /= 3;
            power *= 3;
        }
    }
}

int main() {
    int q;
    cin >> q;
    while (q--) {
        long long n;
        cin >> n;
        cout << findSmallestGoodNumber(n) << endl;
    }
    return 0;
}
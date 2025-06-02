#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

// Function to check if a number is prime using trial division up to sqrt(n)
bool isPrime(int n) {
    if (n <= 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    for (int i = 3; i * i <= n; i += 2) {
        if (n % i == 0) return false;
    }
    return true;
}

// Function to find the first prime sextuplet whose sum exceeds sum_limit
vector<int> find_primes_sextuplet(int sum_limit) {
    // The sextuplet is of the form [p, p+4, p+6, p+10, p+12, p+16]
    // The sum of the sextuplet is 6p + (4+6+10+12+16) = 6p + 48
    // So, 6p + 48 > sum_limit => p > (sum_limit - 48)/6
    // We start checking from p = 7 (the first known sextuplet)
    int p = 7;
    while (true) {
        // Check if p, p+4, p+6, p+10, p+12, p+16 are all primes
        if (isPrime(p) && isPrime(p + 4) && isPrime(p + 6) && 
            isPrime(p + 10) && isPrime(p + 12) && isPrime(p + 16)) {
            int sum = 6 * p + 48;
            if (sum > sum_limit) {
                return {p, p + 4, p + 6, p + 10, p + 12, p + 16};
            }
        }
        // Move to the next candidate p (must be of the form 30k + 7 or 30k + 11, etc., but for simplicity, we check all odd numbers)
        // Optimized: The starting prime p must be congruent to 7 mod 30 (based on known sextuplets)
        if (p % 30 == 7) {
            p += 4; // next candidate is p + 4 (11 mod 30)
        } else if (p % 30 == 11) {
            p += 14; // next candidate is p + 14 (25 mod 30, but 25 is not prime, so we skip to 30k + 7)
        } else if (p % 30 == 13) {
            p += 24; // next candidate is p + 24 (37 mod 30, which is 7 mod 30)
        } else if (p % 30 == 17) {
            p += 20; // next candidate is p + 20 (37 mod 30, which is 7 mod 30)
        } else if (p % 30 == 19) {
            p += 18; // next candidate is p + 18 (37 mod 30, which is 7 mod 30)
        } else if (p % 30 == 23) {
            p += 14; // next candidate is p + 14 (37 mod 30, which is 7 mod 30)
        } else if (p % 30 == 29) {
            p += 8; // next candidate is p + 8 (37 mod 30, which is 7 mod 30)
        } else {
            p += 2; // default increment for other cases (not optimal but works)
        }
    }
}
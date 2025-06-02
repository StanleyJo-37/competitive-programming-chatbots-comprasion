#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

// Function to generate primes up to a given limit using Sieve of Eratosthenes
void sieve(int limit, std::vector<bool>& is_prime, std::vector<int>& primes) {
    is_prime.assign(limit + 1, true);
    is_prime[0] = is_prime[1] = false;
    int sqrt_limit = static_cast<int>(std::sqrt(limit));
    for (int i = 2; i <= sqrt_limit; ++i) {
        if (is_prime[i]) {
            for (int j = i * i; j <= limit; j += i)
                is_prime[j] = false;
        }
    }
    for (int i = 2; i <= limit; ++i) {
        if (is_prime[i]) primes.push_back(i);
    }
}

// Main function to find the first prime sextuplet whose sum exceeds sum_limit
std::vector<int> find_primes_sextuplet(int sum_limit) {
    // The sextuplet is [p, p+4, p+6, p+10, p+12, p+16]
    // The sum is 6*p + (4+6+10+12+16) = 6*p + 48
    // To guarantee we find the answer, we need to sieve up to a high enough limit.
    // For the largest test, sum_limit < 29700000, so p can be at most (sum_limit-48)/6
    // But to be safe, we sieve up to sum_limit + 100000 (enough margin)
    int sieve_limit = sum_limit + 100000;
    std::vector<bool> is_prime;
    std::vector<int> primes;
    sieve(sieve_limit, is_prime, primes);

    // For each prime p, check if all sextuplet members are prime
    for (size_t i = 0; i < primes.size(); ++i) {
        int p = primes[i];
        int p1 = p + 4;
        int p2 = p + 6;
        int p3 = p + 10;
        int p4 = p + 12;
        int p5 = p + 16;
        // Check if all are within sieve and are prime
        if (p5 > sieve_limit) break;
        if (is_prime[p1] && is_prime[p2] && is_prime[p3] && is_prime[p4] && is_prime[p5]) {
            int sum = p + p1 + p2 + p3 + p4 + p5;
            if (sum > sum_limit) {
                // Return the sextuplet as a vector
                return {p, p1, p2, p3, p4, p5};
            }
        }
    }
    // If not found (should not happen with given constraints), return empty vector
    return {};
}

// For testing purposes
/*
int main() {
    std::vector<int> res1 = find_primes_sextuplet(70);
    for (int x : res1) std::cout << x << " ";
    std::cout << std::endl;

    std::vector<int> res2 = find_primes_sextuplet(600);
    for (int x : res2) std::cout << x << " ";
    std::cout << std::endl;
    return 0;
}
*/
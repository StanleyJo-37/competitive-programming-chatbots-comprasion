#include <vector> // Required for std::vector

// Define the maximum value up to which we need to check for primality.
// The largest possible 'p' for sum_limit ~2.97e7 is around 4.95e6.
// The largest term in the sextuplet is p + 16.
// So, 4.95e6 + 16 = 4,950,000 + 16 = 4,950,016.
// We set a slightly larger limit to be safe, e.g., 5,000,000 + 20.
const int MAX_PRIME_CHECK = 5000020;

// Use a static vector for the sieve to ensure it's initialized only once
// across multiple calls to find_primes_sextuplet (e.g., in test cases).
// std::vector<bool> is a specialized template that uses bits, making it memory efficient.
static std::vector<bool> is_prime_sieve(MAX_PRIME_CHECK, true);
static bool sieve_initialized = false; // Flag to track if the sieve has been run

// Function to initialize the Sieve of Eratosthenes.
// This function should be called only once.
void initialize_sieve() {
    // If the sieve has already been initialized, do nothing.
    if (sieve_initialized) {
        return;
    }

    // 0 and 1 are not prime numbers.
    is_prime_sieve[0] = is_prime_sieve[1] = false;

    // Apply the Sieve of Eratosthenes algorithm.
    // Iterate from 2 up to sqrt(MAX_PRIME_CHECK).
    for (long long p = 2; p * p < MAX_PRIME_CHECK; ++p) {
        // If p is prime, mark all its multiples as not prime.
        if (is_prime_sieve[p]) {
            // Start marking multiples from p*p, as smaller multiples
            // (e.g., 2*p, 3*p) would have already been marked by smaller primes.
            for (long long i = p * p; i < MAX_PRIME_CHECK; i += p)
                is_prime_sieve[i] = false;
        }
    }
    // Set the flag to true to indicate that the sieve is now initialized.
    sieve_initialized = true;
}

// Function to find the first prime sextuplet whose sum surpasses sum_limit.
std::vector<long long> find_primes_sextuplet(long long sum_limit) {
    // Ensure the sieve is initialized before performing primality checks.
    initialize_sieve();

    // Iterate through possible starting primes 'p'.
    // The problem states the first sextuplet is [7, 11, 13, 17, 19, 23],
    // so we can start checking from p = 7.
    // Primes 2 and 3 cannot be the starting prime 'p' for a valid sextuplet:
    // If p=2: [2, 6, 8, 12, 14, 18] - contains non-primes.
    // If p=3: [3, 7, 9, 13, 15, 19] - contains non-primes (9, 15).
    // Also, for p > 3, if p % 3 == 2, then p+4 would be divisible by 3 and > 3,
    // thus not prime. So p must be of the form 3k+1 (like 7, 13, 19, etc.).
    // However, simply iterating through all numbers and checking is_prime_sieve[p]
    // is sufficient and simpler, as the sieve handles non-primes efficiently.
    for (long long p = 7; ; ++p) {
        // Check if the largest term (p + 16) would exceed our precomputed sieve range.
        // This check is a safeguard; given the problem constraints, a valid sextuplet
        // should always be found within MAX_PRIME_CHECK.
        if (p + 16 >= MAX_PRIME_CHECK) {
            // If this point is reached, it means no sextuplet was found within the
            // precomputed range that satisfies the sum_limit. This should not happen
            // based on the problem's test constraints.
            break;
        }

        // Check if all six numbers in the potential sextuplet are prime.
        if (is_prime_sieve[p] &&
            is_prime_sieve[p + 4] &&
            is_prime_sieve[p + 6] &&
            is_prime_sieve[p + 10] &&
            is_prime_sieve[p + 12] &&
            is_prime_sieve[p + 16]) {

            // Calculate the sum of the six primes.
            // The sum is p + (p+4) + (p+6) + (p+10) + (p+12) + (p+16) = 6p + 48.
            long long current_sum = 6 * p + 48;

            // If the current sextuplet's sum surpasses the sum_limit,
            // this is the first such sextuplet, so return it.
            if (current_sum > sum_limit) {
                return {p, p + 4, p + 6, p + 10, p + 12, p + 16};
            }
        }
    }

    // This line should theoretically not be reached if the problem guarantees
    // a solution will always be found within the defined limits.
    // It's a fallback in case no sextuplet is found (e.g., if sum_limit is extremely high
    // or MAX_PRIME_CHECK is too small for some edge case not covered by constraints).
    return {}; // Return an empty vector indicating no solution found.
}
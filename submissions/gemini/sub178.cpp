#include <iostream> // Required for input/output operations (std::cin, std::cout)
#include <vector>   // Required for std::vector, a dynamic array

// Define the maximum value of N as per constraints (10^7).
// This constant is used to size the sieve arrays.
const int MAX_N = 10000000;

// is_prime[i] will be true if i is a prime number, false otherwise.
// std::vector<bool> is a specialized template that uses bits to store booleans,
// making it memory-efficient.
std::vector<bool> is_prime(MAX_N + 1, true);

// prime_count[i] will store the total number of prime numbers less than or equal to i.
// This allows for O(1) lookup of prime counts in ranges.
std::vector<int> prime_count(MAX_N + 1, 0);

/**
 * @brief Implements the Sieve of Eratosthenes to precompute prime numbers
 *        up to MAX_N and then calculates prefix sums of prime counts.
 *
 * This function runs once at the beginning of the program.
 * Time Complexity: O(MAX_N log log MAX_N) for sieve, O(MAX_N) for prefix sums.
 * Space Complexity: O(MAX_N) for storing prime flags and counts.
 */
void sieve() {
    // 0 and 1 are not considered prime numbers.
    is_prime[0] = is_prime[1] = false;

    // Iterate from 2 up to sqrt(MAX_N).
    // If a number 'p' is prime, mark all its multiples (starting from p*p) as not prime.
    // Multiples smaller than p*p would have already been marked by smaller prime factors.
    for (long long p = 2; p * p <= MAX_N; ++p) {
        if (is_prime[p]) {
            // Mark multiples of p as not prime.
            for (long long i = p * p; i <= MAX_N; i += p)
                is_prime[i] = false;
        }
    }

    // After sieving, populate the prime_count array.
    // prime_count[i] stores the number of primes up to i.
    // This is a prefix sum array.
    for (int i = 2; i <= MAX_N; ++i) {
        prime_count[i] = prime_count[i - 1]; // Inherit count from previous number
        if (is_prime[i]) {
            prime_count[i]++; // Increment if current number 'i' is prime
        }
    }
}

/**
 * @brief Main function to solve the problem.
 *
 * Reads test cases and for each N, calculates the number of groups.
 */
int main() {
    // Optimize C++ standard streams for faster input/output.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams.
    // std::cin.tie(NULL) prevents std::cout from flushing before std::cin reads input.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    // Call the sieve function to precompute primes and their counts.
    // This is done only once before processing any test cases.
    sieve();

    int T;
    std::cin >> T; // Read the number of test cases

    // Process each test case.
    while (T--) {
        int N;
        std::cin >> N; // Read the integer N for the current test case

        // Handle small N values as special cases.
        // The problem states "choose 2 distinct integers".
        if (N == 2) {
            // If N=2, the only integer in the range [2, N] is 2.
            // It's impossible to choose 2 distinct integers.
            // Therefore, no merging operations can occur.
            // The number 2 forms a single group by itself.
            std::cout << 1 << "\n";
        } else if (N == 3) {
            // If N=3, the integers in the range [2, N] are {2, 3}.
            // We can choose (2, 3). Their greatest common divisor (gcd(2, 3)) is 1.
            // Since gcd(2, 3) is not greater than 1, they do not merge.
            // Thus, {2} forms one group and {3} forms another.
            // Total groups = 2.
            std::cout << 2 << "\n";
        } else {
            // For N >= 4, a general pattern emerges:
            // All numbers X in the range [2, N] that are either:
            // 1. Composite numbers.
            // 2. Prime numbers P' such that 2P' <= N (i.e., P' <= N/2).
            // These numbers will all form one large connected group.
            //
            // Reasoning:
            // - Any composite number C <= N (for N >= 4) must have at least one prime factor p <= N/2.
            //   (Proof by contradiction: If all prime factors p_i of C are > N/2, then C = p_1 * p_2 * ... * p_k.
            //   Since C is composite, k >= 2. Thus C >= p_1 * p_2 > (N/2) * (N/2) = N^2/4.
            //   For N >= 4, N^2/4 > N (e.g., for N=4, 16/4=4; for N=5, 25/4=6.25>5).
            //   So, C would be > N, which contradicts C <= N.
            //   Therefore, any composite C <= N must have a prime factor p <= N/2.
            //   This means C is connected to p (via common factor p)).
            // - Any prime P' <= N/2 is connected to 2P' (since 2P' <= N, and they share factor P').
            // - The number 2P' is connected to 2 (as gcd(2P', 2) = 2).
            // Combining these, any composite number C <= N is connected to some prime p <= N/2,
            // which in turn is connected to 2. So, all composite numbers are connected to 2.
            // Similarly, all primes P' <= N/2 are connected to 2.
            // Thus, all these numbers form one large group, which includes the number 2.
            //
            // The numbers that form their own distinct groups are prime numbers P such that 2P > N.
            // This condition is equivalent to P > N/2.
            // For such a prime P, its only multiple within the range [2, N] is P itself.
            // Therefore, P cannot share a common factor (P) with any other number X in [2, N]
            // (because X would have to be kP for some integer k >= 2, but kP would be > N).
            // So, each such prime P forms its own separate group.
            //
            // The total number of groups is:
            // 1 (for the large group containing 2 and all connected numbers)
            // + (the count of primes P such that N/2 < P <= N).
            // The count of primes P such that N/2 < P <= N can be found using the precomputed
            // prime_count array: prime_count[N] - prime_count[N/2].
            std::cout << 1 + (prime_count[N] - prime_count[N / 2]) << "\n";
        }
    }

    return 0; // Indicate successful execution
}

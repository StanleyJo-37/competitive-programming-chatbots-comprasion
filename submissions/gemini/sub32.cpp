#include <iostream>
#include <vector>

// Define the maximum value for 'a' and 'b' as per problem constraints.
const int MAX_VAL = 5000000;

// spf[i] stores the smallest prime factor of i.
// Initialized to 0, will be populated by the sieve.
int spf[MAX_VAL + 1];

// dp[i] stores the total count of prime factors of i (with multiplicity).
// For example, dp[12] = 3 because 12 = 2 * 2 * 3.
int dp[MAX_VAL + 1];

// prefix_sum_dp[i] stores the sum of dp[j] for all j from 1 to i.
// This allows O(1) calculation of sum(dp[j]) for a range [b+1, a].
long long prefix_sum_dp[MAX_VAL + 1]; // Using long long to be safe, though int might suffice.

// Function to precompute spf, dp, and prefix_sum_dp arrays.
void precompute() {
    // Initialize spf array: every number is initially considered its own smallest prime factor.
    // This assumption holds true for prime numbers.
    for (int i = 2; i <= MAX_VAL; ++i) {
        spf[i] = i;
    }

    // Linear Sieve algorithm to find the smallest prime factor (spf) for each number.
    // This sieve runs in O(MAX_VAL) time.
    std::vector<int> primes; // Stores all prime numbers found so far.
    for (int i = 2; i <= MAX_VAL; ++i) {
        // If spf[i] is still i, it means i has not been marked by any smaller prime factor,
        // thus i must be a prime number.
        if (spf[i] == i) {
            primes.push_back(i);
        }

        // For each prime 'p' found so far:
        // We mark multiples of 'p' (i * p) with 'p' as their smallest prime factor.
        // The loop breaks if:
        // 1. 'p' is greater than spf[i]: This optimization ensures that each composite number
        //    'k' is marked exactly once by its smallest prime factor. If p > spf[i], then
        //    i*p would have already been marked by spf[i] (which is smaller than p).
        // 2. 'i * p' exceeds MAX_VAL: We only care about numbers within our defined range.
        for (int p : primes) {
            if (p > spf[i] || (long long)i * p > MAX_VAL) {
                break;
            }
            spf[i * p] = p;
        }
    }

    // Compute dp values: total number of prime factors for each number.
    // dp[1] is 0 as 1 has no prime factors.
    dp[1] = 0;
    // For any number i > 1, its total prime factors count is 1 (for spf[i]) plus
    // the total prime factors count of i / spf[i].
    for (int i = 2; i <= MAX_VAL; ++i) {
        dp[i] = 1 + dp[i / spf[i]];
    }

    // Compute prefix sums of dp values.
    // prefix_sum_dp[k] = sum_{j=1}^{k} dp[j].
    // This allows us to answer queries for sum of dp values in a range [b+1, a] in O(1) time.
    prefix_sum_dp[0] = 0;
    for (int i = 1; i <= MAX_VAL; ++i) {
        prefix_sum_dp[i] = prefix_sum_dp[i-1] + dp[i];
    }
}

int main() {
    // Optimize C++ standard streams for faster input/output operations.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams.
    // std::cin.tie(NULL) prevents std::cout from flushing before std::cin reads input.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    // Call the precomputation function once before processing any test cases.
    precompute();

    int t;
    std::cin >> t; // Read the number of test cases.
    while (t--) {
        int a, b;
        std::cin >> a >> b; // Read the input integers a and b for the current test case.

        // The problem asks for the maximum number of rounds, which is the total count of prime factors
        // of n = a! / b!.
        // n = (b+1) * (b+2) * ... * a.
        // The total count of prime factors of n is sum_{i=b+1}^{a} (total prime factors of i).
        // This is equivalent to sum_{i=b+1}^{a} dp[i].
        // Using prefix sums, this sum can be calculated as prefix_sum_dp[a] - prefix_sum_dp[b].
        long long result = prefix_sum_dp[a] - prefix_sum_dp[b];
        std::cout << result << "\n"; // Output the calculated result followed by a newline.
    }

    return 0; // Indicate successful execution.
}
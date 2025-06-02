#include <iostream>
#include <vector>
#include <numeric>
#include <array> // For std::array

// Modulo constant for calculations
const int MOD = 1e9 + 7;

// Maximum value of N as per constraints
const int N_MAX = 400005;

// is_prime_sum[s] is true if sum 's' is a prime number.
// Max sum for 5 digits is 45 (9*5).
bool is_prime_sum[46];

// is_valid_5_tuple[a][b][c][d][e] is true if the 5-tuple (a,b,c,d,e) satisfies
// all three rules for consecutive sums ending at 'e'.
// Rules: c+d+e is prime, b+c+d+e is prime, a+b+c+d+e is prime.
bool is_valid_5_tuple[10][10][10][10][10];

// total_counts[i] stores the total number of valid i-digit numbers.
long long total_counts[N_MAX];

// prev_dp and curr_dp are used for dynamic programming.
// dp[d0][d1][d2][d3] stores the count of valid prefixes of length 'i'
// ending with digits d0, d1, d2, d3.
// Using std::array for fixed-size multi-dimensional arrays for better performance
// and stack allocation if small enough, or static allocation.
std::array<std::array<std::array<std::array<long long, 10>, 10>, 10>, 10> prev_dp;
std::array<std::array<std::array<std::array<long long, 10>, 10>, 10>, 10> curr_dp;

// Function to precompute primes up to 45.
// This uses a hardcoded list of primes for efficiency given the small range.
void sieve() {
    // Initialize all sums as not prime
    std::fill(is_prime_sum, is_prime_sum + 46, false);
    // List of primes up to 45
    int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43};
    // Mark primes as true in the boolean array
    for (int p : primes) {
        is_prime_sum[p] = true;
    }
}

// Function to precompute all valid 5-tuples (a,b,c,d,e).
// A 5-tuple is valid if the sums of its last 3, 4, and 5 digits are all prime.
void precompute_valid_5_tuples() {
    for (int a = 0; a <= 9; ++a) {
        for (int b = 0; b <= 9; ++b) {
            for (int c = 0; c <= 9; ++c) {
                for (int d = 0; d <= 9; ++d) {
                    for (int e = 0; e <= 9; ++e) {
                        // Check the three conditions for a valid 5-tuple
                        if (is_prime_sum[c + d + e] &&         // Sum of last 3 digits (c,d,e)
                            is_prime_sum[b + c + d + e] &&     // Sum of last 4 digits (b,c,d,e)
                            is_prime_sum[a + b + c + d + e]) { // Sum of last 5 digits (a,b,c,d,e)
                            is_valid_5_tuple[a][b][c][d][e] = true;
                        } else {
                            is_valid_5_tuple[a][b][c][d][e] = false;
                        }
                    }
                }
            }
        }
    }
}

// Main function to precompute DP values for all N up to N_MAX.
void precompute_dp() {
    // Initialize DP arrays to 0.
    // This ensures that non-reachable states have a count of 0.
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            for (int k = 0; k < 10; ++k) {
                for (int l = 0; l < 10; ++l) {
                    prev_dp[i][j][k][l] = 0;
                    curr_dp[i][j][k][l] = 0;
                }
            }
        }
    }

    // Base cases for N=1, 2, 3, 4.
    // The first digit (d1) of the N-digit number cannot be 0.

    // N=1: d1. d1 must be 1-9. No rules apply.
    total_counts[1] = 9; // Numbers are 1, 2, ..., 9

    // N=2: d1 d2. d1 must be 1-9, d2 can be 0-9. No rules apply.
    total_counts[2] = 90; // 9 choices for d1 * 10 choices for d2

    // N=3: d1 d2 d3. d1 must be 1-9. Rule: d1+d2+d3 must be prime.
    long long count_N3 = 0;
    for (int d1 = 1; d1 <= 9; ++d1) {
        for (int d2 = 0; d2 <= 9; ++d2) {
            for (int d3 = 0; d3 <= 9; ++d3) {
                if (is_prime_sum[d1 + d2 + d3]) {
                    count_N3++;
                }
            }
        }
    }
    total_counts[3] = count_N3;

    // N=4: d1 d2 d3 d4. d1 must be 1-9. Rules:
    // d1+d2+d3 prime
    // d2+d3+d4 prime
    // d1+d2+d3+d4 prime
    long long count_N4 = 0;
    for (int d1 = 1; d1 <= 9; ++d1) {
        for (int d2 = 0; d2 <= 9; ++d2) {
            for (int d3 = 0; d3 <= 9; ++d3) {
                for (int d4 = 0; d4 <= 9; ++d4) {
                    // Check all three rules for the 4-digit number
                    if (is_prime_sum[d1 + d2 + d3] &&
                        is_prime_sum[d2 + d3 + d4] &&
                        is_prime_sum[d1 + d2 + d3 + d4]) {
                        // Store this count in prev_dp for the next iteration (N=5)
                        // The state (d1,d2,d3,d4) represents the last four digits of the 4-digit number.
                        prev_dp[d1][d2][d3][d4] = 1;
                        count_N4++;
                    }
                }
            }
        }
    }
    total_counts[4] = count_N4;

    // DP for N >= 5.
    // For length 'i', we compute curr_dp based on prev_dp (length i-1).
    // The state (d1,d2,d3,d4) for curr_dp means the number ends with d1 d2 d3 d4.
    // The digit preceding d1 is d0.
    for (int i = 5; i <= N_MAX; ++i) {
        // Clear curr_dp for the current length 'i' before filling it.
        for (int d1 = 0; d1 < 10; ++d1) {
            for (int d2 = 0; d2 < 10; ++d2) {
                for (int d3 = 0; d3 < 10; ++d3) {
                    for (int d4 = 0; d4 < 10; ++d4) {
                        curr_dp[d1][d2][d3][d4] = 0;
                    }
                }
            }
        }

        long long current_total_count = 0;
        // Iterate over all possible last four digits (d1, d2, d3, d4) for the current length i.
        // These digits can be 0-9, as they are not the first digit of the overall number.
        for (int d1 = 0; d1 <= 9; ++d1) {
            for (int d2 = 0; d2 <= 9; ++d2) {
                for (int d3 = 0; d3 <= 9; ++d3) {
                    for (int d4 = 0; d4 <= 9; ++d4) {
                        // Iterate over the digit d0 that would precede d1.
                        // d0 can be 0-9.
                        for (int d0 = 0; d0 <= 9; ++d0) {
                            // Check if the 5-tuple (d0, d1, d2, d3, d4) is valid.
                            // This check implicitly covers all three rules for this segment.
                            if (is_valid_5_tuple[d0][d1][d2][d3][d4]) {
                                // Add the count from the previous state (d0, d1, d2, d3)
                                // to the current state (d1, d2, d3, d4).
                                // The modulo operation is applied at each addition to prevent overflow.
                                curr_dp[d1][d2][d3][d4] = (curr_dp[d1][d2][d3][d4] + prev_dp[d0][d1][d2][d3]) % MOD;
                            }
                        }
                        // Accumulate the total count for length 'i'
                        current_total_count = (current_total_count + curr_dp[d1][d2][d3][d4]) % MOD;
                    }
                }
            }
        }
        total_counts[i] = current_total_count;
        // Swap prev_dp and curr_dp for the next iteration.
        // This efficiently updates prev_dp to the newly computed curr_dp.
        prev_dp.swap(curr_dp);
    }
}

int main() {
    // Optimize C++ standard streams for faster input/output.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    // Perform all necessary precomputations.
    sieve();
    precompute_valid_5_tuples();
    precompute_dp();

    int q;
    std::cin >> q; // Read the number of queries

    // Process each query by printing the precomputed result.
    while (q--) {
        int n;
        std::cin >> n; // Read n for the current query
        std::cout << total_counts[n] << "\n"; // Print the precomputed answer
    }

    return 0;
}

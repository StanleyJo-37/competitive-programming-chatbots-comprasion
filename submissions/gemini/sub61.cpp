#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <cmath> // For __builtin_popcountll

// Function to solve a single test case
void solve() {
    long long n;
    std::cin >> n;

    // Precompute factorials.
    // We only need factorials up to 13! because 14! > 10^12.
    // 0! = 1
    // 1! = 1
    // 2! = 2
    // 3! = 6
    // ...
    // 13! = 6,227,020,800
    std::vector<long long> factorials;
    long long current_factorial = 1;
    for (int i = 0; i <= 13; ++i) {
        if (i == 0) {
            current_factorial = 1;
        } else {
            // Check for potential overflow before multiplication.
            // Max long long is ~9e18. 13! is ~6e9. 14! is ~8.7e10.
            // 14! is the first factorial that exceeds 10^12.
            // We only care about factorials <= N_MAX = 10^12.
            // The condition `current_factorial > n / i` is a common way to check for `current_factorial * i > n`
            // without overflowing `current_factorial * i` itself.
            // Here, `n` is the input, not the maximum possible value.
            // We should check against `10^12` or `LLONG_MAX` if we want to precompute all possible factorials.
            // However, since we only need factorials up to 13! (which is less than 10^12),
            // and 14! would exceed 10^12, we can simply stop at 13!.
            // The loop condition `i <= 13` already ensures this.
            current_factorial *= i;
        }
        factorials.push_back(current_factorial);
    }

    // The set of powerful numbers consists of powers of two and factorials.
    // We need to represent N as a sum of *distinct* powerful numbers.
    // Powers of two are $2^0, 2^1, 2^2, \ldots$.
    // Factorials are $0!, 1!, 2!, 3!, \ldots$.
    // Overlaps:
    // 1 ($0!, 1!, 2^0$)
    // 2 ($2!, 2^1$)
    // All other factorials ($3!, 4!, \ldots, 13!$) are not powers of two.
    // This is because for $d \ge 3$, $d!$ contains an odd prime factor (e.g., 3),
    // while powers of two only have 2 as a prime factor.
    // So, we can separate the powerful numbers into two disjoint sets:
    // 1. Factorials that are NOT powers of two: {6, 24, 120, ..., 13!}
    // 2. Powers of two: {1, 2, 4, 8, ..., 2^k, ...}
    //
    // The strategy is to iterate through all possible subsets of the "factorials that are NOT powers of two".
    // For each subset, calculate its sum and the count of numbers used.
    // The remaining value (n - sum) must then be represented as a sum of distinct powers of two.
    // The minimum number of distinct powers of two required to sum to a value X is simply the count of set bits in X's binary representation (__builtin_popcountll(X)).
    // Since the two sets are disjoint, all numbers chosen will be distinct.

    // Create the list of factorials that are not powers of two.
    // These are 3!, 4!, ..., 13!.
    std::vector<long long> non_power_of_2_factorials;
    for (int i = 3; i < factorials.size(); ++i) { // Start from 3! (index 3 in factorials vector)
        non_power_of_2_factorials.push_back(factorials[i]);
    }

    // Initialize minimum k to a very large value.
    // The maximum possible k is small: 11 (for all non-power-of-2 factorials) + 64 (for powers of 2) = 75.
    int min_k = 100; 

    // Iterate through all subsets of non_power_of_2_factorials using a bitmask.
    // There are 11 such factorials (3! to 13!), so 2^11 = 2048 subsets. This is very fast.
    int num_factorials_to_consider = non_power_of_2_factorials.size();
    for (int i = 0; i < (1 << num_factorials_to_consider); ++i) {
        long long current_sum_factorials = 0;
        int current_count_factorials = 0;

        // Build the current sum and count from the selected factorials.
        for (int j = 0; j < num_factorials_to_consider; ++j) {
            if ((i >> j) & 1) { // If the j-th bit is set, include this factorial
                current_sum_factorials += non_power_of_2_factorials[j];
                current_count_factorials++;
            }
        }

        // If the sum of selected factorials already exceeds n, this path is invalid.
        if (current_sum_factorials > n) {
            continue;
        }

        // Calculate the remaining value that needs to be formed by powers of two.
        long long remaining_n = n - current_sum_factorials;

        // The number of distinct powers of two needed for remaining_n is its population count.
        // __builtin_popcountll is a GCC extension for counting set bits in a long long.
        int powers_of_2_count = __builtin_popcountll(remaining_n);

        // Total count for this combination.
        int total_k = current_count_factorials + powers_of_2_count;

        // Update the minimum k found so far.
        min_k = std::min(min_k, total_k);
    }

    std::cout << min_k << std::endl;
}

int main() {
    // Optimize C++ standard streams for competitive programming.
    // This unties cin/cout from stdio and prevents flushing cout before cin.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}

#include <iostream>
#include <vector>

int main() {
    // Optimize C++ standard streams for competitive programming.
    // This unties cin/cout from stdio and prevents flushing cout before cin.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    long long n, l, r;
    std::cin >> n >> l >> r;

    long long MOD = 1e9 + 7;

    // Calculate the count of numbers in the range [l, r] for each remainder modulo 3.
    // counts[0]: numbers x such that x % 3 == 0
    // counts[1]: numbers x such that x % 3 == 1
    // counts[2]: numbers x such that x % 3 == 2
    std::vector<long long> counts(3);

    // Total numbers in the range [l, r]
    long long total_numbers_in_range = r - l + 1;

    // Each remainder (0, 1, 2) appears equally often in full cycles of 3 numbers.
    long long base_count = total_numbers_in_range / 3;
    counts[0] = base_count;
    counts[1] = base_count;
    counts[2] = base_count;

    // Handle the remaining numbers (if total_numbers_in_range is not a multiple of 3).
    // These are l, l+1, ..., l + (total_numbers_in_range % 3) - 1.
    long long remaining_numbers = total_numbers_in_range % 3;
    long long start_remainder = l % 3;

    // Distribute the remaining numbers based on the starting remainder.
    // For example, if l % 3 == 0, the sequence of remainders starts 0, 1, 2, ...
    // If l % 3 == 1, the sequence of remainders starts 1, 2, 0, ...
    // If l % 3 == 2, the sequence of remainders starts 2, 0, 1, ...
    for (int i = 0; i < remaining_numbers; ++i) {
        counts[(start_remainder + i) % 3]++;
    }

    // Dynamic programming approach:
    // dp_prev[j] represents the number of ways to form an array of length (i-1)
    // such that the sum of its elements modulo 3 is j.
    // dp_curr[j] represents the number of ways for length i.
    // We only need to store the DP values for the previous length to calculate the current length,
    // thus optimizing space to O(1).
    std::vector<long long> dp_prev(3);
    std::vector<long long> dp_curr(3);

    // Base case: For an empty array (length 0), the sum is 0. There's 1 way to achieve this.
    dp_prev[0] = 1;
    dp_prev[1] = 0;
    dp_prev[2] = 0;

    // Iterate from array length 1 up to n.
    for (int i = 1; i <= n; ++i) {
        // Calculate dp_curr[0]: number of ways to get sum % 3 == 0 for current length i.
        // This can be achieved by combining:
        // (previous sum % 3 == 0) + (current number % 3 == 0)
        // (previous sum % 3 == 1) + (current number % 3 == 2)
        // (previous sum % 3 == 2) + (current number % 3 == 1)
        dp_curr[0] = (dp_prev[0] * counts[0] % MOD +
                      dp_prev[1] * counts[2] % MOD +
                      dp_prev[2] * counts[1] % MOD) % MOD;

        // Calculate dp_curr[1]: number of ways to get sum % 3 == 1 for current length i.
        // This can be achieved by combining:
        // (previous sum % 3 == 0) + (current number % 3 == 1)
        // (previous sum % 3 == 1) + (current number % 3 == 0)
        // (previous sum % 3 == 2) + (current number % 3 == 2)
        dp_curr[1] = (dp_prev[0] * counts[1] % MOD +
                      dp_prev[1] * counts[0] % MOD +
                      dp_prev[2] * counts[2] % MOD) % MOD;

        // Calculate dp_curr[2]: number of ways to get sum % 3 == 2 for current length i.
        // This can be achieved by combining:
        // (previous sum % 3 == 0) + (current number % 3 == 2)
        // (previous sum % 3 == 1) + (current number % 3 == 1)
        // (previous sum % 3 == 2) + (current number % 3 == 0)
        dp_curr[2] = (dp_prev[0] * counts[2] % MOD +
                      dp_prev[1] * counts[1] % MOD +
                      dp_prev[2] * counts[0] % MOD) % MOD;

        // Update dp_prev to dp_curr for the next iteration (next array length).
        dp_prev = dp_curr;
    }

    // The final answer is the number of ways to form an array of length n
    // such that the sum of its elements modulo 3 is 0.
    std::cout << dp_prev[0] << std::endl;

    return 0;
}
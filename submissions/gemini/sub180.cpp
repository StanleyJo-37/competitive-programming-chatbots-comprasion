#include <iostream>
#include <vector>

// Define the maximum value for r, which is 10^5.
// This constant is used to size our precomputation arrays.
const int MAX_R = 100000;

// Global vectors to store precomputed values.
// Using global variables allows them to be initialized once and
// persist across multiple test cases without being reallocated.

// sigma_values[k] will store the sum of all divisors of k.
// For example, sigma_values[6] = 1 + 2 + 3 + 6 = 12.
std::vector<long long> sigma_values(MAX_R + 1);

// f_values[i] will store f(i), which is defined as the sum of all odd divisors of i.
// For example, f(10) = 1 + 5 = 6.
std::vector<long long> f_values(MAX_R + 1);

// prefix_sum_f[k] will store the cumulative sum f(1) + f(2) + ... + f(k).
// This allows for efficient range sum queries.
std::vector<long long> prefix_sum_f(MAX_R + 1);

// Function to perform all necessary precomputations before handling test cases.
void precompute() {
    // Step 1: Calculate sigma(k) for all k from 1 to MAX_R.
    // The sum of divisors function sigma(k) is computed using a sieve-like approach.
    // For each number 'i' from 1 to MAX_R, we iterate through its multiples 'j' (i, 2i, 3i, ...)
    // up to MAX_R. 'i' is a divisor of 'j', so we add 'i' to sigma_values[j].
    // This approach has a time complexity of O(MAX_R * log(MAX_R)).
    for (int i = 1; i <= MAX_R; ++i) {
        for (int j = i; j <= MAX_R; j += i) {
            sigma_values[j] += i;
        }
    }

    // Step 2: Calculate f(i) for all i from 1 to MAX_R.
    // f(i) is the sum of all odd divisors of i.
    // Any positive integer 'i' can be uniquely expressed as i = 2^k * m, where 'm' is an odd integer.
    // The key insight is that all odd divisors of 'i' are precisely the divisors of its odd part 'm'.
    // Therefore, f(i) is simply the sum of all divisors of 'm' (which is sigma(m)).
    // We find 'm' by repeatedly dividing 'i' by 2 until it becomes odd.
    // This loop runs at most log2(i) times for each 'i'.
    // The total time complexity for this step is O(MAX_R * log(MAX_R)).
    for (int i = 1; i <= MAX_R; ++i) {
        int m = i;
        // Find the largest odd divisor 'm' of 'i'.
        while (m % 2 == 0) {
            m /= 2;
        }
        // Assign f(i) as the sum of divisors of 'm'.
        f_values[i] = sigma_values[m];
    }

    // Step 3: Calculate prefix sums of f_values.
    // prefix_sum_f[k] stores the sum f(1) + f(2) + ... + f(k).
    // This allows us to answer range sum queries (sum from l to r) in O(1) time
    // using the formula: sum(l, r) = prefix_sum_f[r] - prefix_sum_f[l-1].
    // The time complexity for this step is O(MAX_R).
    prefix_sum_f[0] = 0; // Initialize base case for prefix sum.
    for (int i = 1; i <= MAX_R; ++i) {
        prefix_sum_f[i] = prefix_sum_f[i-1] + f_values[i];
    }
}

int main() {
    // Optimize C++ standard streams for faster input/output.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams.
    // std::cin.tie(NULL) prevents cin from flushing cout before each input operation.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    // Call the precomputation function once at the beginning of the program.
    // This ensures all necessary data is ready before processing any test cases.
    precompute();

    int T; // Variable to store the number of test cases.
    std::cin >> T; // Read the number of test cases.

    // Loop through each test case.
    while (T--) {
        int l, r; // Variables to store the range [l, r] for the current query.
        std::cin >> l >> r; // Read the range l and r.

        // Calculate the sum f(l) + ... + f(r) using the precomputed prefix sums.
        // The sum is prefix_sum_f[r] - prefix_sum_f[l-1].
        // The result is stored in a long long to accommodate large sums.
        long long result = prefix_sum_f[r] - prefix_sum_f[l-1];
        
        // Output the calculated sum followed by a newline character.
        std::cout << result << "\n";
    }

    return 0; // Indicate successful execution.
}

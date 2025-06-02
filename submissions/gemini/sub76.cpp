#include <iostream>
#include <vector>
#include <algorithm> // For std::max

int main() {
    // Optimize C++ standard streams for competitive programming.
    // This unties cin/cout from stdio and prevents flushing cout before cin.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n; // Number of elements
    int k; // Maximum number of operations
    long long x; // Multiplier for each operation

    // Read n, k, x from standard input
    std::cin >> n >> k >> x;

    // Declare a vector to store the n numbers.
    // Use long long to accommodate potential large values after multiplication,
    // and to be consistent with bitwise OR operations which will result in large numbers.
    std::vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    // Calculate x raised to the power of k.
    // This is the total multiplier applied to one number.
    // Since x can be up to 8 and k up to 10, x_power_k can be 8^10 = 2^30.
    // This value fits within a long long.
    long long x_power_k = 1;
    for (int i = 0; i < k; ++i) {
        x_power_k *= x;
    }

    // Precompute prefix ORs.
    // prefix_OR[i] stores the bitwise OR of a[0] through a[i].
    // This allows efficient calculation of OR sum of a prefix segment.
    std::vector<long long> prefix_OR(n);
    prefix_OR[0] = a[0];
    for (int i = 1; i < n; ++i) {
        prefix_OR[i] = prefix_OR[i - 1] | a[i];
    }

    // Precompute suffix ORs.
    // suffix_OR[i] stores the bitwise OR of a[i] through a[n-1].
    // This allows efficient calculation of OR sum of a suffix segment.
    std::vector<long long> suffix_OR(n);
    suffix_OR[n - 1] = a[n - 1];
    for (int i = n - 2; i >= 0; --i) {
        suffix_OR[i] = suffix_OR[i + 1] | a[i];
    }

    long long max_overall_OR = 0; // Initialize the maximum OR value found

    // Iterate through each number a[i] in the array.
    // The problem asks to maximize the bitwise OR of all numbers.
    // Given that 'k' is very small (up to 10) and 'x' is also small (up to 8),
    // applying all 'k' operations to a single number 'a[i]' is the optimal strategy.
    // This is because multiplying a number by x^k makes it significantly larger,
    // which tends to set higher-order bits in the final OR sum, dominating contributions
    // from other numbers or from distributing operations.
    // For each a[i], we calculate the OR sum of (all other numbers) | (a[i] * x^k).
    for (int i = 0; i < n; ++i) {
        long long current_OR_without_ai = 0; // OR sum of all numbers EXCEPT a[i]

        // If there are elements before a[i], include their OR sum from prefix_OR.
        // This covers the range a[0]...a[i-1].
        if (i > 0) {
            current_OR_without_ai |= prefix_OR[i - 1];
        }
        // If there are elements after a[i], include their OR sum from suffix_OR.
        // This covers the range a[i+1]...a[n-1].
        if (i < n - 1) {
            current_OR_without_ai |= suffix_OR[i + 1];
        }

        // Calculate the value of a[i] after applying all k operations.
        // a[i] can be up to 10^9, x_power_k up to 2^30. Their product can be ~10^18,
        // which fits in a long long.
        long long modified_ai = a[i] * x_power_k;

        // Calculate the total OR sum for this specific choice of modifying a[i].
        // It's the OR of all other numbers (current_OR_without_ai) and the modified a[i].
        long long current_total_OR = current_OR_without_ai | modified_ai;

        // Update the maximum overall OR value found so far.
        max_overall_OR = std::max(max_overall_OR, current_total_OR);
    }

    // Output the maximum possible bitwise OR value.
    std::cout << max_overall_OR << std::endl;

    return 0;
}

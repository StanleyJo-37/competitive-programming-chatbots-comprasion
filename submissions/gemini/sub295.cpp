#include <iostream>
#include <vector>
#include <map>
#include <cmath> // For sqrt

int main() {
    // Optimize C++ standard streams for competitive programming.
    // This unties cin/cout from stdio and disables synchronization with C stdio,
    // which can significantly speed up I/O operations.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    long long k;
    std::cin >> n >> k;

    std::vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    // Step 1: Find prime factorization of k.
    // Store prime factors and their required exponents in a map.
    std::map<long long, int> k_prime_factors;
    long long temp_k = k;
    for (long long i = 2; i * i <= temp_k; ++i) {
        while (temp_k % i == 0) {
            k_prime_factors[i]++;
            temp_k /= i;
        }
    }
    if (temp_k > 1) { // If temp_k is still greater than 1, it's a prime factor itself
        k_prime_factors[temp_k]++;
    }

    // Handle k=1 case: any non-empty subarray product is divisible by 1.
    // The number of non-empty subarrays is n * (n + 1) / 2.
    // This is because for k=1, the condition `satisfied_factors_count == k_prime_factors.size()`
    // will always be true (0 == 0), and the loop will correctly sum `n - L + 1` for each L.
    // The sum `(n-0+1) + (n-1+1) + ... + (n-(n-1)+1)` is `(n+1) + n + ... + 1`, which is `(n+1)*n/2`.
    // This special handling is not strictly necessary as the general algorithm covers it,
    // but it can be a minor optimization or clarity point.
    if (k == 1) {
        std::cout << (long long)n * (n + 1) / 2 << std::endl;
        return 0;
    }

    // Step 2: Precompute prime factors for each a_i relevant to k's prime factors.
    // This avoids repeated calculations of prime factors for a_i within the two-pointer loop.
    // a_factors[i][p] stores the count of prime p in a[i].
    std::vector<std::map<long long, int>> a_factors(n);
    for (int i = 0; i < n; ++i) {
        for (auto const& [p, e_k] : k_prime_factors) {
            int count = 0;
            long long temp_val = a[i]; // Use a temporary variable to avoid modifying a[i]
            while (temp_val > 0 && temp_val % p == 0) {
                count++;
                temp_val /= p;
            }
            if (count > 0) {
                a_factors[i][p] = count;
            }
        }
    }

    // Step 3: Two-pointer (sliding window) approach.
    // L is the left pointer (start index of the current subarray).
    // R is the right pointer (end index of the current subarray + 1, i.e., next element to add).
    long long ans = 0;
    int R = 0; // R points to the first element NOT included in the current window [L, R-1]
    
    // current_prime_factors stores the accumulated counts of prime factors for the window a[L...R-1].
    std::map<long long, int> current_prime_factors;
    // satisfied_factors_count tracks how many of k's prime factor requirements are met.
    // It increments when current_prime_factors[p] reaches or exceeds k_prime_factors[p].
    // It decrements when current_prime_factors[p] drops below k_prime_factors[p].
    int satisfied_factors_count = 0;

    for (int L = 0; L < n; ++L) {
        // Expand the window by moving R to the right until the condition is met
        // or R reaches the end of the array.
        while (R < n && satisfied_factors_count < k_prime_factors.size()) {
            // Add a[R] to the window
            for (auto const& [p, e_k] : k_prime_factors) {
                // Get the count of prime p in a[R] from precomputed factors.
                // If p is not a factor of a[R], a_factors[R][p] will be 0.
                int count_p_in_aR = a_factors[R][p];
                if (count_p_in_aR > 0) {
                    // Check if adding this factor makes the count for 'p' satisfy the requirement.
                    bool was_below = (current_prime_factors[p] < e_k);
                    current_prime_factors[p] += count_p_in_aR;
                    bool is_above_or_equal = (current_prime_factors[p] >= e_k);
                    if (was_below && is_above_or_equal) {
                        satisfied_factors_count++;
                    }
                }
            }
            R++; // Move R to include the next element
        }

        // After the while loop, if satisfied_factors_count equals k_prime_factors.size(),
        // it means the window a[L...R-1] is valid.
        // Any window a[L...R'] where R' >= R-1 will also be valid because adding more elements
        // can only increase or keep the same prime factor counts, never decrease them.
        if (satisfied_factors_count == k_prime_factors.size()) {
            // The number of valid right endpoints for the current L is (n - 1) - (R - 1) + 1 = n - R + 1.
            // These correspond to subarrays a[L...R-1], a[L...R], ..., a[L...n-1].
            ans += (n - R + 1);
        } else {
            // If the condition is not met even with R at n (i.e., a[L...n-1] is not valid),
            // then no subarray starting at L (or any L' > L) can be valid.
            // This is because removing elements from the left (increasing L) can only decrease
            // the total prime factor counts, making it harder to satisfy the condition.
            // So, we can break the loop early.
            if (R == n) {
                break;
            }
        }

        // Shrink the window by moving L to the right.
        // Remove a[L] from the window.
        for (auto const& [p, e_k] : k_prime_factors) {
            // Get the count of prime p in a[L] from precomputed factors.
            int count_p_in_aL = a_factors[L][p];
            if (count_p_in_aL > 0) {
                // Check if removing this factor makes the count for 'p' drop below the requirement.
                bool was_above_or_equal = (current_prime_factors[p] >= e_k);
                current_prime_factors[p] -= count_p_in_aL;
                bool is_below = (current_prime_factors[p] < e_k);
                if (was_above_or_equal && is_below) {
                    satisfied_factors_count--;
                }
            }
        }
    }

    std::cout << ans << std::endl;

    return 0;
}

#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    // Optimize C++ standard streams for faster input/output operations.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    std::cin >> n; // Read the size of set A.

    // Define a constant for the maximum possible value of a_i, which is 10^6.
    const int MAX_A = 1000000;

    // Create a boolean array 'isPresent' to quickly check if a number is in set A.
    // Initialize all elements to false.
    std::vector<bool> isPresent(MAX_A + 1, false);

    // Create a vector 'a' to store the input numbers.
    std::vector<int> a(n);

    // Read the n distinct positive integers and mark their presence in 'isPresent'.
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
        isPresent[a[i]] = true;
    }

    // dp[i] will store the maximum clique size ending with 'i' (where 'i' is an element from set A).
    // Initialize dp values to 0.
    std::vector<int> dp(MAX_A + 1, 0);

    // The maximum clique size found so far.
    int maxCliqueSize = 0;

    // Iterate through the input numbers in ascending order.
    // This is crucial because for a divisibility clique {x1, x2, ..., xk} where x1 | x2 | ... | xk,
    // we process numbers in increasing order, ensuring that when we consider 'num',
    // all its divisors smaller than 'num' (which could be part of a clique ending at 'num')
    // have already been processed and their 'dp' values calculated.
    for (int num : a) {
        // For each number 'num' in set A, the minimum clique size it can form by itself is 1.
        dp[num] = 1;

        // Iterate through all multiples of 'num' starting from 'num' * 2 up to MAX_A.
        // If a multiple 'multiple' is present in set A, it means 'num' divides 'multiple'.
        // So, 'num' can extend any clique ending at 'num' to include 'multiple'.
        // However, this approach is incorrect for DP. We need to iterate through divisors.
        // Let's re-think the DP state.
        // dp[i] should represent the maximum clique size where 'i' is the *largest* element.
        // This is a standard approach for longest increasing subsequence problems, adapted for divisibility.

        // When considering 'num', we want to find the largest clique that can be formed
        // by appending 'num' to a clique whose largest element is a divisor of 'num'.
        // So, for each 'num' in the input array 'a':
        // 1. Initialize dp[num] = 1 (the clique containing only 'num' itself).
        // 2. Iterate through all divisors 'd' of 'num'.
        // 3. If 'd' is present in set A, then we can potentially extend a clique ending at 'd'
        //    by adding 'num'.
        //    So, dp[num] = max(dp[num], dp[d] + 1).

        // To efficiently find divisors, we iterate from 1 up to sqrt(num).
        // This calculates the dp value for 'num' based on its divisors.
        for (int i = 1; i * i <= num; ++i) {
            if (num % i == 0) {
                // 'i' is a divisor of 'num'.
                if (isPresent[i]) {
                    // If 'i' is in set A, we can potentially extend a clique ending at 'i'.
                    dp[num] = std::max(dp[num], dp[i] + 1);
                }
                // 'num / i' is also a divisor of 'num'.
                if (i * i != num) { // Avoid counting the same divisor twice if num is a perfect square.
                    if (isPresent[num / i]) {
                        // If 'num / i' is in set A, we can potentially extend a clique ending at 'num / i'.
                        dp[num] = std::max(dp[num], dp[num / i] + 1);
                    }
                }
            }
        }
        // After calculating dp[num] based on its divisors, update the overall maximum clique size.
        maxCliqueSize = std::max(maxCliqueSize, dp[num]);
    }

    std::cout << maxCliqueSize << std::endl; // Print the maximum clique size.

    return 0;
}
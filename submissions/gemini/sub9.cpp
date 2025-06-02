#include <iostream> // Required for input/output operations (cin, cout)
#include <vector>   // Required for using std::vector
#include <string>   // Required for using std::string
#include <algorithm> // Required for std::min, std::max (though not strictly used here)

// Function to check if a number contains the digit 'd'
bool containsDigit(int num, int d) {
    // If the number is 0, it doesn't contain any non-zero digit.
    // The problem states positive integers, so num will be >= 1.
    // 'd' is between 1 and 9.
    // Iterate through each digit of the number
    while (num > 0) {
        // If the last digit is 'd', then it contains 'd'
        if (num % 10 == d) {
            return true;
        }
        // Remove the last digit by integer division
        num /= 10;
    }
    // If no digit 'd' was found after checking all digits
    return false;
}

// Solve function for each test case
void solve() {
    int q, d; // q: number of queries, d: Nezzar's favorite digit
    std::cin >> q >> d;

    // Define a maximum value for which we will precompute reachability using Dynamic Programming (DP).
    // For problems involving sums of numbers where one of the numbers is small (like 'd')
    // and another is a multiple of 10 containing 'd' (like 'd*10'), it's a common pattern
    // that all numbers above a certain threshold can be formed.
    // The maximum value of 'd' is 9, so 'd*10' is at most 90.
    // The example outputs for d=7 show that numbers like 53, 55, 59 (which are < 70) are YES,
    // while 52, 60 (also < 70) are NO. This implies a full DP is needed for numbers below 70.
    // For numbers >= 70, they are all YES in the example.
    // This suggests that the threshold for "always YES" is 'd*10'.
    // Therefore, we only need to run DP for numbers up to 'd*10 - 1'.
    // A safe upper bound for the DP table size is 100, as max(d*10 - 1) for d=9 is 89.
    const int MAX_DP_VAL = 100; 

    // dp[i] will be true if 'i' can be formed as a sum of lucky numbers, false otherwise.
    // Initialize dp[0] to true. This is a standard base case for sum problems,
    // meaning 0 can be formed by an empty set of numbers.
    // All other dp[i] are initialized to false by default.
    std::vector<bool> dp(MAX_DP_VAL + 1, false);
    dp[0] = true;

    // Collect all lucky numbers up to MAX_DP_VAL.
    // These are the "coins" we can use to form sums.
    std::vector<int> lucky_numbers;
    for (int i = 1; i <= MAX_DP_VAL; ++i) {
        if (containsDigit(i, d)) {
            lucky_numbers.push_back(i);
        }
    }

    // Dynamic programming calculation.
    // This is a classic unbounded knapsack problem (also known as change-making problem).
    // Iterate through each lucky number (coin).
    for (int L : lucky_numbers) {
        // For each lucky number L, iterate through all possible sums 'i' from L up to MAX_DP_VAL.
        // If 'i - L' can be formed (i.e., dp[i - L] is true), then 'i' can also be formed
        // by adding L to the sum that forms 'i - L'.
        for (int i = L; i <= MAX_DP_VAL; ++i) {
            if (dp[i - L]) { // If (i - L) can be formed
                dp[i] = true; // Then i can be formed by adding L
            }
        }
    }

    // Process each query
    for (int k = 0; k < q; ++k) {
        int a_i; // The number for which Nezzar wants to know if it can be a sum of lucky numbers
        std::cin >> a_i;

        // Based on the problem constraints and example outputs, if a_i is large enough
        // (specifically, greater than or equal to d*10), it can always be formed.
        // This is because 'd' is a lucky number, and 'd*10' is also a lucky number.
        // Since 'd' and 'd*10' are lucky, and their greatest common divisor is 'd',
        // and there are other lucky numbers (e.g., 10+d, 20+d, etc.) that are not multiples of 'd'
        // (e.g., for d=7, 17 is lucky and gcd(7,17)=1), it implies that all sufficiently large
        // numbers can be formed. The threshold 'd*10' is empirically confirmed by the examples.
        if (a_i >= d * 10) {
            std::cout << "YES\n";
        } else {
            // For numbers smaller than d*10, we rely on the precomputed DP table.
            // If dp[a_i] is true, it means a_i can be formed.
            if (dp[a_i]) {
                std::cout << "YES\n";
            } else {
                std::cout << "NO\n";
            }
        }
    }
}

int main() {
    // Optimize C++ standard streams for competitive programming.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams.
    // std::cin.tie(NULL) prevents cin from flushing cout before each input operation.
    // These two lines significantly speed up I/O operations in C++.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t; // Number of test cases
    std::cin >> t;
    while (t--) {
        solve(); // Call the solve function for each test case
    }

    return 0; // Indicate successful program execution
}

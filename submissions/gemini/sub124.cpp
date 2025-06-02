#include <iostream> // Required for input/output operations (std::cin, std::cout)

// Function to solve a single test case
void solve() {
    int n;
    std::cin >> n; // Read the integer n for the current test case

    // Find the largest power of 2 that is strictly less than n.
    // Let this value be P.
    // This P is crucial because it represents the minimum possible maximum XOR cost.
    //
    // Proof for minimum cost P:
    // Let P = 2^k be the largest power of 2 such that P < n.
    // This implies 2^k < n <= 2^(k+1).
    // Consider the numbers in the range [0, n-1].
    // Any number x in [P, n-1] has its k-th bit (the bit corresponding to P) set.
    // Any number y in [0, P-1] has its k-th bit unset.
    // Since P < n, the set of numbers [P, n-1] is non-empty.
    // The set of numbers [0, P-1] is also non-empty (it contains 0).
    // In any permutation of 0 to n-1, there must be at least one adjacent pair (a, b)
    // where one element is from [P, n-1] and the other is from [0, P-1].
    // For such a pair, the bitwise XOR a ^ b will have its k-th bit set (because one has it set and the other doesn't).
    // This means a ^ b >= 2^k = P.
    // Therefore, the maximum XOR value in any permutation must be at least P.
    // Our construction aims to achieve exactly P.
    int P = 1;
    while (P * 2 < n) {
        P *= 2; // Double P until it's the largest power of 2 strictly less than n
    }

    // Construct the permutation sequence:
    // The sequence is formed by two parts:
    // 1. Numbers from P-1 down to 0.
    // 2. Numbers from P up to n-1.

    // Part 1: Print numbers from P-1 down to 0.
    // Example: if P=4, prints 3 2 1 0
    // The maximum XOR value within this segment:
    // For any i in [1, P-1], the XOR i ^ (i-1) is calculated.
    // The maximum of these values occurs when i is a power of 2 (e.g., P/2).
    // (P/2) ^ (P/2 - 1) = (2^(k-1)) ^ (2^(k-1) - 1) = 2^k - 1 = P - 1.
    // So, the maximum XOR in this first part is P-1.
    for (int i = P - 1; i >= 0; --i) {
        std::cout << i << " ";
    }

    // Part 2: Print numbers from P up to n-1.
    // Example: if P=4, n=5, prints 4
    // Example: if P=8, n=10, prints 8 9
    // The maximum XOR value within this segment:
    // For any x, y in [P, n-1], we can write x = P + a and y = P + b,
    // where a, b are in [0, n-1-P].
    // Since P is the MSB for all numbers in [P, n-1], x ^ y = (P+a) ^ (P+b) = a ^ b.
    // The maximum value of a ^ b for a, b in [0, n-1-P] is n-1-P.
    // Since P is the largest power of 2 strictly less than n, we have P < n <= 2P.
    // This implies n-1 < 2P-1, so n-1-P < P-1.
    // Thus, the maximum XOR in this second part is strictly less than P.
    for (int i = P; i < n; ++i) {
        std::cout << i << (i == n - 1 ? "" : " "); // Print space after each number except the last one
    }
    std::cout << "\n"; // Newline after each test case output
}

int main() {
    // Optimize C++ standard streams for competitive programming.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams.
    // std::cin.tie(NULL) prevents std::cout from flushing before each std::cin operation.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t; // Read the number of test cases
    while (t--) {
        solve(); // Call the solve function for each test case
    }

    return 0; // Indicate successful execution
}

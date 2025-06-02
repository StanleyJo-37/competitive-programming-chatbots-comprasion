#include <iostream>

// Function to solve a single test case
void solve() {
    long long n;
    std::cin >> n; // Read the input integer n

    // The problem asks for the sum of differences between neighboring participants
    // in the sequence 0, 1, ..., n.
    // The difference between two numbers A and B is defined as the number of bit positions
    // where one has zero and another has one (Hamming distance).
    // This is equivalent to popcount(A XOR B).

    // We need to calculate sum_{i=0}^{n-1} popcount(i XOR (i+1)).

    // Let's analyze i XOR (i+1):
    // When we add 1 to a number i, all trailing 1s become 0s, and the rightmost 0 becomes a 1.
    // For example, if i = ...X0111 (where X is some prefix, and there are k trailing 1s)
    // then i+1 = ...X1000 (where there are k trailing 0s).
    // XORing i and i+1:
    // The bits in the prefix X are the same, so they XOR to 0.
    // The bit at position k (0-indexed from right) is 0 in i and 1 in i+1. This XORs to 1.
    // The k trailing bits are 1s in i and 0s in i+1. These k bits XOR to 1s.
    // So, i XOR (i+1) will have 1 at position k, and 1s at positions 0 to k-1.
    // This means popcount(i XOR (i+1)) = k + 1.
    // Here, k is the number of trailing 1s in i.
    // Equivalently, k is the number of trailing 0s in i+1 (i.e., ctz(i+1)).
    // So, popcount(i XOR (i+1)) = ctz(i+1) + 1.

    // The total unfairness is sum_{i=0}^{n-1} (ctz(i+1) + 1).
    // Let j = i+1. The sum becomes sum_{j=1}^{n} (ctz(j) + 1).
    // This can be split into sum_{j=1}^{n} ctz(j) + sum_{j=1}^{n} 1.
    // The second part is simply n.

    // So, the problem reduces to calculating n + sum_{j=1}^{n} ctz(j).

    // The sum sum_{j=1}^{n} ctz(j) is the exponent of the highest power of 2 that divides n!.
    // This is given by Legendre's formula: sum_{k=1}^{infinity} floor(n / 2^k).
    // This sum can be computed efficiently by repeatedly dividing n by 2 and summing the results.
    // For example, floor(n/2) counts numbers divisible by 2.
    // floor(n/4) counts numbers divisible by 4.
    // A number j with ctz(j) = c is divisible by 2^c but not 2^(c+1).
    // It contributes 1 to floor(n/2), 1 to floor(n/4), ..., 1 to floor(n/2^c).
    // So it is counted exactly c times in the sum floor(n/2) + floor(n/4) + ...
    // This is exactly sum_{j=1}^{n} ctz(j).

    long long sum_of_ctz = 0;
    long long temp_n = n;
    while (temp_n > 0) {
        temp_n /= 2; // Equivalent to floor(temp_n / 2)
        sum_of_ctz += temp_n;
    }

    // The total unfairness is n + sum_of_ctz.
    // This is also equivalent to 2*n - popcount(n) based on the identity
    // sum_{k=1}^{infinity} floor(n / 2^k) = n - popcount(n).
    // So, n + (n - popcount(n)) = 2*n - popcount(n).
    // Both methods are efficient and correct. The iterative sum is more portable.

    long long total_unfairness = n + sum_of_ctz;
    std::cout << total_unfairness << std::endl;
}

int main() {
    // Optimize C++ standard streams for competitive programming.
    // This unties cin/cout from stdio and prevents flushing cout before cin.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t; // Read the number of test cases
    while (t--) {
        solve(); // Solve each test case
    }

    return 0;
}

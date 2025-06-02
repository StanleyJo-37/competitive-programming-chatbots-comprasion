#include <iostream>
#include <vector>

using namespace std;

// Precompute the sum of odd divisors for all numbers up to 1e5 using a sieve-like approach.
// For each odd number i, add i to all multiples of i (since i is an odd divisor of its multiples).
// This approach efficiently computes f(n) for all n in O(n log n) time.
vector<long long> precomputeSumOfOddDivisors(int max_n) {
    vector<long long> f(max_n + 1, 0);
    for (int i = 1; i <= max_n; i += 2) { // Only consider odd divisors
        for (int j = i; j <= max_n; j += i) {
            f[j] += i; // Add the odd divisor i to all its multiples
        }
    }
    return f;
}

int main() {
    const int MAX = 1e5;
    vector<long long> f = precomputeSumOfOddDivisors(MAX);
    vector<long long> prefix_sum(MAX + 1, 0);
    
    // Compute prefix sums to answer range queries in O(1) per query
    for (int i = 1; i <= MAX; ++i) {
        prefix_sum[i] = prefix_sum[i - 1] + f[i];
    }
    
    int T;
    cin >> T;
    while (T--) {
        int l, r;
        cin >> l >> r;
        cout << prefix_sum[r] - prefix_sum[l - 1] << endl;
    }
    
    return 0;
}
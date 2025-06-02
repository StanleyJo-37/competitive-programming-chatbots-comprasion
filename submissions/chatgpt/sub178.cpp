#include <bits/stdc++.h>
using namespace std;

// Maximum N as per constraints
const int MAXN = 1e7 + 5;

// Array to store the count of primes up to i
int prime_count[MAXN];

// Sieve of Eratosthenes to precompute prime counts up to MAXN
void precompute_prime_counts() {
    // is_prime[i] is true if i is prime
    vector<bool> is_prime(MAXN, true);
    is_prime[0] = is_prime[1] = false;
    // Sieve
    for (int i = 2; i * i < MAXN; ++i) {
        if (is_prime[i]) {
            for (int j = i * i; j < MAXN; j += i) {
                is_prime[j] = false;
            }
        }
    }
    // Compute prefix sum of primes up to i
    for (int i = 2; i < MAXN; ++i) {
        prime_count[i] = prime_count[i - 1] + (is_prime[i] ? 1 : 0);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Precompute prime counts up to MAXN
    precompute_prime_counts();

    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        // The number of groups is equal to the number of primes in [2, N]
        // plus 1 (for the group containing all composite numbers and 2)
        // But actually, the group containing 2, 4, 6, ... and all composites
        // is one group, and each prime > 2 forms its own group.
        // So, answer = number of primes in [3, N] + 1
        // That is, answer = (number of primes in [2, N]) - 1 + 1 = number of primes in [2, N]
        cout << prime_count[N] << '\n';
    }
    return 0;
}
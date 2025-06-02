#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 1e7 + 5;

// Precompute smallest prime factors (spf) for sieve
int spf[MAX_N];

// Precompute the number of primes up to N for each test case
int primeCount[MAX_N];

void sieve() {
    for (int i = 2; i < MAX_N; ++i) {
        if (spf[i] == 0) {
            spf[i] = i;
            for (long long j = (long long)i * i; j < MAX_N; j += i) {
                if (spf[j] == 0) {
                    spf[j] = i;
                }
            }
        }
    }
}

void precomputePrimes() {
    sieve();
    primeCount[0] = 0;
    primeCount[1] = 0;
    for (int i = 2; i < MAX_N; ++i) {
        primeCount[i] = primeCount[i - 1] + (spf[i] == i ? 1 : 0);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    precomputePrimes();

    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        // The answer is the number of primes in [2, N] plus 1 if N >= 2,
        // but subtract 1 if there's a prime <= N/2 (since primes <= N/2 will merge with 2).
        // Alternatively, the answer is (number of primes in [2, N]) - (number of primes in [2, N/2]) + 1.
        // Because all numbers in [2, N] that have a prime factor <= N/2 will merge into the same group as 2.
        // The remaining primes (those > N/2) form their own groups.
        int primesUpToN = primeCount[N];
        int primesUpToHalfN = primeCount[N / 2];
        int ans = (primesUpToN - primesUpToHalfN) + 1;
        cout << ans << '\n';
    }

    return 0;
}
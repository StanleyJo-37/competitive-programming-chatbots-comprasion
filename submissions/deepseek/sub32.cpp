#include <bits/stdc++.h>
using namespace std;

const int MAX = 5e6 + 5;

// Precompute smallest prime factors (SPF) for sieve
int spf[MAX];

// Precompute the number of prime factors for each number up to MAX
int prime_factors[MAX];

void sieve() {
    for (int i = 2; i < MAX; ++i) {
        if (spf[i] == 0) {
            spf[i] = i;
            for (int j = 2 * i; j < MAX; j += i) {
                if (spf[j] == 0) {
                    spf[j] = i;
                }
            }
        }
    }
}

void compute_prime_factors() {
    for (int i = 2; i < MAX; ++i) {
        prime_factors[i] = prime_factors[i / spf[i]] + 1;
    }
}

void precompute_prefix_sums() {
    for (int i = 1; i < MAX; ++i) {
        prime_factors[i] += prime_factors[i - 1];
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    sieve();
    compute_prime_factors();
    precompute_prefix_sums();

    int t;
    cin >> t;
    while (t--) {
        int a, b;
        cin >> a >> b;
        cout << (prime_factors[a] - prime_factors[b]) << '\n';
    }

    return 0;
}
#include <iostream>
#include <vector>
using namespace std;

// The problem reduces to finding the maximum number of times we can divide n = a! / b! by an integer > 1.
// Each division corresponds to removing a prime factor from n.
// So, the answer is the total number of prime factors (with multiplicity) in n = a! / b! = product_{i=b+1}^{a} i
// This is equal to the sum of the exponents of all primes in the range (b, a] in their prime factorization.

// We precompute for all numbers up to 5,000,000 the total number of prime factors (with multiplicity) in their prime factorization.
// Then, for each query (a, b), the answer is: pf[a] - pf[b], where pf[i] is the total number of prime factors in i!

const int MAXN = 5000000 + 10;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // pf[i] will store the total number of prime factors (with multiplicity) in i!
    static vector<int> pf(MAXN, 0);

    // cnt[i] will store the number of prime factors (with multiplicity) in i
    static vector<int> cnt(MAXN, 0);

    // Sieve to fill cnt[i] for all i up to MAXN
    for (int i = 2; i < MAXN; ++i) {
        if (cnt[i] == 0) { // i is prime
            for (int j = i; j < MAXN; j += i) {
                int x = j;
                while (x % i == 0) {
                    cnt[j]++;
                    x /= i;
                }
            }
        }
    }

    // Now, pf[i] = pf[i-1] + cnt[i]
    for (int i = 2; i < MAXN; ++i) {
        pf[i] = pf[i-1] + cnt[i];
    }

    int t;
    cin >> t;
    while (t--) {
        int a, b;
        cin >> a >> b;
        // The answer is the number of prime factors in (a! / b!) = product_{i=b+1}^{a} i
        // Which is pf[a] - pf[b]
        cout << pf[a] - pf[b] << '\n';
    }
    return 0;
}
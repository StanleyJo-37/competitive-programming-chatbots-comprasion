#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;
const int MOD = 1000000007;

// Function to compute factorial modulo MOD
ll factorial(int n) {
    ll res = 1;
    for (int i = 2; i <= n; ++i)
        res = (res * i) % MOD;
    return res;
}

// Function to compute power modulo MOD
ll power(ll base, ll exp) {
    ll res = 1;
    while (exp) {
        if (exp & 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp >>= 1;
    }
    return res;
}

// Function to compute modular inverse modulo MOD
ll modinv(ll x) {
    return power(x, MOD - 2);
}

int main() {
    int n;
    cin >> n;

    // For n = 1, only one permutation, so only one pair (1,1)
    if (n == 1) {
        cout << 1 << endl;
        return 0;
    }

    // The sum operation is defined as:
    // c_i = ((a_i - 1 + b_i - 1) % n) + 1
    // For c to be a permutation, the mapping i -> (a_i - 1 + b_i - 1) % n must be a permutation of {0, ..., n-1}
    // This is equivalent to: for each i, (a_i + b_i) % n must be all different for i = 1..n

    // For each permutation a, the number of permutations b such that c is a permutation is (n-1)!
    // This is because for fixed a, the mapping b_i -> (a_i + b_i) % n is a bijection iff b is a permutation
    // and the mapping is a Latin square (Cayley table of Z_n), so for each a, there are (n-1)! valid b

    // But let's prove it by counting:
    // For each a, for each b, c is a permutation iff the mapping i -> (a_i + b_i) % n is a permutation
    // For each a, the number of b such that c is a permutation is (n-1)!
    // So total number of pairs is n! * (n-1)!

    // Compute n! and (n-1)!
    ll fact_n = factorial(n);
    ll fact_n_1 = factorial(n - 1);

    // The answer is n! * (n-1)!
    ll ans = (fact_n * fact_n_1) % MOD;
    cout << ans << endl;
    return 0;
}
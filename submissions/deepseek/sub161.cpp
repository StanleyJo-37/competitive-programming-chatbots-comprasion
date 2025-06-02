#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

int main() {
    int n;
    cin >> n;

    // Precompute factorial and inverse factorial modulo MOD for combinatorial calculations
    vector<long long> fact(n + 1, 1);
    for (int i = 1; i <= n; ++i) {
        fact[i] = fact[i - 1] * i % MOD;
    }

    // The key observation is that for each permutation 'a', the number of valid 'b' is the same.
    // The problem reduces to counting the number of valid 'b' for a fixed 'a' (e.g., identity permutation)
    // and then multiplying by n! (since 'a' can be any permutation).

    // For a fixed 'a' (identity), 'b' must be such that (i-1 + b_i - 1) mod n + 1 is a permutation.
    // This simplifies to (b_i - 2) mod n + 1 must be a permutation, which is equivalent to b_i mod n being a permutation shifted by 1.
    // Essentially, 'b' must be a permutation where (b_i - 2) mod n + 1 is a permutation, which is the same as (b_i - 1) mod n is a permutation.
    // This is equivalent to 'b' being a permutation where (b_i - 1) mod n is a derangement (no fixed points) of the identity permutation.

    // However, the correct approach is to realize that the condition is equivalent to (a_i + b_i - 2) mod n being a permutation of 0..n-1.
    // For a fixed 'a', 'b' must satisfy that (a_i + b_i - 2) mod n is a permutation. This is equivalent to b_i ≡ (c_i - a_i + 2) mod n for some permutation 'c'.
    // The number of valid 'b' is equal to the number of permutations 'c' multiplied by the number of ways to choose 'b' given 'c'.
    // But since 'c' is fixed as a permutation, the number of valid 'b' is the number of Latin squares of size n, which is known to be n! * (n-1)! * ... * 1! / (n^(n(n-1)/2)) for n <= 16, but this is not directly applicable.

    // Instead, we can use dynamic programming with bitmask to count the number of valid 'b' for a fixed 'a' (identity).
    // The condition is that (i-1 + b_i - 1) mod n must be a permutation, i.e., all (i + b_i - 2) mod n must be distinct.
    // So, for each position i, b_i must be such that (i + b_i - 2) mod n is unique.

    // We can model this as counting the number of permutations 'b' where (i + b_i - 2) mod n are all distinct.
    // This is equivalent to counting the number of permutations 'b' where the mapping i -> (i + b_i - 2) mod n is a bijection.
    // This is the same as counting the number of solutions to b_i ≡ (k - i + 2) mod n for some permutation k.

    // Therefore, the number of valid 'b' for any fixed 'a' is equal to the number of permutations 'k' multiplied by the number of 'b' that satisfy b_i ≡ (k_i - a_i + 2) mod n.
    // But since 'a' is fixed as identity, a_i = i, so b_i ≡ (k_i - i + 2) mod n.
    // For 'b' to be a permutation, (k_i - i + 2) mod n must be a permutation, which is equivalent to k_i ≡ (b_i + i - 2) mod n.
    // Since 'k' is a permutation, the number of valid 'b' is equal to the number of permutations 'k' where (k_i - i + 2) mod n is a permutation, which is the same as the number of permutations 'k' where (k_i - i) mod n is a permutation shifted by -2.

    // However, this seems circular. The correct insight is that for any permutation 'a', the number of valid 'b' is equal to the number of permutations 'b' such that (a_i + b_i - 2) mod n is a permutation. This is equivalent to counting the number of Latin squares, but for n <= 16, we can use dynamic programming with bitmask.

    // The total number of pairs is n! multiplied by the number of valid 'b' for a fixed 'a' (identity).
    // So, we need to compute the number of permutations 'b' such that (i + b_i - 2) mod n are all distinct.

    // We can compute this using DP with bitmask, where the mask represents which (i + b_i - 2) mod n values have been used.
    vector<vector<long long>> dp(n + 1, vector<long long>(1 << n, 0));
    dp[0][0] = 1;

    for (int i = 0; i < n; ++i) {
        for (int mask = 0; mask < (1 << n); ++mask) {
            if (dp[i][mask] == 0) continue;
            for (int b_i = 1; b_i <= n; ++b_i) {
                int k = (i + b_i - 2) % n;
                if (!(mask & (1 << k))) {
                    int new_mask = mask | (1 << k);
                    dp[i + 1][new_mask] = (dp[i + 1][new_mask] + dp[i][mask]) % MOD;
                }
            }
        }
    }

    long long valid_b = dp[n][(1 << n) - 1];
    long long total_pairs = fact[n] * valid_b % MOD;
    cout << total_pairs << endl;

    return 0;
}
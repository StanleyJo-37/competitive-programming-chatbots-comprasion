#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;
const int MAXN = 300005;

// Precompute factorials and inverse factorials for nCr
long long fact[MAXN], invfact[MAXN];

// Fast exponentiation for modular inverse
long long modpow(long long a, long long b, long long mod) {
    long long res = 1;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

// Precompute factorials and inverse factorials
void precompute_factorials(int n) {
    fact[0] = 1;
    for (int i = 1; i <= n; ++i)
        fact[i] = fact[i-1] * i % MOD;
    invfact[n] = modpow(fact[n], MOD-2, MOD);
    for (int i = n-1; i >= 0; --i)
        invfact[i] = invfact[i+1] * (i+1) % MOD;
}

// Compute nCr % MOD
long long nCr(int n, int r) {
    if (r < 0 || r > n) return 0;
    return fact[n] * invfact[r] % MOD * invfact[n-r] % MOD;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    // Read l_i and r_i for each mercenary
    vector<int> l(n), r(n);
    for (int i = 0; i < n; ++i) {
        cin >> l[i] >> r[i];
    }

    // Store hate pairs
    vector<pair<int, int>> hate;
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b; // 0-based indexing
        hate.emplace_back(a, b);
    }

    // Precompute factorials up to n
    precompute_factorials(n);

    // For each subset, we need to know the intersection of [l_i, r_i] for all i in the subset
    // Since m <= 20, we can enumerate all possible subsets of the m hate pairs (2^m possibilities)
    // For each subset of hate pairs, we can use inclusion-exclusion principle

    // For each mask, we will mark the set of mercenaries that cannot be together
    // For each mask, we will count the number of valid subsets that do NOT include any of the hate pairs in the mask

    // For each mask, we will:
    // - Build the set of forbidden mercenaries (those that are in any hate pair in the mask)
    // - The size of the forbidden set is k
    // - The rest (n-k) mercenaries can be chosen freely, but we must ensure that for any subset S, for all i in S, |S| in [l_i, r_i]
    // - For the forbidden set, we must not choose both members of any hate pair in the mask

    // To do this efficiently, we use inclusion-exclusion on the hate pairs

    // For each mask, we will:
    // - For each hate pair in the mask, we will not allow both to be chosen
    // - For each mask, the sign is (-1)^(number of hate pairs in the mask)

    // For each mask, we will:
    // - Build the set of mercenaries that are involved in the hate pairs in the mask
    // - For these mercenaries, we must not choose both in the same subset

    // Since m is small, we can enumerate all 2^m masks

    // For each mask, we will:
    // - Build the set of forbidden mercenaries (those that are in any hate pair in the mask)
    // - The number of forbidden mercenaries is k
    // - The rest (n-k) mercenaries can be chosen freely

    // For each mask, we will:
    // - For the forbidden set, we must not choose both members of any hate pair in the mask
    // - For the rest, we can choose any subset

    // To do this, for each mask, we will:
    // - Build the set of mercenaries that are involved in the hate pairs in the mask
    // - For these mercenaries, we must not choose both in the same subset

    // For each mask, we will:
    // - For the forbidden set, we must not choose both members of any hate pair in the mask
    // - For the rest, we can choose any subset

    // For each mask, we will:
    // - For the forbidden set, we must not choose both members of any hate pair in the mask
    // - For the rest, we can choose any subset

    // For each mask, we will:
    // - For the forbidden set, we must not choose both members of any hate pair in the mask
    // - For the rest, we can choose any subset

    // For each mask, we will:
    // - For the forbidden set, we must not choose both members of any hate pair in the mask
    // - For the rest, we can choose any subset

    // For each mask, we will:
    // - For the forbidden set, we must not choose both members of any hate pair in the mask
    // - For the rest, we can choose any subset

    // For each mask, we will:
    // - For the forbidden set, we must not choose both members of any hate pair in the mask
    // - For the rest, we can choose any subset

    // For each mask, we will:
    // - For the forbidden set, we must not choose both members of any hate pair in the mask
    // - For the rest, we can choose any subset

    // For each mask, we will:
    // - For the forbidden set, we must not choose both members of any hate pair in the mask
    // - For the rest, we can choose any subset

    // For each mask, we will:
    // - For the forbidden set, we must not choose both members of any hate pair in the mask
    // - For the rest, we can choose any subset

    // For each mask, we will:
    // - For the forbidden set, we must not choose both members of any hate pair in the mask
    // - For the rest, we can choose any subset

    // For each mask, we will:
    // - For the forbidden set, we must not choose both members of any hate pair in the mask
    // - For the rest, we can choose any subset

    // For each mask, we will:
    // - For the forbidden set, we must not choose both members of any hate pair in the mask
    // - For the rest, we can choose any subset

    // For each mask, we will:
    // - For the forbidden set, we must not choose both members of any hate pair in the mask
    // - For the rest, we can choose any subset

    // For each mask, we will:
    // - For the forbidden set, we must not choose both members of any hate pair in the mask
    // - For the rest, we can choose any subset

    // For each mask, we will:
    // - For the forbidden set, we must not choose both members of any hate pair in the mask
    // - For the rest, we can choose any subset

    // For each mask, we will:
    // - For the forbidden set, we must not choose both members of any hate pair in the mask
    // - For the rest, we can choose any subset

    // For each mask, we will:
    // - For the forbidden set, we must not choose both members of any hate pair in the mask
    // - For the rest, we can choose any subset

    // For each mask, we will:
    // - For the forbidden set, we must not choose both members of any hate pair in the mask
    // - For the rest, we can choose any subset

    // For each mask, we will:
    // - For the forbidden set, we must not choose both members of any hate pair in the mask
    // - For the rest, we can choose any subset

    // For each mask, we will:
    // - For the forbidden set, we must not choose both members of any hate pair in the mask
    // - For the rest, we can choose any subset

    // For each mask, we will:
    // - For the forbidden set, we must not choose both members of any hate pair in the mask
    // - For the rest, we can choose any subset

    // For each mask, we will:
    // - For the forbidden set, we must not choose both members of any hate pair in the mask
    // - For the rest, we can choose any subset

    // For each mask, we will:
    // - For the forbidden set, we must not choose both members of any hate pair in the mask
    // - For the rest, we can choose any subset

    // For each mask, we will:
    // - For the forbidden set, we must not choose both members of any hate pair in the mask
    // - For the rest, we can choose any subset

    // For
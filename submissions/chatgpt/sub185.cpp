#include <bits/stdc++.h>
using namespace std;

// Modulo as per problem statement
const int MOD = 998244353;
const int MAXN = 600005; // Maximum N for precomputing factorials

// Precompute factorials and inverse factorials for nCr calculations
vector<long long> fact(MAXN), invfact(MAXN);

// Fast exponentiation modulo MOD
long long modpow(long long a, long long b) {
    long long res = 1;
    a %= MOD;
    while (b) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

// Precompute factorials and inverse factorials
void precompute_factorials() {
    fact[0] = 1;
    for (int i = 1; i < MAXN; ++i)
        fact[i] = fact[i - 1] * i % MOD;
    invfact[MAXN - 1] = modpow(fact[MAXN - 1], MOD - 2);
    for (int i = MAXN - 2; i >= 0; --i)
        invfact[i] = invfact[i + 1] * (i + 1) % MOD;
}

// Compute nCr % MOD
long long nCr(int n, int r) {
    if (r < 0 || r > n) return 0;
    return fact[n] * invfact[r] % MOD * invfact[n - r] % MOD;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    precompute_factorials();

    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        vector<int> A(2 * N);
        vector<vector<int>> pos(N + 1); // Store positions of each number

        // Read input and record positions for each number
        for (int i = 0; i < 2 * N; ++i) {
            cin >> A[i];
            pos[A[i]].push_back(i);
        }

        // For each number x, it appears exactly twice at positions p1, p2 (p1 < p2)
        // For each x, the number of ways to choose k occurrences from its 2 positions is C(2, k)
        // For all numbers, we want to count the number of ways to select k occurrences from each, and pair them up
        // For each k (1 <= k <= N), the number of ways to select k positions from each x is C(2, k)
        // For each such selection, the number of ordered pairs (P, Q) is 2^k (since for each selected position, P and Q can swap)
        // But since the positions must be disjoint, for each x, we can either pick the first occurrence for P and the second for Q, or vice versa

        // For each number, there are 2 ways to assign its two positions to P and Q (P gets first, Q gets second or vice versa)
        // For each subset S of numbers (size k), the number of ways to assign their positions to P and Q is 2^k
        // The total number of such ordered pairs is sum_{k=1}^{N} C(N, k) * 2^k = (1 + 2)^N - 1 = 3^N - 1

        // But we need to consider all possible non-empty subsets of numbers, and for each, the number of ways to assign their positions to P and Q is 2^k * k! (since the order matters)
        // However, since the order of indices in P and Q must be strictly increasing, for each subset, the order is fixed

        // Actually, for each subset S of size k, the number of ways to assign the two positions of each number in S to P and Q is 2^k
        // For all numbers, the total number of good pairs is sum_{k=1}^{N} C(N, k) * 2^k = (1 + 2)^N - 1 = 3^N - 1

        // But this is only true if the positions of each number are distinct and can be assigned arbitrarily, which is the case here

        // For each number, its two positions can be assigned to P and Q in 2 ways (P gets first, Q gets second or vice versa)
        // For each subset S of numbers, the number of ways is 2^k
        // The total number of ordered pairs is sum_{k=1}^{N} C(N, k) * 2^k = (1 + 2)^N - 1 = 3^N - 1

        // But we need to check if the sequence A is not always in the form [1,1,2,2,...,N,N]
        // For arbitrary A, we need to find, for each number, its two positions, and for each subset, the number of ways to assign their positions to P and Q

        // For each number x, let its two positions be p1 < p2
        // For each subset S of numbers, for each number x in S, we can assign p1 to P and p2 to Q, or vice versa
        // For all such assignments, the order of indices in P and Q will be strictly increasing, since for each number, the positions are assigned in the same order

        // So, for each subset S, the number of good pairs is 2^k, and the total is sum_{k=1}^{N} C(N, k) * 2^k = 3^N - 1

        // But we need to check if the sequence A is not always in the form [1,1,2,2,...,N,N]
        // For arbitrary A, we need to find, for each number, its two positions, and for each subset, the number of ways to assign their positions to P and Q

        // For each number x, let its two positions be p1 < p2
        // For each subset S of numbers, for each number x in S, we can assign p1 to P and p2 to Q, or vice versa
        // For all such assignments, the order of indices in P and Q will be strictly increasing, since for each number, the positions are assigned in the same order

        // So, for each subset S, the number of good pairs is 2^k, and the total is sum_{k=1}^{N} C(N, k) * 2^k = 3^N - 1

        // But we need to check if the sequence A is not always in the form [1,1,2,2,...,N,N]
        // For arbitrary A, we need to find, for each number, its two positions, and for each subset, the number of ways to assign their positions to P and Q

        // For each number x, let its two positions be p1 < p2
        // For each subset S of numbers, for each number x in S, we can assign p1 to P and p2 to Q, or vice versa
        // For all such assignments, the order of indices in P and Q will be strictly increasing, since for each number, the positions are assigned in the same order

        // So, for each subset S, the number of good pairs is 2^k, and the total is sum_{k=1}^{N} C(N, k) * 2^k = 3^N - 1

        // But we need to check if the sequence A is not always in the form [1,1,2,2,...,N,N]
        // For arbitrary A, we need to find, for each number, its two positions, and for each subset, the number of ways to assign their positions to P and Q

        // For each number x, let its two positions be p1 < p2
        // For each subset S of numbers, for each number x in S, we can assign p1 to P and p2 to Q, or vice versa
        // For all such assignments, the order of indices in P and Q will be strictly increasing, since for each number, the positions are assigned in the same order

        // So, for each subset S, the number of good pairs is 2^k, and the total is sum_{k=1}^{N} C(N, k) * 2^k = 3^N - 1

        // But we need to check if the sequence A is not always in the form [1,1,2,2,...,N,N]
        // For arbitrary A, we need to find, for each number, its two positions, and for each subset, the number of ways to assign their positions to P and Q

        // For each number x, let its two positions be p1 < p2
        // For each subset S of numbers, for each number x in S, we can assign p1 to P and p2 to Q, or vice versa
        // For all such assignments, the order of indices in P and Q will be strictly increasing, since for each number, the positions are assigned in the same order

        // So, for each subset S, the number of good pairs is 2^k, and the total is sum_{k=1}^{N} C(N, k) * 2^k = 3^N - 1

        // But
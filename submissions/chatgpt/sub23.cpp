#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MOD = 1'000'000'007;
const int MAX_N = 400005;

// Precompute all primes up to 45 (max sum of 5 digits: 9*5=45)
vector<bool> is_prime(46, true);

// DP[pos][a][b][c][d]: number of ways to build a number of length pos, where
// the last 4 digits are a,b,c,d (a,b,c,d in 0..9)
ll dp[MAX_N][10][10][10][10];

// To store answers for all n up to max_n in queries
ll answers[MAX_N];

// Precompute all primes up to 45
void sieve() {
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i <= 45; ++i) {
        if (is_prime[i]) {
            for (int j = i * 2; j <= 45; j += i)
                is_prime[j] = false;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    sieve();

    // Precompute valid 3,4,5 digit windows
    // valid3[a][b][c] = true if a+b+c is prime
    // valid4[a][b][c][d] = true if a+b+c+d is prime
    // valid5[a][b][c][d][e] = true if a+b+c+d+e is prime
    bool valid3[10][10][10] = {};
    bool valid4[10][10][10][10] = {};
    bool valid5[10][10][10][10][10] = {};

    for (int a = 0; a <= 9; ++a)
        for (int b = 0; b <= 9; ++b)
            for (int c = 0; c <= 9; ++c)
                valid3[a][b][c] = is_prime[a + b + c];

    for (int a = 0; a <= 9; ++a)
        for (int b = 0; b <= 9; ++b)
            for (int c = 0; c <= 9; ++c)
                for (int d = 0; d <= 9; ++d)
                    valid4[a][b][c][d] = is_prime[a + b + c + d];

    for (int a = 0; a <= 9; ++a)
        for (int b = 0; b <= 9; ++b)
            for (int c = 0; c <= 9; ++c)
                for (int d = 0; d <= 9; ++d)
                    for (int e = 0; e <= 9; ++e)
                        valid5[a][b][c][d][e] = is_prime[a + b + c + d + e];

    // Read queries and find max n needed
    int q;
    cin >> q;
    vector<int> ns(q);
    int max_n = 0;
    for (int i = 0; i < q; ++i) {
        cin >> ns[i];
        max_n = max(max_n, ns[i]);
    }

    // Initialize DP for n=4 (first 4 digits)
    // For n=4, we need to ensure that all 3-digit and 4-digit windows are prime
    // For n=4, the only 3-digit windows are digits 1-3 and 2-4
    // The only 4-digit window is digits 1-4
    for (int a = 1; a <= 9; ++a) // first digit can't be 0
        for (int b = 0; b <= 9; ++b)
            for (int c = 0; c <= 9; ++c)
                for (int d = 0; d <= 9; ++d)
                    if (valid3[a][b][c] && valid3[b][c][d] && valid4[a][b][c][d])
                        dp[4][a][b][c][d] = 1;

    // For n=5 and above, build up using DP
    for (int pos = 5; pos <= max_n; ++pos) {
        // For each possible last 4 digits (a,b,c,d)
        for (int a = 0; a <= 9; ++a)
            for (int b = 0; b <= 9; ++b)
                for (int c = 0; c <= 9; ++c)
                    for (int d = 0; d <= 9; ++d)
                        if (dp[pos-1][a][b][c][d]) {
                            // Try all possible next digit e
                            for (int e = 0; e <= 9; ++e) {
                                // Check if all new windows are valid
                                // The new windows are:
                                // - last 3: c,d,e
                                // - last 4: b,c,d,e
                                // - last 5: a,b,c,d,e
                                if (valid3[c][d][e] && valid4[b][c][d][e] && valid5[a][b][c][d][e]) {
                                    dp[pos][b][c][d][e] = (dp[pos][b][c][d][e] + dp[pos-1][a][b][c][d]) % MOD;
                                }
                            }
                        }
    }

    // For each n, sum up all valid numbers
    // For n < 4, no such number exists (since we can't have 3,4,5 consecutive digits)
    for (int n = 1; n <= max_n; ++n) {
        if (n < 4) {
            answers[n] = 0;
        } else {
            ll total = 0;
            for (int a = 0; a <= 9; ++a)
                for (int b = 0; b <= 9; ++b)
                    for (int c = 0; c <= 9; ++c)
                        for (int d = 0; d <= 9; ++d)
                            total = (total + dp[n][a][b][c][d]) % MOD;
            answers[n] = total;
        }
    }

    // Output answers for each query
    for (int i = 0; i < q; ++i) {
        cout << answers[ns[i]] << '\n';
    }
}
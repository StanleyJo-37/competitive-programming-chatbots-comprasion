#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

// Precompute primes up to the maximum possible sum (5 digits max sum is 9*5=45)
vector<bool> sieve(int max_num) {
    vector<bool> is_prime(max_num + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * i <= max_num; ++i) {
        if (is_prime[i]) {
            for (int j = i * i; j <= max_num; j += i) {
                is_prime[j] = false;
            }
        }
    }
    return is_prime;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // The maximum sum for 5 digits is 9*5=45
    vector<bool> is_prime = sieve(45);

    // Precompute all possible 5-digit sequences (a, b, c, d, e) where:
    // a + b + c is prime, a + b + c + d is prime, b + c + d + e is prime,
    // a + b + c + d + e is prime, and b + c + d is prime, c + d + e is prime.
    // But since the problem requires all 3,4,5 consecutive sums to be prime,
    // we need to ensure that for any 5-digit window, all 3,4,5 sums are prime.
    // So, we can model the DP state as the last 5 digits (but for n < 5, we adjust).

    // For n >= 5, the DP state is (d1, d2, d3, d4, d5), but tracking all is memory-heavy.
    // Instead, we can track the last 4 digits (d2, d3, d4, d5) since d1 can be derived from previous transitions.

    // However, for n up to 4e5, we need a more efficient approach.
    // We'll use dynamic programming where the state is the last 4 digits (since the next digit depends on the last 4 to check all conditions).

    // Precompute all valid 5-digit sequences (a, b, c, d, e) where:
    // a + b + c, b + c + d, c + d + e,
    // a + b + c + d, b + c + d + e,
    // a + b + c + d + e are all primes.
    // Then, the DP can transition based on the last 4 digits.

    // Precompute all possible 4-digit prefixes (d1, d2, d3, d4) and for each, track valid next digits d5.

    // Initialize DP for n=5:
    // dp[5][d2][d3][d4][d5] = 1 if all conditions are met.

    // But for n=1 to n=4, handle separately.

    // Precompute all valid transitions:
    // For a 5-digit number (a, b, c, d, e), the following must hold:
    // 1. a + b + c is prime
    // 2. b + c + d is prime
    // 3. c + d + e is prime
    // 4. a + b + c + d is prime
    // 5. b + c + d + e is prime
    // 6. a + b + c + d + e is prime

    // For n < 5, the conditions are fewer:
    // n=3: only a + b + c must be prime.
    // n=4: a + b + c, b + c + d, a + b + c + d must be primes.

    // Precompute for n=1 to n=5:
    vector<int> ans(400001, 0);

    // n=1: any digit 1-9 is valid (no conditions)
    ans[1] = 9;

    // n=2: any two digits (no conditions)
    ans[2] = 90;

    // n=3: a + b + c must be prime
    int count3 = 0;
    for (int a = 1; a <= 9; ++a) {
        for (int b = 0; b <= 9; ++b) {
            for (int c = 0; c <= 9; ++c) {
                if (is_prime[a + b + c]) {
                    ++count3;
                }
            }
        }
    }
    ans[3] = count3;

    // n=4: a + b + c, b + c + d, a + b + c + d must be primes
    int count4 = 0;
    for (int a = 1; a <= 9; ++a) {
        for (int b = 0; b <= 9; ++b) {
            for (int c = 0; c <= 9; ++c) {
                for (int d = 0; d <= 9; ++d) {
                    if (is_prime[a + b + c] && is_prime[b + c + d] && is_prime[a + b + c + d]) {
                        ++count4;
                    }
                }
            }
        }
    }
    ans[4] = count4;

    // n=5: all 3,4,5 consecutive sums must be primes
    int count5 = 0;
    for (int a = 1; a <= 9; ++a) {
        for (int b = 0; b <= 9; ++b) {
            for (int c = 0; c <= 9; ++c) {
                for (int d = 0; d <= 9; ++d) {
                    for (int e = 0; e <= 9; ++e) {
                        int sum3_1 = a + b + c;
                        int sum3_2 = b + c + d;
                        int sum3_3 = c + d + e;
                        int sum4_1 = a + b + c + d;
                        int sum4_2 = b + c + d + e;
                        int sum5 = a + b + c + d + e;
                        if (is_prime[sum3_1] && is_prime[sum3_2] && is_prime[sum3_3] &&
                            is_prime[sum4_1] && is_prime[sum4_2] && is_prime[sum5]) {
                            ++count5;
                        }
                    }
                }
            }
        }
    }
    ans[5] = count5;

    // For n >=6, we use dynamic programming with the state being the last 4 digits.
    // We'll represent the state as a 4-digit number (d2, d3, d4, d5) and track transitions.

    // Initialize DP for n=5:
    // We'll use a map or a 4D array, but for efficiency, we'll flatten the state.
    // The maximum state is 9999 (4 digits), so we can use a 1D array of size 10000.

    vector<int> dp(10000, 0); // dp[state] = number of ways to reach state (d2d3d4d5)
    vector<int> next_dp(10000, 0);

    // Initialize dp with all valid 5-digit numbers (state is last 4 digits)
    for (int a = 1; a <= 9; ++a) {
        for (int b = 0; b <= 9; ++b) {
            for (int c = 0; c <= 9; ++c) {
                for (int d = 0; d <= 9; ++d) {
                    for (int e = 0; e <= 9; ++e) {
                        int sum3_1 = a + b + c;
                        int sum3_2 = b + c + d;
                        int sum3_3 = c + d + e;
                        int sum4_1 = a + b + c + d;
                        int sum4_2 = b + c + d + e;
                        int sum5 = a + b + c + d + e;
                        if (is_prime[sum3_1] && is_prime[sum3_2] && is_prime[sum3_3] &&
                            is_prime[sum4_1] && is_prime[sum4_2] && is_prime[sum5]) {
                            int state = b * 1000 + c * 100 + d * 10 + e;
                            dp[state]++;
                        }
                    }
                }
            }
        }
    }

    for (int len = 6; len <= 400000; ++len) {
        fill(next_dp.begin(), next_dp.end(), 0);
        int total = 0;
        for (int state = 0; state < 10000; ++state) {
            if (dp[state] == 0) continue;
            int d2 = state / 1000;
            int d3 = (state / 100) % 10;
            int d4 = (state / 10) % 10;
            int d5 = state % 10;
            // Try adding a new digit d6
            for (int d6 = 0; d6 <= 9; ++d6) {
                // Check all required sums:
                // 1. d3 + d4 + d5 + d6 must be prime (sum4)
                // 2. d4 + d5 + d6 must be prime (sum3)
                // 3. d2 + d3 + d4 + d5 + d6 must be prime (sum5)
                // But since the previous state (d2,d3,d4,d5) was valid, we only need to check the new sums involving d6.
                int sum3 = d4 + d5 + d6;
                int sum4 = d3 + d4 + d5 + d6;
                int sum5 = d2 + d3 + d4 + d5 + d6;
                if (is_prime[sum3] && is_prime[sum4] && is_prime[sum5]) {
                    int new_state = d3 * 1000 + d4 * 100 + d5 * 10 + d6;
                    next_dp[new_state] = (next_dp[new_state] + dp[state]) % MOD;
                }
            }
        }
        // Compute total for current len
        for (int state = 0; state < 10000; ++state) {
            total = (total + next_dp[state]) % MOD;
        }
        ans[len] = total;
        dp.swap(next_dp);
    }

    int q;
    cin >> q;
    while (q--) {
        int n;
        cin >> n;
        cout << ans[n] << '\n';
    }

    return 0;
}
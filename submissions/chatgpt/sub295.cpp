#include <iostream>
#include <vector>
#include <map>
using namespace std;

// Function to factorize k into its prime factors and their exponents
void factorize(int k, vector<int>& primes, vector<int>& exponents) {
    for (int p = 2; 1LL * p * p <= k; ++p) {
        if (k % p == 0) {
            int cnt = 0;
            while (k % p == 0) {
                k /= p;
                ++cnt;
            }
            primes.push_back(p);
            exponents.push_back(cnt);
        }
    }
    if (k > 1) {
        primes.push_back(k);
        exponents.push_back(1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int& x : a) cin >> x;

    // Step 1: Factorize k
    vector<int> primes, exponents;
    factorize(k, primes, exponents);
    int m = primes.size();

    // Step 2: For each card, compute the exponent of each prime in a[i]
    // prefix_sums[i][j]: sum of exponents of primes[j] in a[0..i-1]
    vector<vector<int>> prefix_sums(n + 1, vector<int>(m, 0));
    for (int i = 0; i < n; ++i) {
        vector<int> cur(m, 0);
        int val = a[i];
        for (int j = 0; j < m; ++j) {
            int cnt = 0;
            while (val % primes[j] == 0) {
                val /= primes[j];
                ++cnt;
            }
            cur[j] = cnt;
        }
        for (int j = 0; j < m; ++j) {
            prefix_sums[i + 1][j] = prefix_sums[i][j] + cur[j];
        }
    }

    // Step 3: Two pointers to find all valid subarrays
    long long ans = 0;
    int r = 0;
    for (int l = 0; l < n; ++l) {
        // Move r to the right as long as the subarray [l, r] is not valid
        while (r < n) {
            bool valid = true;
            for (int j = 0; j < m; ++j) {
                int cnt = prefix_sums[r + 1][j] - prefix_sums[l][j];
                if (cnt < exponents[j]) {
                    valid = false;
                    break;
                }
            }
            if (valid) break;
            ++r;
        }
        // If r == n, no more valid subarrays starting from l
        if (r == n) break;
        // For this l, all subarrays [l, r], [l, r+1], ..., [l, n-1] are valid
        ans += n - r;
    }

    cout << ans << '\n';
    return 0;
}
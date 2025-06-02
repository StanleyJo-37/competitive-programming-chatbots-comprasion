#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 100000;

// Precompute f(n) for all n up to MAXN, where f(n) is the sum of all odd divisors of n
// Also, precompute prefix sums for fast range queries
int main() {
    // f[i] will store the sum of all odd divisors of i
    vector<long long> f(MAXN + 1, 0);
    // For every odd number d, add d to all its multiples up to MAXN
    for (int d = 1; d <= MAXN; d += 2) {
        for (int m = d; m <= MAXN; m += d) {
            f[m] += d;
        }
    }
    // prefix[i] will store sum of f[1] + f[2] + ... + f[i]
    vector<long long> prefix(MAXN + 1, 0);
    for (int i = 1; i <= MAXN; ++i) {
        prefix[i] = prefix[i - 1] + f[i];
    }

    int T;
    cin >> T;
    while (T--) {
        int l, r;
        cin >> l >> r;
        // The answer is prefix[r] - prefix[l-1]
        cout << (prefix[r] - prefix[l - 1]) << '\n';
    }
    return 0;
}
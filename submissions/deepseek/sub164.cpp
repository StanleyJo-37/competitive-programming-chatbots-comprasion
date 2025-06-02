#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9 + 7;

// Function to compute the sum S for given L and R
long long solve(long long L, long long R) {
    long long sum = 0;
    // Iterate over each bit position from 0 to 60 (since 1e18 < 2^60)
    for (int k = 0; k <= 60; ++k) {
        long long mask = 1LL << k;
        // Check if the k-th bit is set in L
        if ((L & mask) == 0) continue;
        // Find the maximum number m such that L AND (L+1) AND ... AND m has the k-th bit set
        // This happens when m < (L | (mask - 1)), i.e., m < (L with all lower bits set)
        long long max_m = (L | (mask - 1));
        max_m = min(max_m, R);
        if (max_m < L) continue;
        // The count of numbers where the k-th bit is set is (max_m - L + 1)
        long long cnt = max_m - L + 1;
        // Add the contribution of this bit to the sum
        sum = (sum + (mask % MOD) * (cnt % MOD)) % MOD) % MOD;
    }
    return sum;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        long long L, R;
        cin >> L >> R;
        cout << solve(L, R) << '\n';
    }
    return 0;
}
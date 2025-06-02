#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll MOD = 1e9 + 7;

// Function to compute the AND of all numbers from L to R (inclusive)
// This is only nonzero as long as the highest differing bit between L and R is not set
ll range_and(ll L, ll R) {
    // The AND of all numbers from L to R is L & (L+1) & ... & R
    // This is equal to L & L+1 & ... & R = L with all bits after the highest differing bit zeroed
    // So, we shift L and R right until they are equal, counting the shifts
    ll shift = 0;
    while (L < R) {
        L >>= 1;
        R >>= 1;
        shift++;
    }
    return L << shift;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;
    while (T--) {
        ll L, R;
        cin >> L >> R;

        ll ans = 0;
        ll cur = L;
        ll and_val = L;

        // For each i from L to R, the AND value can only decrease (bits can only be turned off)
        // Once a bit is turned off, it never comes back
        // So, for each segment where the AND value stays the same, we can sum up the length of the segment
        while (cur <= R) {
            // Find the next position where the AND value will change
            // The AND value changes at the next number where a bit in 'and_val' is turned off
            // The next such number is (cur | (cur - 1)) + 1, but we need to ensure we don't go past R
            ll next = cur;
            // Find the next number where the AND value will change
            // The AND value for [cur, x] is the same as long as all numbers in [cur, x] have the same bits as 'and_val'
            // The AND value changes at the first number where a bit in 'and_val' is turned off
            // The next number where the AND value changes is when cur increases to a number where a bit in 'and_val' is 0
            // So, we can use the property that the AND of [cur, x] is the same as long as x < (cur | (~and_val & ((1LL<<62)-1)))
            // But it's easier to just brute force up to 64 steps, since the AND value can only change at most 64 times
            ll temp = cur;
            ll temp_and = and_val;
            while (temp <= R) {
                temp_and &= temp;
                if (temp_and != and_val) break;
                temp++;
            }
            // Now, [cur, temp-1] all have the same AND value
            ll cnt = temp - cur;
            ans = (ans + (and_val % MOD) * (cnt % MOD)) % MOD;
            cur = temp;
            and_val = temp_and;
        }
        cout << ans << '\n';
    }
    return 0;
}
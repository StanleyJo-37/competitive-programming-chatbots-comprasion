#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;
const ll MOD = 1000000007;

// Function to count numbers in [l, r] with remainder rem mod 3
ll count(ll l, ll r, int rem) {
    // First number >= l with remainder rem
    ll first = l + ((rem - (l % 3) + 3) % 3);
    if (first > r) return 0;
    // Last number <= r with remainder rem
    ll last = r - ((r % 3 - rem + 3) % 3);
    if (last < l) return 0;
    // Number of terms in arithmetic progression
    return (last - first) / 3 + 1;
}

int main() {
    ll n, l, r;
    cin >> n >> l >> r;

    // cnt[rem] = number of numbers in [l, r] with remainder rem mod 3
    vector<ll> cnt(3);
    for (int rem = 0; rem < 3; ++rem) {
        cnt[rem] = count(l, r, rem);
    }

    // dp[i][rem] = number of ways to fill i elements so that sum % 3 == rem
    vector<ll> dp(3, 0);
    dp[0] = 1; // 0 elements, sum 0

    // For each position, update dp
    for (ll i = 0; i < n; ++i) {
        vector<ll> ndp(3, 0);
        for (int rem = 0; rem < 3; ++rem) {
            for (int add = 0; add < 3; ++add) {
                // Add a number with remainder 'add'
                int nrem = (rem + add) % 3;
                ndp[nrem] = (ndp[nrem] + dp[rem] * cnt[add]) % MOD;
            }
        }
        dp = ndp;
    }

    // The answer is the number of ways with sum % 3 == 0
    cout << dp[0] << endl;
    return 0;
}
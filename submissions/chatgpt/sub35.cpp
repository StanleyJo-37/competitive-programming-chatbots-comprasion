#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;

int main() {
    int n;
    cin >> n;
    vector<ll> a(n), b(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < n; ++i) cin >> b[i];

    // Calculate the initial sum without any reversal
    ll initial_sum = 0;
    for (int i = 0; i < n; ++i) {
        initial_sum += a[i] * b[i];
    }

    ll max_sum = initial_sum;

    // dp[l][r]: the gain in sum if we reverse subarray a[l..r]
    // We only need to keep current and previous rows, so we can optimize space to O(n)
    vector<vector<ll>> dp(n, vector<ll>(n, 0));

    // For all possible centers (odd and even length subarrays)
    // Odd length subarrays
    for (int center = 0; center < n; ++center) {
        int l = center, r = center;
        ll gain = 0;
        while (l >= 0 && r < n) {
            // When we reverse a[l..r], a[l] goes to a[r]'s place and vice versa
            // The gain is: (a[r]*b[l] + a[l]*b[r]) - (a[l]*b[l] + a[r]*b[r])
            if (l == r) {
                // Only one element, no change
                gain = 0;
            } else {
                gain += a[l] * b[r] + a[r] * b[l] - a[l] * b[l] - a[r] * b[r];
            }
            max_sum = max(max_sum, initial_sum + gain);
            --l;
            ++r;
        }
    }

    // Even length subarrays
    for (int center = 0; center < n - 1; ++center) {
        int l = center, r = center + 1;
        ll gain = 0;
        while (l >= 0 && r < n) {
            gain += a[l] * b[r] + a[r] * b[l] - a[l] * b[l] - a[r] * b[r];
            max_sum = max(max_sum, initial_sum + gain);
            --l;
            ++r;
        }
    }

    cout << max_sum << endl;
    return 0;
}
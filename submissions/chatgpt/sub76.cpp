#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Read input
    int n, k, x;
    cin >> n >> k >> x;
    vector<ll> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];

    // Precompute prefix and suffix ORs for fast calculation
    // prefix_or[i] = a[0] | a[1] | ... | a[i-1]
    // suffix_or[i] = a[i] | a[i+1] | ... | a[n-1]
    vector<ll> prefix_or(n+1, 0), suffix_or(n+1, 0);
    for (int i = 0; i < n; ++i) prefix_or[i+1] = prefix_or[i] | a[i];
    for (int i = n-1; i >= 0; --i) suffix_or[i] = suffix_or[i+1] | a[i];

    // The answer is the maximum OR we can get by multiplying one element by x^k
    // For each position, try multiplying a[i] by x^k and OR with the rest
    ll max_or = 0;
    ll xk = 1;
    for (int i = 0; i < k; ++i) xk *= x; // x^k

    for (int i = 0; i < n; ++i) {
        // Calculate the value if we multiply a[i] by x^k
        ll val = a[i] * xk;
        // OR with all other elements (using prefix and suffix ORs)
        ll cur_or = prefix_or[i] | val | suffix_or[i+1];
        if (cur_or > max_or) max_or = cur_or;
    }

    // Output the result
    cout << max_or << '\n';
    return 0;
}
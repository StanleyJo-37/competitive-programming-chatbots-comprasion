#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

// Function to compute x^y % m using binary exponentiation
ll mod_pow(ll x, ll y, ll m) {
    ll res = 1;
    x %= m;
    while (y) {
        if (y & 1) res = res * x % m;
        x = x * x % m;
        y >>= 1;
    }
    return res;
}

// Function to compute modular inverse of a under modulo m (m must be prime)
ll mod_inv(ll a, ll m) {
    // Fermat's little theorem: a^(m-2) % m
    return mod_pow(a, m - 2, m);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;
    vector<pair<int, int>> points; // (x, y)
    // Read sequence a
    for (int i = 1; i <= n; ++i) {
        int x;
        cin >> x;
        points.emplace_back(x, i);
    }
    // Read sequence b
    for (int i = 1; i <= n; ++i) {
        int x;
        cin >> x;
        points.emplace_back(x, i);
    }
    int m;
    cin >> m;

    // Sort all 2n points by x-coordinate, then by y-coordinate
    sort(points.begin(), points.end());

    // Precompute factorials and inverse factorials up to 2n modulo m
    // We need to compute (2n)! / (cnt1! * cnt2! * ... * cntk!) % m
    // where cnti is the count of identical points (x, y)
    int N = 2 * n;
    vector<ll> fact(N + 1, 1), inv_fact(N + 1, 1);
    for (int i = 1; i <= N; ++i) {
        fact[i] = fact[i - 1] * i % m;
    }
    // Compute inverse factorials
    inv_fact[N] = mod_inv(fact[N], m);
    for (int i = N - 1; i >= 0; --i) {
        inv_fact[i] = inv_fact[i + 1] * (i + 1) % m;
    }

    // Count the number of ways to interleave the two sequences
    // such that x-coordinates are non-decreasing and each point is used once
    // This is the number of distinct permutations of the 2n points
    // with possible repeated (x, y) pairs
    ll ans = fact[N];
    // For each group of identical (x, y), divide by cnt!
    for (int i = 0; i < N;) {
        int j = i;
        while (j < N && points[j] == points[i]) ++j;
        int cnt = j - i;
        ans = ans * inv_fact[cnt] % m;
        i = j;
    }
    cout << ans << '\n';
    return 0;
}
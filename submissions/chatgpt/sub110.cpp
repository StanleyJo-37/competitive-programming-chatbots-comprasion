#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    // Fast IO
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long l, r;
    cin >> n >> l >> r;

    vector<long long> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];

    vector<int> p(n);
    for (int i = 0; i < n; ++i) cin >> p[i];

    // c must be a permutation of n distinct values, so we can assign c_i = sorted_c[p_i-1]
    // Let's construct c such that its compressed sequence is exactly p

    // Step 1: Build c such that its compressed sequence is p
    // Since p is a permutation of 1..n, we can assign c values in increasing order
    // For example, let c_values = [base, base+1, ..., base+n-1]
    // The actual values of c don't matter as long as they are distinct and in order

    // But we need to ensure that for each i, b_i = c_i + a_i is in [l, r]
    // So, for each i, b_i = c_i + a_i, and l <= b_i <= r
    // => l - a_i <= c_i <= r - a_i

    // Let's choose base as the minimal possible value so that all b_i are in [l, r]
    // For each i, c_i = base + (p[i] - 1)
    // So, b_i = a_i + base + (p[i] - 1)
    // So, l <= b_i <= r
    // => l - a_i - (p[i] - 1) <= base <= r - a_i - (p[i] - 1)
    // For all i, base must satisfy all these constraints

    long long min_base = -1e18, max_base = 1e18;
    for (int i = 0; i < n; ++i) {
        long long min_bi = l - a[i] - (p[i] - 1);
        long long max_bi = r - a[i] - (p[i] - 1);
        if (min_bi > min_base) min_base = min_bi;
        if (max_bi < max_base) max_base = max_bi;
    }

    // If no valid base, print -1
    if (min_base > max_base) {
        cout << -1 << '\n';
        return 0;
    }

    // Now, assign base = min_base (any value in [min_base, max_base] is valid)
    long long base = min_base;

    // Build c and b
    vector<long long> c(n), b(n);
    for (int i = 0; i < n; ++i) {
        c[i] = base + (p[i] - 1);
        b[i] = a[i] + c[i];
        // b[i] must be in [l, r] by construction
    }

    // Output b
    for (int i = 0; i < n; ++i) {
        cout << b[i] << (i + 1 == n ? '\n' : ' ');
    }
    return 0;
}
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    // Read input
    int n;
    long long m;
    cin >> n >> m;
    vector<long long> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];

    // Split the array into two halves for meet-in-the-middle
    int n1 = n / 2;
    int n2 = n - n1;

    vector<long long> left, right;

    // Generate all possible subset sums for the left half
    for (int mask = 0; mask < (1 << n1); ++mask) {
        long long sum = 0;
        for (int i = 0; i < n1; ++i) {
            if (mask & (1 << i)) sum += a[i];
        }
        left.push_back(sum % m);
    }

    // Generate all possible subset sums for the right half
    for (int mask = 0; mask < (1 << n2); ++mask) {
        long long sum = 0;
        for (int i = 0; i < n2; ++i) {
            if (mask & (1 << i)) sum += a[n1 + i];
        }
        right.push_back(sum % m);
    }

    // Sort the right half for binary search
    sort(right.begin(), right.end());

    long long ans = 0;

    // For each sum in the left half, find the best possible sum in the right half
    for (long long l : left) {
        // We want to maximize (l + r) % m
        // For a given l, the best r is the largest r such that l + r < m
        long long need = m - 1 - l;
        // upper_bound returns iterator to first element > need
        auto it = upper_bound(right.begin(), right.end(), need);
        if (it != right.begin()) {
            --it;
            ans = max(ans, (l + *it) % m);
        }
        // Also consider the case where we wrap around modulo m (i.e., l + r >= m)
        // The largest r in right
        ans = max(ans, (l + right.back()) % m);
    }

    cout << ans << endl;
    return 0;
}
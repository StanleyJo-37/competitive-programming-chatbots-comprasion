#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    // Fast IO
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<long long> a(n), b(n);

    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < n; ++i) cin >> b[i];

    // Compute c[i] = a[i] - b[i]
    vector<long long> c(n);
    for (int i = 0; i < n; ++i) c[i] = a[i] - b[i];

    // Sort c to allow binary search
    sort(c.begin(), c.end());

    long long ans = 0;
    // For each i, count number of j > i such that c[i] + c[j] > 0
    // This is equivalent to c[j] > -c[i]
    for (int i = 0; i < n; ++i) {
        // upper_bound returns iterator to first element > -c[i]
        // We need j > i, so search in c[i+1..n-1]
        // But since c is sorted, we can search in the whole array and subtract i+1
        auto it = upper_bound(c.begin() + i + 1, c.end(), -c[i]);
        // Number of elements in c[i+1..n-1] that are > -c[i]
        ans += c.end() - it;
    }

    cout << ans << '\n';
    return 0;
}
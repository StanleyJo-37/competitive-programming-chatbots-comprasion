#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k, x;
    cin >> n >> k >> x;
    vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    // Precompute prefix and suffix OR arrays to optimize OR calculation
    vector<long long> prefix(n + 1, 0), suffix(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        prefix[i + 1] = prefix[i] | a[i];
    }
    for (int i = n - 1; i >= 0; --i) {
        suffix[i] = suffix[i + 1] | a[i];
    }

    long long max_or = 0;
    // For each element, apply all k multiplications and compute OR with others
    for (int i = 0; i < n; ++i) {
        long long temp = a[i];
        for (int j = 0; j < k; ++j) {
            temp *= x;
        }
        // The OR is prefix[i] OR temp OR suffix[i+1]
        long long current_or = prefix[i] | temp | suffix[i + 1];
        if (current_or > max_or) {
            max_or = current_or;
        }
    }

    cout << max_or << '\n';
    return 0;
}
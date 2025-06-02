#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    // Compute prefix XOR array
    vector<int> prefix(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        prefix[i + 1] = prefix[i] ^ a[i];
    }

    // We need to count pairs (l, r) where r - l + 1 is even and
    // XOR from l to mid equals XOR from mid+1 to r.
    // This is equivalent to prefix[l-1] ^ prefix[mid] = prefix[mid] ^ prefix[r]
    // Which simplifies to prefix[l-1] = prefix[r].
    // So for even-length subarrays, we need prefix[l-1] = prefix[r] where (r - l + 1) is even.

    long long res = 0;
    // We'll use two maps to track prefix XORs at even and odd indices separately.
    // Because (r - (l-1)) must be odd (since r - l + 1 is even), so (l-1) and r must have opposite parity.
    // So we'll track prefix XORs at even and odd indices separately.
    unordered_map<int, int> count[2];
    count[0][0] = 1; // prefix[0] is at index 0 (even)

    for (int i = 1; i <= n; ++i) {
        res += count[i % 2][prefix[i]];
        count[i % 2][prefix[i]]++;
    }

    cout << res << endl;

    return 0;
}
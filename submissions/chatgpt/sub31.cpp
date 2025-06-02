#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n+1); // 1-based indexing
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    // Compute prefix XORs: pxor[i] = a[1] ^ a[2] ^ ... ^ a[i]
    vector<int> pxor(n+1, 0);
    for (int i = 1; i <= n; ++i) {
        pxor[i] = pxor[i-1] ^ a[i];
    }

    // We want to count pairs (l, r) with even length, l <= r
    // For each even length subarray, the XOR of left half == XOR of right half
    // That is, for subarray [l, r], len = r-l+1 is even, mid = (l+r-1)/2
    // left: [l, mid], right: [mid+1, r]
    // pxor[mid] ^ pxor[l-1] == pxor[r] ^ pxor[mid]
    // => pxor[mid] ^ pxor[l-1] == pxor[r] ^ pxor[mid]
    // => pxor[l-1] == pxor[r]

    // For all pairs (l, r) with even length, pxor[l-1] == pxor[r]
    // For each r, l = r - len + 1, len even, l >= 1

    // To count efficiently, for each parity (even/odd index), we keep a map of prefix XORs
    // For each position i, we count how many previous positions j (with same parity) have pxor[j] == pxor[i]
    // This is because for (l, r), r = i, l-1 = j, and (r - (l-1)) is even <=> parity of r == parity of l-1

    // Two maps: one for even indices, one for odd indices
    unordered_map<int, int> cnt[2];
    cnt[0][0] = 1; // pxor[0] = 0, index 0 is even

    long long ans = 0;
    for (int i = 1; i <= n; ++i) {
        int parity = i % 2;
        // Count how many previous prefix XORs with same parity equal to pxor[i]
        ans += cnt[parity][pxor[i]];
        // Add current prefix XOR to the map for this parity
        cnt[parity][pxor[i]]++;
    }

    cout << ans << '\n';
    return 0;
}
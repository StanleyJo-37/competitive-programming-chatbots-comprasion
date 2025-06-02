#include <iostream>
#include <vector>
using namespace std;

// Function to compute the unfairness for a given n
// Unfairness is the sum of Hamming distances between consecutive numbers from 0 to n
// For each bit position, count how many times the bit flips between consecutive numbers
// For numbers from 0 to n, the number of flips at bit position k is ((n + 1) / (1LL << (k + 1))) * (1LL << k) + max(0LL, (n + 1) % (1LL << (k + 1)) - (1LL << k))
// Sum over all bit positions
long long unfairness(long long n) {
    long long res = 0;
    // For 64-bit numbers, bits go up to 60 (since 2^60 > 1e18)
    for (int k = 0; k < 61; ++k) {
        long long len = 1LL << (k + 1); // length of a full cycle for bit k
        long long full_cycles = (n + 1) / len;
        long long rem = (n + 1) % len;
        // Each full cycle has (1 << k) flips at bit k
        long long flips = full_cycles * (1LL << k);
        // In the remaining part, if rem > (1 << k), there are (rem - (1 << k)) more flips
        if (rem > (1LL << k)) {
            flips += rem - (1LL << k);
        }
        res += flips;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        long long n;
        cin >> n;
        cout << unfairness(n) << '\n';
    }
    return 0;
}
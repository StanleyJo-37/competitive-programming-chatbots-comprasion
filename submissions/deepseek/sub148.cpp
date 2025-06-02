#include <iostream>
using namespace std;

// Function to calculate the unfairness for a given n.
// The key observation is that the sum of bit differences between consecutive numbers
// from 0 to n is equal to the total number of set bits in all numbers from 1 to n.
// This is because each transition from x to x+1 flips all trailing 1s to 0s and the next 0 to 1.
// Thus, the number of differing bits is exactly (number of trailing 1s in x) + 1.
// Summing this for all x from 0 to n-1 gives the total unfairness.
// The total unfairness can be computed as 2 * total_set_bits - count_set_bits(n).
// However, a more efficient approach is to compute the sum of set bits from 1 to n,
// which can be done using a mathematical formula for each bit position.
long long calculateUnfairness(long long n) {
    if (n == 0) return 0;
    long long unfairness = 0;
    long long i = 0;
    // For each bit position, calculate how many numbers from 1 to n have that bit set.
    // The formula is: (n + 1) / (2^(i+1)) * 2^i + max(0, (n + 1) % (2^(i+1)) - 2^i)
    while ((1LL << i) <= n) {
        long long next = 1LL << (i + 1);
        long long completeCycles = (n + 1) / next;
        long long setBits = completeCycles * (1LL << i);
        long long remainder = (n + 1) % next;
        setBits += max(0LL, remainder - (1LL << i));
        unfairness += setBits;
        i++;
    }
    return unfairness;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        long long n;
        cin >> n;
        cout << calculateUnfairness(n) << '\n';
    }
    return 0;
}
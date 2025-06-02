#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Function to generate a permutation of [0, n-1] with minimal maximal XOR between adjacent elements
void solve(int n) {
    // The idea is to use Gray code sequence of length n.
    // Gray code of length n ensures that adjacent numbers differ by only one bit,
    // so their XOR is always a power of two (and minimal possible).
    // For n not a power of two, we generate Gray codes for 0..n-1.
    vector<int> res(n);
    for (int i = 0; i < n; ++i) {
        // Gray code for i is i ^ (i >> 1)
        res[i] = i ^ (i >> 1);
    }
    // Output the permutation
    for (int i = 0; i < n; ++i) {
        cout << res[i] << (i + 1 == n ? '\n' : ' ');
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        solve(n);
    }
    return 0;
}
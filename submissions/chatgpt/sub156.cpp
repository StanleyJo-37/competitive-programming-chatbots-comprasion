#include <iostream>
#include <vector>
using namespace std;

// Function to compute XOR from 0 to n
int xor_to(int n) {
    // XOR from 0 to n follows a pattern based on n mod 4
    if (n < 0) return 0;
    int m = n % 4;
    if (m == 0) return n;
    if (m == 1) return 1;
    if (m == 2) return n + 1;
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int l, r;
        cin >> l >> r;
        int n = r - l + 1;
        vector<int> a(n);
        int xor_a = 0;
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
            xor_a ^= a[i]; // XOR of all elements in a
        }
        // XOR of all numbers from l to r is xor_to(r) ^ xor_to(l-1)
        int xor_lr = xor_to(r) ^ xor_to(l - 1);
        // Since a is a permutation of [l, r] with each element XORed with x,
        // xor_a = xor_lr ^ (n % 2 == 1 ? x : 0)
        // But since n is always odd (because permutation of [l, r] and l <= r),
        // xor_a = xor_lr ^ x => x = xor_a ^ xor_lr
        int x = xor_a ^ xor_lr;
        cout << x << '\n';
    }
    return 0;
}
#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false); // Fast IO
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<long long> a(n); // Number of rooms in each dormitory
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    // Compute prefix sums of rooms for each dormitory
    // prefix[i] = total number of rooms in dormitories 0..i-1
    vector<long long> prefix(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        prefix[i] = prefix[i - 1] + a[i - 1];
    }

    int dorm = 1; // Current dormitory index (1-based)
    for (int j = 0; j < m; ++j) {
        long long b;
        cin >> b;

        // Since b_j are sorted, we can use a moving pointer (two pointers)
        // Move dorm pointer until prefix[dorm] >= b
        while (prefix[dorm] < b) {
            ++dorm;
        }
        // The room number in the dormitory is b - prefix[dorm-1]
        cout << dorm << " " << (b - prefix[dorm - 1]) << "\n";
    }

    return 0;
}
#include <iostream>
#include <vector>
using namespace std;

// Function to check if a number contains digit d
bool contains_digit(int num, int d) {
    while (num > 0) {
        if (num % 10 == d) return true;
        num /= 10;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int q, d;
        cin >> q >> d;
        vector<int> a(q);
        for (int i = 0; i < q; ++i) cin >> a[i];

        // For each query, check if a_i can be written as sum of lucky numbers
        // Observation: For any number >= d*10, we can always form it
        // For numbers < d*10, we can brute force by checking a_i - k*d for k=0..a_i/d
        for (int i = 0; i < q; ++i) {
            int ai = a[i];
            bool found = false;
            // If ai >= d*10, always possible
            if (ai >= d * 10) {
                cout << "YES\n";
                continue;
            }
            // Try subtracting k*d for k=0..10 (since ai < d*10, at most 10 subtractions)
            for (int k = 0; k <= 100; ++k) {
                int val = ai - k * d;
                if (val < 0) break;
                if (contains_digit(val, d)) {
                    found = true;
                    break;
                }
            }
            cout << (found ? "YES" : "NO") << '\n';
        }
    }
    return 0;
}
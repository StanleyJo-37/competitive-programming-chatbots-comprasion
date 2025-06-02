#include <iostream>
#include <vector>
using namespace std;

int main() {
    int t;
    cin >> t; // Read number of test cases
    while (t--) {
        int n;
        cin >> n; // Read size of the sequence
        vector<int> a(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i]; // Read the sequence
        }
        // If the sequence has only one element, we can erase it in one operation
        if (n == 1) {
            cout << 1 << endl;
            continue;
        }
        // For n > 1, we need to check if the sequence is alternating (like 1 2 1 2 ...)
        // If so, after removing any element, the two adjacent elements will be equal and one will be erased immediately
        // The minimum number of operations is n/2 + 1 (if n is even), otherwise n
        // But actually, the maximum number of operations is n if we erase elements in such a way that no two equal elements become adjacent
        // Let's check if the sequence is alternating
        bool is_alternating = true;
        for (int i = 0; i < n; ++i) {
            if (a[i] != a[i % 2]) {
                is_alternating = false;
                break;
            }
        }
        // If the sequence is alternating and n is even, the answer is n/2 + 1
        // Otherwise, the answer is n
        if (is_alternating && n % 2 == 0) {
            cout << n / 2 + 1 << endl;
        } else {
            cout << n << endl;
        }
    }
    return 0;
}
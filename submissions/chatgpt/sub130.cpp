#include <iostream>
#include <vector>
using namespace std;

int main() {
    int t;
    cin >> t; // Read number of test cases
    while (t--) {
        int n;
        cin >> n; // Read size of array
        vector<int> a(n);
        int total_xor = 0;
        // Read the array and compute the XOR of all elements
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
            total_xor ^= a[i];
        }
        // The answer is simply the XOR of all elements in the array.
        // This is because: let the original array be b of size n-1, and x = b[0]^b[1]^...^b[n-2]
        // The new array is b[0], b[1], ..., b[n-2], x (shuffled)
        // So, XOR of all elements in the new array = b[0]^b[1]^...^b[n-2]^x = x^x = 0
        // Therefore, x = total_xor of all elements in the array.
        cout << total_xor << endl;
    }
    return 0;
}
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }
        
        // The original array had n-1 elements, and x was XOR of all those.
        // After adding x, the new array has n elements, and XOR of all is x XOR x = 0.
        // So, the XOR of all elements in the shuffled array must be 0.
        // Therefore, x is the XOR of all elements in the current array (since x XOR x = 0).
        int x = 0;
        for (int num : a) {
            x ^= num;
        }
        cout << x << endl;
    }
    return 0;
}
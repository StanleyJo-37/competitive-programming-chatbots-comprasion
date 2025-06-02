#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    while (t--) {
        int a, b;
        cin >> a >> b;
        
        // The MEX is 'a', so the array must contain all numbers from 0 to a-1.
        // The XOR of all elements must be 'b'.
        // The minimal array length is either:
        // 1. a (if XOR of 0..a-1 is already b), or
        // 2. a+1 (if XOR of 0..a-1 is not b, we can adjust by adding a number to make the total XOR b).
        // 3. a+2 (if XOR of 0..a-1 is (b ^ a), then adding a and another number (b ^ a ^ something) to make total XOR b).
        
        int xor_up_to_a_minus_1;
        if (a % 4 == 1) {
            xor_up_to_a_minus_1 = a - 1;
        } else if (a % 4 == 2) {
            xor_up_to_a_minus_1 = 1;
        } else if (a % 4 == 3) {
            xor_up_to_a_minus_1 = a;
        } else {
            xor_up_to_a_minus_1 = 0;
        }
        
        if (xor_up_to_a_minus_1 == b) {
            // No need to add any extra elements, the array is [0..a-1].
            cout << a << '\n';
        } else {
            // The required XOR is (xor_up_to_a_minus_1 ^ x) = b.
            // So x = xor_up_to_a_minus_1 ^ b.
            // If x is not equal to a, we can add it directly (length a+1).
            // If x is equal to a, we need to add two more numbers (a and some other number) to avoid MEX becoming a+1.
            int x = xor_up_to_a_minus_1 ^ b;
            if (x != a) {
                cout << a + 1 << '\n';
            } else {
                cout << a + 2 << '\n';
            }
        }
    }
    
    return 0;
}
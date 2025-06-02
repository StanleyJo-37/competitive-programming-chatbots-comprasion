#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int a, b;
        cin >> a >> b;

        // Calculate the XOR of all numbers from 0 to a-1
        int x = 0;
        for (int i = 0; i < a; ++i) {
            x ^= i;
        }

        // If x == b, then the array [0, 1, ..., a-1] has MEX a and XOR b
        if (x == b) {
            cout << a << '\n';
        }
        // If (x ^ b) == a, then adding (x ^ b) would make the array contain 'a', which is not allowed (MEX must be a)
        // So, we need to add two more elements: (x ^ b) and any other (e.g., a), but since a is not allowed, we add two elements
        else if ((x ^ b) == a) {
            cout << a + 2 << '\n';
        }
        // Otherwise, we can add (x ^ b) to the array, which does not equal 'a', so MEX remains a
        else {
            cout << a + 1 << '\n';
        }
    }
    return 0;
}
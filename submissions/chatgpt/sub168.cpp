#include <iostream>
using namespace std;

int main() {
    int T;
    cin >> T; // Read number of test cases
    while (T--) {
        int L, R;
        cin >> L >> R; // Read range [L, R]
        int count = 0;
        // Iterate through all numbers in the range [L, R]
        for (int i = L; i <= R; ++i) {
            int last_digit = i % 10; // Get the last digit
            // Check if the last digit is 2, 3, or 9
            if (last_digit == 2 || last_digit == 3 || last_digit == 9) {
                ++count; // Increment count if pretty
            }
        }
        cout << count << endl; // Output the result for this test case
    }
    return 0;
}
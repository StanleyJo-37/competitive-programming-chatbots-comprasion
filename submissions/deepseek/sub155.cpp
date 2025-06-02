#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;
    
    // Since k=2, the operation is XOR. The problem reduces to finding x in 0..n-1
    // with adaptive changes: x_new = x_old XOR y (if guess y is wrong).
    // Strategy: Guess all numbers from 0 to n-1 in order, but account for the XOR changes.
    // The key observation is that after i-th wrong guess (y_i), the password becomes x_i = x_0 XOR y_1 XOR y_2 ... XOR y_i.
    // To guess correctly on the i-th try, we need y_i = x_0 XOR y_1 XOR ... XOR y_{i-1}.
    // So, we can guess y_i = (i-1) XOR y_1 XOR y_2 ... XOR y_{i-1}, but since y_1..y_{i-1} are previous guesses,
    // we can track the cumulative XOR and guess i-1 XOR cumulative_xor.
    // However, since x_0 is unknown, we need to ensure that our guesses cover all possibilities.
    // The correct approach is to guess 0, then 1 XOR 0, then 2 XOR 1 XOR 0, etc.
    // This way, the i-th guess is (i-1) XOR cumulative_xor, where cumulative_xor is the XOR of all previous guesses.
    
    int cumulative_xor = 0;
    for (int i = 0; i < n; ++i) {
        int guess = i ^ cumulative_xor;
        cout << guess << endl;
        cout.flush();
        
        int r;
        cin >> r;
        if (r == 1) {
            return; // Correct guess, move to next test case
        } else if (r == -1) {
            exit(0); // Error, exit immediately
        }
        
        cumulative_xor ^= guess;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    
    return 0;
}
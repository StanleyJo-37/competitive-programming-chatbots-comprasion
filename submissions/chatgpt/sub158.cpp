#include <iostream>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false); // Fast IO
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        string A, B;
        cin >> A >> B;

        // The operation: select i, set A[i] = A[i] ^ A[i+1], A[i+1] = A[i] ^ A[i+1]
        // After operation, both A[i] and A[i+1] become the same: x ^ y
        // This means, for any adjacent pair, we can set both to x ^ y
        // The only way to change bits is to "spread" 1s or 0s, but only if there is at least one '1' in A

        // If at any point, we need to change a 0 to 1 or 1 to 0, we need at least one '1' in A up to that point
        // Let's simulate greedily from left to right

        int ones = 0, zeros = 0;
        for (char c : A) {
            if (c == '1') ones++;
            else zeros++;
        }

        // If there is no '1' in A, A is all zeros, so we can only make B if B is also all zeros
        if (ones == 0) {
            if (B.find('1') == string::npos) {
                cout << "YES\n";
            } else {
                cout << "NO\n";
            }
            continue;
        }

        // If there is no '0' in A, A is all ones, so we can only make B if B is also all ones
        if (zeros == 0) {
            if (B.find('0') == string::npos) {
                cout << "YES\n";
            } else {
                cout << "NO\n";
            }
            continue;
        }

        // Otherwise, if A has at least one '1' and one '0', we can always make A equal to B
        // This is because, for any pair, we can set both to 0 or 1 as needed, and propagate changes
        cout << "YES\n";
    }
    return 0;
}
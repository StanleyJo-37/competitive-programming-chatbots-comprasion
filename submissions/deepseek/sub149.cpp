#include <iostream>
using namespace std;

int main() {
    int T;
    cin >> T;
    while (T--) {
        int A, B, N;
        cin >> A >> B >> N;
        
        int target = A ^ B;
        
        if (target == 0) {
            cout << 0 << endl;
            continue;
        }
        
        // The maximum possible XOR value with X < N is (N-1)
        int max_possible_xor = N - 1;
        
        if (target <= max_possible_xor) {
            cout << 1 << endl;
            continue;
        }
        
        // If target is not directly achievable in one step, check if it can be done in two steps
        // The idea is to find if (target ^ max_possible_xor) < N, because:
        // A ^ X1 ^ X2 = B => X1 ^ X2 = target. If X1 is max_possible_xor, then X2 = target ^ X1.
        // If X2 < N, then it's possible in two steps.
        int required_xor = target ^ max_possible_xor;
        if (required_xor < N) {
            cout << 2 << endl;
        } else {
            cout << -1 << endl;
        }
    }
    return 0;
}
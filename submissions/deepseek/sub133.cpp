#include <iostream>
#include <string>
using namespace std;

void solve() {
    int T;
    cin >> T;
    while (T--) {
        int N;
        string S;
        cin >> N >> S;
        
        int count0 = 0, count1 = 0;
        for (char c : S) {
            if (c == '0') count0++;
            else count1++;
        }
        
        // For a xor palindrome, all pairs (i, N+1-i) must have the same XOR value.
        // XOR can be either 0 (both bits same) or 1 (bits different).
        // Case 1: All XORs are 0 (all pairs are same).
        // This requires even number of bits (N even) or exactly one middle bit (N odd).
        // Total 0s and 1s must both be even (if N even) or differ by 1 (if N odd).
        bool case0_possible = false;
        if (N % 2 == 0) {
            if (count0 % 2 == 0 && count1 % 2 == 0) {
                case0_possible = true;
            }
        } else {
            if ((count0 % 2 == 1 && count1 % 2 == 0) || (count0 % 2 == 0 && count1 % 2 == 1)) {
                case0_possible = true;
            }
        }
        
        // Case 2: All XORs are 1 (all pairs are different).
        // This requires exactly half 0s and half 1s (if N even).
        // If N is odd, it's impossible because the middle bit would have to XOR with itself (0).
        bool case1_possible = false;
        if (N % 2 == 0) {
            if (count0 == count1) {
                case1_possible = true;
            }
        }
        
        if (case0_possible || case1_possible) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
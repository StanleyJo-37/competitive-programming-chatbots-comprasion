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
        string S;
        cin >> N >> S;

        int cnt0 = 0, cnt1 = 0;
        // Count number of 0s and 1s in the string
        for (char c : S) {
            if (c == '0') cnt0++;
            else cnt1++;
        }

        // For a string to be rearranged into a xor palindrome:
        // There are two possible values for S_i ^ S_{N+1-i}: 0 or 1.
        // - If S_i ^ S_{N+1-i} == 0 for all i, then S is a palindrome (S_i == S_{N+1-i} for all i).
        //   This is possible if we can pair all 0s and all 1s (i.e., at most one unpaired if N is odd).
        // - If S_i ^ S_{N+1-i} == 1 for all i, then S_i != S_{N+1-i} for all i.
        //   This is possible only if N is even and cnt0 == cnt1 (since every pair must be (0,1) or (1,0)).

        bool possible = false;
        if (N % 2 == 0) {
            // N even: possible if cnt0 == cnt1 (for xor=1) or always possible (for xor=0, i.e., palindrome)
            if (cnt0 % 2 == 0 || cnt1 % 2 == 0) possible = true;
            // Actually, for N even, we can always make a palindrome (xor=0) if both counts are even,
            // and we can make xor=1 if cnt0 == cnt1.
            // But, more generally, for N even, it's always possible unless both cnt0 and cnt1 are odd.
            // Let's check that:
            if (cnt0 % 2 == 0 || cnt1 % 2 == 0) possible = true;
            else possible = false;
        } else {
            // N odd: the middle character is unpaired, so for palindrome (xor=0), at most one count is odd
            // For xor=1, not possible since odd N can't be fully paired with different values
            // So, possible if at most one of cnt0 or cnt1 is odd
            if (abs(cnt0 - cnt1) <= 1) possible = true;
            else possible = false;
        }

        // Actually, the above can be simplified:
        // For N even: possible unless both cnt0 and cnt1 are odd
        // For N odd: always possible

        if (N % 2 == 0) {
            if (cnt0 % 2 == 1 && cnt1 % 2 == 1) cout << "NO\n";
            else cout << "YES\n";
        } else {
            cout << "YES\n";
        }
    }
    return 0;
}
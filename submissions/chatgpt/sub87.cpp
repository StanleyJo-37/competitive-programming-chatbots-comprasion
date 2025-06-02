#include <iostream>
#include <string>
using namespace std;

int main() {
    int t;
    cin >> t; // Read number of test cases
    while (t--) {
        int n;
        string s;
        cin >> n >> s; // Read length and bracket sequence

        // The idea: For a string to be a regular bracket sequence,
        // at any prefix, the number of ')' should never exceed '('.
        // We simulate the balance as we traverse the string.
        // If at any point the balance goes negative, it means we have more ')' than '(' up to that point.
        // The minimum number of moves required is the maximum number of unmatched ')' in any prefix,
        // i.e., the minimum number of '(' we need to move to the front to fix all unmatched ')'.

        int balance = 0; // Current balance of '(' minus ')'
        int min_balance = 0; // Minimum balance encountered

        for (char c : s) {
            if (c == '(') balance++;
            else balance--;
            if (balance < min_balance) min_balance = balance;
        }

        // If min_balance is negative, we need to fix -min_balance unmatched ')'
        // Each such unmatched ')' can be fixed by moving a '(' to the front.
        // If min_balance >= 0, the string is already regular, so 0 moves needed.
        cout << -min_balance << endl;
    }
    return 0;
}
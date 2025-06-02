#include <iostream>
#include <string>

using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        string s;
        cin >> n >> s;
        int balance = 0;
        int min_balance = 0; // Tracks the minimum balance encountered
        for (char c : s) {
            if (c == '(') {
                balance++;
            } else {
                balance--;
            }
            min_balance = min(min_balance, balance);
        }
        // The answer is the number of times balance goes below 0 (i.e., -min_balance)
        cout << -min_balance << endl;
    }
    return 0;
}
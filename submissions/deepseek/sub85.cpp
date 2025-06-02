#include <iostream>
#include <string>
using namespace std;

void solve() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        string s;
        cin >> n >> s;
        int balance = 0; // Tracks the number of unanswered questions
        for (char c : s) {
            if (c == 'Q') {
                balance++; // New question increases the balance
            } else {
                if (balance > 0) {
                    balance--; // Answer reduces the balance if there are pending questions
                }
            }
        }
        // If balance is <= 0, all questions have been answered (or extra answers exist)
        cout << (balance <= 0 ? "Yes" : "No") << endl;
    }
}

int main() {
    solve();
    return 0;
}
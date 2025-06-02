#include <iostream>
#include <string>
using namespace std;

// Function to check if a given bracket sequence is regular
bool is_regular(const string& s) {
    int balance = 0;
    for (char c : s) {
        if (c == '(') balance++;
        else balance--;
        if (balance < 0) return false; // More closing than opening at some point
    }
    return balance == 0; // Must be balanced at the end
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        string a;
        cin >> a;
        int n = a.size();
        // There are 2^3 = 8 possible mappings for 'A', 'B', 'C' to '(' or ')'
        // We try all possible mappings
        bool found = false;
        for (int mask = 0; mask < 8; ++mask) {
            // mapping[0] for 'A', mapping[1] for 'B', mapping[2] for 'C'
            char mapping[3];
            for (int i = 0; i < 3; ++i) {
                if (mask & (1 << i)) mapping[i] = '(';
                else mapping[i] = ')';
            }
            // Build the bracket sequence b
            string b;
            for (char c : a) {
                b += mapping[c - 'A'];
            }
            // Check if b is a regular bracket sequence
            if (is_regular(b)) {
                found = true;
                break;
            }
        }
        cout << (found ? "YES" : "NO") << '\n';
    }
    return 0;
}
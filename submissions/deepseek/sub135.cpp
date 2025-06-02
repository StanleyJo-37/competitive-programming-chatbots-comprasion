#include <iostream>
#include <string>
#include <vector>
#include <stack>

using namespace std;

// Function to check if a given bracket sequence is regular
bool isRegular(const string &s) {
    stack<char> st;
    for (char c : s) {
        if (c == '(') {
            st.push(c);
        } else {
            if (st.empty()) return false;
            st.pop();
        }
    }
    return st.empty();
}

// Function to solve each test case
void solve() {
    int t;
    cin >> t;
    while (t--) {
        string a;
        cin >> a;
        bool possible = false;
        
        // There are 2^3 = 8 possible mappings for A, B, C to '(' or ')'
        // We will check all possible mappings
        for (int mask = 0; mask < 8; ++mask) {
            string b;
            // Determine the mapping for each character
            char mapA = (mask & 1) ? '(' : ')';
            char mapB = (mask & 2) ? '(' : ')';
            char mapC = (mask & 4) ? '(' : ')';
            
            // Construct the bracket sequence based on the current mapping
            for (char c : a) {
                if (c == 'A') b += mapA;
                else if (c == 'B') b += mapB;
                else if (c == 'C') b += mapC;
            }
            
            // Check if the constructed sequence is regular
            if (isRegular(b)) {
                possible = true;
                break;
            }
        }
        cout << (possible ? "YES" : "NO") << endl;
    }
}

int main() {
    solve();
    return 0;
}
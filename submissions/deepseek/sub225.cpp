#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

void solve() {
    int t;
    cin >> t;
    while (t--) {
        string s;
        cin >> s;
        vector<bool> working(26, false); // Tracks if a character is working for sure
        
        // Iterate through the string to determine working characters
        int n = s.size();
        for (int i = 0; i < n; ) {
            if (i + 1 < n && s[i] == s[i+1]) {
                // If current and next character are same, it could be malfunctioning or working
                // So we cannot be sure, skip next character
                i += 2;
            } else {
                // If current character is not followed by same, it must be working
                working[s[i] - 'a'] = true;
                i += 1;
            }
        }
        
        // Collect all working characters in alphabetical order
        string res;
        for (int i = 0; i < 26; ++i) {
            if (working[i]) {
                res += ('a' + i);
            }
        }
        cout << res << endl;
    }
}

int main() {
    solve();
    return 0;
}
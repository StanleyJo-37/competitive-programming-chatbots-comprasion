#include <iostream>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false); // Fast IO
    cin.tie(nullptr);

    int n;
    cin >> n;
    // For each test case
    while (n--) {
        string s, t;
        cin >> s >> t;
        int i = 0, j = 0;
        // Use two pointers: i for s, j for t
        // Try to match all characters of t in order in s
        while (i < s.size() && j < t.size()) {
            if (s[i] == t[j]) {
                // If current characters match, move both pointers
                ++j;
            }
            // Always move pointer in s
            ++i;
        }
        // If we have matched all characters in t, it's possible
        if (j == t.size()) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
    return 0;
}
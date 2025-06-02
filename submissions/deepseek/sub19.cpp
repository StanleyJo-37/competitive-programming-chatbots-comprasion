#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    string s;
    cin >> s;
    int n = s.size();
    vector<int> dp(n + 1, -1); // dp[i] = length of the last name (1-8) if s[0..i-1] is valid, else -1
    dp[0] = 0; // base case: empty string is valid

    for (int i = 1; i <= n; ++i) {
        // Check for possible name lengths (1-8) ending at i-1
        for (int l = 1; l <= 8 && i - l >= 0; ++l) {
            int start = i - l;
            if (dp[start] != -1) {
                // Check if there's a '.' in the last 3 characters of the current segment
                int dot_pos = s.substr(start, l).find_last_of('.');
                if (dot_pos != string::npos) {
                    int ext_len = l - dot_pos - 1;
                    if (ext_len >= 1 && ext_len <= 3) {
                        dp[i] = l;
                        break;
                    }
                }
            }
        }
    }

    if (dp[n] == -1) {
        cout << "NO" << endl;
        return 0;
    }

    // Reconstruct the solution
    vector<string> parts;
    int pos = n;
    while (pos > 0) {
        int l = dp[pos];
        parts.push_back(s.substr(pos - l, l));
        pos -= l;
    }

    cout << "YES" << endl;
    for (auto it = parts.rbegin(); it != parts.rend(); ++it) {
        cout << *it << endl;
    }

    return 0;
}
#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Function to check if a substring is a valid file name in BerFS
bool isValidFileName(const string& s, int start, int end) {
    // s[start..end-1] is the substring
    int len = end - start;
    // Minimum length is 3: 1 for name, 1 for dot, 1 for ext
    if (len < 3 || len > 12) return false;
    // Find the dot position
    int dot = -1;
    for (int i = start + 1; i < end - 1; ++i) { // dot cannot be at start or end
        if (s[i] == '.') {
            dot = i;
            break;
        }
    }
    if (dot == -1) return false; // no dot
    int nameLen = dot - start;
    int extLen = end - dot - 1;
    // name: 1..8, ext: 1..3
    if (nameLen < 1 || nameLen > 8) return false;
    if (extLen < 1 || extLen > 3) return false;
    // Check name and ext are all lowercase letters
    for (int i = start; i < dot; ++i) {
        if (s[i] < 'a' || s[i] > 'z') return false;
    }
    for (int i = dot + 1; i < end; ++i) {
        if (s[i] < 'a' || s[i] > 'z') return false;
    }
    return true;
}

int main() {
    string s;
    cin >> s;
    int n = s.size();
    // dp[i] = true if s[0..i-1] can be partitioned into valid file names
    vector<bool> dp(n + 1, false);
    // prev[i] = previous split position for dp[i]
    vector<int> prev(n + 1, -1);
    dp[0] = true; // empty prefix is valid

    // For each position, try to extend with a valid file name ending at i
    for (int i = 1; i <= n; ++i) {
        // File name length: 3 to 12
        for (int len = 3; len <= 12; ++len) {
            if (i - len < 0) continue;
            if (!dp[i - len]) continue;
            if (isValidFileName(s, i - len, i)) {
                dp[i] = true;
                prev[i] = i - len;
                break; // Only need one valid split
            }
        }
    }

    if (!dp[n]) {
        cout << "NO" << endl;
        return 0;
    }

    // Reconstruct the answer
    vector<string> ans;
    int pos = n;
    while (pos > 0) {
        int p = prev[pos];
        ans.push_back(s.substr(p, pos - p));
        pos = p;
    }
    // The answer is in reverse order
    cout << "YES" << endl;
    for (int i = ans.size() - 1; i >= 0; --i) {
        cout << ans[i] << endl;
    }
    return 0;
}
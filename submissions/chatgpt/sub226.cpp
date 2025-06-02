#include <iostream>
#include <string>
#include <algorithm>
#include <climits>
using namespace std;

// Helper function to compute minimum deletions needed to make s[l..r] palindrome
// by only deleting character 'ch'. Returns INT_MAX if impossible.
int min_deletions(const string& s, int l, int r, char ch) {
    int cnt = 0;
    while (l < r) {
        if (s[l] == s[r]) {
            l++;
            r--;
        } else if (s[l] == ch) {
            cnt++;
            l++;
        } else if (s[r] == ch) {
            cnt++;
            r--;
        } else {
            // Can't make palindrome by only deleting 'ch'
            return INT_MAX;
        }
    }
    return cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        string s;
        cin >> n >> s;

        // First, check if s is already a palindrome
        bool is_palindrome = true;
        for (int i = 0; i < n / 2; ++i) {
            if (s[i] != s[n - 1 - i]) {
                is_palindrome = false;
                break;
            }
        }
        if (is_palindrome) {
            cout << 0 << '\n';
            continue;
        }

        // Try all possible characters 'a' to 'z'
        int ans = INT_MAX;
        for (char ch = 'a'; ch <= 'z'; ++ch) {
            int res = min_deletions(s, 0, n - 1, ch);
            if (res < ans) ans = res;
        }
        if (ans == INT_MAX) cout << -1 << '\n';
        else cout << ans << '\n';
    }
    return 0;
}
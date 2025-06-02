#include <bits/stdc++.h>
using namespace std;

// Function to check if the string can be made palindrome by removing some occurrences of a chosen character
int minDeletionsToPalindrome(const string &s) {
    int left = 0, right = s.size() - 1;
    while (left < right) {
        if (s[left] != s[right]) {
            // Mismatch found, need to check possibilities of removing left or right character
            return -1;
        }
        left++;
        right--;
    }
    return 0; // Already a palindrome
}

// Function to check if the string can be made palindrome by removing some occurrences of 'c'
int checkForChar(const string &s, char c) {
    int left = 0, right = s.size() - 1;
    int deletions = 0;
    while (left < right) {
        if (s[left] == s[right]) {
            left++;
            right--;
        } else {
            if (s[left] == c) {
                deletions++;
                left++;
            } else if (s[right] == c) {
                deletions++;
                right--;
            } else {
                return -1; // Cannot make palindrome by removing 'c'
            }
        }
    }
    return deletions;
}

int solve() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        string s;
        cin >> n >> s;
        
        // First check if it's already a palindrome
        int res = minDeletionsToPalindrome(s);
        if (res == 0) {
            cout << 0 << endl;
            continue;
        }
        
        // If not, find the first mismatch and check possible characters to remove
        int left = 0, right = n - 1;
        while (left < right && s[left] == s[right]) {
            left++;
            right--;
        }
        
        // Check both possibilities (remove s[left] or s[right])
        int option1 = checkForChar(s, s[left]);
        int option2 = checkForChar(s, s[right]);
        
        if (option1 == -1 && option2 == -1) {
            cout << -1 << endl;
        } else if (option1 == -1) {
            cout << option2 << endl;
        } else if (option2 == -1) {
            cout << option1 << endl;
        } else {
            cout << min(option1, option2) << endl;
        }
    }
    return 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
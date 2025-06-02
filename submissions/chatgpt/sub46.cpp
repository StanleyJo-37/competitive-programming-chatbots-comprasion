#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

// Function to check if a string is a palindrome
bool isPalindrome(const string& s) {
    int l = 0, r = s.size() - 1;
    while (l < r) {
        if (s[l] != s[r]) return false;
        ++l; --r;
    }
    return true;
}

int main() {
    string s;
    cin >> s;
    int n = s.size();
    string best = "";

    // Iterate over all possible non-empty subsequences using bitmask
    // For each mask, build the subsequence and check if it's a palindrome
    // If it is, update the best answer if it's lexicographically larger
    for (int mask = 1; mask < (1 << n); ++mask) {
        string t = "";
        for (int i = 0; i < n; ++i) {
            if (mask & (1 << i)) t += s[i];
        }
        if (isPalindrome(t)) {
            if (t > best) best = t;
        }
    }

    cout << best << endl;
    return 0;
}
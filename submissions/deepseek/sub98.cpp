#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool canForm(const string &s, const string &t) {
    // Check if t is a subsequence of s in the order of deletions
    int i = 0, j = 0;
    while (i < s.size() && j < t.size()) {
        if (s[i] == t[j]) {
            i++;
            j++;
        } else {
            i++;
        }
    }
    // If we matched all characters in t, proceed to frequency check
    if (j != t.size()) return false;
    
    // Check frequency of each character in t is <= frequency in s
    vector<int> freqS(26, 0), freqT(26, 0);
    for (char c : s) freqS[c - 'A']++;
    for (char c : t) freqT[c - 'A']++;
    for (int k = 0; k < 26; k++) {
        if (freqT[k] > freqS[k]) {
            return false;
        }
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    cin.ignore(); // Ignore the newline after n
    
    while (n--) {
        string s, t;
        cin >> s >> t;
        if (canForm(s, t)) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
    
    return 0;
}
#include <iostream>
#include <string>
#include <vector>
#include <cctype>
using namespace std;

int main() {
    string s, t;
    cin >> s >> t;

    // Arrays to count occurrences of each letter (case-sensitive)
    // 0-25: 'A'-'Z', 26-51: 'a'-'z'
    vector<int> cnt_s(52, 0), cnt_t(52, 0);

    // Helper lambda to map character to index
    auto idx = [](char c) {
        if (isupper(c)) return c - 'A';
        else return c - 'a' + 26;
    };

    // Count letters in s and t
    for (char c : s) cnt_s[idx(c)]++;
    for (char c : t) cnt_t[idx(c)]++;

    int yay = 0, whoops = 0;

    // First, match exact case and letter for "YAY!"
    for (int i = 0; i < 52; ++i) {
        int match = min(cnt_s[i], cnt_t[i]);
        yay += match;
        cnt_s[i] -= match;
        cnt_t[i] -= match;
    }

    // Then, match only letter (case-insensitive) for "WHOOPS"
    for (int i = 0; i < 26; ++i) {
        // i: uppercase, i+26: lowercase
        // Try to match remaining uppercase in s with lowercase in t
        int match1 = min(cnt_s[i], cnt_t[i+26]);
        whoops += match1;
        cnt_s[i] -= match1;
        cnt_t[i+26] -= match1;

        // Try to match remaining lowercase in s with uppercase in t
        int match2 = min(cnt_s[i+26], cnt_t[i]);
        whoops += match2;
        cnt_s[i+26] -= match2;
        cnt_t[i] -= match2;
    }

    cout << yay << " " << whoops << endl;
    return 0;
}
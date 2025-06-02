#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <algorithm>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        string s;
        cin >> s;
        int n = s.size();
        // For each character, we will check if it is possible for it to be malfunctioning.
        // If for any occurrence, the character appears an odd number of times consecutively,
        // then it cannot be malfunctioning (since malfunctioning always produces pairs).
        // So, we will count consecutive runs for each character.
        // If all runs for a character are of length 1, then it is working for sure.
        // If any run is of odd length, it cannot be malfunctioning.
        // If all runs are even, it could be malfunctioning, but we want to find those that are working for sure.

        // We will mark characters that are working for sure.
        vector<bool> working(26, true);

        // For each character, we will check all its runs.
        // If any run is of odd length, it cannot be malfunctioning, so it must be working.
        // If all runs are even, it could be malfunctioning, so we will not include it.

        // We will use a set to store all characters that appear in the string.
        set<char> chars_in_s(s.begin(), s.end());

        // For each character, check all its runs.
        for (char c = 'a'; c <= 'z'; ++c) {
            int i = 0;
            bool can_be_malfunctioning = true;
            while (i < n) {
                if (s[i] == c) {
                    int j = i;
                    // Count the length of the run of character c.
                    while (j < n && s[j] == c) ++j;
                    int len = j - i;
                    // If the run length is odd, it cannot be malfunctioning.
                    if (len % 2 == 1) {
                        can_be_malfunctioning = false;
                        break;
                    }
                    i = j;
                } else {
                    ++i;
                }
            }
            // If it can be malfunctioning, it is not working for sure.
            // So, we only keep those that cannot be malfunctioning and appear in s.
            if (can_be_malfunctioning) working[c - 'a'] = false;
        }

        // Output all working characters in alphabetical order.
        for (char c = 'a'; c <= 'z'; ++c) {
            if (working[c - 'a'] && chars_in_s.count(c)) {
                cout << c;
            }
        }
        cout << '\n';
    }
    return 0;
}
#include <iostream>
#include <string>
using namespace std;

int main() {
    string s;
    cin >> s; // Read the input string

    string target = "hello"; // The word we want to form
    int j = 0; // Pointer for the target string

    // Iterate through the input string
    for (int i = 0; i < s.length(); ++i) {
        // If current character matches the current target character
        if (s[i] == target[j]) {
            ++j; // Move to the next character in "hello"
            // If we've matched all characters in "hello", break early
            if (j == target.length()) break;
        }
    }

    // If we've matched all characters in "hello" in order, print "YES"
    if (j == target.length()) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }

    return 0;
}
#include <iostream>
#include <string>

using namespace std;

int main() {
    string s;
    cin >> s;
    string target = "hello";
    int targetIndex = 0; // Tracks the current character to match in "hello"

    // Iterate through each character in the input string
    for (char c : s) {
        // If the current character matches the next required character in "hello"
        if (c == target[targetIndex]) {
            targetIndex++;
            // If we've matched all characters in "hello", print "YES" and exit
            if (targetIndex == target.length()) {
                cout << "YES" << endl;
                return 0;
            }
        }
    }
    // If loop completes without matching all characters, print "NO"
    cout << "NO" << endl;
    return 0;
}
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    string password;
    cin >> password;
    int n;
    cin >> n;
    vector<string> words(n);
    for (int i = 0; i < n; ++i) {
        cin >> words[i];
    }

    // Check if any word directly matches the password
    for (const string& word : words) {
        if (word == password) {
            cout << "YES" << endl;
            return 0;
        }
    }

    // Check if there exists a pair of words where the first ends with password[0]
    // and the second starts with password[1]
    bool hasFirstChar = false, hasSecondChar = false;
    for (const string& word : words) {
        if (word[1] == password[0]) {
            hasFirstChar = true;
        }
        if (word[0] == password[1]) {
            hasSecondChar = true;
        }
        // Early exit if both conditions are met
        if (hasFirstChar && hasSecondChar) {
            break;
        }
    }

    if (hasFirstChar && hasSecondChar) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }

    return 0;
}
#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    // Read the password
    string password;
    cin >> password;

    // Read the number of words
    int n;
    cin >> n;

    // Store the words
    vector<string> words(n);
    for (int i = 0; i < n; ++i) {
        cin >> words[i];
    }

    // Check if any word matches the password directly
    for (int i = 0; i < n; ++i) {
        if (words[i] == password) {
            cout << "YES" << endl;
            return 0;
        }
    }

    // Check if we can form the password as a substring by concatenating two words
    // The password is of length 2, so we need to check:
    // - If there exists a word whose second character matches the first character of the password
    // - And another word whose first character matches the second character of the password
    bool first_match = false, second_match = false;
    for (int i = 0; i < n; ++i) {
        if (words[i][1] == password[0]) first_match = true;
        if (words[i][0] == password[1]) second_match = true;
    }

    // If both conditions are satisfied, we can form the password as a substring
    if (first_match && second_match) {
        cout << "YES" << endl;
        return 0;
    }

    // Otherwise, it's not possible
    cout << "NO" << endl;
    return 0;
}
#include <iostream>
#include <string>
using namespace std;

// Helper function to check if a character is a vowel
bool isVowel(char c) {
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

int main() {
    string s;
    cin >> s;
    int n = s.size();

    // Result string to build the output with spaces inserted as needed
    string result;

    // Track the start of the current block of consonants
    int cons_start = -1;
    // Track the last consonant character in the current block
    char last_cons = 0;
    // Track the number of different consonants in the current block
    int diff_cons = 0;

    // For each character in the input string
    for (int i = 0; i < n; ++i) {
        char c = s[i];
        result += c;

        if (!isVowel(c)) {
            // If current character is a consonant
            if (cons_start == -1) {
                // Start a new consonant block
                cons_start = i;
                last_cons = c;
                diff_cons = 1;
            } else {
                // Continue the consonant block
                if (c != last_cons) {
                    ++diff_cons;
                    last_cons = c;
                }
            }

            // If the block has at least 3 consonants and at least 2 different letters
            if (i - cons_start + 1 >= 3 && diff_cons >= 2) {
                // Insert a space before the current character to break the typo
                // (We want to break as late as possible, so we break before the current character)
                result.insert(result.size() - 1, 1, ' ');
                // Start a new consonant block from the current character
                cons_start = i;
                last_cons = c;
                diff_cons = 1;
            }
        } else {
            // If current character is a vowel, reset consonant block tracking
            cons_start = -1;
            last_cons = 0;
            diff_cons = 0;
        }
    }

    cout << result << endl;
    return 0;
}
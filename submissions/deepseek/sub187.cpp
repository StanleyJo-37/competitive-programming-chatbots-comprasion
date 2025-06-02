#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    int n;
    string s;
    cin >> n >> s;

    // Frequency array to count occurrences of each character
    vector<int> freq(26, 0);
    for (char c : s) {
        freq[c - 'a']++;
    }

    bool possible = false;
    // Check if there's at least one character with frequency >= 2
    // Or if there's only one character (n == 1)
    for (int count : freq) {
        if (count >= 2 || n == 1) {
            possible = true;
            break;
        }
    }

    // If all characters have frequency 1 and n > 1, it's impossible
    cout << (possible ? "Yes" : "No") << endl;
    return 0;
}
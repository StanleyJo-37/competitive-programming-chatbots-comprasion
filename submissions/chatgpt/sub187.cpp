#include <iostream>
#include <string>
using namespace std;

int main() {
    int n;
    string s;
    cin >> n >> s;

    // Array to count occurrences of each color ('a' to 'z')
    int freq[26] = {0};

    // Count frequency of each color
    for (char c : s) {
        freq[c - 'a']++;
    }

    // If there's any color with at least 2 puppies, it's possible to standardize
    // Or if there's only one puppy, it's already standardized
    for (int i = 0; i < 26; ++i) {
        if (freq[i] >= 2 || n == 1) {
            cout << "Yes" << endl;
            return 0;
        }
    }

    // Otherwise, it's not possible
    cout << "No" << endl;
    return 0;
}
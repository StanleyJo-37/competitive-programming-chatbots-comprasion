#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    int n;
    cin >> n; // Read the number of friends
    vector<string> numbers(n);
    for (int i = 0; i < n; ++i) {
        cin >> numbers[i]; // Read each phone number
    }
    int len = numbers[0].size(); // All numbers have the same length
    int prefixLength = 0; // To store the length of the common prefix

    // For each position in the string
    for (int i = 0; i < len; ++i) {
        char current = numbers[0][i]; // Take the character from the first string
        bool allMatch = true;
        // Check if all strings have the same character at position i
        for (int j = 1; j < n; ++j) {
            if (numbers[j][i] != current) {
                allMatch = false;
                break; // As soon as a mismatch is found, break
            }
        }
        if (allMatch) {
            ++prefixLength; // If all match, increase the prefix length
        } else {
            break; // Stop at the first mismatch
        }
    }
    cout << prefixLength << endl; // Output the result
    return 0;
}
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<string> numbers(n);
    
    for (int i = 0; i < n; ++i) {
        cin >> numbers[i];
    }
    
    int min_len = numbers[0].length();
    int common_prefix_len = 0;
    bool mismatch_found = false;
    
    // Iterate over each character position
    for (int i = 0; i < min_len; ++i) {
        char current_char = numbers[0][i];
        // Check if all strings have the same character at position i
        for (int j = 1; j < n; ++j) {
            if (numbers[j][i] != current_char) {
                mismatch_found = true;
                break;
            }
        }
        if (mismatch_found) {
            break;
        }
        common_prefix_len++;
    }
    
    cout << common_prefix_len << endl;
    return 0;
}
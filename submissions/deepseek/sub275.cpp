#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    int T;
    cin >> T; // Read number of test cases
    
    while (T--) {
        string N;
        cin >> N; // Read the number as a string to handle leading zeros if any (though constraints say first block is never 0)
        
        string reversedN = N;
        reverse(reversedN.begin(), reversedN.end()); // Reverse the string
        
        if (N == reversedN) {
            cout << "wins" << endl; // If original and reversed are the same, it's a palindrome
        } else {
            cout << "loses" << endl; // Otherwise, the player loses
        }
    }
    
    return 0;
}
#include <iostream>
#include <string>
using namespace std;

int main() {
    int T;
    cin >> T; // Read number of test cases
    while (T--) {
        string N;
        cin >> N; // Read the number as a string to easily check for palindrome
        int len = N.length();
        bool isPalindrome = true;
        // Check if the string is a palindrome by comparing characters from both ends
        for (int i = 0; i < len / 2; ++i) {
            if (N[i] != N[len - 1 - i]) {
                isPalindrome = false;
                break;
            }
        }
        // Output result based on palindrome check
        if (isPalindrome)
            cout << "wins" << endl;
        else
            cout << "loses" << endl;
    }
    return 0;
}
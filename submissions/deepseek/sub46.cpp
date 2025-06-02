#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    string s;
    cin >> s;
    
    // The lexicographically largest palindromic subsequence is simply the largest character repeated as many times as it appears.
    // Because a single character is a palindrome, and the largest character repeated will form the largest possible lex string.
    char max_char = *max_element(s.begin(), s.end());
    
    // Count the occurrences of the max_char
    int count = 0;
    for (char c : s) {
        if (c == max_char) {
            count++;
        }
    }
    
    // Construct the result by repeating max_char 'count' times
    string result(count, max_char);
    cout << result << endl;
    
    return 0;
}
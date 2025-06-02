#include <iostream>
#include <string>
#include <vector>
#include <map> // For character mapping

// Function to check if a given string is a regular bracket sequence.
// A string s is a regular bracket sequence if:
// 1. The total number of '(' equals the total number of ')'.
// 2. For any prefix of s, the number of '(' is greater than or equal to the number of ')'.
bool is_regular(const std::string& s) {
    int balance = 0; // Tracks the current balance of open brackets
    for (char c : s) {
        if (c == '(') {
            balance++;
        } else { // c == ')'
            balance--;
        }
        // If balance ever drops below zero, it means we have a closing bracket
        // without a matching open bracket before it, so it's not regular.
        if (balance < 0) {
            return false;
        }
    }
    // For a regular bracket sequence, the final balance must be zero.
    // This ensures that the total number of '(' equals the total number of ')'.
    return balance == 0;
}

void solve() {
    std::string a;
    std::cin >> a;
    int n = a.length();

    // Optimization: A regular bracket sequence must start with '(' and end with ')'.
    // If a[0] and a[n-1] are the same character, say 'X', then 'X' must map to '('
    // and 'X' must map to ')'. This is a contradiction, as one character cannot map
    // to two different bracket types. Thus, if a[0] == a[n-1], it's impossible.
    if (a[0] == a[n-1]) {
        std::cout << "NO\n";
        return;
    }

    // Identify the three distinct characters 'A', 'B', 'C'.
    // char_first must map to '(', char_last must map to ')'.
    char char_first = a[0];
    char char_last = a[n-1];
    
    // Determine char_mid. It's the character among 'A', 'B', 'C' that is not char_first or char_last.
    // This uses the property that 'A', 'B', 'C' are distinct characters.
    // The sum of ASCII values of 'A', 'B', 'C' minus the ASCII values of char_first and char_last
    // will yield the ASCII value of char_mid.
    char char_mid = 'A' + 'B' + 'C' - char_first - char_last;

    // There are two possibilities for mapping char_mid:
    // 1. char_mid maps to '('
    // 2. char_mid maps to ')'
    // We try both possibilities.
    bool possible = false;
    for (int i = 0; i < 2; ++i) { // i=0 for char_mid maps to '(', i=1 for char_mid maps to ')'
        std::map<char, char> current_map;
        current_map[char_first] = '(';
        current_map[char_last] = ')';

        if (i == 0) { // char_mid maps to '('
            current_map[char_mid] = '(';
        } else { // char_mid maps to ')'
            current_map[char_mid] = ')';
        }

        std::string b = "";
        // Construct string b based on the current mapping
        for (char ch_a : a) {
            b += current_map[ch_a];
        }

        // Check if the constructed string b is a regular bracket sequence
        if (is_regular(b)) {
            possible = true;
            break; // Found a valid mapping, no need to check further
        }
    }

    if (possible) {
        std::cout << "YES\n";
    } else {
        std::cout << "NO\n";
    }
}

int main() {
    // Optimize C++ standard streams for competitive programming.
    // Unties cin/cout from stdio and disables synchronization with C stdio.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}

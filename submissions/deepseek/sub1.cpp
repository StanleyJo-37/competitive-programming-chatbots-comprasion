#include <iostream>
#include <string>
#include <set>
#include <algorithm>

using namespace std;

int main() {
    int n;
    string s;
    cin >> n >> s;

    // Count the number of each color
    int b = 0, g = 0, r = 0;
    for (char c : s) {
        if (c == 'B') b++;
        else if (c == 'G') g++;
        else if (c == 'R') r++;
    }

    set<char> possible;

    // If all cards are the same, the result is that color
    if (b == n || g == n || r == n) {
        possible.insert(s[0]);
    } 
    // If counts are all odd or all even, the result can be any color
    else if ((b % 2 == 1 && g % 2 == 1 && r % 2 == 1) || 
             (b % 2 == 0 && g % 2 == 0 && r % 2 == 0)) {
        possible.insert('B');
        possible.insert('G');
        possible.insert('R');
    } 
    // Otherwise, the result depends on the parity of counts
    else {
        if ((b % 2 == 1 && g % 2 == 0 && r % 2 == 0) || 
            (b % 2 == 0 && g % 2 == 1 && r % 2 == 1)) {
            possible.insert('B');
        }
        if ((g % 2 == 1 && b % 2 == 0 && r % 2 == 0) || 
            (g % 2 == 0 && b % 2 == 1 && r % 2 == 1)) {
            possible.insert('G');
        }
        if ((r % 2 == 1 && b % 2 == 0 && g % 2 == 0) || 
            (r % 2 == 0 && b % 2 == 1 && g % 2 == 1)) {
            possible.insert('R');
        }
    }

    // Output the result in alphabetical order
    for (char c : possible) {
        cout << c;
    }
    cout << endl;

    return 0;
}
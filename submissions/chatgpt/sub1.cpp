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
    int cntR = 0, cntG = 0, cntB = 0;
    for (char c : s) {
        if (c == 'R') cntR++;
        else if (c == 'G') cntG++;
        else if (c == 'B') cntB++;
    }

    // If only one color exists, that's the only possible answer
    if ((cntR > 0) + (cntG > 0) + (cntB > 0) == 1) {
        if (cntR) cout << "R\n";
        else if (cntG) cout << "G\n";
        else cout << "B\n";
        return 0;
    }

    // If all three colors exist, all are possible
    if (cntR > 0 && cntG > 0 && cntB > 0) {
        cout << "BGR\n";
        return 0;
    }

    // Now, only two colors exist. Let's determine which ones.
    set<char> result;

    // If only R and G exist
    if (cntR > 0 && cntG > 0 && cntB == 0) {
        // If there are at least 2 of any color, we can always get the third color
        if (cntR > 1 || cntG > 1) {
            result.insert('B');
        }
        // If both are 1, only B is possible
        if (cntR > 0) result.insert('R');
        if (cntG > 0) result.insert('G');
        // But if both are 1, only B is possible
        if (cntR == 1 && cntG == 1) {
            result.clear();
            result.insert('B');
        }
    }
    // If only R and B exist
    else if (cntR > 0 && cntB > 0 && cntG == 0) {
        if (cntR > 1 || cntB > 1) {
            result.insert('G');
        }
        if (cntR > 0) result.insert('R');
        if (cntB > 0) result.insert('B');
        if (cntR == 1 && cntB == 1) {
            result.clear();
            result.insert('G');
        }
    }
    // If only G and B exist
    else if (cntG > 0 && cntB > 0 && cntR == 0) {
        if (cntG > 1 || cntB > 1) {
            result.insert('R');
        }
        if (cntG > 0) result.insert('G');
        if (cntB > 0) result.insert('B');
        if (cntG == 1 && cntB == 1) {
            result.clear();
            result.insert('R');
        }
    }

    // Output the result in alphabetical order
    for (char c : {'B', 'G', 'R'}) {
        if (result.count(c)) cout << c;
    }
    cout << '\n';
    return 0;
}
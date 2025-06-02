#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main() {
    int T;
    cin >> T; // Read number of test cases
    while (T--) {
        int N;
        cin >> N; // Read number of rooms
        string S;
        cin >> S; // Read color configuration

        // Count occurrences of each color
        int countR = 0, countG = 0, countB = 0;
        for (char c : S) {
            if (c == 'R') countR++;
            else if (c == 'G') countG++;
            else if (c == 'B') countB++;
        }

        // To make all rooms the same color, repaint all rooms that are not of that color.
        // The minimum number of repaints is N - max(countR, countG, countB)
        int maxCount = max({countR, countG, countB});
        cout << (N - maxCount) << endl;
    }
    return 0;
}
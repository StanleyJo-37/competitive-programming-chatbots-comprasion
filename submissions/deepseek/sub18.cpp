#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

// Function to find the smallest number with m digits and sum of digits s
string findMin(int m, int s) {
    if (s == 0) {
        return (m == 1) ? "0" : "-1"; // Only possible if m=1 and s=0
    }
    if (s > 9 * m) {
        return "-1"; // Impossible to form such a number
    }
    string res;
    int remaining = s;
    for (int i = 0; i < m; i++) {
        // For each digit, choose the smallest possible digit (0 for leading is not allowed)
        int digit;
        if (i == 0) {
            // First digit must be at least 1
            digit = max(1, remaining - 9 * (m - i - 1));
        } else {
            digit = max(0, remaining - 9 * (m - i - 1));
        }
        remaining -= digit;
        res += to_string(digit);
    }
    return (remaining == 0) ? res : "-1";
}

// Function to find the largest number with m digits and sum of digits s
string findMax(int m, int s) {
    if (s == 0) {
        return (m == 1) ? "0" : "-1"; // Only possible if m=1 and s=0
    }
    if (s > 9 * m) {
        return "-1"; // Impossible to form such a number
    }
    string res;
    int remaining = s;
    for (int i = 0; i < m; i++) {
        // For each digit, choose the largest possible digit (9 if possible)
        int digit = min(9, remaining);
        remaining -= digit;
        res += to_string(digit);
    }
    return (remaining == 0) ? res : "-1";
}

int main() {
    int m, s;
    cin >> m >> s;
    
    string minNum = findMin(m, s);
    string maxNum = findMax(m, s);
    
    if (minNum == "-1" || maxNum == "-1") {
        cout << "-1 -1" << endl;
    } else {
        cout << minNum << " " << maxNum << endl;
    }
    
    return 0;
}
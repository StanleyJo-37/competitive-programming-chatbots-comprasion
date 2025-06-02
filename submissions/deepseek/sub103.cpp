#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

int main() {
    string s, t;
    cin >> s >> t;

    // Count frequency of each character in s and t (case-sensitive)
    unordered_map<char, int> sCount, tCount;
    for (char c : s) sCount[c]++;
    for (char c : t) tCount[c]++;

    int yay = 0, whoops = 0;

    // First pass: match exact characters (case-sensitive) to maximize YAY
    for (auto &[c, cnt] : sCount) {
        int matched = min(cnt, tCount[c]);
        yay += matched;
        sCount[c] -= matched;
        tCount[c] -= matched;
    }

    // Second pass: match case-insensitive characters (only if cases differ) for WHOOPS
    for (auto &[c, cnt] : sCount) {
        if (cnt == 0) continue;
        char oppositeCase = islower(c) ? toupper(c) : tolower(c);
        int matched = min(cnt, tCount[oppositeCase]);
        whoops += matched;
        sCount[c] -= matched;
        tCount[oppositeCase] -= matched;
    }

    cout << yay << " " << whoops << endl;

    return 0;
}
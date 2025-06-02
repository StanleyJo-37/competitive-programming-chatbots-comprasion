#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Function to compute the minimum prefix of s1 that is lexicographically not greater than s2
string minimize(const string& s1, const string& s2) {
    // s1 and s2 both start with '#'
    int n1 = s1.size();
    int n2 = s2.size();
    int i = 1; // skip the '#'
    // Find the first position where s1 and s2 differ
    while (i < n1 && i < n2 && s1[i] == s2[i]) {
        ++i;
    }
    // If we reached the end of s1, keep it as is
    if (i == n1) return s1;
    // If we reached the end of s2, s1 should not be longer than s2
    if (i == n2) return s1.substr(0, n2);
    // If s1[i] > s2[i], we need to cut s1 at position i
    if (s1[i] > s2[i]) {
        return s1.substr(0, i);
    }
    // If s1[i] < s2[i], s1 is already less, keep as is
    return s1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<string> hashtags(n);
    for (int i = 0; i < n; ++i) {
        cin >> hashtags[i];
    }

    // Process from the end to the beginning
    for (int i = n - 2; i >= 0; --i) {
        hashtags[i] = minimize(hashtags[i], hashtags[i + 1]);
    }

    // Output the result
    for (const string& s : hashtags) {
        cout << s << '\n';
    }
    return 0;
}
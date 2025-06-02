#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

string twoSort(vector<string> s) {
    // Sort the vector of strings in ascending order (case-sensitive, ASCII order)
    sort(s.begin(), s.end());
    // Get the first string after sorting
    string first = s[0];
    // Build the result string with "***" between each character
    string result;
    for (size_t i = 0; i < first.size(); ++i) {
        result += first[i];
        // Add "***" between characters, but not after the last character
        if (i != first.size() - 1) {
            result += "***";
        }
    }
    return result;
}

// Example usage and test
int main() {
    vector<string> input;
    string str;
    int n;
    // Read number of strings
    cin >> n;
    // Read n strings into the vector
    for (int i = 0; i < n; ++i) {
        cin >> str;
        input.push_back(str);
    }
    // Output the result of twoSort
    cout << twoSort(input) << endl;
    return 0;
}
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>

using namespace std;

// Function to generate all possible strings of length 'len' in lexicographical order
vector<string> generateStrings(int len) {
    vector<string> result;
    if (len == 0) return result;
    
    // Start with the smallest character 'a'
    result.push_back("");
    for (int i = 0; i < len; ++i) {
        vector<string> temp;
        for (const string &s : result) {
            for (char c = 'a'; c <= 'z'; ++c) {
                temp.push_back(s + c);
            }
        }
        result = temp;
    }
    return result;
}

int main() {
    int n;
    cin >> n;
    vector<string> titles(n);
    string allText; // Concatenate all titles to search substrings efficiently
    
    for (int i = 0; i < n; ++i) {
        cin >> titles[i];
        allText += titles[i] + " "; // Add a separator to avoid cross-title substrings
    }
    
    // Check for the shortest possible string (length 1 to max possible)
    for (int len = 1; len <= 20; ++len) {
        vector<string> candidates = generateStrings(len);
        for (const string &s : candidates) {
            bool found = false;
            // Check if 's' is a substring in any of the titles
            for (const string &title : titles) {
                if (title.find(s) != string::npos) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << s << endl;
                return 0;
            }
        }
    }
    
    // In case no string up to length 20 is found (unlikely per constraints)
    cout << "a" << endl; // Fallback, though problem says title can't be empty
    return 0;
}
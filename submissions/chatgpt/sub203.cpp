#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

// Helper function to split a string by a delimiter and return a vector of substrings
vector<string> split(const string& s, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// Helper function to calculate the alphabetical value of a character (case-insensitive)
int charValue(char c) {
    if (c >= 'A' && c <= 'Z') return c - 'A' + 1;
    if (c >= 'a' && c <= 'z') return c - 'a' + 1;
    return 0;
}

// Main function as per the problem statement
string rank(const string& st, vector<int> we, int n) {
    // If the input string is empty, return "No participants"
    if (st.empty()) return "No participants";

    // Split the names by comma
    vector<string> names = split(st, ',');

    // If n is greater than the number of participants, return "Not enough participants"
    if (n > (int)names.size()) return "Not enough participants";

    // Vector to store pairs of (winning number, name)
    vector<pair<long long, string>> winList;

    // Calculate the winning number for each name
    for (size_t i = 0; i < names.size(); ++i) {
        string name = names[i];
        long long som = name.length(); // Start with the length of the name
        for (char c : name) {
            som += charValue(c); // Add the alphabetical value of each character
        }
        long long winning_number = som * we[i]; // Multiply by the corresponding weight
        winList.push_back({winning_number, name});
    }

    // Sort by decreasing winning number, then alphabetically for ties
    sort(winList.begin(), winList.end(), [](const pair<long long, string>& a, const pair<long long, string>& b) {
        if (a.first != b.first) return a.first > b.first; // Descending by winning number
        return a.second < b.second; // Ascending alphabetically
    });

    // Return the name at the (n-1)th index (since rank is 1-based)
    return winList[n-1].second;
}

// Example usage and test
int main() {
    // Example from the problem statement
    string names = "COLIN,AMANDBA,AMANDAB,CAROL,PauL,JOSEPH";
    vector<int> weights = {1, 4, 4, 5, 2, 1};
    int n = 4;
    cout << rank(names, weights, n) << endl; // Should output "PauL"
    return 0;
}
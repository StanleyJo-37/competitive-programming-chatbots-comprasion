#include <iostream>
#include <vector>
#include <unordered_set>
#include <climits>

using namespace std;

// Define vowels for easy lookup
const unordered_set<char> vowels = {'a', 'e', 'i', 'o', 'u'};

// Function to check if a character is a consonant
bool isConsonant(char c) {
    return vowels.find(c) == vowels.end();
}

int main() {
    string word;
    cin >> word;
    int n = word.size();
    vector<int> dp(n + 1, INT_MAX); // dp[i] = min spaces needed up to index i
    vector<int> prev(n + 1, -1);    // To reconstruct the solution
    dp[0] = 0;

    for (int i = 1; i <= n; ++i) {
        for (int j = i - 1; j >= 0; --j) {
            string sub = word.substr(j, i - j);
            bool hasTypo = false;
            int consonantStreak = 0;
            char lastConsonant = '\0';
            bool allSame = true;

            for (char c : sub) {
                if (isConsonant(c)) {
                    consonantStreak++;
                    if (lastConsonant == '\0') {
                        lastConsonant = c;
                    } else if (c != lastConsonant) {
                        allSame = false;
                    }
                } else {
                    consonantStreak = 0;
                    lastConsonant = '\0';
                    allSame = true;
                }

                if (consonantStreak >= 3 && !allSame) {
                    hasTypo = true;
                    break;
                }
            }

            if (!hasTypo && dp[j] != INT_MAX) {
                if (dp[i] > dp[j] + (j != 0 ? 1 : 0)) {
                    dp[i] = dp[j] + (j != 0 ? 1 : 0);
                    prev[i] = j;
                }
            }
        }
    }

    if (dp[n] == 0) {
        cout << word << endl;
        return 0;
    }

    // Reconstruct the solution
    vector<string> parts;
    int pos = n;
    while (pos > 0) {
        int start = prev[pos];
        parts.push_back(word.substr(start, pos - start));
        pos = start;
    }

    for (int i = parts.size() - 1; i >= 0; --i) {
        cout << parts[i];
        if (i > 0) cout << " ";
    }
    cout << endl;

    return 0;
}
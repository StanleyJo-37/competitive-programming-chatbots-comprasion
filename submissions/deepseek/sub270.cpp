#include <vector>
#include <algorithm>
#include <string>
#include <climits>

using namespace std;

bool is_vowel(char c) {
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

string solve(const string &s) {
    vector<char> vowels, consonants;
    for (char c : s) {
        if (is_vowel(c)) {
            vowels.push_back(c);
        } else {
            consonants.push_back(c);
        }
    }
    
    int v = vowels.size();
    int c = consonants.size();
    
    // Check if alternation is possible
    if (abs(v - c) > 1) {
        return "failed";
    }
    
    // Sort vowels and consonants to generate lex smallest string
    sort(vowels.begin(), vowels.end());
    sort(consonants.begin(), consonants.end());
    
    string result;
    bool start_with_vowel;
    
    if (v > c) {
        start_with_vowel = true;
    } else if (c > v) {
        start_with_vowel = false;
    } else {
        start_with_vowel = true; // if equal, start with vowel
    }
    
    int vi = 0, ci = 0;
    bool failed = false;
    
    for (int i = 0; i < s.size(); ++i) {
        if (start_with_vowel) {
            if (i % 2 == 0) {
                if (vi >= vowels.size()) {
                    failed = true;
                    break;
                }
                result += vowels[vi++];
            } else {
                if (ci >= consonants.size()) {
                    failed = true;
                    break;
                }
                result += consonants[ci++];
            }
        } else {
            if (i % 2 == 0) {
                if (ci >= consonants.size()) {
                    failed = true;
                    break;
                }
                result += consonants[ci++];
            } else {
                if (vi >= vowels.size()) {
                    failed = true;
                    break;
                }
                result += vowels[vi++];
            }
        }
    }
    
    if (failed) {
        return "failed";
    }
    
    // Check if the generated string alternates correctly
    for (int i = 1; i < result.size(); ++i) {
        bool prev_vowel = is_vowel(result[i-1]);
        bool curr_vowel = is_vowel(result[i]);
        if (prev_vowel == curr_vowel) {
            return "failed";
        }
    }
    
    return result;
}
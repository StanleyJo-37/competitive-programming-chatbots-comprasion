#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// Helper function to check if a character is a vowel
bool is_vowel(char c) {
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

// Main solve function as per the problem statement
std::string solve(const std::string& s) {
    std::vector<char> vowels, consonants;
    // Separate vowels and consonants
    for (char c : s) {
        if (is_vowel(c)) vowels.push_back(c);
        else consonants.push_back(c);
    }
    int v = vowels.size();
    int c = consonants.size();
    // If the difference in count is more than 1, alternation is impossible
    if (std::abs(v - c) > 1) return "failed";
    // Sort both lists to ensure lexicographically smallest result
    std::sort(vowels.begin(), vowels.end());
    std::sort(consonants.begin(), consonants.end());
    std::string res1, res2;
    // If counts are equal, must start with vowel
    if (v == c) {
        // Build result starting with vowel
        int vi = 0, ci = 0;
        for (int i = 0; i < s.size(); ++i) {
            if (i % 2 == 0) res1 += vowels[vi++];
            else res1 += consonants[ci++];
        }
        return res1;
    }
    // If vowels are more, must start with vowel
    if (v > c) {
        int vi = 0, ci = 0;
        for (int i = 0; i < s.size(); ++i) {
            if (i % 2 == 0) res1 += vowels[vi++];
            else res1 += consonants[ci++];
        }
        return res1;
    }
    // If consonants are more, must start with consonant
    if (c > v) {
        int vi = 0, ci = 0;
        for (int i = 0; i < s.size(); ++i) {
            if (i % 2 == 0) res1 += consonants[ci++];
            else res1 += vowels[vi++];
        }
        return res1;
    }
    // Should never reach here
    return "failed";
}

// For testing
int main() {
    std::vector<std::string> tests = {
        "have",      // ahev
        "codewars",  // failed
        "oruder",    // edorur
        "orudere",   // ederoru
        "aeiou",     // failed
        "bcdfg",     // failed
        "abcde",     // abced
        "aabbcc",    // abacbc
        "aabbc",     // ababc
        "aab",       // aba
        "baa",       // aba
        "baba",      // abab
        "abab",      // abab
        "a",         // a
        "b",         // b
        "ab",        // ab
        "ba",        // ab
        "aeioubcdfg" // abcdaeiou
    };
    for (const auto& test : tests) {
        std::cout << "solve(\"" << test << "\") = \"" << solve(test) << "\"\n";
    }
    return 0;
}
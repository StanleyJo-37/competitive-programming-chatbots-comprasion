#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// Function to get the colour for a given term index (1-based)
std::string get_colour(int idx) {
    // The sequence is: red, yellow, blue, repeating every 3 terms
    static const std::string colours[3] = {"red", "yellow", "blue"};
    return colours[(idx - 1) % 3];
}

// Function to compute the nth term of the sequence: f(n) = n*(n+1)/2
long long sequence_term(int n) {
    return (1LL * n * (n + 1)) / 2;
}

// Main function as described in the problem
std::vector<long long> same_col_seq(int val, int k, const std::string& colour) {
    std::vector<long long> result;
    // The maximum value to search up to, as per the problem statement
    long long max_val = 2LL * k * val;
    // We need to find the smallest k terms of the given colour, greater than val, and <= max_val

    // Since f(n) = n*(n+1)/2, we can estimate the starting n using quadratic formula:
    // n^2 + n - 2*val > 0 => n = ceil((-1 + sqrt(1 + 8*val))/2)
    int n = (int)( ( -1.0 + sqrt(1.0 + 8.0 * val) ) / 2.0 );
    // Ensure f(n) > val
    while (sequence_term(n) <= val) ++n;

    // Now, iterate from n upwards, checking colour and collecting terms
    while (result.size() < (size_t)k && sequence_term(n) <= max_val) {
        long long term = sequence_term(n);
        if (term > val && get_colour(n) == colour) {
            result.push_back(term);
        }
        ++n;
    }
    // If not enough terms found, return empty vector
    if (result.size() < (size_t)k) return {};
    return result;
}

// For testing purposes
/*
int main() {
    // Example 1
    auto res1 = same_col_seq(3, 3, "blue");
    for (auto v : res1) std::cout << v << " ";
    std::cout << std::endl;

    // Example 2
    auto res2 = same_col_seq(100, 4, "red");
    for (auto v : res2) std::cout << v << " ";
    std::cout << std::endl;

    // Example 3
    auto res3 = same_col_seq(250, 6, "yellow");
    for (auto v : res3) std::cout << v << " ";
    std::cout << std::endl;

    return 0;
}
*/
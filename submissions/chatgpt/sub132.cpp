#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Function to count the number of set bits (1s) in the binary representation of n
int countBits(int n) {
    int cnt = 0;
    n = abs(n); // Only the magnitude matters for bit counting
    while (n) {
        cnt += n & 1;
        n >>= 1;
    }
    return cnt;
}

// Main function to determine the winner
string bits_war(const vector<int>& arr) {
    int odd_score = 0, even_score = 0;
    for (int num : arr) {
        int bits = countBits(num);
        if (num % 2 == 0) { // Even number
            if (num < 0)
                even_score -= bits; // Negative even: subtract bits
            else
                even_score += bits; // Positive even: add bits
        } else { // Odd number
            if (num < 0)
                odd_score -= bits; // Negative odd: subtract bits
            else
                odd_score += bits; // Positive odd: add bits
        }
    }
    // Compare scores and return the result
    if (odd_score > even_score)
        return "odds win";
    else if (even_score > odd_score)
        return "evens win";
    else
        return "tie";
}

// For testing purposes
int main() {
    // Example 1: odds win
    vector<int> arr1 = {1, 5, 12};
    cout << bits_war(arr1) << endl; // Output: odds win

    // Example 2: evens win
    vector<int> arr2 = {7, -3, 20};
    cout << bits_war(arr2) << endl; // Output: evens win

    // Example 3: tie
    vector<int> arr3 = {7, -3, -2, 6};
    cout << bits_war(arr3) << endl; // Output: tie

    return 0;
}
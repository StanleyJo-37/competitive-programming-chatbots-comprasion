#include <iostream>
#include <string>
using namespace std;

// Function to determine the winner of the game
string counterGame(unsigned long long n) {
    // If n is 1, Louise cannot make a move, so Richard wins
    if (n == 1) return "Richard";
    int turns = 0; // Count the number of moves made

    // Continue until n becomes 1
    while (n != 1) {
        // Check if n is a power of 2 using (n & (n-1)) == 0
        if ((n & (n - 1)) == 0) {
            // If n is a power of 2, divide by 2
            n >>= 1;
        } else {
            // If not, subtract the largest power of 2 less than n
            // Find the highest set bit (most significant bit)
            unsigned long long p = 1ULL << (63 - __builtin_clzll(n));
            n -= p;
        }
        // Increment the number of moves
        turns++;
    }
    // If the number of moves is even, Richard wins (since Louise starts)
    // If odd, Louise wins
    return (turns % 2 == 0) ? "Richard" : "Louise";
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        unsigned long long n;
        cin >> n;
        cout << counterGame(n) << endl;
    }
    return 0;
}
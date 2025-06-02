#include <iostream>
#include <string>
#include <bitset>

using namespace std;

// Function to determine the winner of the game
string counterGame(long long unsigned n) {
    // If n is 1, Louise cannot make a move, so Richard wins
    if (n == 1) {
        return "Richard";
    }
    
    int turns = 0;
    while (n != 1) {
        // Check if n is a power of 2 by verifying (n & (n - 1)) == 0
        if ((n & (n - 1)) == 0) {
            n /= 2;
        } else {
            // Find the largest power of 2 less than n by clearing all bits except the highest set bit
            long long unsigned power = 1;
            while (power * 2 <= n) {
                power *= 2;
            }
            n -= power;
        }
        turns++;
    }
    
    // If the number of turns is odd, Louise wins; otherwise, Richard wins
    return (turns % 2 == 1) ? "Louise" : "Richard";
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        long long unsigned n;
        cin >> n;
        cout << counterGame(n) << endl;
    }
    return 0;
}
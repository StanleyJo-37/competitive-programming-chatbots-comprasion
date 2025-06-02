#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    // Read the number of cards
    cin >> n;
    vector<int> cards(n);
    // Read the values on the cards
    for (int i = 0; i < n; ++i) {
        cin >> cards[i];
    }

    int sereja = 0, dima = 0; // Scores for Sereja and Dima
    int l = 0, r = n - 1;     // Two pointers: left and right ends of the cards
    bool turn = true;         // true: Sereja's turn, false: Dima's turn

    // Continue until all cards are taken
    while (l <= r) {
        // Choose the card with the larger value from either end
        if (cards[l] > cards[r]) {
            if (turn)
                sereja += cards[l];
            else
                dima += cards[l];
            ++l; // Move left pointer right
        } else {
            if (turn)
                sereja += cards[r];
            else
                dima += cards[r];
            --r; // Move right pointer left
        }
        turn = !turn; // Alternate turns
    }

    // Output the final scores
    cout << sereja << " " << dima << endl;
    return 0;
}
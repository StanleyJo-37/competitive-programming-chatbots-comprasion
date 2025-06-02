#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

// Function to determine the winner of the card game
string winner(const vector<char>& deckSteve, const vector<char>& deckJosh) {
    // Map each card character to its rank value for easy comparison
    unordered_map<char, int> rank = {
        {'2', 2}, {'3', 3}, {'4', 4}, {'5', 5}, {'6', 6}, {'7', 7},
        {'8', 8}, {'9', 9}, {'T', 10}, {'J', 11}, {'Q', 12}, {'K', 13}, {'A', 14}
    };

    int steveScore = 0, joshScore = 0;
    int n = deckSteve.size(); // Both decks are of the same size

    // Compare each card in order
    for (int i = 0; i < n; ++i) {
        int steveCard = rank[deckSteve[i]];
        int joshCard = rank[deckJosh[i]];
        if (steveCard > joshCard) {
            ++steveScore;
        } else if (joshCard > steveCard) {
            ++joshScore;
        }
        // If equal, no points are awarded
    }

    // Determine the result string based on scores
    if (steveScore > joshScore) {
        return "Steve wins " + to_string(steveScore) + " to " + to_string(joshScore);
    } else if (joshScore > steveScore) {
        return "Josh wins " + to_string(joshScore) + " to " + to_string(steveScore);
    } else {
        return "Tie";
    }
}

// Example usage and test
int main() {
    // Example decks
    vector<char> deckSteve = {'A','7','8'};
    vector<char> deckJosh = {'K','5','9'};
    // Output the result
    cout << winner(deckSteve, deckJosh) << endl; // Should output: Steve wins 2 to 1
    return 0;
}
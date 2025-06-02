#include <vector>
#include <string>
#include <map>

using namespace std;

string winner(vector<char> deckSteve, vector<char> deckJosh) {
    // Define the card rankings in order from lowest to highest
    const string cardRanks = "23456789TJQKA";
    // Create a map to quickly look up the rank of a card (higher value means higher rank)
    map<char, int> rankMap;
    for (int i = 0; i < cardRanks.size(); ++i) {
        rankMap[cardRanks[i]] = i;
    }

    int steveScore = 0, joshScore = 0;

    // Iterate through each card in the decks (assuming both decks are of the same size)
    for (int i = 0; i < deckSteve.size(); ++i) {
        char steveCard = deckSteve[i];
        char joshCard = deckJosh[i];
        
        // Compare the ranks of the cards
        if (rankMap[steveCard] > rankMap[joshCard]) {
            steveScore++;
        } else if (rankMap[joshCard] > rankMap[steveCard]) {
            joshScore++;
        }
        // If equal, no points are awarded
    }

    // Determine the result based on the scores
    if (steveScore > joshScore) {
        return "Steve wins " + to_string(steveScore) + " to " + to_string(joshScore);
    } else if (joshScore > steveScore) {
        return "Josh wins " + to_string(joshScore) + " to " + to_string(steveScore);
    } else {
        return "Tie";
    }
}
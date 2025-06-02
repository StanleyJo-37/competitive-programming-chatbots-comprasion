#include <string> // Required for std::string and std::to_string
#include <vector> // Required for std::vector

// Function to determine the winner of the card game between Steve and Josh.
// It takes two constant references to vectors of characters, representing their decks.
std::string winner(const std::vector<char>& deckSteve, const std::vector<char>& deckJosh) {
    // Define the card ranks from lowest to highest.
    // The position (index) of a card character in this string directly corresponds to its value.
    // For example, '2' is at index 0, '3' at index 1, ..., 'A' at index 12.
    const std::string card_ranks = "23456789TJQKA";

    // Initialize scores for both players to zero.
    int steveScore = 0;
    int joshScore = 0;

    // Iterate through the decks, comparing cards round by round.
    // The problem statement implies that both players are dealt the same number of cards,
    // so we can use the size of either deck to control the loop.
    for (size_t i = 0; i < deckSteve.size(); ++i) {
        // Get the current card for Steve and Josh for the current round.
        char steveCard = deckSteve[i];
        char joshCard = deckJosh[i];

        // Determine the numerical value (rank) of Steve's card.
        // std::string::find returns the zero-based index of the first occurrence of the character.
        // This index serves as the card's numerical value for comparison.
        int steveValue = card_ranks.find(steveCard);

        // Determine the numerical value (rank) of Josh's card.
        int joshValue = card_ranks.find(joshCard);

        // Compare the values of the cards to decide the winner of the current round.
        if (steveValue > joshValue) {
            // If Steve's card has a higher value, Steve wins the round and gets a point.
            steveScore++;
        } else if (joshValue > steveValue) {
            // If Josh's card has a higher value, Josh wins the round and gets a point.
            joshScore++;
        }
        // If steveValue == joshValue, the cards are of the same value,
        // and neither player gets a point for this round. No action is needed here.
    }

    // After all cards have been played and scores tallied, determine the overall game winner.
    if (steveScore > joshScore) {
        // If Steve has a higher total score, Steve wins the game.
        // Construct the result string in the specified format: "Steve wins x to y".
        return "Steve wins " + std::to_string(steveScore) + " to " + std::to_string(joshScore);
    } else if (joshScore > steveScore) {
        // If Josh has a higher total score, Josh wins the game.
        // Construct the result string in the specified format: "Josh wins x to y".
        // Note: For Josh winning, the problem asks for Josh's score first, then Steve's.
        return "Josh wins " + std::to_string(joshScore) + " to " + std::to_string(steveScore);
    } else {
        // If both players have the same total score, the game is a tie.
        return "Tie";
    }
}
#include <iostream> // Required for input/output operations (std::cin, std::cout)
#include <vector>   // Required for using std::vector to store card numbers

int main() {
    // Optimize C++ standard streams for competitive programming.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard I/O.
    // std::cin.tie(NULL) prevents std::cout from being flushed before each std::cin operation.
    // These two lines can significantly speed up I/O, especially for large inputs.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n; // Declare an integer variable 'n' to store the number of cards.
    std::cin >> n; // Read the number of cards from standard input.

    // Declare a std::vector named 'cards' of size 'n'.
    // This vector will store the integer values written on the cards.
    std::vector<int> cards(n);
    // Loop to read 'n' card values from standard input and store them in the 'cards' vector.
    for (int i = 0; i < n; ++i) {
        std::cin >> cards[i];
    }

    // Initialize scores for Sereja and Dima to zero.
    // Using 'long long' for scores is a good practice to prevent potential overflow,
    // although for given constraints (N=1000, card value=1000), int would also suffice
    // as max score is around 1000 * 1000 = 1,000,000, which fits in a 32-bit int.
    long long sereja_score = 0;
    long long dima_score = 0;

    // Initialize two pointers: 'left' pointing to the first card (index 0)
    // and 'right' pointing to the last card (index n-1).
    int left = 0;
    int right = n - 1;

    // Initialize a turn counter. '0' represents Sereja's turn, '1' represents Dima's turn.
    // The modulo operator (%) will be used to determine whose turn it is.
    int turn = 0; 

    // The game continues as long as there are cards left to pick.
    // This condition holds true as long as the 'left' pointer has not crossed the 'right' pointer.
    while (left <= right) {
        int current_card_value; // Variable to temporarily store the value of the card picked in the current turn.

        // Implement the greedy strategy: choose the card with the larger number.
        // If the value of the leftmost card is greater than or equal to the value of the rightmost card,
        // the current player takes the leftmost card.
        if (cards[left] >= cards[right]) {
            current_card_value = cards[left]; // Take the leftmost card.
            left++; // Move the left pointer one position to the right, effectively removing the card.
        } else {
            // Otherwise (if the rightmost card's value is greater),
            // the current player takes the rightmost card.
            current_card_value = cards[right]; // Take the rightmost card.
            right--; // Move the right pointer one position to the left, effectively removing the card.
        }

        // Add the value of the picked card to the appropriate player's score.
        // If 'turn' is even (0, 2, 4...), it's Sereja's turn.
        // If 'turn' is odd (1, 3, 5...), it's Dima's turn.
        if (turn % 2 == 0) {
            sereja_score += current_card_value;
        } else {
            dima_score += current_card_value;
        }

        turn++; // Increment the turn counter to switch to the next player.
    }

    // After the loop finishes (all cards have been picked), print the final scores.
    // Print Sereja's score, followed by a space, then Dima's score, and finally a newline character.
    std::cout << sereja_score << " " << dima_score << std::endl;

    return 0; // Indicate successful program execution.
}
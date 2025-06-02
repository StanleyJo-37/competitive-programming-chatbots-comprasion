#include <iostream> // Required for input/output operations (cin, cout)
#include <string>   // Required for using std::string

int main() {
    // Optimize C++ standard streams for competitive programming.
    // This unties cin/cout from stdio and disables synchronization with C stdio,
    // which can significantly speed up I/O operations.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::string password; // Declare a string to store the password
    std::cin >> password; // Read the password from standard input

    int n; // Declare an integer to store the number of words Kashtanka knows
    std::cin >> n; // Read n from standard input

    // Use boolean flags to track the conditions for unlocking the phone.
    // direct_match: true if any known word is exactly the password.
    bool direct_match = false;
    // first_char_of_any_word_is_password_second_char: true if any known word's first character
    // matches the second character of the password. This is for the case where
    // the password P = P1P2 is formed by concatenating two words W_i and W_j,
    // such that P = W_i[1] + W_j[0]. Here, W_j[0] must be P2 (password[1]).
    bool first_char_of_any_word_is_password_second_char = false;
    // second_char_of_any_word_is_password_first_char: true if any known word's second character
    // matches the first character of the password. This is for the case where
    // the password P = P1P2 is formed by concatenating two words W_i and W_j,
    // such that P = W_i[1] + W_j[0]. Here, W_i[1] must be P1 (password[0]).
    bool second_char_of_any_word_is_password_first_char = false;

    // Loop through each of the n words Kashtanka knows.
    for (int i = 0; i < n; ++i) {
        std::string word; // Declare a string to store the current word
        std::cin >> word; // Read the current word from standard input

        // Check for a direct match: if the current word is exactly the password.
        // If found, set direct_match to true.
        if (word == password) {
            direct_match = true;
        }

        // Check if the first character of the current word matches the second character of the password.
        // This condition is needed for forming the password by concatenating two words.
        // For example, if password is "ab" and current word is "xb", then 'b' (word[1]) matches password[1].
        // No, this is incorrect. The logic for concatenation is:
        // password = P1P2. We need W_i[1] == P1 and W_j[0] == P2.
        // So, we need to find a word whose second char is P1, and a word whose first char is P2.
        // Let's re-evaluate the flags based on this.

        // Check if the first character of the current word matches the second character of the password.
        // This means `word[0]` is `password[1]`. This word could be `W_j` in `W_i[1] + W_j[0]`.
        if (word[0] == password[1]) {
            first_char_of_any_word_is_password_second_char = true;
        }

        // Check if the second character of the current word matches the first character of the password.
        // This means `word[1]` is `password[0]`. This word could be `W_i` in `W_i[1] + W_j[0]`.
        if (word[1] == password[0]) {
            second_char_of_any_word_is_password_first_char = true;
        }
    }

    // Determine if the phone can be unlocked based on the conditions.
    // The phone can be unlocked if:
    // 1. A direct match was found (one of the words is the password itself).
    // OR
    // 2. It's possible to form the password by concatenating two words.
    //    This requires finding a word W_i such that W_i[1] == password[0]
    //    AND finding a word W_j such that W_j[0] == password[1].
    //    (Note: W_i and W_j can be the same word. For example, if password is "ah" and Kashtanka knows "ha".
    //    Here, "ha"[1] ('a') == password[0] ('a'), and "ha"[0] ('h') == password[1] ('h').
    //    So "ha" can serve as both W_i and W_j. Concatenating "ha" + "ha" results in "haha",
    //    which contains "ah" as a substring.)
    if (direct_match || (first_char_of_any_word_is_password_second_char && second_char_of_any_word_is_password_first_char)) {
        std::cout << "YES\n"; // If conditions met, print "YES"
    } else {
        std::cout << "NO\n"; // Otherwise, print "NO"
    }

    return 0; // Indicate successful execution
}
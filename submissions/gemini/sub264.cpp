#include <string>   // Required for std::string and std::to_string
#include <vector>   // Required for std::vector
#include <algorithm> // Required for std::transform and std::all_of
#include <cctype>   // Required for std::tolower, std::isupper

// Function to convert a given string to its lowercase equivalent.
// This is used to perform case-insensitive comparisons for event types.
std::string toLower(std::string s) {
    // std::transform applies a given operation to each element in a range.
    // Here, it converts each character of the string 's' to its lowercase version.
    // The static_cast<unsigned char> is important for std::tolower to work correctly
    // with various character sets and avoid undefined behavior for negative char values.
    std::transform(s.begin(), s.end(), s.begin(),
                   [](unsigned char c){ return std::tolower(static_cast<unsigned char>(c)); });
    return s;
}

// Function to check if all characters in a string are uppercase.
// This is used to determine the coffee cost (1 for lowercase, 2 for uppercase).
bool isAllUpper(const std::string& s) {
    // An empty string cannot be considered all uppercase.
    if (s.empty()) {
        return false;
    }
    // std::all_of checks if a predicate is true for all elements in a range.
    // Here, it checks if every character in the string 's' is an uppercase character.
    // The static_cast<unsigned char> is important for std::isupper to work correctly.
    return std::all_of(s.begin(), s.end(), [](unsigned char c){ return std::isupper(static_cast<unsigned char>(c)); });
}

// The main function to calculate the amount of coffee needed.
// It takes a vector of event strings and returns a string representing
// the total coffee count or a specific message if the count exceeds 3.
std::string howMuchCoffee(const std::vector<std::string>& events) {
    int coffee_count = 0; // Initialize the total coffee count to zero.

    // Iterate through each event string in the input vector.
    for (const std::string& event : events) {
        // Convert the current event string to lowercase for case-insensitive matching
        // against the predefined event types ('cw', 'dog', 'cat', 'movie').
        std::string lower_event = toLower(event);

        // Check if the lowercase version of the event matches any of the relevant types.
        if (lower_event == "cw" || lower_event == "dog" || lower_event == "cat" || lower_event == "movie") {
            // If it's a relevant event, determine the coffee cost based on its original case.
            if (isAllUpper(event)) {
                // If the original event string was entirely uppercase (e.g., "CW", "DOG"),
                // it costs 2 coffees.
                coffee_count += 2;
            } else {
                // Otherwise (if it was lowercase, e.g., "cw", "dog", or mixed case like "cW"
                // which is treated as not all uppercase), it costs 1 coffee.
                // The problem statement implies relevant events will be strictly all-lowercase or all-uppercase.
                coffee_count += 1;
            }
        }
        // Events that are not 'cw', 'dog', 'cat', or 'movie' (case-insensitive) are ignored
        // and do not contribute to the coffee count.

        // After processing each event, check if the total coffee count has exceeded 3.
        if (coffee_count > 3) {
            // If the count exceeds 3, return the specific message immediately,
            // as no further calculation is needed.
            return "You need extra sleep";
        }
    }

    // If the loop completes without the coffee count exceeding 3,
    // convert the final coffee count to a string and return it.
    return std::to_string(coffee_count);
}
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// Function to determine the number of coffees needed based on events
std::string howMuchCoffee(const std::vector<std::string>& events) {
    // List of relevant events (all lowercase for comparison)
    const std::vector<std::string> relevant = {"cw", "dog", "cat", "movie"};
    int coffee = 0;
    for (const std::string& event : events) {
        // Convert event to lowercase for comparison
        std::string lower_event = event;
        std::transform(lower_event.begin(), lower_event.end(), lower_event.begin(), ::tolower);
        // Check if the event is relevant
        bool is_relevant = false;
        for (const std::string& rel : relevant) {
            if (lower_event == rel) {
                is_relevant = true;
                break;
            }
        }
        if (!is_relevant) continue;
        // If event is all lowercase, add 1 coffee; if any uppercase, add 2 coffees
        bool is_all_lower = true;
        for (char c : event) {
            if (std::isalpha(c) && std::isupper(c)) {
                is_all_lower = false;
                break;
            }
        }
        if (is_all_lower) {
            coffee += 1;
        } else {
            coffee += 2;
        }
    }
    // If coffee count exceeds 3, return the warning string
    if (coffee > 3) return "You need extra sleep";
    // Otherwise, return the coffee count as a string
    return std::to_string(coffee);
}

// Example usage and test cases
int main() {
    // Test case 1: 2 relevant events, both lowercase
    std::vector<std::string> events1 = {"cw", "dog"};
    std::cout << howMuchCoffee(events1) << std::endl; // Output: 2

    // Test case 2: 2 relevant events, one uppercase
    std::vector<std::string> events2 = {"CW", "dog"};
    std::cout << howMuchCoffee(events2) << std::endl; // Output: 3

    // Test case 3: 3 relevant events, all uppercase
    std::vector<std::string> events3 = {"CW", "DOG", "MOVIE"};
    std::cout << howMuchCoffee(events3) << std::endl; // Output: You need extra sleep

    // Test case 4: Irrelevant events
    std::vector<std::string> events4 = {"party", "sleep", "work"};
    std::cout << howMuchCoffee(events4) << std::endl; // Output: 0

    // Test case 5: Mixed case, mixed events
    std::vector<std::string> events5 = {"cw", "DOG", "cat", "movie", "party"};
    std::cout << howMuchCoffee(events5) << std::endl; // Output: You need extra sleep

    return 0;
}
#include <vector>
#include <string>
#include <cctype>

using namespace std;

int howMuchCoffee(vector<string> events) {
    int coffeeCount = 0;
    for (const string& event : events) {
        // Check if the event is one of the relevant types (cw, dog, cat, movie)
        if (event == "cw" || event == "dog" || event == "cat" || event == "movie" ||
            event == "CW" || event == "DOG" || event == "CAT" || event == "MOVIE") {
            // Check if the event is uppercase (all characters uppercase)
            bool isUppercase = true;
            for (char c : event) {
                if (!isupper(c)) {
                    isUppercase = false;
                    break;
                }
            }
            // Add to coffee count based on case
            coffeeCount += isUppercase ? 2 : 1;
        }
        // Ignore other events
    }
    // Return result based on coffee count
    return coffeeCount > 3 ? -1 : coffeeCount;
}

// Wrapper function to handle the output requirement (return string if >3)
string coffeeNeeded(vector<string> events) {
    int result = howMuchCoffee(events);
    if (result == -1) {
        return "You need extra sleep";
    } else {
        return to_string(result);
    }
}
#include <iostream> // Required for input/output operations (std::cin, std::cout, std::endl)
#include <unordered_set> // Required for using std::unordered_set, which provides average O(1) time complexity for insertion and lookup
#include <string> // Not strictly necessary if reading integers directly, but often useful for line-based input
#include <sstream> // Not strictly necessary if reading integers directly, but useful for parsing space-separated integers from a line

// Helper function to read a set of integers from standard input.
// It first reads the count of elements, then reads that many integers
// and inserts them into an unordered_set.
std::unordered_set<int> read_set() {
    int n;
    std::cin >> n; // Read the number of elements in the set
    std::unordered_set<int> s; // Declare an unordered_set to store the roll numbers
    for (int i = 0; i < n; ++i) {
        int roll_number;
        std::cin >> roll_number; // Read each roll number
        s.insert(roll_number); // Insert the roll number into the set. Duplicates are automatically handled by sets.
    }
    return s; // Return the populated set
}

int main() {
    // Optimize C++ standard streams for faster input/output operations.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams.
    // std::cin.tie(NULL) prevents std::cout from being flushed before each std::cin operation.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    // Read the set of student roll numbers who subscribed to the English newspaper.
    // This set represents 'E' in the problem description (English subscribers).
    std::unordered_set<int> english_subscribers = read_set();

    // Read the set of student roll numbers who subscribed to the French newspaper.
    // This set represents 'F' in the problem description (French subscribers).
    std::unordered_set<int> french_subscribers = read_set();

    int only_english_count = 0; // Initialize a counter for students subscribed only to English.

    // Iterate through each student roll number in the 'english_subscribers' set.
    // This loop effectively checks each element of set E.
    for (int roll_number : english_subscribers) {
        // Check if the current 'roll_number' is NOT found in the 'french_subscribers' set.
        // The 'find()' method returns an iterator to the element if found,
        // or 'french_subscribers.end()' if the element is not present.
        // If a student is in 'english_subscribers' but not in 'french_subscribers',
        // it means they subscribed ONLY to the English newspaper.
        if (french_subscribers.find(roll_number) == french_subscribers.end()) {
            only_english_count++; // Increment the counter for students subscribed only to English.
        }
    }

    // Output the final count of students who subscribed only to the English newspaper.
    std::cout << only_english_count << std::endl;

    return 0; // Indicate successful program execution.
}

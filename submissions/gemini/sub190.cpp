#include <string>   // Required for std::string operations.
#include <vector>   // Required for std::vector container.
#include <algorithm> // Required for std::sort algorithm.

// Function to sort a vector of strings and then transform the first element.
// The problem asks to sort the input vector alphabetically (case-sensitive, ASCII order),
// take the first string, and then return it with "***" inserted between each of its letters.
std::string twoSort(std::vector<std::string> arr) {
    // Step 1: Sort the input vector of strings.
    // std::sort sorts elements in ascending order. For std::string, this means
    // lexicographical comparison based on character ASCII values, which directly
    // fulfills the requirement for case-sensitive alphabetical sorting.
    std::sort(arr.begin(), arr.end());

    // Step 2: Get the first string after sorting.
    // After sorting, the string that comes first alphabetically will be at index 0.
    // The problem implies that the input vector will not be empty, so arr[0] is safe.
    std::string first_sorted_string = arr[0];

    // Step 3: Build the result string by inserting "***" between each character.
    // Initialize an empty string to store the final transformed result.
    std::string result = "";

    // Iterate through each character of the first_sorted_string.
    // Using size_t for loop counter is good practice for string/vector indices.
    for (size_t i = 0; i < first_sorted_string.length(); ++i) {
        // Append the current character to the result string.
        result += first_sorted_string[i];

        // If it's not the last character in the string, append "***".
        // This condition ensures that "***" is only placed *between* characters,
        // not after the very last character.
        if (i < first_sorted_string.length() - 1) {
            result += "***";
        }
    }

    // Return the final transformed string.
    return result;
}

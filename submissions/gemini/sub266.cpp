#include <vector> // Required for std::vector
#include <string> // Required for std::string and std::to_string
#include <map>    // Required for std::map

// This function transforms an array of numbers into an array of objects.
// Each object's key is the number as a string, and its value is the corresponding character code as a string.
//
// @param arr: A constant reference to a vector of integers.
//             Each integer represents a character code (e.g., 97 for 'a').
//             The input array is guaranteed not to be empty.
//             All character codes are valid lowercase letters.
//
// @return: A vector of maps. Each map represents an "object" with a single key-value pair.
//          The key is the string representation of the number.
//          The value is the string representation of the character corresponding to the number's code.
std::vector<std::map<std::string, std::string>> solve(const std::vector<int>& arr) {
    // Initialize an empty vector to store the resulting maps (objects).
    // This vector will hold the final transformed data.
    std::vector<std::map<std::string, std::string>> result_objects;

    // Iterate through each integer 'num' in the input array 'arr'.
    // A range-based for loop is used for concise iteration.
    for (int num : arr) {
        // Convert the current integer 'num' into its string representation.
        // For example, if num is 97, key_str will be "97".
        // This string will serve as the key for the map.
        std::string key_str = std::to_string(num);

        // Convert the integer 'num' (which is a character code) into its corresponding character.
        // Then, convert that character into a string.
        // For example, if num is 97, static_cast<char>(97) yields 'a'.
        // std::string(1, 'a') then creates the string "a".
        // This string will serve as the value for the map.
        std::string value_str(1, static_cast<char>(num));

        // Create a new map to represent the current "object".
        // In C++, std::map is a suitable data structure for key-value pairs,
        // analogous to objects in other languages like JavaScript.
        std::map<std::string, std::string> current_object;

        // Insert the generated key-value pair into the 'current_object' map.
        // The key is the string representation of the number, and the value is the character string.
        current_object[key_str] = value_str;

        // Add the fully constructed 'current_object' map to the 'result_objects' vector.
        // This accumulates all the transformed objects.
        result_objects.push_back(current_object);
    }

    // Return the vector containing all the transformed objects.
    return result_objects;
}

#include <iostream>
#include <vector>
#include <string>
#include <map>

// For each number in the input array, create a map<string, string> where:
// - key: the number as a string
// - value: the corresponding character (from ASCII code) as a string
// Return a vector of these maps.
std::vector<std::map<std::string, std::string>> numberToCharObjectArray(const std::vector<int>& arr) {
    std::vector<std::map<std::string, std::string>> result;
    for (int num : arr) {
        std::map<std::string, std::string> obj;
        // Convert number to string for the key
        std::string key = std::to_string(num);
        // Convert number to char, then to string for the value
        std::string value(1, static_cast<char>(num));
        obj[key] = value;
        result.push_back(obj);
    }
    return result;
}

// Helper function to print the result in the required format
void printResult(const std::vector<std::map<std::string, std::string>>& result) {
    std::cout << "[";
    for (size_t i = 0; i < result.size(); ++i) {
        std::cout << "{";
        // Each map has only one key-value pair
        for (auto it = result[i].begin(); it != result[i].end(); ++it) {
            std::cout << "\"" << it->first << "\":\"" << it->second << "\"";
        }
        std::cout << "}";
        if (i != result.size() - 1) std::cout << ", ";
    }
    std::cout << "]" << std::endl;
}

int main() {
    // Example input
    std::vector<int> arr = {97, 98, 99, 100};
    // Call the function
    std::vector<std::map<std::string, std::string>> result = numberToCharObjectArray(arr);
    // Print the result
    printResult(result);
    return 0;
}
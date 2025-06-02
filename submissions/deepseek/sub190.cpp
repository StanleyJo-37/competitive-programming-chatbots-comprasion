#include <vector>
#include <string>
#include <algorithm>

std::string firstValue(std::vector<std::string> arr) {
    // Edge case: if the array is empty, return an empty string
    if (arr.empty()) {
        return "";
    }

    // Sort the vector of strings lexicographically (case-sensitive)
    std::sort(arr.begin(), arr.end());

    // Get the first string after sorting
    std::string first = arr[0];

    // Edge case: if the string is empty, return it as is
    if (first.empty()) {
        return "";
    }

    // Insert "***" between each character of the first string
    std::string result;
    for (size_t i = 0; i < first.size(); ++i) {
        result += first[i];
        if (i != first.size() - 1) {
            result += "***";
        }
    }

    return result;
}
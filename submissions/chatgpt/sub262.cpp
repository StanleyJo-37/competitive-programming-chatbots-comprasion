#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

// Function to check if two arrays have at least one identical element
bool haveCommonElement(const vector<int>& m, const vector<int>& n) {
    // If either array is empty, return false (no common elements possible)
    if (m.empty() || n.empty()) return false;

    // Use an unordered_set for O(1) average lookup time
    unordered_set<int> elements;

    // Insert all elements from the first array into the set
    for (int num : m) {
        elements.insert(num);
    }

    // Check if any element in the second array exists in the set
    for (int num : n) {
        if (elements.count(num)) {
            return true; // Found a common element
        }
    }

    // No common elements found
    return false;
}

// Example usage and test cases
int main() {
    // Test case 1: Common element exists
    vector<int> m1 = {1, 2, 3, 4};
    vector<int> n1 = {5, 6, 3, 8};
    cout << (haveCommonElement(m1, n1) ? "true" : "false") << endl; // Output: true

    // Test case 2: No common element
    vector<int> m2 = {10, 20, 30};
    vector<int> n2 = {40, 50, 60};
    cout << (haveCommonElement(m2, n2) ? "true" : "false") << endl; // Output: false

    // Test case 3: One array is empty
    vector<int> m3 = {};
    vector<int> n3 = {1, 2, 3};
    cout << (haveCommonElement(m3, n3) ? "true" : "false") << endl; // Output: false

    // Test case 4: Both arrays are empty
    vector<int> m4 = {};
    vector<int> n4 = {};
    cout << (haveCommonElement(m4, n4) ? "true" : "false") << endl; // Output: false

    // Test case 5: Large numbers and negative numbers
    vector<int> m5 = {INT_MIN, 0, INT_MAX};
    vector<int> n5 = {-1, INT_MAX};
    cout << (haveCommonElement(m5, n5) ? "true" : "false") << endl; // Output: true

    return 0;
}
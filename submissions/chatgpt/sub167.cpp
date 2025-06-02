#include <vector>
#include <set>
using namespace std;

// Function to replace every element with the least greater element to its right
vector<int> arrayManip(const vector<int>& arr) {
    int n = arr.size();
    vector<int> result(n); // Result array to store the answer
    set<int> bst; // Set to maintain elements to the right (acts as BST)

    // Traverse the array from right to left
    for (int i = n - 1; i >= 0; --i) {
        // Find the least greater element than arr[i] in the set
        auto it = bst.upper_bound(arr[i]);
        if (it == bst.end()) {
            // No greater element exists to the right
            result[i] = -1;
        } else {
            // The least greater element found
            result[i] = *it;
        }
        // Insert current element into the set for future queries
        bst.insert(arr[i]);
    }
    return result;
}
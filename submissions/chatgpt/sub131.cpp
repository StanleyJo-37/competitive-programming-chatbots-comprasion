#include <iostream>
#include <vector>
using namespace std;

// Function to perform element-wise binary OR on two arrays.
// If arrays are of unequal length, unmatched elements are OR'ed with 'def' (default 0).
vector<int> or_arrays(const vector<int>& arr1, const vector<int>& arr2, int def = 0) {
    // Determine the maximum length of the two arrays.
    size_t n = max(arr1.size(), arr2.size());
    vector<int> result;
    result.reserve(n); // Reserve space for efficiency.

    for (size_t i = 0; i < n; ++i) {
        // Get value from arr1 if within bounds, else use 'def'.
        int a = (i < arr1.size()) ? arr1[i] : def;
        // Get value from arr2 if within bounds, else use 'def'.
        int b = (i < arr2.size()) ? arr2[i] : def;
        // Perform bitwise OR and add to result.
        result.push_back(a | b);
    }
    return result;
}

// Helper function to print a vector in the required format.
void print_vector(const vector<int>& v) {
    cout << "[";
    for (size_t i = 0; i < v.size(); ++i) {
        if (i > 0) cout << ",";
        cout << v[i];
    }
    cout << "]" << endl;
}

int main() {
    // Test cases as per the problem statement.
    print_vector(or_arrays({1,2,3}, {1,2,3}));      // [1,2,3]
    print_vector(or_arrays({1,2,3}, {4,5,6}));      // [5,7,7]
    print_vector(or_arrays({1,2,3}, {1,2}));        // [1,2,3]
    print_vector(or_arrays({1,2}, {1,2,3}));        // [1,2,3]
    print_vector(or_arrays({1,2,3}, {1,2,3}, 3));   // [1,2,3]
    return 0;
}
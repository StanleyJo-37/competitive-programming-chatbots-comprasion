#include <iostream>
#include <vector>
using namespace std;

// Function to add two polynomials represented as vectors
vector<int> poly_add(const vector<int>& p1, const vector<int>& p2) {
    // Determine the maximum length of the two polynomials
    size_t n = max(p1.size(), p2.size());
    // Initialize the result vector with zeros of size n
    vector<int> result(n, 0);
    // Add corresponding coefficients from both polynomials
    for (size_t i = 0; i < n; ++i) {
        // If index i is within bounds of p1, add its value
        if (i < p1.size()) result[i] += p1[i];
        // If index i is within bounds of p2, add its value
        if (i < p2.size()) result[i] += p2[i];
    }
    // Remove trailing zeros (if any) to match expected output format
    while (result.size() > 1 && result.back() == 0) {
        result.pop_back();
    }
    return result;
}

// Helper function to print a vector (for demonstration/testing)
void print_vector(const vector<int>& v) {
    cout << "[";
    for (size_t i = 0; i < v.size(); ++i) {
        if (i > 0) cout << ", ";
        cout << v[i];
    }
    cout << "]" << endl;
}

// Main function for testing
int main() {
    // Test case 1: [1, 2] + [1] = [2, 2]
    vector<int> p1 = {1, 2};
    vector<int> p2 = {1};
    vector<int> res = poly_add(p1, p2);
    print_vector(res); // Expected: [2, 2]

    // Test case 2: [0, 1, 2] + [1, 2, 3] = [1, 3, 5]
    vector<int> p3 = {0, 1, 2};
    vector<int> p4 = {1, 2, 3};
    res = poly_add(p3, p4);
    print_vector(res); // Expected: [1, 3, 5]

    // Test case 3: [1, 2, 3] + [4, 5] = [5, 7, 3]
    vector<int> p5 = {1, 2, 3};
    vector<int> p6 = {4, 5};
    res = poly_add(p5, p6);
    print_vector(res); // Expected: [5, 7, 3]

    // Test case 4: [0, 0, 0] + [0, 0, 0] = [0]
    vector<int> p7 = {0, 0, 0};
    vector<int> p8 = {0, 0, 0};
    res = poly_add(p7, p8);
    print_vector(res); // Expected: [0]

    // Test case 5: [1] + [0, 0, 2] = [1, 0, 2]
    vector<int> p9 = {1};
    vector<int> p10 = {0, 0, 2};
    res = poly_add(p9, p10);
    print_vector(res); // Expected: [1, 0, 2]

    return 0;
}
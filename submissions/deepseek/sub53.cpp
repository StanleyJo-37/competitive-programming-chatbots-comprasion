#include <vector>
#include <iostream>

using namespace std;

int custom_fib(vector<int> signature, vector<int> indexes, int n) {
    // If n is within the initial signature, return the element directly
    if (n < signature.size()) {
        return signature[n];
    }

    // Extend the sequence until we reach the nth element
    while (signature.size() <= n) {
        int next_val = 0;
        // Sum the elements at the specified indexes from the last 'length' elements
        for (int idx : indexes) {
            // The index is relative to the last 'length' elements (signature.size() is the current length)
            next_val += signature[signature.size() - signature.size() + idx];
        }
        signature.push_back(next_val);
    }

    return signature[n];
}

// Note: The problem examples are in Python, but the logic is the same in C++.
// The function can be tested with the same inputs as provided in the examples.
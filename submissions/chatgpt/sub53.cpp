#include <iostream>
#include <vector>
using namespace std;

// Function to compute the custom Fibonacci-like sequence
int custom_fib(const vector<int>& signature, const vector<int>& idx, int n) {
    int length = signature.size();
    // If n is within the signature, return it directly
    if (n < length) return signature[n];
    // Initialize the sequence with the signature
    vector<int> seq = signature;
    // Generate sequence up to the nth element
    for (int i = length; i <= n; ++i) {
        int next = 0;
        // For each index in idx, sum the corresponding element from the last 'length' elements
        for (int j = 0; j < idx.size(); ++j) {
            // The last 'length' elements are from seq[i-length] to seq[i-1]
            // idx[j] is the index in this window
            next += seq[i - length + idx[j]];
        }
        seq.push_back(next);
    }
    return seq[n];
}

// Driver code for testing
int main() {
    // Test cases as per the problem statement
    cout << custom_fib({1,1}, {0,1}, 2) << endl; // Output: 2
    cout << custom_fib({1,1}, {0,1}, 3) << endl; // Output: 3
    cout << custom_fib({1,1}, {0,1}, 4) << endl; // Output: 5
    cout << custom_fib({3,5,2}, {0,1,2}, 4) << endl; // Output: 17
    cout << custom_fib({7,3,4,1}, {1,1}, 6) << endl; // Output: 2
    return 0;
}
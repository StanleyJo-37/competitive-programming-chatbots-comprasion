#include <iostream>
#include <unordered_set>
#include <vector>
using namespace std;

// Function to count unique odd values in the pentanacci-like sequence up to n-th term
int count_odd_pentaFib(int n) {
    // Handle edge case where n < 1
    if (n < 1) return 0;

    // Vector to store sequence values up to n
    vector<long long> f(n + 1, 0);

    // Set to store unique odd values
    unordered_set<long long> odd_values;

    // Initial values as per the problem statement
    f[0] = 0;
    if (n >= 1) f[1] = 1;
    if (n >= 2) f[2] = 1;
    if (n >= 3) f[3] = 2;
    if (n >= 4) f[4] = 4;

    // Insert initial odd values (1) only once
    if (n >= 1) odd_values.insert(1);
    if (n >= 2) odd_values.insert(1);

    // Compute the sequence and collect unique odd values
    for (int i = 5; i <= n; ++i) {
        // Recurrence relation
        f[i] = f[i-1] + f[i-2] + f[i-3] + f[i-4] + f[i-5];
        // If value is odd, insert into set
        if (f[i] % 2 != 0) {
            odd_values.insert(f[i]);
        }
    }

    // Return the number of unique odd values
    return odd_values.size();
}

int main() {
    // Example usage and test cases
    cout << count_odd_pentaFib(5) << endl;   // Output: 1
    cout << count_odd_pentaFib(10) << endl;  // Output: 3
    cout << count_odd_pentaFib(15) << endl;  // Output: 5

    // For custom input
    // int n;
    // cin >> n;
    // cout << count_odd_pentaFib(n) << endl;

    return 0;
}
#include <iostream>
#include <vector>
using namespace std;

// Memoization vector to store computed values of Q(n)
vector<int> memo;

// Recursive function to compute Hofstadter Q sequence
int hofstadterQ(int n) {
    // If n is less than or equal to 0, the sequence is not defined
    if (n <= 0) return 0;
    // Base cases: Q(1) = 1, Q(2) = 1
    if (n == 1 || n == 2) return 1;
    // If already computed, return the stored value
    if (memo[n] != -1) return memo[n];
    // Recursively compute Q(n) = Q(n - Q(n-1)) + Q(n - Q(n-2))
    memo[n] = hofstadterQ(n - hofstadterQ(n - 1)) + hofstadterQ(n - hofstadterQ(n - 2));
    return memo[n];
}

int main() {
    int n;
    // Read input n
    cin >> n;
    // Resize memoization vector to handle up to n, initialize with -1
    memo.assign(n + 2, -1);
    // Output the nth Hofstadter Q number
    cout << hofstadterQ(n) << endl;
    return 0;
}
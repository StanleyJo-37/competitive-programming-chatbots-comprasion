#include <vector> // Required for std::vector to store computed Q values.

// Function to compute the Hofstadter Q sequence value for a given n.
// The Hofstadter Q sequence is defined recursively:
// Q(1) = 1
// Q(2) = 1
// Q(n) = Q(n - Q(n-1)) + Q(n - Q(n-2)) for n > 2
//
// This implementation uses dynamic programming (specifically, an iterative bottom-up approach)
// to store and reuse previously computed Q values. This avoids redundant calculations
// that would occur with a naive recursive approach, significantly improving performance
// and preventing potential stack overflow for larger 'n'.
int hofstadterQ(int n) {
    // The problem states 'n' is always positive.
    // Handle the base cases for the sequence.
    if (n == 1) {
        return 1; // Q(1) is defined as 1.
    }
    if (n == 2) {
        return 1; // Q(2) is defined as 1.
    }

    // Create a vector to store the computed Q values.
    // q_values[i] will store the value of Q(i).
    // We use a size of 'n + 1' to allow for 1-based indexing,
    // making q_values[k] directly correspond to Q(k).
    std::vector<int> q_values(n + 1);

    // Initialize the base cases in our memoization table.
    q_values[1] = 1;
    q_values[2] = 1;

    // Iterate from i = 3 up to n to compute Q(i) using the recursive definition.
    // At each step 'i', the values Q(i-1) and Q(i-2) (and any other required
    // smaller Q values) will have already been computed and stored in 'q_values'.
    for (int i = 3; i <= n; ++i) {
        // Apply the Hofstadter Q definition: Q(n) = Q(n - Q(n-1)) + Q(n - Q(n-2)).
        // The indices (i - q_values[i-1]) and (i - q_values[i-2]) are guaranteed
        // to be valid (i.e., >= 1) because for the Hofstadter Q sequence, it's known
        // that Q(k) <= k for all k >= 1.
        // Thus, i - Q(i-1) >= i - (i-1) = 1, and i - Q(i-2) >= i - (i-2) = 2.
        q_values[i] = q_values[i - q_values[i-1]] + q_values[i - q_values[i-2]];
    }

    // After the loop completes, q_values[n] will contain the desired Q(n) value.
    return q_values[n];
}
#include <iostream>
#include <string>
#include <vector>
#include <algorithm> // Required for std::min

// Function to solve a single test case
void solve() {
    std::string s;
    std::cin >> s; // Read the balanced parenthesis sequence
    int n = s.length(); // Get the length of the sequence

    // next_closing_paren[k] will store the index of the first ')' character
    // found at or after index k. If no ')' is found from index k to n-1,
    // it will store 'n' (which acts as an indicator for "not found" or "infinity").
    std::vector<int> next_closing_paren(n);

    // Populate next_closing_paren array by iterating backwards from the end of the string.
    // This allows us to efficiently find the next ')' for any given index.
    if (s[n - 1] == ')') {
        next_closing_paren[n - 1] = n - 1; // If the last character is ')', it's the first ')' at or after n-1.
    } else {
        next_closing_paren[n - 1] = n; // Otherwise, no ')' at or after n-1.
    }

    for (int k = n - 2; k >= 0; --k) {
        if (s[k] == ')') {
            next_closing_paren[k] = k; // If s[k] is ')', then k is the first ')' at or after k.
        } else {
            // If s[k] is '(', then the first ')' at or after k is the same as
            // the first ')' at or after k+1.
            next_closing_paren[k] = next_closing_paren[k + 1];
        }
    }

    // Initialize min_swaps with a value larger than any possible answer.
    // The maximum possible swaps would be N-1 (e.g., moving the last ')' to the first position).
    int min_swaps = n; 
    // current_balance tracks the balance of the prefix S[0...i-1].
    // A balanced sequence always has non-negative prefix sums.
    // To make it unbalanced, we need to create a prefix with a negative balance.
    // The simplest way to do this with minimum swaps is to achieve a balance of -1.
    // This happens if we have a balanced prefix S[0...k] (balance 0), and then
    // we swap S[k+1] (which must be '(') with some S[j] (which is ')', j > k+1).
    // The new prefix S[0...k] + S[j] would have balance 0 + (-1) = -1.
    int current_balance = 0; 

    // Iterate through the string to find potential swap locations.
    for (int i = 0; i < n; ++i) {
        // Check if the current position 'i' is a potential starting point for a swap.
        // This condition means that the prefix S[0...i-1] is balanced (current_balance == 0)
        // and the character at S[i] is an opening parenthesis '('.
        // This 'i' marks the beginning of a new balanced segment.
        if (current_balance == 0 && s[i] == '(') {
            // We need to find the closest ')' to the right of S[i] (i.e., at an index j > i).
            // We use the precomputed next_closing_paren array for this.
            // next_closing_paren[i+1] gives us the index of the first ')' starting from i+1.
            int j = next_closing_paren[i + 1];
            
            // If a ')' was found (j < n), calculate the number of swaps needed.
            // The number of adjacent swaps required to move an element from index j to index i (j > i)
            // is simply j - i. This operation effectively swaps S[i] and S[j] while shifting
            // intermediate characters.
            if (j < n) {
                min_swaps = std::min(min_swaps, j - i);
            }
        }

        // Update the current balance based on the character at S[i].
        if (s[i] == '(') {
            current_balance++;
        } else { // s[i] == ')'
            current_balance--;
        }
    }

    // Output the minimum number of swaps found.
    std::cout << min_swaps << std::endl;
}

int main() {
    // Optimize C++ standard streams for faster input/output operations.
    // This is common practice in competitive programming.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t; // Read the number of test cases
    while (t--) {
        solve(); // Solve each test case
    }

    return 0;
}

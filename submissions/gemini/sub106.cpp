#include <iostream> // Required for input/output operations (cin, cout)
#include <vector>   // Required for std::vector
#include <string>   // Required for std::string
#include <algorithm> // Required for std::nth_element and std::abs

// Function to solve a single test case
void solve() {
    int n; // Declare integer n for the length of the string
    std::cin >> n; // Read n
    std::string s; // Declare string s for the level description
    std::cin >> s; // Read the string s

    std::vector<int> sheep_indices; // Create a vector to store the 0-indexed positions of sheep
    for (int i = 0; i < n; ++i) { // Iterate through the string
        if (s[i] == '*') { // If a sheep is found
            sheep_indices.push_back(i); // Add its index to the vector
        }
    }

    int k = sheep_indices.size(); // Get the total number of sheep

    if (k == 0) { // If there are no sheep, no moves are needed
        std::cout << 0 << std::endl; // Output 0
        return; // End this test case
    }

    // The problem asks to arrange k sheep into a contiguous block.
    // Let the initial positions of the sheep be p_0, p_1, ..., p_{k-1}.
    // We want to move them to j_0, j_0+1, ..., j_0+k-1 for some starting position j_0.
    // The total number of moves is sum_{m=0}^{k-1} |p_m - (j_0 + m)|.
    // This sum can be rewritten as sum_{m=0}^{k-1} |(p_m - m) - j_0|.
    // Let q_m = p_m - m. We need to find j_0 that minimizes sum_{m=0}^{k-1} |q_m - j_0|.
    // This is a classic problem where the optimal j_0 is the median of the q_m values.
    // The "empty square" constraint does not affect the minimum number of moves,
    // as long as the relative order of sheep is preserved, which is implicitly assumed
    // by matching the m-th sheep to the m-th position in the target block.

    std::vector<int> q_values(k); // Create a vector to store q_m values
    for (int m = 0; m < k; ++m) { // Calculate q_m for each sheep
        q_values[m] = sheep_indices[m] - m;
    }

    // Find the median of q_values.
    // std::nth_element rearranges elements such that the element at the n-th position
    // (specified by the second iterator) is the element that would be in that position
    // in a sorted sequence. Elements before it are less than or equal to it, and
    // elements after it are greater than or equal to it.
    // For the median, we want the element at index k/2 (0-indexed).
    std::nth_element(q_values.begin(), q_values.begin() + k / 2, q_values.end());
    int median_q = q_values[k / 2]; // The median value

    long long total_moves = 0; // Use long long for total_moves as it can exceed int limits (up to 2 * 10^12)

    // Calculate the total moves based on the chosen median j_0 (which is median_q)
    for (int m = 0; m < k; ++m) {
        // The target position for the m-th sheep (originally at sheep_indices[m]) is median_q + m.
        // Calculate the absolute difference and add to total_moves.
        // Cast to long long before subtraction to ensure the absolute difference is calculated
        // using long long arithmetic, preventing potential overflow if intermediate values are large.
        total_moves += std::abs(static_cast<long long>(sheep_indices[m]) - (static_cast<long long>(median_q) + m));
    }

    std::cout << total_moves << std::endl; // Output the minimum number of moves
}

int main() {
    // Optimize C++ standard streams for faster input/output.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams,
    // which can significantly speed up I/O operations.
    // std::cin.tie(NULL) prevents std::cout from flushing before std::cin reads input,
    // further improving performance for interactive problems or those with mixed I/O.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t; // Declare integer t for the number of test cases
    std::cin >> t; // Read t
    while (t--) { // Loop t times
        solve(); // Call the solve function for each test case
    }

    return 0; // Indicate successful execution
}

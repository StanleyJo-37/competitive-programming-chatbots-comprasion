#include <iostream> // Required for input/output operations (cin, cout)
#include <vector>   // Required for using std::vector
#include <string>   // Required for using std::string
#include <algorithm> // Required for std::min
#include <limits>   // Required for std::numeric_limits (for LLONG_MAX)

void solve() {
    int n, p, k; // Declare integers n, p, k for number of cells, first platform cell, and period
    std::cin >> n >> p >> k; // Read n, p, k from input

    std::string a; // Declare string a for the level pattern
    std::cin >> a; // Read the level pattern string

    long long x, y; // Declare long long x, y for costs (can be large)
    std::cin >> x >> y; // Read x and y from input

    // dp[j] will store the minimum cost to add platforms at cells j, j+k, j+2k, ...
    // up to n-1, assuming these are the required cells.
    // We use long long for dp values to prevent potential overflow, as costs can sum up.
    std::vector<long long> dp(n); 

    // Iterate from the end of the level backwards to fill the dp array.
    // This is a suffix DP approach.
    // j represents the 0-based index in the original string 'a'.
    for (int j = n - 1; j >= 0; --j) {
        // Cost for the current cell j:
        // If a platform is missing (a[j] == '0'), we need to add one, costing x.
        // If a platform is present (a[j] == '1'), cost is 0.
        dp[j] = (a[j] == '0' ? x : 0);

        // If j+k is within the bounds of the level (i.e., j+k < n),
        // add the cost of making platforms from j+k onwards.
        // This is the recursive step of the DP: cost(j) = cost_at_j + cost(j+k).
        if (j + k < n) {
            dp[j] += dp[j + k];
        }
    }

    // Initialize minimum total cost to a very large value.
    // We will update this with the minimum cost found across all possible scenarios.
    long long min_total_cost = std::numeric_limits<long long>::max();

    // Iterate through all possible numbers of cells 'i' to remove from the beginning.
    // 'i' can range from 0 (no cells removed) up to n-p.
    // We cannot remove more than n-p cells because the problem states that the number of cells
    // cannot be reduced to less than 'p'. If 'i' cells are removed, the new length is n-i.
    // So, n-i >= p implies i <= n-p.
    for (int i = 0; i <= n - p; ++i) {
        // Calculate the cost for the current scenario where 'i' cells are removed:
        // 1. Cost of removing 'i' cells: i * y.
        // 2. Cost of adding platforms for the required sequence.
        //    If 'i' cells are removed, the original cell 'p+i' (1-based index) becomes the new cell 'p'.
        //    In 0-based indexing, this corresponds to original index (p+i)-1, which is p-1+i.
        //    The cost to add platforms for the sequence starting at original index (p-1)+i
        //    (i.e., (p-1+i), (p-1+i)+k, (p-1+i)+2k, ...) is precomputed in dp[p-1+i].
        long long current_cost = (long long)i * y + dp[p - 1 + i];

        // Update the minimum total cost found so far.
        min_total_cost = std::min(min_total_cost, current_cost);
    }

    // Output the minimum total cost.
    std::cout << min_total_cost << std::endl;
}

int main() {
    // Optimize C++ standard streams for faster input/output.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams.
    // std::cin.tie(NULL) prevents std::cout from flushing before std::cin reads input.
    // These are common competitive programming optimizations.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t; // Declare integer t for the number of test cases
    std::cin >> t; // Read the number of test cases

    // Loop through each test case
    while (t--) {
        solve(); // Call the solve function for each test case
    }

    return 0; // Indicate successful execution
}

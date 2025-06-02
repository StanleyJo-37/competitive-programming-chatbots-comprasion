#include <iostream> // Required for input/output operations (cin, cout)
#include <vector>   // Required for using std::vector
#include <numeric>  // Required for std::accumulate (though not strictly needed as sums are computed iteratively)
#include <algorithm> // Required for std::max

// Function to solve a single test case
void solve() {
    int N; // Declare N to store the number of days
    std::cin >> N; // Read N from standard input

    // Declare vector A to store profits if the shop is in Chefland on day i
    // Using long long to prevent overflow, as sum of profits can exceed int max.
    std::vector<long long> A(N); 
    for (int i = 0; i < N; ++i) {
        std::cin >> A[i]; // Read elements of A
    }

    // Declare vector B to store profits if the shop is in Chefabad on day i
    // Using long long for consistency and potential future use, though individual B[i] fit in int.
    std::vector<long long> B(N); 
    for (int i = 0; i < N; ++i) {
        std::cin >> B[i]; // Read elements of B
    }

    // Calculate suffix sums for array B.
    // suffix_B[i] will store the sum of B[i] + B[i+1] + ... + B[N-1].
    // We need suffix_B[k+1] for k from 0 to N-1.
    // This means we need suffix_B up to index N (for k=N-1, we need suffix_B[N]).
    // suffix_B[N] will represent an empty sum, which is 0.
    std::vector<long long> suffix_B(N + 1, 0); 
    for (int i = N - 1; i >= 0; --i) {
        // The sum from B[i] to B[N-1] is B[i] plus the sum from B[i+1] to B[N-1].
        suffix_B[i] = B[i] + suffix_B[i + 1];
    }

    // Initialize max_profit with the first possible scenario:
    // Chef moves the shop before day 1. In this case, the shop is in Chefabad for all N days.
    // The total profit is the sum of all B[i] from day 0 to N-1, which is stored in suffix_B[0].
    long long max_profit = suffix_B[0];

    // current_prefix_A_sum will store the sum of A[0] + A[1] + ... + A[k].
    long long current_prefix_A_sum = 0; 

    // Iterate through all other possible move scenarios.
    // 'k' represents the last day (0-indexed) the shop is in Chefland.
    // The shop moves after day 'k' and before day 'k+1'.
    // So, for days 0 to 'k', the shop is in Chefland (profit A[i]).
    // For days 'k+1' to N-1, the shop is in Chefabad (profit B[i]).
    for (int k = 0; k < N; ++k) {
        current_prefix_A_sum += A[k]; // Add profit for day k in Chefland to the prefix sum

        // Calculate the total profit for this specific move strategy:
        // (sum of A from day 0 to k) + (sum of B from day k+1 to N-1)
        // The sum of B from day k+1 to N-1 is efficiently retrieved from suffix_B[k+1].
        long long current_profit = current_prefix_A_sum + suffix_B[k + 1];
        
        // Update max_profit if the current strategy yields a higher profit.
        max_profit = std::max(max_profit, current_profit);
    }

    // Print the maximum profit found across all scenarios.
    std::cout << max_profit << std::endl;
}

int main() {
    // Optimize C++ standard streams for competitive programming.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams,
    // which can speed up I/O operations significantly.
    std::ios_base::sync_with_stdio(false);
    // std::cin.tie(NULL) prevents std::cout from flushing before std::cin reads input,
    // further speeding up I/O.
    std::cin.tie(NULL);

    int T; // Declare T to store the number of test cases
    std::cin >> T; // Read the number of test cases

    while (T--) { // Loop T times, calling solve() for each test case
        solve(); 
    }

    return 0; // Indicate successful program execution
}
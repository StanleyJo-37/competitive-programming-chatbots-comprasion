#include <iostream> // Required for input/output operations (cin, cout)
#include <vector>   // Required for using std::vector to store the walks schedule

int main() {
    // Optimize C++ standard streams for competitive programming.
    // This unties cin/cout from C standard streams and disables synchronization
    // with C stdio, potentially speeding up I/O operations.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n; // Declare integer n for the number of days
    int k; // Declare integer k for the minimum walks required for any two consecutive days

    // Read n and k from standard input
    std::cin >> n >> k;

    // Declare a vector 'b' of size n to store the number of walks for each day.
    // Initialize 'b' with the planned walks 'a_i'.
    // We will modify 'b' in place to find the optimal schedule.
    std::vector<int> b(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> b[i]; // Read a_i into b[i]
    }

    long long additional_walks = 0; // Use long long to store the total additional walks.
                                    // Although int might be sufficient given constraints (N*K max 250,000),
                                    // long long is safer for sums in competitive programming.

    // Iterate through the days from the first day up to the second-to-last day.
    // We check the condition for pairs (day i, day i+1).
    // The loop goes from i=0 to n-2 to cover all pairs (b[0], b[1]), (b[1], b[2]), ..., (b[n-2], b[n-1]).
    // The problem states that on the day before the first day (b_0) and after the n-th day (b_{n+1}),
    // Polycarp walks k times. These boundary conditions (k + b[0] >= k and b[n-1] + k >= k)
    // are always satisfied if b[i] >= 0, so they don't force any additional walks.
    // Thus, we only need to consider the internal pairs.
    for (int i = 0; i < n - 1; ++i) {
        // Calculate the sum of walks for the current consecutive days.
        int current_sum = b[i] + b[i+1];

        // If the current sum is less than the required minimum 'k',
        // we need to add more walks.
        if (current_sum < k) {
            int needed = k - current_sum; // Calculate how many more walks are needed.
            b[i+1] += needed;             // Add the needed walks to the *next* day (b[i+1]).
                                          // This is the greedy choice: always add to the later day
                                          // to potentially help satisfy future conditions (b[i+1] + b[i+2] >= k).
                                          // Adding to b[i] would be suboptimal as b[i] is already fixed
                                          // based on previous day's constraints and a[i], and increasing it
                                          // would not help future pairs.
            additional_walks += needed;   // Accumulate the total additional walks.
        }
    }

    // Print the total minimum number of additional walks.
    std::cout << additional_walks << std::endl;

    // Print the resulting schedule (b_1, b_2, ..., b_n).
    for (int i = 0; i < n; ++i) {
        std::cout << b[i] << (i == n - 1 ? "" : " "); // Print each element, separated by spaces.
                                                      // No trailing space after the last element.
    }
    std::cout << std::endl; // Print a newline at the end of the output.

    return 0; // Indicate successful execution.
}

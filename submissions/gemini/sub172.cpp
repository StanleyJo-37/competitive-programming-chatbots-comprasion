#include <iostream> // Required for input/output operations (cin, cout)
#include <vector>   // Required for using std::vector to store prefix sums
#include <numeric>  // Required for std::accumulate (though not strictly necessary if summing manually)
#include <algorithm> // Required for std::min and std::max

int main() {
    // Optimize C++ standard streams for competitive programming.
    // This unties cin/cout from the C standard streams and disables synchronization
    // with C's stdio, which can significantly speed up I/O operations.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int T; // Declare variable T for the number of test cases
    std::cin >> T; // Read the number of test cases

    while (T--) { // Loop T times for each test case
        int N; // Declare variable N for the number of tasks
        std::cin >> N; // Read the number of tasks

        // Create a vector to store prefix sums.
        // prefix_sum[i] will store the sum of A[0]...A[i-1].
        // The size is N+1 because prefix_sum[0] will be 0 (sum of no elements),
        // and prefix_sum[N] will store the sum of all N tasks.
        std::vector<long long> prefix_sum(N + 1, 0); 

        // Read task execution times and compute prefix sums.
        for (int i = 1; i <= N; ++i) {
            long long A_i; // Declare variable for current task's execution time
            std::cin >> A_i; // Read the execution time for the i-th task
            // Calculate the prefix sum: current prefix_sum is previous prefix_sum + current task time.
            prefix_sum[i] = prefix_sum[i - 1] + A_i;
        }

        // Initialize min_total_time with a very large value or the total sum.
        // The total sum (prefix_sum[N]) is a valid initial upper bound,
        // as it represents the time if one processor takes all tasks and the other takes none.
        long long min_total_time = prefix_sum[N]; 

        // Iterate through all possible split points.
        // 'k' represents the number of tasks assigned to the first processor.
        // k can range from 0 (first processor gets no tasks) to N (first processor gets all tasks).
        for (int k = 0; k <= N; ++k) {
            // Time taken by the first processor: sum of tasks from 1 to k.
            // This is directly given by prefix_sum[k].
            long long time_P1 = prefix_sum[k];

            // Time taken by the second processor: sum of tasks from k+1 to N.
            // This can be calculated as total sum (prefix_sum[N]) minus sum of tasks 1 to k (prefix_sum[k]).
            long long time_P2 = prefix_sum[N] - prefix_sum[k];

            // The total time for this specific split is the maximum of the times taken by the two processors,
            // because both processors work simultaneously, and the overall execution finishes when the slower one is done.
            long long current_total_time = std::max(time_P1, time_P2);

            // Update the minimum total time found so far.
            min_total_time = std::min(min_total_time, current_total_time);
        }

        // Output the minimum time required to execute all tasks.
        std::cout << min_total_time << "\n";
    }

    return 0; // Indicate successful execution
}

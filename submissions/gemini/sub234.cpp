#include <iostream> // Required for input and output operations (cin, cout)
#include <vector>   // Required for using std::vector to store dormitory room counts

int main() {
    // Optimize C++ standard streams for competitive programming.
    // This unties cin from cout and disables synchronization with C's stdio,
    // which can significantly speed up I/O operations.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n; // Number of dormitories
    int m; // Number of letters (queries)
    std::cin >> n >> m; // Read n and m

    // Create a vector to store the number of rooms in each dormitory.
    // Use long long because a_i (number of rooms in a dormitory) can be up to 10^10.
    std::vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i]; // Read the number of rooms for each dormitory
    }

    // Initialize variables for the two-pointer approach.
    // 'current_dorm_idx' is 0-indexed, representing the current dormitory being considered.
    // It starts at 0, corresponding to the first dormitory.
    int current_dorm_idx = 0;
    // 'current_prefix_sum' stores the cumulative sum of rooms up to and including
    // the 'current_dorm_idx'-th dormitory.
    // It starts with the rooms of the first dormitory (a[0]).
    // This variable will always hold S_k where k = current_dorm_idx + 1.
    long long current_prefix_sum = a[0];

    // Process each letter (query).
    // The problem states that b_j (global room numbers) are given in increasing order.
    // This property is crucial for the efficiency of the two-pointer approach,
    // as 'current_dorm_idx' only moves forward.
    for (int j = 0; j < m; ++j) {
        long long b_j; // The global room number for the current letter
        std::cin >> b_j; // Read the global room number

        // While the global room number b_j is greater than the total rooms
        // accumulated up to the current dormitory ('current_prefix_sum'),
        // it means b_j must be in a subsequent dormitory.
        // We advance 'current_dorm_idx' and update 'current_prefix_sum'
        // until b_j falls within the range of the current dormitory.
        while (b_j > current_prefix_sum) {
            current_dorm_idx++; // Move to the next dormitory (increment 0-indexed index)
            // Add the rooms of the newly entered dormitory to the prefix sum.
            // 'a[current_dorm_idx]' gives the rooms in the (current_dorm_idx + 1)-th dormitory.
            current_prefix_sum += a[current_dorm_idx];
        }

        // At this point, 'b_j' is less than or equal to 'current_prefix_sum'.
        // This means 'b_j' belongs to the dormitory identified by 'current_dorm_idx'.

        // To find the room number within this dormitory, we need to subtract
        // the total number of rooms in all preceding dormitories.
        // The total rooms up to the (current_dorm_idx - 1)-th dormitory is
        // 'current_prefix_sum - a[current_dorm_idx]'.
        long long prev_prefix_sum = current_prefix_sum - a[current_dorm_idx];
        
        // The room number within the current dormitory is b_j minus the
        // total rooms before this dormitory.
        // For example, if b_j is 12 and prev_prefix_sum is 10, the room is 12-10=2.
        long long room_in_dorm = b_j - prev_prefix_sum;

        // Print the 1-indexed dormitory number and the room number within it.
        // 'current_dorm_idx' is 0-indexed, so add 1 for output.
        std::cout << current_dorm_idx + 1 << " " << room_in_dorm << "\n";
    }

    return 0; // Indicate successful execution
}

#include <iostream> // Required for input/output operations (std::cin, std::cout)
#include <vector>   // Required for std::vector to store results and cyclic elements
#include <deque>    // Required for std::deque, the main data structure
#include <algorithm> // Required for std::max_element (though not strictly used in final code, max_val is found manually)

int main() {
    // Optimize C++ standard streams for competitive programming.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard I/O,
    // preventing potential synchronization overhead.
    // std::cin.tie(NULL) unties std::cin from std::cout, meaning std::cin will not flush std::cout
    // before reading input, which can speed up input operations.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n; // Number of elements initially in the deque
    int q; // Number of queries
    std::cin >> n >> q;

    std::deque<long long> d; // The deque data structure
    long long max_val = -1; // Variable to store the maximum element found in the deque.
                            // Initialized to -1, assuming a_i are non-negative (0 <= a_i <= 10^9).

    // Read the initial elements into the deque and simultaneously find the maximum value.
    for (int i = 0; i < n; ++i) {
        long long val;
        std::cin >> val;
        d.push_back(val); // Add element to the back of the deque
        if (val > max_val) {
            max_val = val; // Update max_val if a larger element is found
        }
    }

    // This vector will store the pairs (A, B) pulled out during the "initial phase".
    // The initial phase is the period until the maximum element reaches the front of the deque
    // and remains there after an operation.
    std::vector<std::pair<long long, long long>> initial_phase_results;
    long long ops_count = 0; // Counter for the number of operations performed in the initial phase.

    // Simulate operations until the maximum element (max_val) is at the front of the deque.
    // Once max_val is at the front, it will always be the larger element (or equal),
    // so it will be pushed back to the front, creating a stable state.
    while (d.front() != max_val) {
        long long A = d.front(); // Get the first element
        d.pop_front();           // Remove the first element
        long long B = d.front(); // Get the new first element (original second)
        d.pop_front();           // Remove the new first element

        // Store the pair (A, B) that was just pulled out.
        initial_phase_results.push_back({A, B});
        ops_count++; // Increment operation counter

        // Apply the operation rule: the larger of A and B goes to the front, the smaller to the end.
        if (A > B) {
            d.push_front(A); // A is larger, put it back to the front
            d.push_back(B);  // B is smaller, put it to the end
        } else { // A <= B
            d.push_front(B); // B is larger (or equal), put it back to the front
            d.push_back(A);  // A is smaller (or equal), put it to the end
        }
    }

    // After the `while` loop, `d.front()` is `max_val`.
    // The deque is now in a stable state where `max_val` will always be at the front.
    // The remaining `n-1` elements will cycle through the second position,
    // being pulled out with `max_val` and then moved to the end.
    // We store these `n-1` elements in `cyclic_elements`.
    // `d[0]` is `max_val`, so we start from `d[1]` up to `d[n-1]`.
    std::vector<long long> cyclic_elements;
    for (int i = 1; i < n; ++i) {
        cyclic_elements.push_back(d[i]);
    }

    // Process each query.
    for (int k = 0; k < q; ++k) {
        long long m; // The m-th operation for which we need to find the pulled elements.
        std::cin >> m;

        // Check if the query operation `m` falls within the initial phase.
        if (m <= ops_count) {
            // If yes, retrieve the stored pair directly from `initial_phase_results`.
            // `m` is 1-indexed, so we use `m - 1` for 0-indexed vector access.
            std::cout << initial_phase_results[m - 1].first << " "
                      << initial_phase_results[m - 1].second << "\n";
        } else {
            // If `m` is beyond the initial phase, it falls into the cyclic phase.
            // Calculate the effective operation number within the cycle.
            // `m - ops_count` gives how many operations have occurred *after* the initial phase completed.
            // We subtract 1 from `effective_m` because the first operation in the cycle (which is `ops_count + 1`-th overall)
            // corresponds to the element at index 0 in `cyclic_elements`.
            // The modulo `(n - 1)` handles the cycling behavior, as there are `n - 1` elements in the cycle.
            long long effective_m = m - ops_count;
            long long cycle_idx = (effective_m - 1) % (n - 1);
            
            // In the cyclic phase, the first element pulled is always `max_val`,
            // and the second element is determined by `cyclic_elements[cycle_idx]`.
            std::cout << max_val << " " << cyclic_elements[cycle_idx] << "\n";
        }
    }

    return 0; // Indicate successful execution
}

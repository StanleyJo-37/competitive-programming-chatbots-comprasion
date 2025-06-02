#include <iostream> // Required for standard input/output operations (std::cin, std::cout)
#include <vector>   // Required for std::vector to store intervals
#include <algorithm> // Required for std::sort and std::upper_bound
#include <utility>   // Required for std::pair

// Function to solve a single test case
void solve() {
    int N, M;
    std::cin >> N >> M; // Read the number of restaurant open intervals (N) and people (M)

    // Create a vector of pairs to store the intervals.
    // Each pair represents an interval [L_i, R_i), where first is L_i and second is R_i.
    std::vector<std::pair<int, int>> intervals(N);
    for (int i = 0; i < N; ++i) {
        std::cin >> intervals[i].first >> intervals[i].second; // Read L_i and R_i for each interval
    }

    // Sort the intervals based on their start times (L_i).
    // std::pair's default comparison sorts by 'first' element, then by 'second'.
    // Since intervals are guaranteed to be non-overlapping, sorting by L_i ensures
    // that R_i < L_{i+1} for consecutive intervals after sorting.
    std::sort(intervals.begin(), intervals.end());

    // Process each person's arrival time
    for (int i = 0; i < M; ++i) {
        int P;
        std::cin >> P; // Read the arrival time P for the current person

        // Use std::upper_bound to find the first interval [L_k, R_k) such that L_k > P.
        // The lambda function `[](int val, const std::pair<int, int>& interval) { return val < interval.first; }`
        // defines the comparison criteria: it returns true if `val` (which is P) is less than `interval.first` (which is L_k).
        // `upper_bound` returns an iterator to the first element for which this comparison is true.
        auto it = std::upper_bound(intervals.begin(), intervals.end(), P, 
                                   [](int val, const std::pair<int, int>& interval) {
                                       return val < interval.first;
                                   });

        long long wait_time; // Variable to store the calculated waiting time.
                             // Using long long is a safe practice for time differences, though int would suffice here.

        // Case 1: 'it' points to the beginning of the intervals vector.
        // This means P is less than all L_i values. The person arrives before any restaurant opening.
        // The earliest opening is the first interval (intervals[0]).
        if (it == intervals.begin()) {
            wait_time = intervals[0].first - P; // Waiting time is the difference between the first opening time and P.
        }
        // Case 2: 'it' points to the end of the intervals vector.
        // This means P is greater than or equal to all L_i values.
        // We need to check if P falls within the last interval.
        else if (it == intervals.end()) {
            // Get a reference to the last interval in the sorted list.
            const auto& last_interval = intervals[N - 1];
            // If P is within the last open interval [L_{N-1}, R_{N-1}), waiting time is 0.
            // Note: P < R_{N-1} because the interval is [L, R), meaning R is exclusive.
            if (P < last_interval.second) {
                wait_time = 0;
            }
            // Otherwise, P arrives after the last interval closes. There are no future openings.
            else {
                wait_time = -1; // Indicate waiting forever.
            }
        }
        // Case 3: 'it' points to an interval somewhere in the middle of the vector.
        // 'it' points to (L_k, R_k) where L_k > P.
        // The interval immediately before 'it' (let's call it (L_{k-1}, R_{k-1})) has L_{k-1} <= P.
        else {
            // Get an iterator to the interval immediately preceding 'it'.
            auto prev_it = std::prev(it);
            const auto& prev_interval = *prev_it; // Dereference to get the actual pair.

            // Check if P falls within this previous interval [L_{k-1}, R_{k-1}).
            // If P is within this interval, the person does not have to wait.
            if (P < prev_interval.second) {
                wait_time = 0;
            }
            // If P is not within the previous interval (i.e., P >= R_{k-1}),
            // then the person arrived after the previous interval closed.
            // The next available opening is L_k (which is `it->first`).
            else {
                wait_time = it->first - P; // Waiting time is the difference between the next opening time and P.
            }
        }
        std::cout << wait_time << "\n"; // Print the calculated waiting time followed by a newline.
    }
}

int main() {
    // Optimize C++ standard streams for faster input/output operations.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams.
    // std::cin.tie(NULL) prevents std::cout from flushing before std::cin reads, which can speed up I/O.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int T;
    std::cin >> T; // Read the number of test cases
    while (T--) {  // Loop T times, decrementing T in each iteration
        solve();   // Call the solve function for each test case
    }

    return 0; // Indicate successful program execution
}

#include <iostream> // Required for input/output operations (std::cin, std::cout, std::endl)
#include <vector>   // Required for std::vector
#include <algorithm> // Required for std::sort
#include <set>      // Required for std::multiset

// Structure to represent an event in the sweep-line algorithm.
// Events are points on the number line where the set of active intervals changes.
struct Event {
    int coord;        // The coordinate (start or end point) of the event.
    int type;         // Type of event: 0 for interval start, 1 for interval end.
                      // This helps in sorting and processing order.
    int endpoint_val; // For a start event, this stores the end point of the interval.
                      // For an end event, this also stores the end point of the interval.
                      // This value is crucial for managing the `active_intervals_endpoints` multiset.

    // Custom comparator for sorting events.
    // std::sort uses this operator to order Event objects.
    bool operator<(const Event& other) const {
        if (coord != other.coord) {
            // Primary sort key: sort by coordinate in ascending order.
            return coord < other.coord;
        }
        // Secondary sort key: if coordinates are equal, process start events (type 0)
        // before end events (type 1).
        // This ensures that if an interval starts at 'x' and another ends at 'x',
        // the one starting at 'x' is considered active at 'x' before the other one leaves.
        // This is important for correctly counting overlaps at exact points.
        return type < other.type;
    }
};

// Function to solve a single test case.
void solve() {
    int n; // Number of intervals in the current set.
    std::cin >> n;

    // Vector to store all sweep-line events.
    // Each interval generates two events: one start event and one end event.
    std::vector<Event> events;
    events.reserve(2 * n); // Pre-allocate memory for efficiency (2 events per interval).

    // Read intervals and create events.
    for (int i = 0; i < n; ++i) {
        int a, b; // Start and end boundaries of the interval.
        std::cin >> a >> b;
        // Add a start event for the interval [a, b].
        // When this event is processed, we will consider adding this interval.
        // We store 'b' (the end point) with the start event so we know what to insert into the multiset.
        events.push_back({a, 0, b}); 
        // Add an end event for the interval [a, b].
        // When this event is processed, we will consider removing this interval.
        // We store 'b' (the end point) with the end event so we know what to remove from the multiset.
        events.push_back({b, 1, b}); 
    }

    // Sort all events based on their coordinates and types.
    std::sort(events.begin(), events.end());

    // std::multiset to store the end points of currently active intervals.
    // A multiset is used because:
    // 1. It keeps elements sorted, so `*active_intervals_endpoints.begin()` always gives the earliest end point.
    // 2. It allows duplicate elements, which is necessary if multiple chosen intervals share the same end point.
    // 3. `insert`, `find`, and `erase` operations are efficient (logarithmic time complexity).
    std::multiset<int> active_intervals_endpoints;
    int ans = 0; // This variable will store the size of the largest possible subset.

    // Iterate through the sorted events.
    for (const auto& event : events) {
        if (event.type == 0) { // This is a start event for an interval.
            // Optimistically include this interval in our subset.
            // Add its end point to the multiset of active intervals.
            active_intervals_endpoints.insert(event.endpoint_val);
            ans++; // Increment the count of chosen intervals.

            // Check if adding this interval causes more than 2 intervals to overlap
            // at the current point (or any point immediately following).
            if (active_intervals_endpoints.size() > 2) {
                // If there are more than 2 overlapping intervals, we must remove one
                // to satisfy the "no three intervals share a common point" condition.
                // To maximize the total number of chosen intervals, we apply a greedy strategy:
                // remove the interval that ends earliest among the currently overlapping ones.
                // This is because removing an interval that ends earliest frees up the "resource"
                // (the point on the number line) sooner, minimizing its impact on future overlaps
                // and potentially allowing more intervals to be chosen later.
                // `active_intervals_endpoints.begin()` points to the smallest element (earliest end point).
                active_intervals_endpoints.erase(active_intervals_endpoints.begin());
                ans--; // Decrement the count as we had to discard an interval.
            }
        } else { // This is an end event for an interval.
            // An interval is ending. If this interval was chosen (i.e., its end point
            // is still present in our `active_intervals_endpoints` multiset), we remove it.
            // It's possible that this interval was already discarded earlier due to an
            // overlap constraint (if it was the earliest ending interval among >2 overlaps).
            // In that case, `find()` will return `active_intervals_endpoints.end()`, and no action is taken,
            // which is correct.
            auto it = active_intervals_endpoints.find(event.endpoint_val);
            if (it != active_intervals_endpoints.end()) {
                active_intervals_endpoints.erase(it);
            }
        }
    }

    // Print the final answer for the current test case.
    std::cout << ans << std::endl;
}

// Main function to handle multiple test cases.
int main() {
    // Optimize C++ standard streams for competitive programming.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams,
    // potentially speeding up I/O.
    // std::cin.tie(NULL) prevents std::cout from flushing before std::cin reads input,
    // further speeding up I/O.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int s; // Number of interval sets (test cases).
    std::cin >> s;
    while (s--) { // Loop through each test case.
        solve(); // Call the solve function for the current test case.
    }

    return 0; // Indicate successful execution.
}
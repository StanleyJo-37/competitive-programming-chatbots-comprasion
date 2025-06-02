#include <iostream> // Required for input/output operations (cin, cout)
#include <vector>   // Required for std::vector
#include <iomanip>  // Required for std::fixed and std::setprecision
#include <cmath>    // Required for std::abs and std::min

// Define a small epsilon for floating-point comparisons to account for precision issues.
// A common value for double precision is 1e-9 or 1e-12. 1e-9 is usually sufficient for the required 1e-6 precision.
const double EPS = 1e-9;

void solve() {
    int n; // Number of flags
    long long l_ll; // Length of the road (long long to handle large values up to 10^9)
    std::cin >> n >> l_ll;
    double l = static_cast<double>(l_ll); // Convert road length to double for floating-point calculations

    std::vector<int> a(n); // Coordinates of flags (guaranteed to be in increasing order)
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    // Initialize variables for Car 1 (starts at 0, moves towards l)
    double pos1 = 0.0;      // Current position of Car 1
    double speed1 = 1.0;    // Current speed of Car 1
    int flag_idx1 = 0;      // Index of the next flag Car 1 is heading towards (from left to right)

    // Initialize variables for Car 2 (starts at l, moves towards 0)
    double pos2 = l;        // Current position of Car 2
    double speed2 = 1.0;    // Current speed of Car 2
    int flag_idx2 = n - 1;  // Index of the next flag Car 2 is heading towards (from right to left)

    double total_time = 0.0; // Accumulator for total time elapsed until meeting

    // Simulate the movement of cars in discrete steps until they meet or cross each other.
    // The loop continues as long as Car 1 is to the left of Car 2 (or very close, considering EPS).
    while (pos1 < pos2 - EPS) {
        // Calculate time for Car 1 to reach its next flag.
        // If Car 1 has passed all flags (flag_idx1 >= n), it won't hit any more flags.
        // In this case, set time_to_flag1 to a very large value to effectively ignore it.
        double time_to_flag1 = 1e18; // A sufficiently large number
        if (flag_idx1 < n) {
            time_to_flag1 = (a[flag_idx1] - pos1) / speed1;
        }

        // Calculate time for Car 2 to reach its next flag.
        // If Car 2 has passed all flags (flag_idx2 < 0), it won't hit any more flags.
        // Set time_to_flag2 to a very large value.
        double time_to_flag2 = 1e18; // A sufficiently large number
        if (flag_idx2 >= 0) {
            time_to_flag2 = (pos2 - a[flag_idx2]) / speed2;
        }

        // Determine the time until the next "event" occurs.
        // An event is either Car 1 reaching its next flag or Car 2 reaching its next flag.
        // We take the minimum of these two times.
        double dt_event = std::min(time_to_flag1, time_to_flag2);

        // Calculate the hypothetical positions of both cars if they were to move for `dt_event` time
        // without any speed changes (i.e., until the next flag is hit by either car).
        double next_pos1 = pos1 + speed1 * dt_event;
        double next_pos2 = pos2 - speed2 * dt_event;

        // Check if the cars meet or cross within this `dt_event` time segment.
        // If `next_pos1` is greater than or equal to `next_pos2` (considering EPS for floating point),
        // it means they meet within this current segment of constant speeds.
        if (next_pos1 >= next_pos2 - EPS) {
            // If they meet within this segment, calculate the exact time to meet.
            // The distance between them at the start of this segment is `pos2 - pos1`.
            // Their combined speed is `speed1 + speed2`.
            // Time to meet = distance / combined_speed.
            double time_to_meet_in_segment = (pos2 - pos1) / (speed1 + speed2);
            total_time += time_to_meet_in_segment;
            break; // Cars have met, exit the simulation loop.
        } else {
            // If they don't meet within this segment, advance both cars by `dt_event`.
            // Update their current positions and add `dt_event` to the total time.
            pos1 = next_pos1;
            pos2 = next_pos2;
            total_time += dt_event;

            // Update speeds and flag indices based on which car reached its flag (or both).
            // Use `std::abs(dt_event - time_to_flagX) < EPS` for robust floating-point comparison.
            if (std::abs(dt_event - time_to_flag1) < EPS && flag_idx1 < n) {
                speed1++;    // Car 1 reached its flag, increase its speed
                flag_idx1++; // Move to the next flag for Car 1
            }
            if (std::abs(dt_event - time_to_flag2) < EPS && flag_idx2 >= 0) {
                speed2++;    // Car 2 reached its flag, increase its speed
                flag_idx2--; // Move to the next flag for Car 2
            }
        }
    }

    // Print the total time with high precision as required by the problem statement.
    std::cout << std::fixed << std::setprecision(15) << total_time << std::endl;
}

int main() {
    // Optimize C++ standard streams for faster input/output.
    // `std::ios_base::sync_with_stdio(false)` unties C++ streams from C standard streams.
    // `std::cin.tie(NULL)` prevents `cout` from flushing before `cin` reads input.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t; // Number of test cases
    std::cin >> t;
    while (t--) {
        solve(); // Call the solve function for each test case
    }

    return 0; // Indicate successful program execution
}

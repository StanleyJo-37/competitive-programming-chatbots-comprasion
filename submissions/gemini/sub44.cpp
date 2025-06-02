#include <iostream> // Required for standard input/output operations (cin, cout)
#include <vector>   // Required for std::vector, a dynamic array
#include <string>   // Required for std::string, to store runner names
#include <algorithm> // Required for std::sort, to sort runners
#include <iomanip>  // Required for std::fixed and std::setprecision, to format output
#include <limits>   // Required for std::numeric_limits<double>::max(), to initialize min_total_time

// Define a structure to represent a single runner and their times
struct Runner {
    std::string name;   // The runner's name
    double a_time;      // Time taken for the 1st leg (standing start)
    double b_time;      // Time taken for any other leg (flying start)
};

// Custom comparison function for sorting runners based on their b_time.
// This will be used by std::sort to arrange runners in ascending order of their b_time.
bool compareRunnersByBTime(const Runner& r1, const Runner& r2) {
    return r1.b_time < r2.b_time;
}

int main() {
    // Optimize C++ standard streams for faster input/output.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams.
    // std::cin.tie(NULL) prevents std::cout from being flushed before each std::cin operation.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n; // Declare an integer variable 'n' to store the number of runners
    std::cin >> n; // Read the number of runners from standard input

    // Create a std::vector of Runner objects to store data for all 'n' runners.
    std::vector<Runner> runners(n);
    // Loop to read the name, a_time, and b_time for each runner
    for (int i = 0; i < n; ++i) {
        std::cin >> runners[i].name >> runners[i].a_time >> runners[i].b_time;
    }

    // Initialize 'min_total_time' to the maximum possible double value.
    // This ensures that the first valid team time found will be smaller and set as the minimum.
    double min_total_time = std::numeric_limits<double>::max();
    // Create a std::vector of strings to store the names of the runners in the best team.
    // It will store names for leg 1, leg 2, leg 3, and leg 4 in order.
    std::vector<std::string> best_team_names(4);

    // The core logic: Iterate through each runner to consider them as the potential 1st leg runner.
    for (int i = 0; i < n; ++i) {
        // Start the current team's total time with the 'a_time' of the runner chosen for the 1st leg.
        double current_total_time = runners[i].a_time;
        
        // Create a temporary vector to hold all other runners (those not chosen for the 1st leg).
        std::vector<Runner> other_runners;
        // Reserve memory for 'n-1' runners to improve performance by avoiding reallocations.
        other_runners.reserve(n - 1);

        // Populate 'other_runners' vector, excluding the runner currently chosen for the 1st leg.
        for (int j = 0; j < n; ++j) {
            if (i == j) {
                continue; // Skip the runner who is already assigned to the 1st leg
            }
            other_runners.push_back(runners[j]); // Add other runners to the temporary vector
        }

        // Sort the 'other_runners' vector based on their 'b_time' in ascending order.
        // This allows us to easily pick the three fastest runners for legs 2, 3, and 4.
        std::sort(other_runners.begin(), other_runners.end(), compareRunnersByBTime);

        // Add the 'b_time' of the three fastest runners from 'other_runners' to the current total time.
        // Since the problem states n >= 4, 'other_runners' will always have at least 3 elements (n-1 >= 3).
        current_total_time += other_runners[0].b_time; // Fastest 'other' runner for leg 2
        current_total_time += other_runners[1].b_time; // Second fastest 'other' runner for leg 3
        current_total_time += other_runners[2].b_time; // Third fastest 'other' runner for leg 4

        // Compare the 'current_total_time' with the 'min_total_time' found so far.
        if (current_total_time < min_total_time) {
            min_total_time = current_total_time; // Update the minimum total time

            // Store the names of the runners forming this best team.
            best_team_names[0] = runners[i].name;       // Runner for the 1st leg
            best_team_names[1] = other_runners[0].name; // Runner for the 2nd leg
            best_team_names[2] = other_runners[1].name; // Runner for the 3rd leg
            best_team_names[3] = other_runners[2].name; // Runner for the 4th leg
        }
    }

    // Output the minimum total time.
    // std::fixed ensures that the number is printed in fixed-point notation.
    // std::setprecision(2) sets the number of digits after the decimal point to 2,
    // matching the format of the sample output and input times.
    std::cout << std::fixed << std::setprecision(2) << min_total_time << std::endl;

    // Output the names of the runners for each leg of the relay.
    for (int i = 0; i < 4; ++i) {
        std::cout << best_team_names[i] << std::endl;
    }

    return 0; // Indicate successful program execution
}
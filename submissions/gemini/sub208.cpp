#include <iostream> // Required for input/output operations (cin, cout)
#include <vector>   // Required for std::vector to store sorted coordinates
#include <set>      // Required for std::set to store unique points and coordinates
#include <algorithm> // Required for std::sort (though not strictly needed for std::set iterators)
#include <utility>  // Required for std::pair

int main() {
    // Optimize C++ standard streams for competitive programming.
    // This unties cin/cout from C's stdio and disables synchronization,
    // potentially speeding up I/O operations.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    // A set to store the 8 input points. Using std::set automatically handles
    // uniqueness and keeps points sorted, which is not strictly necessary for
    // this problem but doesn't hurt. std::pair is used to represent (x, y) coordinates.
    std::set<std::pair<int, int>> points_set;
    // Sets to store unique x and y coordinates. These will help identify x1, x2, x3 and y1, y2, y3.
    std::set<int> x_coords_set;
    std::set<int> y_coords_set;

    // Read the 8 input points.
    for (int i = 0; i < 8; ++i) {
        int x, y;
        std::cin >> x >> y;
        points_set.insert({x, y}); // Insert the point into the set of points
        x_coords_set.insert(x);    // Insert the x-coordinate into its set
        y_coords_set.insert(y);    // Insert the y-coordinate into its set
    }

    // According to Gerald's rules, there must be exactly 3 distinct x-coordinates
    // and 3 distinct y-coordinates. If not, the set is "ugly".
    if (x_coords_set.size() != 3 || y_coords_set.size() != 3) {
        std::cout << "ugly\n";
        return 0; // Exit the program
    }

    // Extract the unique x-coordinates into a sorted vector.
    // Since std::set stores elements in sorted order, copying to a vector
    // directly gives x1, x2, x3 in increasing order.
    std::vector<int> x_coords(x_coords_set.begin(), x_coords_set.end());
    // Extract the unique y-coordinates into a sorted vector.
    // Similarly, this gives y1, y2, y3 in increasing order.
    std::vector<int> y_coords(y_coords_set.begin(), y_coords_set.end());

    // The problem states x1 < x2 < x3 and y1 < y2 < y3.
    // After sorting, x_coords[0] is x1, x_coords[1] is x2, x_coords[2] is x3.
    // Similarly for y_coords.
    // The point (x2, y2) is the one that should be missing.
    int missing_x = x_coords[1];
    int missing_y = y_coords[1];

    // Now, iterate through all 3x3 = 9 potential intersection points (x_i, y_j).
    // Check if each point adheres to Gerald's rules.
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            int current_x = x_coords[i];
            int current_y = y_coords[j];

            // If the current point is the expected missing point (x2, y2):
            if (current_x == missing_x && current_y == missing_y) {
                // It should NOT be present in the input set.
                // If it IS found in points_set, then the set is "ugly".
                if (points_set.count({current_x, current_y})) {
                    std::cout << "ugly\n";
                    return 0; // Exit
                }
            } else { // If the current point is NOT the expected missing point:
                // It SHOULD be present in the input set.
                // If it is NOT found in points_set, then the set is "ugly".
                if (!points_set.count({current_x, current_y})) {
                    std::cout << "ugly\n";
                    return 0; // Exit
                }
            }
        }
    }

    // If all 9 checks pass (the correct 8 points are present and the one
    // missing point is indeed missing), then the set is "respectable".
    std::cout << "respectable\n";

    return 0; // Successful execution
}

#include <iostream> // Required for input/output operations (std::cin, std::cout)
#include <vector>   // Required for using std::vector to store coordinates
#include <algorithm> // Required for std::sort to sort coordinate vectors

int main() {
    // Optimize C++ standard streams for competitive programming.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard I/O,
    // which can significantly speed up input/output operations.
    std::ios_base::sync_with_stdio(false);
    // std::cin.tie(NULL) prevents std::cout from being flushed before each std::cin operation.
    // This further optimizes I/O, especially when there's a mix of input and output.
    std::cin.tie(NULL);

    int t; // Declare an integer variable 't' to store the number of test cases.
    std::cin >> t; // Read the number of test cases from standard input.

    while (t--) { // Loop 't' times, processing one test case in each iteration.
        int n; // Declare an integer variable 'n' to store the number of houses.
        std::cin >> n; // Read the number of houses for the current test case.

        // Declare two vectors to store x and y coordinates separately.
        // std::vector is used because the number of houses 'n' can vary per test case,
        // and it provides dynamic sizing and convenient sorting capabilities.
        std::vector<int> x_coords(n);
        std::vector<int> y_coords(n);

        // Loop 'n' times to read the coordinates (x_i, y_i) of each house.
        for (int i = 0; i < n; ++i) {
            std::cin >> x_coords[i] >> y_coords[i]; // Read x_i and y_i into their respective vectors.
        }

        // Sort the x-coordinates in non-decreasing order.
        // This step is crucial because the optimal location for minimizing the sum of Manhattan distances
        // along one axis is the median of the coordinates along that axis.
        std::sort(x_coords.begin(), x_coords.end());
        // Sort the y-coordinates in non-decreasing order, for the same reason as x-coordinates.
        std::sort(y_coords.begin(), y_coords.end());

        long long countX; // Declare a long long variable to store the number of optimal X positions.
                          // Using long long is important because the range of coordinates can be up to 10^9,
                          // so the number of optimal positions could also be large (up to 10^9).
        long long countY; // Declare a long long variable to store the number of optimal Y positions.

        // Calculate the number of optimal X positions.
        // The problem of minimizing sum of absolute differences |P - p_i| in 1D is solved by choosing P as the median.
        if (n % 2 == 1) {
            // If 'n' (number of houses) is odd, there is a unique median element.
            // For a 0-indexed sorted array of size 'n', the median is at index n/2.
            // Any point at this unique median minimizes the sum of distances.
            // Therefore, there is only 1 optimal integer X position.
            countX = 1;
        } else {
            // If 'n' is even, any integer point between the two middle elements (inclusive)
            // minimizes the sum of distances.
            // For a 0-indexed sorted array of size 'n', the two middle elements are at indices n/2 - 1 and n/2.
            // The number of integer points in a closed interval [A, B] is B - A + 1.
            countX = x_coords[n / 2] - x_coords[n / 2 - 1] + 1;
        }

        // Calculate the number of optimal Y positions using the exact same logic as for X positions.
        if (n % 2 == 1) {
            countY = 1;
        } else {
            countY = y_coords[n / 2] - y_coords[n / 2 - 1] + 1;
        }

        // The total number of optimal exhibition points is the product of
        // the number of optimal X positions and the number of optimal Y positions.
        // This is because the minimization of the sum of Manhattan distances
        // separates into independent minimizations for the x and y coordinates.
        // The product countX * countY can be as large as (10^9) * (10^9) = 10^18,
        // which requires a 'long long' data type to store.
        std::cout << countX * countY << "\n"; // Print the final result followed by a newline character.
    }

    return 0; // Indicate successful execution of the program.
}
#include <iostream> // Required for input/output operations (std::cin, std::cout)
#include <vector>   // Required for std::vector to store measurements
#include <algorithm> // Required for std::sort to sort the measurements
#include <iomanip>  // Required for std::fixed and std::setprecision for formatted output

int main() {
    // Optimize C++ standard streams for competitive programming.
    // This unties cin from cout and disables synchronization with C's stdio,
    // potentially speeding up I/O operations.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int T; // Declare an integer variable T for the number of test cases
    std::cin >> T; // Read the number of test cases

    // Loop through each test case
    while (T--) {
        int N, K; // Declare integers N for total number of measurements and K for measurements to remove from each end
        std::cin >> N >> K; // Read N and K for the current test case

        // Declare a vector to store the N measurements.
        // Using std::vector is flexible and handles dynamic sizing.
        std::vector<int> A(N);
        // Read N measurements into the vector A
        for (int i = 0; i < N; ++i) {
            std::cin >> A[i];
        }

        // Sort the measurements in ascending order.
        // This is crucial for easily identifying the K lowest and K highest values.
        // After sorting, A[0]...A[K-1] are the K lowest, and A[N-K]...A[N-1] are the K highest.
        std::sort(A.begin(), A.end());

        long long sum = 0; // Use long long for the sum to prevent integer overflow.
                           // N can be up to 10^4 and A_i up to 10^6, so their product (max sum)
                           // can be up to 10^10, which exceeds the maximum value of a 32-bit int.
        
        // Iterate from index K to N-K-1 (inclusive) to sum the remaining measurements.
        // These are the measurements left after removing:
        // - The K lowest values (originally at indices 0 to K-1 after sorting).
        // - The K highest values (originally at indices N-K to N-1 after sorting).
        for (int i = K; i < N - K; ++i) {
            sum += A[i]; // Add the current measurement to the sum
        }

        // Calculate the number of remaining measurements.
        // Total N measurements minus K lowest and K highest measurements removed.
        int count = N - (2 * K);

        // Calculate the average.
        // Cast 'sum' to 'double' before division to ensure floating-point division
        // and to get a precise result. The result itself must be stored in a 'double'.
        double average = static_cast<double>(sum) / count;

        // Output the average value.
        // std::fixed ensures that the number is printed in fixed-point notation (e.g., 4.000000, not 4e+00).
        // std::setprecision(6) sets the precision to 6 digits after the decimal point,
        // as required by the problem statement (error not exceeding 10^-6).
        std::cout << std::fixed << std::setprecision(6) << average << std::endl;
    }

    return 0; // Indicate successful program execution
}

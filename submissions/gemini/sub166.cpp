#include <iostream> // Required for input/output operations (std::cin, std::cout)
#include <vector>   // Required for using std::vector to store the number of girls
#include <algorithm> // Required for std::max function

int main() {
    // Optimize C++ standard streams for faster input/output.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams,
    // which can significantly speed up I/O operations.
    std::ios_base::sync_with_stdio(false);
    // std::cin.tie(NULL) unties std::cin from std::cout. This means std::cout will not be
    // flushed before each std::cin operation, further speeding up I/O.
    std::cin.tie(NULL);

    int T; // Declare variable for the number of test cases
    std::cin >> T; // Read the number of test cases

    while (T--) { // Loop through each test case
        int N, K; // Declare variables for track length N and best speed distance K
        std::cin >> N >> K; // Read N and K for the current test case

        std::vector<int> a(N); // Declare a vector of size N to store the number of girls in each kilometer
        for (int i = 0; i < N; ++i) {
            std::cin >> a[i]; // Read the number of girls for each kilometer into the vector
        }

        // This problem can be solved using a sliding window technique.
        // We need to find the maximum sum of a contiguous subarray of length K.

        // Calculate the sum of the first K elements to initialize the first window.
        // This sum represents the number of girls Vishal can impress in the first K kilometers.
        long long current_girls_sum = 0; // Use long long to prevent potential overflow, though for given constraints (N, K, a_i <= 100), int would suffice (max sum 100*100 = 10000).
        for (int i = 0; i < K; ++i) {
            current_girls_sum += a[i];
        }

        // Initialize max_girls_sum with the sum of the first window.
        long long max_girls_sum = current_girls_sum;

        // Slide the window across the array.
        // The loop starts from index K because the first window covers indices 0 to K-1.
        // In each iteration, we effectively move the window one position to the right.
        // The element a[i-K] is removed from the window, and a[i] is added.
        for (int i = K; i < N; ++i) {
            // Update current_girls_sum by subtracting the element leaving the window (a[i-K])
            // and adding the new element entering the window (a[i]).
            current_girls_sum = current_girls_sum - a[i - K] + a[i];
            
            // Update max_girls_sum if the current window's sum is greater than the previously found maximum.
            max_girls_sum = std::max(max_girls_sum, current_girls_sum);
        }

        // Print the maximum number of girls Vishal can impress for the current test case.
        std::cout << max_girls_sum << std::endl;
    }

    return 0; // Indicate successful program execution
}

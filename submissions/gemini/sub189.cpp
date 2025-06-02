#include <iostream> // Required for input/output operations (std::cin, std::cout)
#include <vector>   // Required for std::vector to store participant strengths
#include <algorithm> // Not strictly necessary for this specific max1/max2 logic, but often useful.
                     // The max1/max2 logic is implemented manually.

// Function to solve a single test case
void solve() {
    int n; // Declare an integer variable 'n' to store the number of participants
    std::cin >> n; // Read the value of 'n' from standard input

    // Declare a vector 's' of size 'n' to store the strengths of participants.
    // Using std::vector allows dynamic sizing and efficient element access.
    std::vector<int> s(n);

    // Initialize 'max1' to store the largest strength found so far.
    // Initialize 'max2' to store the second largest strength found so far.
    // Strengths s_i are positive (1 <= s_i <= 10^9), so -1 is a safe initial value
    // that will be immediately overwritten by any valid strength.
    int max1 = -1;
    int max2 = -1;

    // Loop through 'n' times to read each participant's strength and find max1 and max2
    for (int i = 0; i < n; ++i) {
        std::cin >> s[i]; // Read the strength of the i-th participant into s[i]

        // Logic to update max1 and max2:
        // If the current strength s[i] is strictly greater than the current largest strength (max1)
        if (s[i] > max1) {
            max2 = max1; // The previous largest strength now becomes the second largest
            max1 = s[i]; // The current strength s[i] becomes the new largest
        }
        // Else if s[i] is not strictly greater than max1, but it is strictly greater than the current second largest (max2)
        // This handles cases where s[i] is between max1 and max2.
        // It also correctly handles scenarios with duplicate maximums:
        // If s[i] is equal to max1 (e.g., s = [5, 5, 5]), the first 'if' is skipped.
        // Then, if max2 is less than s[i] (which is max1), max2 will be updated to s[i] (which is max1).
        // This ensures that if there are multiple occurrences of the maximum strength, max1 and max2 will both hold that maximum strength.
        else if (s[i] > max2) {
            max2 = s[i]; // The current strength s[i] becomes the new second largest
        }
    }

    // Loop through the strengths again to calculate and print the required differences
    for (int i = 0; i < n; ++i) {
        // If the current participant's strength s[i] is equal to the overall largest strength (max1)
        if (s[i] == max1) {
            // This participant is one of the strongest.
            // The "other best" participant's strength will be the second largest overall (max2).
            // This correctly handles cases where max1 appears multiple times (e.g., [4,4,4,4]),
            // as max2 would also be 4, resulting in 4-4=0.
            std::cout << s[i] - max2;
        } else {
            // This participant is not the strongest.
            // The "other best" participant's strength will be the largest overall (max1).
            std::cout << s[i] - max1;
        }

        // Print a space after each number, except for the last one in the line
        if (i == n - 1) {
            // If it's the last number, print nothing after it (before the newline)
        } else {
            std::cout << " "; // Otherwise, print a space
        }
    }
    std::cout << "\n"; // After printing all differences for a test case, print a newline
}

// Main function where the program execution begins
int main() {
    // Optimize C++ standard streams for faster input/output.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams,
    // which can speed up I/O operations significantly in competitive programming.
    std::ios_base::sync_with_stdio(false);
    // std::cin.tie(NULL) unties std::cin from std::cout, meaning std::cin will not flush std::cout
    // before reading input. This further speeds up I/O, especially when there's a mix of cin and cout.
    std::cin.tie(NULL);

    int t; // Declare an integer variable 't' to store the number of test cases
    std::cin >> t; // Read the value of 't' from standard input

    // Loop 't' times, calling the 'solve' function for each test case
    while (t--) {
        solve();
    }

    return 0; // Indicate successful program execution
}
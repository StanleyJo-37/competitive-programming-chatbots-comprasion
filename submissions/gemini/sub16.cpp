#include <iostream> // Required for input/output operations (cin, cout)
#include <vector>   // Required for using std::vector to store angles

int main() {
    // Optimize C++ standard streams for faster input/output.
    // This is a common practice in competitive programming to speed up I/O operations.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n; // Declare an integer variable 'n' to store the number of rotations.
    std::cin >> n; // Read the value of 'n' from standard input.

    std::vector<int> a(n); // Declare a vector 'a' of size 'n' to store the rotation angles.
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i]; // Read each rotation angle into the vector.
    }

    // The problem asks if there exists at least one way to choose directions
    // (clockwise or counterclockwise) for 'n' given rotations such that the
    // final pointer position is zero degrees on a 360-degree scale.
    // Since 'n' is small (up to 15), we can iterate through all 2^n possible combinations
    // of clockwise/counterclockwise rotations. This is a brute-force approach.

    // Each combination can be represented by a bitmask from 0 to (2^n - 1).
    // For a given bitmask 'i':
    // If the j-th bit of 'i' is 0, we consider the j-th rotation angle a[j] as counterclockwise (-a[j]).
    // If the j-th bit of 'i' is 1, we consider the j-th rotation angle a[j] as clockwise (+a[j]).

    // Iterate through all possible bitmasks. (1 << n) calculates 2^n.
    for (int i = 0; i < (1 << n); ++i) {
        int current_angle_sum = 0; // Initialize the sum of angles for the current combination.

        // Iterate through each rotation angle a[j] from the input.
        for (int j = 0; j < n; ++j) {
            // Check the j-th bit of the current mask 'i'.
            // (i >> j) shifts the bits of 'i' to the right by 'j' positions, bringing the j-th bit to the rightmost position.
            // & 1 then isolates this rightmost bit.
            if ((i >> j) & 1) {
                // If the j-th bit is 1, it means we choose clockwise rotation for a[j].
                current_angle_sum += a[j];
            } else {
                // If the j-th bit is 0, it means we choose counterclockwise rotation for a[j].
                current_angle_sum -= a[j];
            }
        }

        // After summing all angles for the current combination, we need to check
        // if the final angle is 0 degrees on a 360-degree scale.
        // The modulo operator (%) in C++ can return negative results if the dividend (current_angle_sum) is negative.
        // To ensure the result is always non-negative and within the range [0, 359],
        // we use the formula: (x % M + M) % M.
        int final_angle_mod_360 = (current_angle_sum % 360 + 360) % 360;

        // If the final angle, after considering the 360-degree wrap-around, is 0,
        // then we have found a valid combination of rotations.
        if (final_angle_mod_360 == 0) {
            std::cout << "YES\n"; // Print "YES" followed by a newline.
            return 0; // Terminate the program successfully as we found a solution.
        }
    }

    // If the loop completes without finding any combination that results in 0 degrees,
    // it means no such combination exists.
    std::cout << "NO\n"; // Print "NO" followed by a newline.

    return 0; // Terminate the program successfully.
}
#include <iostream> // Required for input/output operations (std::cin, std::cout)
#include <vector>   // Required for using std::vector to store word forms

// Function to solve a single test case
void solve() {
    int n; // Number of word forms
    int l; // Length of each word in bits
    std::cin >> n >> l; // Read n and l from input

    std::vector<int> x(n); // Vector to store the n word forms
    for (int i = 0; i < n; ++i) {
        std::cin >> x[i]; // Read each word form into the vector
    }

    int initial_form_y = 0; // Initialize the result word y to 0.
                            // We will set its bits one by one.

    // Iterate through each bit position from 0 to l-1 (LSB to MSB).
    // The problem defines bits from 0 to l-1, which aligns with standard
    // binary representation where bit 0 is the least significant bit.
    for (int j = 0; j < l; ++j) {
        int count0 = 0; // Counter for how many x_i have the j-th bit as 0
        int count1 = 0; // Counter for how many x_i have the j-th bit as 1

        // For each given word form x_i, check its j-th bit.
        for (int i = 0; i < n; ++i) {
            // Check if the j-th bit of x[i] is set (1) or not (0).
            // (x[i] >> j) shifts the j-th bit to the 0-th position.
            // & 1 isolates that bit.
            if ((x[i] >> j) & 1) { // If the j-th bit is 1
                count1++;
            } else { // If the j-th bit is 0
                count0++;
            }
        }

        // Decision rule for the j-th bit of y:
        // The total closeness is the sum of Hamming distances d(x_i, y).
        // Hamming distance is the count of differing bits.
        // This sum can be broken down bit by bit:
        // sum(d(x_i, y)) = sum_over_j ( sum_over_i ( (x_i[j] XOR y[j]) ) )
        // To minimize the total sum, we can minimize the contribution from each bit position 'j' independently.
        //
        // For a specific bit position 'j':
        // If we choose y[j] = 0:
        //   The contribution to the total distance from this bit position will be
        //   the number of x_i where x_i[j] is 1 (because 1 XOR 0 = 1, contributing 1 to distance).
        //   This cost is `count1`.
        //
        // If we choose y[j] = 1:
        //   The contribution to the total distance from this bit position will be
        //   the number of x_i where x_i[j] is 0 (because 0 XOR 1 = 1, contributing 1 to distance).
        //   This cost is `count0`.
        //
        // We want to pick y[j] to achieve the minimum of `count0` and `count1`.
        //
        // Case 1: `count0 < count1`
        //   Choosing `y[j] = 1` gives a cost of `count0`.
        //   Choosing `y[j] = 0` gives a cost of `count1`.
        //   Since `count0` is smaller, we choose `y[j] = 1`.
        //
        // Case 2: `count1 < count0`
        //   Choosing `y[j] = 0` gives a cost of `count1`.
        //   Choosing `y[j] = 1` gives a cost of `count0`.
        //   Since `count1` is smaller, we choose `y[j] = 0`.
        //
        // Case 3: `count0 == count1`
        //   Both choices (`y[j]=0` or `y[j]=1`) yield the same cost (`count0` or `count1`).
        //   The problem states "If there are multiple ways to restore the initial form, print any."
        //   So, we can pick either. Let's pick `y[j] = 1` (which corresponds to the `count0` cost).
        //
        // Combining these cases:
        // If `count0 <= count1`: We choose `y[j] = 1`. (This covers Case 1 and Case 3).
        // Else (`count1 < count0`): We choose `y[j] = 0`. (This covers Case 2).
        if (count0 <= count1) {
            // If the number of zeros is less than or equal to the number of ones
            // for this bit position across all x_i, setting y[j] to 1 will minimize
            // the differences (cost = count0).
            initial_form_y |= (1 << j); // Set the j-th bit of initial_form_y to 1
        } else {
            // If the number of ones is less than the number of zeros,
            // setting y[j] to 0 will minimize the differences (cost = count1).
            // No action needed here, as initial_form_y is initialized to 0,
            // and its bits are 0 by default unless explicitly set to 1.
        }
    }

    std::cout << initial_form_y << std::endl; // Print the calculated initial form y
}

int main() {
    // Optimize C++ standard streams for competitive programming.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard I/O.
    // std::cin.tie(NULL) prevents std::cout from flushing before each std::cin.
    // These optimizations can significantly speed up I/O operations.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t; // Number of test cases
    std::cin >> t; // Read the number of test cases
    while (t--) { // Loop through each test case
        solve(); // Call the solve function for the current test case
    }

    return 0; // Indicate successful program execution
}

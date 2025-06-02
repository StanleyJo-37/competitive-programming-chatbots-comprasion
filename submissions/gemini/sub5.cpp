#include <iostream> // Required for input/output operations (std::cin, std::cout)
#include <string>   // Required for string manipulation (std::string)

int main() {
    // Optimize C++ standard streams for competitive programming.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard I/O.
    // std::cin.tie(NULL) prevents std::cout from being flushed before each std::cin operation.
    // These optimizations can significantly speed up I/O operations, which is crucial in competitive programming.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t; // Declare an integer variable 't' to store the number of test cases.
    std::cin >> t; // Read the number of test cases from standard input.

    // Loop through each test case.
    while (t--) {
        int n; // Declare an integer variable 'n' to store the number of columns in the grid.
        std::cin >> n; // Read the number of columns for the current test case.

        std::string row0; // Declare a string to store the first row of the grid.
        std::string row1; // Declare a string to store the second row of the grid.
        std::cin >> row0 >> row1; // Read both rows of the grid from standard input.
                                  // '0' represents a safe cell, '1' represents a trap cell.

        bool possible = true; // Initialize a boolean flag 'possible' to true.
                              // This flag will be set to false if an impassable column is found.

        // Iterate through each column of the grid, from the first column (index 0) to the last (index n-1).
        for (int i = 0; i < n; ++i) {
            // Check if both cells in the current column 'i' are traps.
            // A cell is a trap if its character is '1'.
            // If row0[i] is '1' AND row1[i] is '1', it means both cells (row 0, column i) and (row 1, column i) are traps.
            // The problem states that movement is allowed between cells adjacent by side and/or corner.
            // This means from any cell (r, c-1), it's possible to move to any cell (r', c) if it's safe,
            // where r' can be r-1, r, or r+1 (within grid boundaries).
            // In a 2-row grid, this implies that from any safe cell in column 'i-1',
            // one can reach any safe cell in column 'i'.
            // Therefore, if both cells in column 'i' are traps, it's impossible to pass through column 'i'
            // to reach any subsequent column. This forms an insurmountable barrier.
            if (row0[i] == '1' && row1[i] == '1') {
                possible = false; // Set the 'possible' flag to false, indicating that the level cannot be completed.
                break;            // Since a blocking column has been found, there's no need to check further columns.
                                  // We can immediately break out of the loop.
            }
        }

        // After checking all columns (or breaking early if a block was found),
        // output the result based on the final value of the 'possible' flag.
        if (possible) {
            std::cout << "YES\n"; // If 'possible' is still true, it means no blocking column was found,
                                  // and thus a path exists to complete the level.
        } else {
            std::cout << "NO\n";  // If 'possible' is false, it means a blocking column was encountered,
                                  // and the level cannot be completed.
        }
    }

    return 0; // Indicate successful execution of the program.
}

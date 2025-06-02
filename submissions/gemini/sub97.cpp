#include <iostream> // Required for input/output operations (std::cin, std::cout, std::endl)
#include <vector>   // Required for std::vector to store the matrix and group values
#include <cmath>    // Required for std::abs to calculate absolute difference
#include <algorithm> // Required for std::sort to sort group values

// Function to solve a single test case
void solve() {
    int n, m;
    // Read the dimensions of the matrix
    std::cin >> n >> m;

    // Declare and read the matrix elements
    // Using long long for matrix elements as values can be up to 10^9,
    // and the sum of operations can exceed the range of int.
    std::vector<std::vector<long long>> a(n, std::vector<long long>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            std::cin >> a[i][j];
        }
    }

    // Initialize total operations required to 0
    long long total_operations = 0;

    // Iterate through the "top-left" quadrant of the matrix, including middle row/column if dimensions are odd.
    // This approach ensures that each unique group of symmetric cells is processed exactly once.
    // For a cell (i, j), its symmetric counterparts are (i, m-1-j), (n-1-i, j), and (n-1-i, m-1-j).
    // By iterating i from 0 to (n-1)/2 and j from 0 to (m-1)/2, we cover all such groups.
    // (n-1)/2 uses integer division, which correctly gives floor((n-1)/2).
    // For example, if n=4, (4-1)/2 = 1, so i goes 0, 1.
    // If n=3, (3-1)/2 = 1, so i goes 0, 1.
    for (int i = 0; i <= (n - 1) / 2; ++i) {
        for (int j = 0; j <= (m - 1) / 2; ++j) {
            // Create a vector to store values of the current symmetric group
            std::vector<long long> group_values;
            
            // Add the value at the current cell (i, j)
            group_values.push_back(a[i][j]);

            // Check if the row 'i' is not the middle row (i.e., n-1-i is a distinct row index from i).
            // If it's not the middle row, then (n-1-i, j) is a distinct symmetric position.
            if (i != n - 1 - i) {
                group_values.push_back(a[n - 1 - i][j]);
            }

            // Check if the column 'j' is not the middle column (i.e., m-1-j is a distinct column index from j).
            // If it's not the middle column, then (i, m-1-j) is a distinct symmetric position.
            if (j != m - 1 - j) {
                group_values.push_back(a[i][m - 1 - j]);
            }

            // Check if both row 'i' and column 'j' are not middle (i.e., (i,j) is in a true corner quadrant).
            // If both conditions are true, then (n-1-i, m-1-j) is a distinct symmetric position.
            // This condition implicitly covers the case where (i,j) is in the top-left quadrant
            // and not on any middle axis.
            if (i != n - 1 - i && j != m - 1 - j) {
                group_values.push_back(a[n - 1 - i][m - 1 - j]);
            }

            // Sort the collected values. This is crucial for finding the median and calculating minimum operations.
            std::sort(group_values.begin(), group_values.end());

            // The number of elements in a group can be 1, 2, or 4.
            // 1 element: Occurs at the exact center of an odd x odd matrix (e.g., (n/2, m/2)). No operations needed.
            // 2 elements: Occurs on a middle row (if n is odd) or middle column (if m is odd), but not the center.
            //             E.g., (i, j) and (i, m-1-j) if i is middle row, or (i, j) and (n-1-i, j) if j is middle column.
            //             The cost to make two numbers equal is their absolute difference.
            // 4 elements: Occurs when (i, j) is in a "corner" quadrant, not on any middle axis.
            //             All four symmetric positions are distinct.
            //             The minimum operations to make them equal is achieved by changing them all to their median.
            //             For 4 sorted values x1, x2, x3, x4, the cost is (x4 - x1) + (x3 - x2).
            //             This is because the optimal median X can be any value between x2 and x3 (inclusive).
            //             For example, if X = x2, cost is (x2-x1) + 0 + (x3-x2) + (x4-x2) = x2-x1+x3-x2+x4-x2 = x3+x4-x1-x2.
            //             If X = x3, cost is (x3-x1) + (x3-x2) + 0 + (x4-x3) = x3-x1+x3-x2+x4-x3 = x3+x4-x1-x2.
            //             The sum of absolute differences is minimized when X is the median.
            int num_elements = group_values.size();
            if (num_elements == 2) {
                total_operations += std::abs(group_values[0] - group_values[1]);
            } else if (num_elements == 4) {
                total_operations += (group_values[3] - group_values[0]) + (group_values[2] - group_values[1]);
            }
            // If num_elements is 1, cost is 0, so no addition to total_operations is needed.
        }
    }

    // Print the total minimum operations for the current test case
    std::cout << total_operations << std::endl;
}

int main() {
    // Optimize C++ standard streams for competitive programming.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard I/O.
    // std::cin.tie(NULL) prevents std::cout from flushing before std::cin reads input.
    // These two lines can significantly speed up I/O operations, which is often crucial in competitive programming.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    // Read the number of test cases
    std::cin >> t;
    // Loop through each test case
    while (t--) {
        solve();
    }

    return 0;
}

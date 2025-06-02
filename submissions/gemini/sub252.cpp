#include <iostream> // Required for input/output operations (std::cin, std::cout)
#include <algorithm> // Required for std::min and std::max functions

int main() {
    // Optimize C++ standard streams for competitive programming.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams,
    // which can significantly speed up I/O operations.
    // std::cin.tie(NULL) prevents std::cout from being flushed before each std::cin operation,
    // further improving I/O performance.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    // Declare variables A, B, C, D to store Yuri's favorite numbers.
    // These values are up to 5 * 10^5, which fit within a standard 'int'.
    int A, B, C, D;
    // Read the four integers from standard input.
    std::cin >> A >> B >> C >> D;

    // Declare a variable to store the total count of non-degenerate triangles.
    // The maximum possible count can be very large (e.g., (5e5)^3 in a very loose upper bound,
    // or more realistically, (C-A+1) * (B-A+1) * (D-C+1) which can be ~5e5 * 5e5 * 5e5 = 1.25e17).
    // A tighter upper bound is (C-A+1) * max(num_xy_pairs) * max(num_z_values)
    // which is roughly 5e5 * 5e5 * 5e5 = 1.25e17.
    // This requires a 'long long' type to prevent overflow, as 'int' typically holds up to ~2 * 10^9.
    long long total_triangles = 0;

    // The problem requires finding integer sides x, y, z such that:
    // 1. A <= x <= B
    // 2. B <= y <= C
    // 3. C <= z <= D
    // 4. x + y > z (triangle inequality for non-degenerate triangles)
    // The other two triangle inequalities (x + z > y and y + z > x) are always satisfied
    // given A <= B <= C and the ranges for x, y, z (e.g., x + z >= A + C > C >= y).

    // We can iterate over all possible sums S = x + y.
    // The minimum possible value for S is A + B (when x=A, y=B).
    // The maximum possible value for S is B + C (when x=B, y=C).
    // The loop variable S must be 'long long' because B+C can be up to 10^6,
    // and intermediate calculations involving S (like S-C, S-B, S-1) might result in values
    // that are better handled as 'long long' to avoid potential issues with type promotion.
    for (long long S = (long long)A + B; S <= (long long)B + C; ++S) {
        // For a fixed sum S = x + y, we need to find the number of pairs (x, y) that satisfy:
        // A <= x <= B
        // B <= y <= C
        // Since y = S - x, substitute into B <= y <= C:
        // B <= S - x <= C
        // This implies:
        // S - C <= x <= S - B
        // Combining with A <= x <= B, the valid range for x is:
        // max(A, S - C) <= x <= min(B, S - B)
        // The bounds for x (x_lower_bound, x_upper_bound) can be negative or up to 10^6,
        // so 'long long' is used for consistency with S and to avoid potential issues.
        long long x_lower_bound = std::max((long long)A, S - C);
        long long x_upper_bound = std::min((long long)B, S - B);

        // Calculate the number of valid (x, y) pairs for the current sum S.
        // If x_lower_bound is greater than x_upper_bound, there are no valid x values.
        // Otherwise, the count is x_upper_bound - x_lower_bound + 1.
        long long num_xy_pairs = 0; // This count can be up to 5 * 10^5, fits in int, but long long for consistency.
        if (x_lower_bound <= x_upper_bound) {
            num_xy_pairs = x_upper_bound - x_lower_bound + 1;
        }

        // For the current sum S = x + y, we need to find the number of z values that satisfy:
        // C <= z <= D
        // x + y > z  => S > z  => z < S
        // Combining these, z must be in the range [C, min(D, S - 1)].
        // The effective upper limit for z is min(D, S - 1).
        // z_upper_limit can be up to D (5 * 10^5) or S-1 (10^6 - 1), so 'long long' is used.
        long long z_upper_limit = std::min((long long)D, S - 1);
        
        // Calculate the number of valid z values.
        // If z_upper_limit is less than C, there are no valid z values.
        // Otherwise, the count is z_upper_limit - C + 1.
        long long num_z_values = 0; // This count can be up to 5 * 10^5, fits in int, but long long for consistency.
        if (z_upper_limit >= C) {
            num_z_values = z_upper_limit - C + 1;
        }

        // The total number of triangles for the current sum S is the product of
        // the number of (x, y) pairs and the number of z values.
        // Add this product to the overall total.
        // The product num_xy_pairs * num_z_values can exceed the capacity of 'int',
        // so 'long long' is essential for total_triangles.
        total_triangles += num_xy_pairs * num_z_values;
    }

    // Print the final calculated total number of non-degenerate triangles.
    std::cout << total_triangles << std::endl;

    // Return 0 to indicate successful execution.
    return 0;
}

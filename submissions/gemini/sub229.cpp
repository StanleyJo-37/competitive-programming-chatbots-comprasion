#include <iostream> // Required for input/output operations (cin, cout)
#include <algorithm> // Required for std::max and std::min

int main() {
    // Optimize C++ standard streams for competitive programming.
    // This unties cin/cout from C's stdio and disables flushing cout before cin.
    // It can significantly speed up I/O operations, especially for large inputs.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    long long l, r, x, y, k; // Declare variables to store input values.
                             // Use long long to accommodate values up to 10^7.
                             // While 10^7 fits in int, using long long for all
                             // ensures no overflow issues with intermediate sums
                             // like (l + k - 1) and provides consistency,
                             // especially if k*b were to be calculated directly.

    std::cin >> l >> r >> x >> y >> k; // Read the five integer inputs.

    // The problem asks if there exist integers 'a' (experience) and 'b' (cost) such that:
    // 1. l <= a <= r (experience 'a' is within range [l, r])
    // 2. x <= b <= y (cost 'b' is within range [x, y])
    // 3. a / b = k (efficiency is exactly k)

    // From condition 3, since 'a', 'b', and 'k' are given as integers, we can rewrite it as:
    // a = k * b

    // Now, substitute 'a = k * b' into condition 1:
    // l <= k * b <= r

    // Since k is a positive integer (1 <= k <= 10^7), we can divide the inequality by k
    // without changing the direction of the inequalities:
    // l / k <= b <= r / k

    // Since 'b' must be an integer, we need to consider integer division and ceiling/floor:
    // The smallest integer 'b' satisfying 'b >= l / k' is ceil(l / k).
    // The largest integer 'b' satisfying 'b <= r / k' is floor(r / k).

    // In C++ integer division, for positive integers N and D:
    // floor(N / D) is simply N / D.
    // ceil(N / D) can be computed as (N + D - 1) / D.

    // So, the range of 'b' values that satisfy 'l <= k * b <= r' is:
    // [ (l + k - 1) / k , r / k ]
    // Let's call these bounds b_lower_from_a_range and b_upper_from_a_range.
    long long b_lower_from_a_range = (l + k - 1) / k;
    long long b_upper_from_a_range = r / k;

    // We also have the direct constraint on 'b' from condition 2:
    // [x, y]

    // For a valid integer 'b' to exist, it must satisfy both sets of constraints.
    // This means 'b' must be in the intersection of the range [x, y]
    // and the range [b_lower_from_a_range, b_upper_from_a_range].

    // The effective lower bound for 'b' in this intersection is the maximum of the two lower bounds:
    // max(x, b_lower_from_a_range)
    long long actual_b_lower_bound = std::max(x, b_lower_from_a_range);

    // The effective upper bound for 'b' in this intersection is the minimum of the two upper bounds:
    // min(y, b_upper_from_a_range)
    long long actual_b_upper_bound = std::min(y, b_upper_from_a_range);

    // A valid integer 'b' exists if and only if the calculated effective lower bound
    // is less than or equal to the effective upper bound.
    // If actual_b_lower_bound <= actual_b_upper_bound, then there is at least one integer 'b'
    // (e.g., actual_b_lower_bound itself) that satisfies all conditions.
    // If actual_b_lower_bound > actual_b_upper_bound, the intersection is empty,
    // meaning no such integer 'b' exists.

    if (actual_b_lower_bound <= actual_b_upper_bound) {
        std::cout << "YES\n"; // A potion with efficiency k can be bought.
    } else {
        std::cout << "NO\n";  // No such potion exists.
    }

    return 0; // Indicate successful execution.
}
#include <iostream> // Required for input/output operations (std::cin, std::cout, std::endl)
#include <vector>   // Required for std::vector
#include <algorithm> // Required for std::max
#include <limits>    // Required for std::numeric_limits<long long>::min()

void solve() {
    int n; // Number of pokemons
    int q; // Number of operations (guaranteed to be 0 in this easy version)
    std::cin >> n >> q; // Read n and q

    std::vector<long long> a(n); // Vector to store pokemon strengths
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i]; // Read strengths into the vector
    }

    // max_add_so_far: Stores the maximum alternating sum of a subsequence
    // that ends with an element being ADDED.
    // Initialized to 0, representing an empty subsequence. This allows any a[i]
    // to be chosen as the first element of a new subsequence (sum a[i] + 0).
    long long max_add_so_far = 0;

    // max_sub_so_far: Stores the maximum alternating sum of a subsequence
    // that ends with an element being SUBTRACTED.
    // Initialized to LLONG_MIN (smallest possible long long value) because
    // a subsequence cannot start with a subtraction. A valid sum ending with
    // a subtraction must have originated from a previous addition.
    long long max_sub_so_far = std::numeric_limits<long long>::min();

    // overall_max_sum: Stores the global maximum alternating sum found so far.
    // Since all a_i are positive (1 <= a_i <= n), the minimum possible sum
    // for a non-empty subsequence is 1 (by picking a single element).
    // Initializing to 0 is safe as any valid sum will be >= 1.
    long long overall_max_sum = 0;

    // Iterate through each pokemon strength to build up the DP states
    for (int i = 0; i < n; ++i) {
        // current_add_sum: The maximum sum if a[i] is chosen to be ADDED.
        // It can either be a[i] itself (starting a new subsequence),
        // or a[i] added to a previous sum that ended with a subtraction (max_sub_so_far).
        // std::max(0LL, max_sub_so_far) handles the case where extending a previous
        // subtracted sum would result in a smaller value than just starting with a[i].
        long long current_add_sum = a[i] + std::max(0LL, max_sub_so_far);

        // current_sub_sum: The maximum sum if a[i] is chosen to be SUBTRACTED.
        // This must extend a previous sum that ended with an addition (max_add_so_far).
        // If max_add_so_far is still 0 (meaning no element has been added yet),
        // then current_sub_sum will be -a[i]. This value will likely not be chosen
        // for max_sub_so_far unless LLONG_MIN is the only other option, and it won't
        // contribute to overall_max_sum as overall_max_sum only tracks sums ending with addition.
        long long current_sub_sum = -a[i] + max_add_so_far;

        // Update max_add_so_far: Take the maximum between its current value
        // and the newly calculated current_add_sum.
        max_add_so_far = std::max(max_add_so_far, current_add_sum);

        // Update max_sub_so_far: Take the maximum between its current value
        // and the newly calculated current_sub_sum.
        max_sub_so_far = std::max(max_sub_so_far, current_sub_sum);

        // The overall maximum sum will always end with an element being added.
        // If a subsequence ends with a subtracted element (e.g., S - X), and X > 0,
        // then S itself would be a larger sum. Since all a_i are positive, we can
        // always drop the last subtracted element to get a larger or equal sum.
        overall_max_sum = std::max(overall_max_sum, max_add_so_far);
    }

    // Print the maximal strength for the current test case
    std::cout << overall_max_sum << std::endl;
}

int main() {
    // Optimize C++ standard streams for competitive programming.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams,
    // which can speed up I/O operations.
    // std::cin.tie(NULL) prevents std::cout from being flushed before each std::cin operation,
    // further speeding up I/O.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t; // Number of test cases
    std::cin >> t; // Read the number of test cases
    while (t--) { // Loop through each test case
        solve(); // Call the solve function for each test case
    }

    return 0; // Indicate successful execution
}

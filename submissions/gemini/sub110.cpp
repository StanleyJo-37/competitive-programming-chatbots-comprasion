#include <iostream> // Required for input/output operations (cin, cout)
#include <vector>   // Required for using std::vector
#include <algorithm> // Required for std::sort and std::max

int main() {
    // Optimize C++ standard streams for competitive programming.
    // This unties cin/cout from C standard streams and disables synchronization
    // with C standard streams, leading to faster I/O.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n; // Declare n for the length of sequences
    long long l, r; // Declare l, r for the range boundaries, using long long due to large possible values (10^9)

    // Read n, l, r from standard input
    std::cin >> n >> l >> r;

    // Declare vector 'a' to store elements of sequence a.
    // Use long long for elements of 'a' as they can be up to 10^9.
    std::vector<long long> a(n);
    // Read elements of sequence 'a'
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    // Declare vector of pairs to store (p_i, original_index).
    // This allows sorting based on p_i while keeping track of the original index.
    std::vector<std::pair<int, int>> p_indexed(n);
    // Read elements of sequence 'p' and populate p_indexed
    for (int i = 0; i < n; ++i) {
        int p_val;
        std::cin >> p_val;
        // Store p_val and its original 0-indexed position (i)
        p_indexed[i] = {p_val, i};
    }

    // Sort p_indexed based on the p_val (first element of the pair).
    // After sorting, p_indexed[k].first will be k+1 (if 1-indexed p_val)
    // and p_indexed[k].second will be the original index 'i' such that p_i = k+1.
    std::sort(p_indexed.begin(), p_indexed.end());

    // Declare vector 'c_values' to store the calculated elements of sequence c.
    // Use long long for elements of 'c' as they can be in range approx. -10^9 to 10^9.
    std::vector<long long> c_values(n);

    // Initialize 'prev_c_val' to a value guaranteed to be smaller than any possible c_i.
    // The smallest possible c_i is l - r. So l - r - 1 is a safe lower bound.
    // This ensures that for the first element, prev_c_val + 1 does not constrain it
    // more than its own lower bound (l - a_i).
    long long prev_c_val = l - r - 1;

    // Iterate through the sorted p_indexed pairs to determine c_i values in increasing order of their rank.
    for (int k = 0; k < n; ++k) {
        // Get the original index 'i' for the current rank (k+1)
        int original_idx = p_indexed[k].second;

        // Calculate the minimum and maximum allowed values for c_i based on b_i's constraints:
        // l <= b_i <= r  =>  l <= c_i + a_i <= r
        // => l - a_i <= c_i <= r - a_i
        long long min_c_for_this_idx = l - a[original_idx];
        long long max_c_for_this_idx = r - a[original_idx];

        // Determine the required value for c_i.
        // It must be at least 'prev_c_val + 1' to maintain distinctness and sorted order.
        // It must also be at least 'min_c_for_this_idx' to satisfy b_i's lower bound.
        long long required_c_val = std::max(prev_c_val + 1, min_c_for_this_idx);

        // Check if the required c_i value exceeds its maximum allowed value.
        // If it does, no valid sequence 'b' can be found.
        if (required_c_val > max_c_for_this_idx) {
            std::cout << -1 << std::endl; // Print -1
            return 0; // Exit the program
        }

        // Assign the determined c_i value to its original index.
        c_values[original_idx] = required_c_val;
        // Update prev_c_val for the next iteration.
        prev_c_val = required_c_val;
    }

    // If the loop completes, a valid sequence 'c' has been found.
    // Now, calculate the sequence 'b' using b_i = c_i + a_i.
    // Use long long for elements of 'b' as they can be up to 10^9.
    std::vector<long long> b(n);
    for (int i = 0; i < n; ++i) {
        b[i] = c_values[i] + a[i];
    }

    // Print the elements of sequence 'b' separated by spaces.
    for (int i = 0; i < n; ++i) {
        std::cout << b[i] << (i == n - 1 ? "" : " ");
    }
    std::cout << std::endl; // Print a newline at the end

    return 0; // Indicate successful execution
}

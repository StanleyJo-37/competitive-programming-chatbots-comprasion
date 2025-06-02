#include <iostream> // Required for input/output operations (std::cin, std::cout)
#include <vector>   // Required for std::vector to store sock counts
#include <numeric>  // Not strictly needed for this solution, but often useful for algorithms like std::accumulate
#include <algorithm> // Required for std::min and std::swap

// Function to solve a single test case
void solve() {
    int n; // Total number of socks
    long long initial_l, initial_r; // Initial counts of left and right socks
    std::cin >> n >> initial_l >> initial_r;

    // Use vectors to store counts of socks for each color.
    // Colors are 1-indexed up to n, so size n+1 is appropriate.
    std::vector<int> left_counts(n + 1, 0);
    std::vector<int> right_counts(n + 1, 0);

    // Read colors for left socks and update their counts
    for (int i = 0; i < initial_l; ++i) {
        int c;
        std::cin >> c;
        left_counts[c]++;
    }

    // Read colors for right socks and update their counts
    for (int i = 0; i < initial_r; ++i) {
        int c;
        std::cin >> c;
        right_counts[c]++;
    }

    int cost = 0; // Initialize total cost

    // current_l and current_r will track the number of socks remaining
    // after forming initial same-color, same-type pairs.
    int current_l = initial_l;
    int current_r = initial_r;

    // Step 1: Form initial pairs of same color and type.
    // These pairs cost 0. Update counts in `left_counts`, `right_counts`,
    // and the total remaining socks `current_l`, `current_r`.
    for (int i = 1; i <= n; ++i) {
        int matched = std::min(left_counts[i], right_counts[i]);
        left_counts[i] -= matched;
        right_counts[i] -= matched;
        current_l -= matched; // Reduce total count of remaining left socks
        current_r -= matched; // Reduce total count of remaining right socks
    }

    // Step 2: Balance the number of left and right socks by converting types.
    // We want to convert socks from the side with more socks to the side with fewer.
    // To simplify logic, ensure `current_l` always refers to the side with more socks
    // (or equal), and `current_r` to the side with fewer.
    // If `current_r` is initially larger, swap the counts and the `current_l`/`current_r` variables.
    if (current_l < current_r) {
        std::swap(current_l, current_r);
        std::swap(left_counts, right_counts); // Swap the count vectors as well
    }

    // `current_l` now holds the count of the side with more (or equal) socks.
    // `current_r` holds the count of the side with fewer (or equal) socks.

    // Calculate how many socks need to be converted from the `current_l` side
    // to the `current_r` side to balance the total counts.
    // Each such conversion costs 1 dollar.
    int diff_to_balance = (current_l - current_r) / 2;
    cost += diff_to_balance; // Add cost for these mandatory type conversions

    // Now, try to use these `diff_to_balance` conversions efficiently.
    // An efficient conversion is one where we convert a sock of color C from the `current_l` side
    // to the `current_r` side, and it can then pair with another sock of color C that was
    // originally on the `current_l` side. This is possible if `left_counts[i]` >= 2.
    // Such a conversion effectively forms a pair of color `i` without needing a recoloring operation later.
    for (int i = 1; i <= n; ++i) {
        if (diff_to_balance == 0) break; // All necessary type conversions have been assigned.
        
        // If there are at least 2 socks of color `i` on the `current_l` side,
        // we can convert one of them to the `current_r` type.
        // This forms one pair of color `i` using two socks from the `current_l` side.
        int can_convert_for_pair = left_counts[i] / 2;
        
        // Determine how many such efficient conversions we can actually perform,
        // limited by `diff_to_balance` (total conversions needed) and `can_convert_for_pair`.
        int num_converted_for_pairs = std::min(diff_to_balance, can_convert_for_pair);
        
        // Update counts: these `2 * num_converted_for_pairs` socks are now paired up.
        left_counts[i] -= 2 * num_converted_for_pairs;
        current_l -= 2 * num_converted_for_pairs; // Reduce total remaining `current_l` socks
        diff_to_balance -= num_converted_for_pairs; // Reduce the number of conversions still needed
    }

    // After the above steps:
    // 1. All initial same-color, same-type pairs are formed.
    // 2. The total number of socks on the two sides (`current_l` and `current_r`) are now equal.
    //    (This is because `diff_to_balance` has been fully accounted for, either by efficient conversions
    //    or by simply reducing `current_l` and increasing `current_r` conceptually).
    // 3. `current_l` and `current_r` now represent the total number of socks remaining on each side
    //    that still need to be paired.
    // 4. Since all same-color pairs (both initial and those formed by efficient conversions)
    //    have been exhausted, any remaining left sock of color `X` has no right sock of color `X`, and vice versa.
    // Therefore, to form the remaining `current_l` (which is equal to `current_r`) pairs,
    // each pair will require at least one recoloring operation.
    // The total number of pairs to form is `(current_l + current_r) / 2`.
    // Since `current_l` and `current_r` are now equal, this is simply `current_l`.
    cost += current_l; // Add cost for recoloring these remaining pairs

    std::cout << cost << std::endl;
}

int main() {
    // Optimize C++ standard streams for competitive programming.
    // This unties C++ streams from C standard streams and disables synchronization,
    // leading to faster input/output operations.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t; // Number of test cases
    std::cin >> t;
    while (t--) {
        solve(); // Solve each test case
    }

    return 0;
}

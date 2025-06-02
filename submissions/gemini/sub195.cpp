#include <iostream> // Required for input/output operations (cin, cout)
#include <vector>   // Required for dynamic arrays (std::vector)
#include <algorithm> // Required for sorting (std::sort, std::min, std::max)
#include <set>      // Required for std::multiset

// Function to solve a single test case
void solve() {
    int n; // Number of cheese slices
    std::cin >> n; // Read n

    // Store (min_dimension, max_dimension) for each cheese.
    // Using long long for dimensions to handle values up to 10^9.
    std::vector<std::pair<long long, long long>> cheeses(n); 
    
    // initial_sum_min_w: Sum of widths if all cheeses are oriented with their minimum dimension as width.
    // This is the starting point for current_sum_w.
    long long initial_sum_min_w = 0; 
    
    // max_d_unforced_set: A multiset to store the max_dimensions of cheeses that are currently
    // allowed to use their max_dimension as height. We use a multiset because dimensions can be repeated.
    std::multiset<long long> max_d_unforced_set; 

    // Read dimensions for each cheese and populate initial sums and sets
    for (int i = 0; i < n; ++i) {
        long long a, b;
        std::cin >> a >> b; // Read dimensions a_i and b_i
        long long min_d = std::min(a, b); // Smaller dimension of the current cheese
        long long max_d = std::max(a, b); // Larger dimension of the current cheese
        
        cheeses[i] = {min_d, max_d}; // Store the pair (min_d, max_d)
        initial_sum_min_w += min_d; // Add min_d to the initial sum of widths
        max_d_unforced_set.insert(max_d); // Add max_d to the set of heights that can be chosen
    }

    // Sort cheeses by their max_dimension in descending order.
    // This sorting order is crucial for the sweep-line approach.
    // We process cheeses from those with the largest max_dimension downwards.
    std::sort(cheeses.begin(), cheeses.end(), [](const std::pair<long long, long long>& p1, const std::pair<long long, long long>& p2) {
        return p1.second > p2.second; // Sort by max_d (second element) in descending order
    });

    // current_sum_w: Tracks the sum of widths for the current configuration of cheese orientations.
    // Initially, all widths are min_d (as per initial_sum_min_w).
    long long current_sum_w = initial_sum_min_w; 
    
    // max_min_d_in_forced: Tracks the maximum of min_dimensions for cheeses that have been "forced"
    // to use their min_dimension as height. This happens when the overall maximum height (H_actual)
    // is reduced below their max_dimension.
    long long max_min_d_in_forced = 0; 

    // The perimeter formula is 2 * (total width) + 2 * (maximum height).
    // Initial perimeter candidate: all cheeses use max_d as height, so total width is initial_sum_min_w,
    // and the maximum height is the largest max_d currently in max_d_unforced_set.
    long long min_overall_perimeter = 2 * current_sum_w + 2 * (*max_d_unforced_set.rbegin());

    // Iterate through cheeses sorted by max_d descending.
    // In each step, we simulate "forcing" the current cheese to use its min_d as height.
    // This corresponds to considering a scenario where the overall maximum height (H_actual)
    // is potentially reduced to or below the current cheese's max_d.
    for (int i = 0; i < n; ++i) {
        long long min_d_k = cheeses[i].first;  // min_dimension of current cheese (k)
        long long max_d_k = cheeses[i].second; // max_dimension of current cheese (k)

        // Remove max_d_k from the set of "unforced" heights.
        // This cheese is now considered "forced" to use its min_d_k as height.
        // std::multiset::find returns an iterator to an element, then erase removes it.
        max_d_unforced_set.erase(max_d_unforced_set.find(max_d_k));

        // Update current_sum_w: this cheese's width changes from min_d_k to max_d_k.
        // The difference (max_d_k - min_d_k) is added to the total width.
        current_sum_w += (max_d_k - min_d_k);

        // Update max_min_d_in_forced: track the largest min_d among all cheeses that are now forced.
        max_min_d_in_forced = std::max(max_min_d_in_forced, min_d_k);

        // Calculate the actual maximum height for the current configuration.
        // This is the maximum of:
        // 1. The largest min_d among cheeses forced to use their min_d as height (`max_min_d_in_forced`).
        // 2. The largest max_d among cheeses still allowed to use their max_d as height (`*max_d_unforced_set.rbegin()`).
        long long current_max_h_actual = max_min_d_in_forced;
        if (!max_d_unforced_set.empty()) {
            current_max_h_actual = std::max(current_max_h_actual, *max_d_unforced_set.rbegin());
        }

        // Update the minimum overall perimeter found so far.
        // The perimeter is calculated using the current total width and the actual maximum height.
        min_overall_perimeter = std::min(min_overall_perimeter, 2 * current_sum_w + 2 * current_max_h_actual);
    }

    std::cout << min_overall_perimeter << std::endl; // Output the final minimum perimeter
}

int main() {
    // Optimize C++ standard streams for competitive programming.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams,
    // potentially speeding up I/O operations.
    // std::cin.tie(NULL) prevents std::cout from flushing before std::cin reads input,
    // further optimizing I/O.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t; // Number of test cases
    std::cin >> t; // Read the number of test cases
    while (t--) { // Loop t times, solving each test case
        solve(); // Call the solve function for the current test case
    }

    return 0; // Indicate successful program execution
}

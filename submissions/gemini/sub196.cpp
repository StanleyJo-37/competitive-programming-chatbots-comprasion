#include <iostream> // Required for input/output operations (std::cin, std::cout, std::endl)
#include <vector>   // Required for using std::vector to store dynamic arrays
#include <algorithm> // Required for std::sort and std::max

// Function to solve a single test case
void solve() {
    // Declare integers n and k to store the length of the array and the operation parameter.
    int n, k;
    // Read n and k from standard input.
    std::cin >> n >> k;

    // Declare a vector 'a' of size n to store the input array elements.
    // Use long long for elements as a_i can be up to 10^9, and their sum can exceed 2^31-1.
    std::vector<long long> a(n);
    // Read n integers into the vector 'a'.
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    // Create 'k' groups of elements.
    // Elements a[i] and a[j] can be swapped if (i % k) == (j % k).
    // This means elements with the same remainder when divided by k belong to the same group
    // and can be freely rearranged among themselves.
    // We use a vector of vectors, where groups[m] will store all elements a[i] such that i % k == m.
    std::vector<std::vector<long long>> groups(k);
    for (int i = 0; i < n; ++i) {
        // Add the current element a[i] to its corresponding group (i % k).
        groups[i % k].push_back(a[i]);
    }

    // For each group, sort its elements in descending order.
    // This is a greedy step: to maximize the sum of k consecutive elements,
    // we want to pick the largest possible values for each position.
    // Since elements within a group can be freely swapped, we can always place
    // the largest available element from a group into a desired position.
    for (int i = 0; i < k; ++i) {
        // std::sort with rbegin() and rend() sorts in reverse (descending) order.
        std::sort(groups[i].rbegin(), groups[i].rend());
    }

    // Initialize max_score to 0. This will store the maximum sum found.
    // Use long long for max_score as the sum can be up to k * 10^9 (100 * 10^9 = 10^11).
    long long max_score = 0;

    // Iterate through all possible starting positions 'p' for a window of 'k' consecutive elements.
    // The window starts at index 'p' and ends at 'p + k - 1'.
    // The first possible starting index is 0.
    // The last possible starting index is n - k (to ensure there are 'k' elements remaining).
    for (int p = 0; p <= n - k; ++p) {
        // Initialize current_score for the sum of elements in the current window.
        long long current_score = 0;
        // Iterate 'j' from 0 to k-1 to cover all 'k' elements in the current window.
        for (int j = 0; j < k; ++j) {
            // The actual index in the original array for the j-th element in the window is (p + j).
            int original_array_idx = p + j;
            
            // Determine which group this element belongs to.
            // This is given by (original_array_idx % k).
            int group_id = original_array_idx % k;
            
            // Determine which position within its sorted group this element corresponds to.
            // For example, a[0] is the 0th element of group 0.
            // a[k] is the 1st element of group 0 (since it's the second element in that group).
            // This is given by (original_array_idx / k).
            int pos_in_group = original_array_idx / k;
            
            // Add the element from the sorted group to the current score.
            // Since groups are sorted descending, groups[group_id][pos_in_group]
            // gives the (pos_in_group)-th largest element from that group,
            // which is the optimal choice for that specific position in the array.
            current_score += groups[group_id][pos_in_group];
        }
        // Update max_score if the current window's sum is greater.
        max_score = std::max(max_score, current_score);
    }

    // Print the maximum score found for the current test case.
    std::cout << max_score << std::endl;
}

// Main function to handle multiple test cases
int main() {
    // Optimize C++ standard streams for faster input/output operations.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams.
    // std::cin.tie(NULL) prevents std::cout from flushing before std::cin reads input.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    // Declare an integer 't' to store the number of test cases.
    int t;
    // Read the number of test cases.
    std::cin >> t;
    // Loop 't' times, calling the solve() function for each test case.
    while (t--) {
        solve();
    }

    // Return 0 to indicate successful execution.
    return 0;
}

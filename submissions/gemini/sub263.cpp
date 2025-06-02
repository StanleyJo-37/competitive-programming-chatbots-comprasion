#include <iostream> // Required for input/output operations (cin, cout)
#include <vector>   // Required for using std::vector
#include <algorithm> // Required for std::is_sorted (though manual check is also fine and perhaps clearer for this specific logic)

// Function to solve a single test case
void solve() {
    int n; // Declare integer n for array length
    std::cin >> n; // Read n

    std::vector<int> odds;  // Vector to store odd numbers in their original relative order
    std::vector<int> evens; // Vector to store even numbers in their original relative order

    // Iterate through the input array to populate odds and evens vectors
    for (int i = 0; i < n; ++i) {
        int a_i; // Declare integer a_i for current element
        std::cin >> a_i; // Read a_i
        if (a_i % 2 != 0) { // Check if a_i is odd
            odds.push_back(a_i); // Add to odds vector
        } else { // a_i is even
            evens.push_back(a_i); // Add to evens vector
        }
    }

    // The core logic:
    // The problem states that elements a_i and a_{i+1} can be swapped if their sum is odd.
    // This means one must be odd and the other must be even.
    //
    // Implication 1: Two odd numbers cannot be swapped (sum is even).
    // Implication 2: Two even numbers cannot be swapped (sum is even).
    //
    // This leads to a critical observation:
    // The relative order of any two odd numbers in the array can never change.
    // If odd_A appears before odd_B in the initial array, odd_A will always appear before odd_B
    // in any configuration reachable by the allowed operations. This is because odd_A and odd_B
    // cannot directly swap, and an odd number can only swap with an even number. When an odd
    // number swaps with an even number, it effectively "moves past" it. But it cannot "move past"
    // another odd number.
    //
    // Similarly, the relative order of any two even numbers in the array can never change.
    //
    // Therefore, for the entire array to be sortable into non-decreasing order, two conditions
    // must be met:
    // 1. The subsequence of odd numbers (extracted in their original order) must already be sorted
    //    non-decreasingly.
    // 2. The subsequence of even numbers (extracted in their original order) must already be sorted
    //    non-decreasingly.
    //
    // If these two conditions hold, then the array can be sorted. This is because any odd number
    // can be moved past any even number, allowing the odd and even subsequences to be interleaved
    // in any desired way, as long as their internal relative orders are preserved. Since the
    // internal relative orders are already sorted, we can arrange them to form the fully sorted array.

    bool odds_sorted = true; // Flag to track if odd numbers subsequence is sorted
    // Check if the odds vector is sorted
    for (size_t i = 0; i + 1 < odds.size(); ++i) {
        if (odds[i] > odds[i+1]) { // If any element is greater than the next one
            odds_sorted = false; // Set flag to false
            break; // No need to check further
        }
    }

    bool evens_sorted = true; // Flag to track if even numbers subsequence is sorted
    // Check if the evens vector is sorted
    for (size_t i = 0; i + 1 < evens.size(); ++i) {
        if (evens[i] > evens[i+1]) { // If any element is greater than the next one
            evens_sorted = false; // Set flag to false
            break; // No need to check further
        }
    }

    // If both subsequences are sorted, print "Yes", otherwise print "No"
    if (odds_sorted && evens_sorted) {
        std::cout << "Yes\n";
    } else {
        std::cout << "No\n";
    }
}

int main() {
    // Optimize C++ standard streams for competitive programming
    // This unties cin/cout from stdio and disables synchronization with C standard streams,
    // which can significantly speed up I/O operations.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t; // Declare integer t for number of test cases
    std::cin >> t; // Read t

    // Loop through each test case
    while (t--) {
        solve(); // Call the solve function for each test case
    }

    return 0; // Indicate successful execution
}

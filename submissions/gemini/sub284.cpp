#include <iostream>
#include <vector>
#include <numeric>
#include <set>
#include <algorithm>

void solve() {
    int n, k;
    std::cin >> n >> k; // Read n (length of original array) and k (subarray length for beauty)

    std::set<int> unique_elements_set; // Use a set to store unique elements from array 'a'.
                                       // A set automatically handles uniqueness and keeps elements sorted.
    for (int i = 0; i < n; ++i) {
        int x;
        std::cin >> x; // Read elements of array 'a' one by one
        unique_elements_set.insert(x); // Insert into set. If element already exists, it's ignored.
    }

    // Convert the set of unique elements into a vector.
    // This is done for easier access and to determine the count of unique elements.
    std::vector<int> unique_elements(unique_elements_set.begin(), unique_elements_set.end());

    // A beautiful array 'b' with period 'k' must satisfy b[i] = b[i+k] for all valid i.
    // This implies that the array 'b' is formed by repeating a block of 'k' elements (p_0, p_1, ..., p_{k-1}).
    // All elements from the original array 'a' must be present in this repeating block.
    // Therefore, the number of unique elements in 'a' cannot exceed 'k'.
    if (unique_elements.size() > k) {
        std::cout << -1 << std::endl; // If it does, it's impossible to create such a beautiful array.
        return;
    }

    // Construct the repeating block 'P' of length 'k'.
    // This block will be used to generate the beautiful array.
    std::vector<int> p_block;
    // First, add all unique elements from the original array 'a' to 'p_block'.
    for (int val : unique_elements) {
        p_block.push_back(val);
    }
    // If 'p_block' has fewer than 'k' elements, fill the remaining spots.
    // The problem states inserted integers must be between 1 and n. '1' is a valid and simple choice.
    while (p_block.size() < k) {
        p_block.push_back(1);
    }

    // Determine the length 'm' of the beautiful array 'b'.
    // The problem states 'n <= m <= 10^4' and we don't need to minimize 'm'.
    // A simple choice is to repeat the 'p_block' 'n' times.
    // The length will be k * n.
    // Since 1 <= k <= n <= 100, the maximum length is 100 * 100 = 10000, which satisfies m <= 10^4.
    // Also, k * n >= n (since k >= 1), satisfying m >= n.
    // This construction guarantees that all elements of 'a' are present in 'b' (as 'p_block' contains them),
    // and repeating 'p_block' 'n' times provides enough length for 'a' to be a subsequence of 'b'.
    int m = k * n;
    std::cout << m << std::endl; // Print the length of the beautiful array

    // Print the beautiful array 'b' by repeating 'p_block' 'n' times.
    for (int i = 0; i < n; ++i) { // Repeat 'n' times
        for (int j = 0; j < k; ++j) { // Print elements of 'p_block'
            std::cout << p_block[j] << (i == n - 1 && j == k - 1 ? "" : " "); // Print space unless it's the very last element
        }
    }
    std::cout << std::endl; // Newline after printing the array
}

int main() {
    // Optimize C++ standard streams for faster input/output.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t; // Read the number of test cases
    while (t--) {
        solve(); // Call the solve function for each test case
    }

    return 0;
}

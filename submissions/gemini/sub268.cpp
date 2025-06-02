#include <iostream> // Required for input/output operations (std::cin, std::cout)
#include <vector>   // Required for using std::vector to store the array and prefix/suffix counts
#include <algorithm> // Required for std::max

// Function to solve a single test case
void solve() {
    int n;
    // Read the length of the array
    std::cin >> n;
    std::vector<int> a(n);
    // Read the elements of the array
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    // Calculate the initial number of inversions in the array.
    // An inversion is a pair (i, j) such that i < j and a[i] > a[j].
    // In a binary array, this means a[i] = 1 and a[j] = 0.
    // We can count this by iterating through the array and maintaining a count of 1s encountered so far.
    // When a 0 is encountered, it forms an inversion with all 1s seen before it.
    long long initial_inversions = 0;
    long long ones_count = 0; // Counts 1s encountered from the beginning of the array
    for (int i = 0; i < n; ++i) {
        if (a[i] == 1) {
            ones_count++;
        } else { // a[i] == 0
            initial_inversions += ones_count;
        }
    }

    // Initialize max_inversions with the initial count (case of no operation)
    long long max_inversions = initial_inversions;

    // Precompute prefix_ones: prefix_ones[i] stores the count of 1s in a[0...i-1].
    // This helps to quickly find the number of 1s before any given index k.
    std::vector<long long> prefix_ones(n);
    long long current_ones_prefix = 0;
    for (int i = 0; i < n; ++i) {
        prefix_ones[i] = current_ones_prefix; // Store count of 1s before index i
        if (a[i] == 1) {
            current_ones_prefix++;
        }
    }

    // Precompute suffix_zeros: suffix_zeros[i] stores the count of 0s in a[i+1...n-1].
    // This helps to quickly find the number of 0s after any given index k.
    std::vector<long long> suffix_zeros(n);
    long long current_zeros_suffix = 0;
    for (int i = n - 1; i >= 0; --i) {
        suffix_zeros[i] = current_zeros_suffix; // Store count of 0s after index i
        if (a[i] == 0) {
            current_zeros_suffix++;
        }
    }

    // Iterate through each element of the array to consider flipping it.
    // For each element a[k], calculate the new number of inversions if it's flipped.
    for (int k = 0; k < n; ++k) {
        long long current_inversions_after_flip = initial_inversions;
        long long change_in_inversions = 0;

        if (a[k] == 0) { // If a[k] is 0, we consider flipping it to 1.
            // Original state: (..., 1, ..., 0_k, ..., 0, ...)
            // New state:     (..., 1, ..., 1_k, ..., 0, ...)
            // Effect on inversions:
            // 1. Pairs (i, k) where i < k: If a[i]=1, (a[i], a[k]) was (1,0) (an inversion).
            //    After flip, it becomes (1,1) (not an inversion). So, we lose prefix_ones[k] inversions.
            // 2. Pairs (k, j) where k < j: If a[j]=0, (a[k], a[j]) was (0,0) (not an inversion).
            //    After flip, it becomes (1,0) (an inversion). So, we gain suffix_zeros[k] inversions.
            change_in_inversions = suffix_zeros[k] - prefix_ones[k];
        } else { // a[k] == 1, we consider flipping it to 0.
            // Original state: (..., 1, ..., 1_k, ..., 0, ...)
            // New state:     (..., 1, ..., 0_k, ..., 0, ...)
            // Effect on inversions:
            // 1. Pairs (i, k) where i < k: If a[i]=1, (a[i], a[k]) was (1,1) (not an inversion).
            //    After flip, it becomes (1,0) (an inversion). So, we gain prefix_ones[k] inversions.
            // 2. Pairs (k, j) where k < j: If a[j]=0, (a[k], a[j]) was (1,0) (an inversion).
            //    After flip, it becomes (0,0) (not an inversion). So, we lose suffix_zeros[k] inversions.
            change_in_inversions = prefix_ones[k] - suffix_zeros[k];
        }
        // Update the maximum inversions found so far
        max_inversions = std::max(max_inversions, current_inversions_after_flip + change_in_inversions);
    }

    // Output the maximum number of inversions
    std::cout << max_inversions << std::endl;
}

int main() {
    // Optimize C++ standard streams for competitive programming.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams,
    // which can speed up I/O operations.
    // std::cin.tie(NULL) prevents std::cout from being flushed before each std::cin operation,
    // further speeding up I/O.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    // Read the number of test cases
    std::cin >> t;
    // Process each test case
    while (t--) {
        solve();
    }

    return 0;
}

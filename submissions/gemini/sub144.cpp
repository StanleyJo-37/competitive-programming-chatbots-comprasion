#include <iostream> // Required for input/output operations (std::cin, std::cout)
#include <vector>   // Required for using std::vector to store the array and prefix XOR sums
#include <numeric>  // Not strictly necessary for this solution, but often useful for algorithms like std::accumulate

// Function to solve a single test case
void solve() {
    int n;
    std::cin >> n; // Read the number of elements in the array

    std::vector<int> a(n); // Declare a vector to store the array elements
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i]; // Read array elements
    }

    // Calculate prefix XOR sums.
    // pref[k] will store the XOR sum of a[0] ^ a[1] ^ ... ^ a[k-1].
    // pref[0] is initialized to 0, representing the XOR sum of an empty prefix.
    std::vector<int> pref(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        pref[i + 1] = pref[i] ^ a[i];
    }

    // Case 1: The total XOR sum of the entire array is 0.
    // The total XOR sum of the array a[0...n-1] is pref[n].
    // If pref[n] is 0, we can always split the array into two parts:
    // 1. The first element: a[0]. Its XOR sum is a[0].
    // 2. The rest of the array: a[1...n-1]. Its XOR sum is (a[0] ^ ... ^ a[n-1]) ^ a[0] = pref[n] ^ a[0].
    // Since pref[n] is 0, the second part's XOR sum becomes 0 ^ a[0] = a[0].
    // So, both parts have an XOR sum equal to a[0], making them equal.
    // Since the problem requires at least 2 elements remaining, and n >= 2, this split is always valid.
    // Thus, if pref[n] == 0, the answer is "YES".
    if (pref[n] == 0) {
        std::cout << "YES\n";
        return; // Solution found for this test case
    }

    // Case 2: The total XOR sum of the array is not 0.
    // If we want to make k elements equal to some value X, and the total XOR sum pref[n] is not 0,
    // then k must be an odd number.
    // (Because if k were even, the XOR sum of k identical values X would be 0, which contradicts pref[n] != 0).
    // If k is odd, then the XOR sum of k identical values X is X itself.
    // Therefore, the target value X must be equal to pref[n].
    // We need to find a partition into k (odd) segments, each XORing to pref[n].
    // The smallest odd k that is also >= 2 is k=3.
    // We check if it's possible to partition the array into exactly 3 segments,
    // each having an XOR sum equal to pref[n].
    // Let the three segments be a[0...i], a[i+1...j], and a[j+1...n-1].
    // Their respective XOR sums are:
    // S1 = pref[i+1]
    // S2 = pref[j+1] ^ pref[i+1]
    // S3 = pref[n] ^ pref[j+1]
    // We need S1 = S2 = S3 = pref[n].
    //
    // From S1 = pref[n]: pref[i+1] must be equal to pref[n].
    // From S2 = pref[n] and S1 = pref[n]: (pref[j+1] ^ pref[i+1]) == pref[n]
    //   => (pref[j+1] ^ pref[n]) == pref[n]
    //   => pref[j+1] == 0.
    // From S3 = pref[n] and pref[n] = pref[n]: (pref[n] ^ pref[j+1]) == pref[n]
    //   => (pref[n] ^ pref[j+1]) == pref[n]
    //   => pref[j+1] == 0.
    //
    // So, the conditions for a 3-segment partition are:
    // 1. There exist indices i and j such that 0 <= i < j < n-1.
    //    (This ensures three non-empty segments: a[0...i], a[i+1...j], a[j+1...n-1]).
    // 2. pref[i+1] == pref[n] (XOR sum of first segment equals target_X).
    // 3. pref[j+1] == 0 (XOR sum of second and third segments will also equal target_X).
    //
    // If a solution with k > 3 odd segments exists, it implies that we can find
    // `pref[i_1] = X`, `pref[i_2] = 0`, `pref[i_3] = X`, etc.
    // In such a case, the first two cut points `i_1` and `i_2` would satisfy the conditions
    // for a 3-segment solution (i.e., `pref[i_1] = X` and `pref[i_2] = 0`).
    // Thus, checking for k=3 is sufficient.

    bool possible = false;
    int target_X = pref[n]; // The target value for each segment's XOR sum

    // Iterate through all possible end points for the first segment (0-indexed `i`).
    // `i` can go from 0 up to `n-3` to leave at least two elements for the next two segments.
    for (int i = 0; i < n - 2; ++i) {
        // Check if the XOR sum of the first segment (a[0...i], which is pref[i+1]) equals target_X.
        if (pref[i + 1] == target_X) {
            // Iterate through all possible end points for the second segment (0-indexed `j`).
            // `j` must be greater than `i` and can go up to `n-2` to leave at least one element for the third segment.
            for (int j = i + 1; j < n - 1; ++j) {
                // Check if the XOR sum of the prefix up to `j` (pref[j+1]) is 0.
                // As derived above, this condition ensures that the second and third segments also XOR to target_X.
                if (pref[j + 1] == 0) {
                    possible = true; // Found a valid partition
                    break;           // Exit inner loop
                }
            }
        }
        if (possible) {
            break; // Exit outer loop if a solution is found
        }
    }

    if (possible) {
        std::cout << "YES\n";
    } else {
        std::cout << "NO\n";
    }
}

int main() {
    // Optimize C++ standard streams for faster input/output.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams.
    // std::cin.tie(NULL) prevents std::cout from flushing before std::cin reads input.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t; // Read the number of test cases
    while (t--) {
        solve(); // Solve each test case
    }

    return 0; // Indicate successful execution
}
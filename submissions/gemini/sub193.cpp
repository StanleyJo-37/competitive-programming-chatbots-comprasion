#include <iostream> // Required for input/output operations (cin, cout)
#include <vector>   // Required for using std::vector to store the array elements
#include <numeric>  // Not strictly needed for this solution, but often useful for sums (e.g., std::accumulate)
#include <algorithm> // Required for std::sort (though not strictly necessary as input is pre-sorted)

void solve() {
    int n; // Declare an integer variable 'n' to store the size of the array
    std::cin >> n; // Read the value of 'n' from standard input

    std::vector<int> a(n); // Declare a std::vector named 'a' of size 'n' to store the array elements
    for (int i = 0; i < n; ++i) { // Loop 'n' times to read each element of the array
        std::cin >> a[i]; // Read the i-th element into the vector 'a'
    }

    // The problem statement guarantees that the input array 'a' is already sorted
    // in non-decreasing order: 1 <= a_1 <= a_2 <= ... <= a_n <= 100.
    // This means a[0] is the smallest element and a[n-1] is the largest element.

    // An array is defined as "ugly" if it contains at least one element which is
    // equal to the sum of all elements before it. Otherwise, it is "beautiful".

    // Case 1: All elements in the array are identical.
    // If a[0] == a[n-1], it implies that all elements in the sorted array 'a' are the same.
    // For example, if a = [X, X, ..., X].
    // Any reordering of such an array will still result in [X, X, ..., X].
    // In this configuration, the second element (X) will always be equal to the sum of
    // elements before it (which is X). This satisfies the "ugly" condition.
    // Therefore, if all elements are identical, it's impossible to reorder it to be beautiful.
    if (a[0] == a[n - 1]) {
        std::cout << "NO\n"; // Print "NO" as it's impossible to form a beautiful array.
    } else {
        // Case 2: Not all elements in the array are identical.
        // This means a[0] < a[n-1] (since the array is sorted).
        // In this scenario, we can always construct a beautiful array.
        // A simple and effective strategy is to place the largest element (a[n-1])
        // at the beginning of the reordered array, followed by the rest of the elements
        // (a[0] through a[n-2]) in their original sorted order.
        // Let the reordered array be 'b'. The proposed construction is:
        // b = [a[n-1], a[0], a[1], ..., a[n-2]]

        // Let's verify why this construction guarantees a beautiful array:
        // Let S_k be the sum of the first k elements of the reordered array 'b'.
        // We need to ensure that b_k != S_{k-1} for all k from 2 to n.

        // For k = 1:
        // b_1 = a[n-1]. The sum of elements before it is 0 (empty sum).
        // Since a_i >= 1, a[n-1] >= 1, so b_1 is never 0. This element never makes it ugly.

        // For k = 2:
        // b_2 = a[0].
        // S_1 = b_1 = a[n-1].
        // We need to check if b_2 == S_1, i.e., if a[0] == a[n-1].
        // We are in the 'else' block, which means a[0] != a[n-1].
        // Specifically, since 'a' is sorted, a[0] < a[n-1].
        // Therefore, b_2 != S_1. This element does not make the array ugly.

        // For k >= 3:
        // b_k corresponds to a[k-2] from the original sorted array (e.g., b_3 is a[1], b_4 is a[2], etc.).
        // S_{k-1} is the sum of elements before b_k in the reordered array:
        // S_{k-1} = b_1 + b_2 + ... + b_{k-1}
        //         = a[n-1] + a[0] + a[1] + ... + a[k-3].
        // (Note: a[k-3] is the last element in the sum, which exists because k >= 3 implies k-3 >= 0).

        // Now, let's compare b_k and S_{k-1}:
        // 1. Value of S_{k-1}:
        //    Since all elements a_i are positive (a_i >= 1), the sum S_{k-1} will be:
        //    S_{k-1} = a[n-1] + a[0] + a[1] + ... + a[k-3]
        //    The smallest possible value for this sum (when k >= 3) is a[n-1] + a[0] (when k=3).
        //    Since a[0] >= 1, we have S_{k-1} >= a[n-1] + 1.

        // 2. Value of b_k:
        //    b_k = a[k-2].
        //    Since the original array 'a' is sorted non-decreasingly, a[k-2] is an element
        //    that is less than or equal to the largest element a[n-1].
        //    So, b_k = a[k-2] <= a[n-1].

        // Combining these observations:
        // We have b_k <= a[n-1] AND S_{k-1} >= a[n-1] + 1.
        // This implies b_k <= a[n-1] < a[n-1] + 1 <= S_{k-1}.
        // Therefore, b_k can never be equal to S_{k-1} for any k >= 3.

        // Since all cases (k=1, k=2, k>=3) are covered and none result in the ugly condition,
        // this construction always yields a beautiful array when not all elements are identical.

        std::cout << "YES\n"; // Print "YES" indicating a beautiful array can be formed.
        std::cout << a[n - 1]; // Print the largest element first.
        for (int i = 0; i < n - 1; ++i) { // Loop through the remaining elements (from a[0] to a[n-2]).
            std::cout << " " << a[i]; // Print each remaining element, separated by a space.
        }
        std::cout << "\n"; // Print a newline character to end the output for this test case.
    }
}

int main() {
    // Optimize C++ standard streams for competitive programming.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams,
    // potentially speeding up I/O operations by not synchronizing with C's stdio.
    // std::cin.tie(NULL) prevents std::cout from flushing before std::cin reads input,
    // which can further improve performance for interactive problems or those with large I/O.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t; // Declare an integer variable 't' to store the number of test cases.
    std::cin >> t; // Read the value of 't' from standard input.

    while (t--) { // Loop 't' times, decrementing 't' in each iteration.
        solve(); // Call the 'solve' function for each test case.
    }

    return 0; // Indicate successful program execution.
}

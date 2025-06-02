#include <iostream> // Required for input/output operations (std::cin, std::cout, std::endl)
#include <vector>   // Required for std::vector to store the sequence
#include <set>      // Required for std::set to count distinct elements
#include <numeric>  // Not strictly necessary for this solution, but often useful for algorithms
#include <algorithm> // Not strictly necessary for this solution, but often useful for algorithms

void solve() {
    int n; // Declare an integer variable 'n' to store the size of the cyclic sequence.
    std::cin >> n; // Read the value of 'n' from standard input.

    std::vector<int> a(n); // Declare a vector 'a' of size 'n' to store the sequence elements.
    std::set<int> distinct_elements; // Declare a set 'distinct_elements' to store unique elements and count them.

    // Loop through 'n' elements to read them and insert into the set.
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i]; // Read the i-th element into the vector.
        distinct_elements.insert(a[i]); // Insert the element into the set. Sets only store unique values.
    }

    // Case 1: If the sequence has only one element.
    // As per the problem statement, "in a ring of size 1, its only element isn't considered adjacent to itself".
    // This means it won't be immediately erased. Muxii can perform 1 operation to erase it.
    if (n == 1) {
        std::cout << 1 << std::endl; // Output 1 operation.
        return; // End the function for this test case.
    }

    // Case 2: If the sequence has more than one element (n > 1).
    // We want to maximize Muxii's operations. This is equivalent to minimizing the number of
    // automatic erasures. An automatic erasure occurs if Muxii removes an element 'x', and
    // its two neighbors 'L' and 'R' become adjacent and 'L == R'.
    // Muxii's optimal strategy is to always remove an element whose neighbors are NOT equal, if one exists.
    // This costs 1 operation and incurs 0 automatic erasures.
    // If all elements in the current sequence have equal neighbors, Muxii must remove one,
    // which will incur 1 automatic erasure. This is the only way an automatic erasure happens.

    // A sequence has all its elements with equal neighbors (i.e., all elements are "critical")
    // if and only if it is of the form [X, Y, X, Y, ...] (meaning a[j] == a[(j+2)%current_n] for all j)
    // AND its current length (current_n) is even. If current_n is odd, it's impossible for all elements to be critical.

    // Get the number of distinct elements in the initial sequence.
    int k = distinct_elements.size();

    // If there are exactly two distinct elements (k == 2).
    // Due to the problem constraints (a_i != a_{i+1} and a_n != a_1 for n > 1),
    // if there are only two distinct elements (say X and Y), the sequence must alternate: [X, Y, X, Y, ...].
    // In this scenario, regardless of whether 'n' is even or odd, Muxii will be forced to incur exactly one automatic erasure.
    // For example:
    // - If n is even (e.g., [1, 2, 1, 2]): All elements are critical. Muxii removes one, 1 auto-erasure. Remaining n-2 elements are distinct. Total n-1 ops.
    // - If n is odd (e.g., [1, 2, 1, 2, 1]): There are non-critical elements (e.g., a[0] and a[n-1]). Muxii removes one (0 auto-erasure).
    //   The remaining n-1 elements form an [X, Y, X, Y, ...] pattern of even length. All elements in this new sequence are critical.
    //   Muxii must remove one, incurring 1 auto-erasure. Total 1 + (n-1-1) = n-1 ops.
    // So, if k == 2, the maximum operations is n-1.
    if (k == 2) {
        std::cout << n - 1 << std::endl;
    } else {
        // If k != 2, it means either k == n (all elements are distinct) or k > 2 (more than two distinct elements).
        // If k == n (all elements are distinct):
        //   Then a[j-1] != a[j+1] for any j. So all elements are non-critical. Muxii can remove all 'n' elements
        //   one by one without any automatic erasures. Total 'n' operations.
        // If k > 2 (more than two distinct elements):
        //   The sequence cannot be of the form [X, Y, X, Y, ...]. Therefore, there must be at least one
        //   element whose neighbors are NOT equal (a non-critical element). Muxii can always choose to remove
        //   such a non-critical element. This costs 1 operation and incurs 0 automatic erasures.
        //   The sequence becomes n-1 elements. Muxii can continue this process. Since Muxii plays optimally,
        //   they will always choose an operation that avoids an automatic erasure if possible.
        //   With k > 2, it's always possible to avoid automatic erasures throughout the process.
        //   Total 'n' operations.
        std::cout << n << std::endl;
    }
}

int main() {
    // Optimize C++ standard streams for competitive programming.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams,
    // potentially speeding up I/O operations.
    std::ios_base::sync_with_stdio(false);
    // std::cin.tie(NULL) prevents std::cout from flushing before std::cin reads input,
    // further speeding up I/O.
    std::cin.tie(NULL);

    int t; // Declare an integer variable 't' to store the number of test cases.
    std::cin >> t; // Read the number of test cases.
    while (t--) { // Loop 't' times, decrementing 't' in each iteration.
        solve(); // Call the solve function for each test case.
    }

    return 0; // Indicate successful execution.
}

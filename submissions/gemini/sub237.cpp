#include <iostream> // Required for input/output operations (cin, cout)
#include <vector>   // Required for using std::vector to store problem complexities
#include <algorithm> // Required for std::sort (though problem states arrays are already sorted, it's good practice to include if sorting was needed)

int main() {
    // Optimize C++ standard streams for competitive programming.
    // This unties cin/cout from C standard streams and disables synchronization
    // with C stdio, which can significantly speed up I/O operations.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, m; // Declare variables for the number of required problems (n) and prepared problems (m)
    std::cin >> n >> m; // Read n and m from standard input

    std::vector<int> a(n); // Declare a vector 'a' of size n to store required complexities
    // Read the n required complexities into vector 'a'.
    // The problem statement guarantees a_1 < a_2 < ... < a_n, so 'a' is already sorted.
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    std::vector<int> b(m); // Declare a vector 'b' of size m to store prepared complexities
    // Read the m prepared complexities into vector 'b'.
    // The problem statement guarantees b_1 <= b_2... <= b_m, so 'b' is already sorted.
    for (int i = 0; i < m; ++i) {
        std::cin >> b[i];
    }

    int satisfied_requirements = 0; // Counter for how many 'a' requirements have been met
    int a_ptr = 0; // Pointer for iterating through the 'a' (required complexities) vector
    int b_ptr = 0; // Pointer for iterating through the 'b' (prepared complexities) vector

    // Use a two-pointer approach to find the maximum number of 'a' requirements
    // that can be satisfied by 'b' problems.
    // Both 'a' and 'b' are sorted in ascending order.
    while (a_ptr < n && b_ptr < m) {
        // If the current prepared problem b[b_ptr] has complexity
        // greater than or equal to the current required complexity a[a_ptr],
        // it means b[b_ptr] can be simplified to satisfy a[a_ptr].
        // We greedily use b[b_ptr] for a[a_ptr] because:
        // 1. We satisfy the smallest current requirement a[a_ptr].
        // 2. By using the smallest available b[b_ptr] that is sufficient,
        //    we leave larger b problems for potentially larger future a requirements,
        //    maximizing our chances of satisfying more requirements.
        if (b[b_ptr] >= a[a_ptr]) {
            satisfied_requirements++; // Increment the count of satisfied requirements
            a_ptr++; // Move to the next required complexity
            b_ptr++; // Move to the next prepared problem (as b[b_ptr] is now used)
        } else {
            // If b[b_ptr] is too small for a[a_ptr] (b[b_ptr] < a[a_ptr]),
            // then b[b_ptr] cannot satisfy a[a_ptr].
            // Since 'a' is sorted, b[b_ptr] also cannot satisfy any subsequent
            // required complexity a[a_ptr+1], a[a_ptr+2], etc., because they are
            // all greater than or equal to a[a_ptr].
            // Therefore, b[b_ptr] is useless for any remaining requirement.
            // We discard b[b_ptr] and move to the next prepared problem.
            b_ptr++;
        }
    }

    // The minimum number of new problems George needs to come up with
    // is the total number of required problems (n) minus the number of
    // requirements that were satisfied by existing problems.
    std::cout << n - satisfied_requirements << std::endl;

    return 0; // Indicate successful execution
}
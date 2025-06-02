#include <iostream> // Required for input/output operations (cin, cout)
#include <vector>   // Required for using std::vector

void solve() {
    int n; // Declare an integer variable 'n' to store the size of the array.
    std::cin >> n; // Read the value of 'n' from standard input.

    // Declare a vector 'a' of size 'n + 1' to store the array elements.
    // Using 'n + 1' size allows for 1-based indexing, matching the problem description.
    std::vector<int> a(n + 1); 
    for (int i = 1; i <= n; ++i) { // Loop from 1 to 'n' to read array elements.
        std::cin >> a[i]; // Read each element into the vector.
    }

    long long count = 0; // Declare a long long variable 'count' to store the total number of good subarrays.
                         // 'long long' is used because the maximum possible count can exceed the capacity of 'int'
                         // (N * (N+1) / 2 for N=2e5 is approx 2e10).

    int r = 0; // Initialize the right pointer 'r'. It represents the rightmost index of the current good subarray.
               // 'r' is initialized to 0, effectively meaning no elements are included yet.

    // Iterate with the left pointer 'l' from 1 to 'n'.
    // For each 'l', we are trying to find all good subarrays starting at 'l'.
    for (int l = 1; l <= n; ++l) {
        // The right pointer 'r' should never be less than 'l - 1'.
        // If 'l' has advanced past 'r' (meaning the previous good subarray ended before 'l'),
        // we reset 'r' to 'l - 1'. This ensures that 'r + 1' will correctly start checking from 'l'.
        if (r < l - 1) {
            r = l - 1;
        }

        // Extend the right pointer 'r' as far as possible while maintaining the "good" property.
        // The condition for a subarray [a_l, ..., a_k] to be good is a_i >= i for all i from 1 to k-l+1.
        // For the next element a_{r+1} (which would be the (r+1 - l + 1)-th element in the subarray),
        // the condition is a_{r+1} >= (r+1 - l + 1).
        while (r < n && a[r + 1] >= (r + 1) - l + 1) {
            r++; // If the condition holds, extend 'r' to include the next element.
        }

        // After the while loop, 'r' is the maximum index such that the subarray [a_l, ..., a_r] is good.
        // All subarrays [a_l, ..., a_k] where 'l <= k <= r' are also good.
        // The number of such subarrays is 'r - l + 1'.
        count += (r - l + 1); // Add this count to the total.
    }

    std::cout << count << std::endl; // Print the total count of good subarrays.
}

int main() {
    // Optimize C++ standard streams for competitive programming.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams,
    // potentially speeding up I/O operations.
    // std::cin.tie(NULL) prevents std::cout from flushing before std::cin reads,
    // further speeding up I/O.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t; // Declare an integer variable 't' to store the number of test cases.
    std::cin >> t; // Read the number of test cases.
    while (t--) { // Loop 't' times, once for each test case.
        solve(); // Call the 'solve' function to handle each test case.
    }

    return 0; // Indicate successful program execution.
}

#include <iostream> // Required for input/output operations (std::cin, std::cout, std::endl)
#include <vector>   // Required for using std::vector, a dynamic array
#include <algorithm> // Required for sorting algorithms (std::sort)

// Function to solve a single test case
void solve() {
    // Declare an integer variable 'n' to store the number of daughters/necklaces/bracelets.
    int n;
    // Read the value of 'n' from standard input.
    std::cin >> n;

    // Declare two std::vector<int> named 'a' and 'b' of size 'n'.
    // 'a' will store the brightnesses of necklaces.
    // 'b' will store the brightnesses of bracelets.
    std::vector<int> a(n);
    std::vector<int> b(n);

    // Loop to read 'n' distinct necklace brightnesses into vector 'a'.
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    // Loop to read 'n' distinct bracelet brightnesses into vector 'b'.
    for (int i = 0; i < n; ++i) {
        std::cin >> b[i];
    }

    // Sort both vectors 'a' and 'b' in ascending order.
    // The core idea behind this solution is that if we sort both sets of brightnesses
    // (necklaces and bracelets) in ascending order, and then pair the i-th smallest
    // necklace brightness with the i-th smallest bracelet brightness, the resulting
    // sums will be strictly increasing and thus distinct.
    // Proof: Let a_1 < a_2 < ... < a_n be the sorted necklace brightnesses,
    // and b_1 < b_2 < ... < b_n be the sorted bracelet brightnesses.
    // For any i < j, we have a_i < a_j and b_i < b_j.
    // Therefore, a_i + b_i < a_j + b_j. This guarantees all sums are distinct.
    std::sort(a.begin(), a.end());
    std::sort(b.begin(), b.end());

    // Print the sorted necklace brightnesses. These will be the x_i values.
    // Each number is followed by a space, except for the last one.
    for (int i = 0; i < n; ++i) {
        std::cout << a[i] << (i == n - 1 ? "" : " ");
    }
    // Print a newline character to move to the next line for the bracelet brightnesses.
    std::cout << std::endl;

    // Print the sorted bracelet brightnesses. These will be the y_i values.
    // Each number is followed by a space, except for the last one.
    for (int i = 0; i < n; ++i) {
        std::cout << b[i] << (i == n - 1 ? "" : " ");
    }
    // Print a newline character after printing all y_i values.
    std::cout << std::endl;
}

int main() {
    // Optimize C++ standard streams for faster input/output operations.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams.
    // std::cin.tie(NULL) prevents std::cout from flushing before each std::cin.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    // Declare an integer variable 't' to store the number of test cases.
    int t;
    // Read the value of 't' from standard input.
    std::cin >> t;

    // Loop 't' times, calling the 'solve()' function for each test case.
    while (t--) {
        solve();
    }

    // Return 0 to indicate successful program execution.
    return 0;
}

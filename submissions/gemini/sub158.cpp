#include <iostream> // Required for input/output operations (std::cin, std::cout)
#include <string>   // Required for string manipulation (std::string)
#include <vector>   // Not strictly necessary for this solution, but often useful

// Function to solve a single test case
void solve() {
    int n; // Declare integer N for string length
    std::cin >> n; // Read N
    std::string a, b; // Declare binary strings A and B
    std::cin >> a >> b; // Read strings A and B

    // Check if string A consists of all '0's
    bool is_a_all_zeros = true;
    for (char c : a) {
        if (c == '1') {
            is_a_all_zeros = false; // Found a '1', so not all zeros
            break;
        }
    }

    // The core logic:
    // The operation (x, y) -> (x^y, x^y) has specific properties.
    // 1. If A[i] = 0 and A[i+1] = 0: (0,0) -> (0,0). The pair remains 00.
    //    This means if a segment is all zeros, it will remain all zeros.
    // 2. If A[i] = 1 and A[i+1] = 1: (1,1) -> (0,0). The pair becomes 00.
    // 3. If A[i] != A[i+1] (i.e., 01 or 10): (0,1) -> (1,1) or (1,0) -> (1,1). The pair becomes 11.

    // Case 1: String A is "00...0" (all zeros).
    // If A is all zeros, any operation on (0,0) results in (0,0).
    // This means A cannot change from "00...0".
    // Therefore, if A is "00...0", it can only be transformed into B if B is also "00...0".
    if (is_a_all_zeros) {
        // Check if B is also all zeros
        bool is_b_all_zeros = true;
        for (char c : b) {
            if (c == '1') {
                is_b_all_zeros = false;
                break;
            }
        }
        if (is_b_all_zeros) {
            std::cout << "YES\n"; // A is 00...0 and B is 00...0
        } else {
            std::cout << "NO\n"; // A is 00...0 but B is not
        }
    } 
    // Case 2: String A is NOT "00...0".
    // This means A contains at least one '1'.
    // If A is "11...1" (all ones):
    // An operation on (1,1) results in (0,0). For N > 2, this changes A from all ones
    // to a string like "001...1", which now contains both '0's and '1's.
    // If A contains both '0's and '1's (e.g., "010", "0011"):
    // This means there is at least one adjacent pair (A[i], A[i+1]) where A[i] != A[i+1] (e.g., "01" or "10").
    // Such a pair can be transformed into "11". A "11" pair can then be transformed into "00".
    // This flexibility (being able to create "11" from "01"/"10", and "00" from "11")
    // allows for sufficient manipulation. It is a known property for this type of problem
    // that if the string is not all zeros, it can be transformed into any other string B.
    // The only exception is the "all zeros" case, which is handled above.
    else {
        std::cout << "YES\n";
    }
}

int main() {
    // Optimize C++ standard streams for competitive programming.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams,
    // potentially speeding up I/O.
    // std::cin.tie(NULL) prevents std::cout from flushing before std::cin reads,
    // further speeding up I/O.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t; // Declare integer T for the number of test cases
    std::cin >> t; // Read T
    while (t--) { // Loop T times
        solve(); // Call the solve function for each test case
    }

    return 0; // Indicate successful execution
}

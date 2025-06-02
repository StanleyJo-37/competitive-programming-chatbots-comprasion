#include <iostream> // Required for input/output operations (std::cin, std::cout)

// Function to solve a single query
void solve() {
    int u, v; // Declare variables for the start and end vertices
    std::cin >> u >> v; // Read u and v for the current query

    // Condition 1: Cannot travel to a smaller vertex.
    // In the Infinite Zoo, edges are from u to u+x where x > 0 (since v must be a submask of u,
    // and if v=0, u+v=u, but the problem implies movement, and typically x>0 for "travel").
    // If u is strictly greater than v, it's impossible to reach v from u because all moves
    // result in a strictly larger vertex (u+x > u for x > 0).
    // If u == v, it's possible (0 steps), which will be handled by the bitwise check.
    if (u > v) {
        std::cout << "NO\n"; // Output "NO" and a newline
        return; // End function for this query
    }

    // Condition 2: Check bitwise prefix popcounts.
    // This is the core condition for reachability in this type of bit manipulation problem.
    // For u to reach v, for every bit position k (from LSB to MSB),
    // the number of set bits in u up to position k must be greater than or equal to
    // the number of set bits in v up to position k.
    // Let's maintain prefix popcounts for u and v.
    int u_prefix_popcount = 0; // Accumulator for set bits in u from bit 0 up to current bit k
    int v_prefix_popcount = 0; // Accumulator for set bits in v from bit 0 up to current bit k

    // Iterate through bit positions from 0 (Least Significant Bit) to 29 (Most Significant Bit).
    // The maximum value for u, v is less than 2^30, so bits up to position 29 are relevant.
    for (int k = 0; k < 30; ++k) {
        // Check if the k-th bit is set in u using bitwise right shift and AND operation.
        if ((u >> k) & 1) {
            u_prefix_popcount++; // Increment u's prefix popcount if bit k is set
        }
        // Check if the k-th bit is set in v.
        if ((v >> k) & 1) {
            v_prefix_popcount++; // Increment v's prefix popcount if bit k is set
        }

        // If at any point, u's accumulated prefix popcount is less than v's,
        // it means u does not have enough "lower" bits (including bit k) to form
        // the "lower" bits of v, or to generate necessary carries to form higher bits of v.
        // This implies it's impossible to reach v.
        // This condition is necessary because setting a bit at position k in v that is 0 in u
        // requires a carry from a lower position. This carry "consumes" a set bit from a lower position.
        // If u doesn't have enough set bits in its prefix to cover v's prefix and generate carries,
        // then it's impossible.
        if (u_prefix_popcount < v_prefix_popcount) {
            std::cout << "NO\n"; // Output "NO"
            return; // End function for this query as it's already determined to be impossible
        }
    }

    // If both conditions are met (u <= v, and the prefix popcount condition holds for all bits),
    // then it is possible to travel from u to v.
    // The sufficiency of this condition can be proven by a constructive greedy strategy.
    std::cout << "YES\n"; // Output "YES"
}

int main() {
    // Optimize C++ standard streams for faster input/output.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams,
    // which can speed up I/O operations.
    std::ios_base::sync_with_stdio(false);
    // std::cin.tie(NULL) unties std::cin from std::cout, meaning std::cin will not flush
    // std::cout before reading input, further speeding up I/O.
    std::cin.tie(NULL);

    int q; // Declare variable for the number of queries
    std::cin >> q; // Read the number of queries

    // Loop through each query and call the solve function
    while (q--) {
        solve();
    }

    return 0; // Indicate successful program execution
}

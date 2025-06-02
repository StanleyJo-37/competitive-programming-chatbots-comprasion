#include <iostream> // Required for input/output operations (cin, cout)
#include <vector>   // Required for using std::vector to store roots
#include <algorithm> // Required for std::sort, std::binary_search, std::upper_bound

int main() {
    // Optimize C++ standard streams for faster input/output.
    // This unties cin from cout and prevents flushing cout before each cin.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int N, Q;
    // Read the number of roots (N) and the number of queries (Q).
    std::cin >> N >> Q;

    // Declare a vector to store the N roots.
    // Using long long because |a_i| can be up to 10^9, which fits within long long.
    std::vector<long long> a(N);
    // Read the N roots into the vector.
    for (int i = 0; i < N; ++i) {
        std::cin >> a[i];
    }

    // Sort the roots. This is crucial for efficient querying using binary search.
    // Sorting takes O(N log N) time.
    std::sort(a.begin(), a.end());

    // Process each query.
    // Each query takes O(log N) time due to binary search operations.
    for (int q = 0; q < Q; ++q) {
        long long x;
        // Read the query value x.
        std::cin >> x;

        // First, check if x is one of the roots.
        // If x is a root, P(x) will be 0 because one of the terms (x - a_i) will be (x - x) = 0.
        // std::binary_search efficiently checks for existence in a sorted range.
        if (std::binary_search(a.begin(), a.end(), x)) {
            std::cout << "0\n";
        } else {
            // If x is not a root, P(x) will not be 0.
            // The sign of P(x) depends on the number of negative terms (x - a_i).
            // A term (x - a_i) is negative if x < a_i.
            // A term (x - a_i) is positive if x > a_i.

            // std::upper_bound returns an iterator to the first element in the sorted range [a.begin(), a.end())
            // that is strictly greater than x.
            // All elements from this iterator to a.end() are greater than x.
            // These are the roots a_i for which (x - a_i) will be negative.
            auto it = std::upper_bound(a.begin(), a.end(), x);

            // The number of roots a_i such that x < a_i (i.e., (x - a_i) is negative)
            // is the distance from 'it' to 'a.end()'.
            // This is equivalent to N - (it - a.begin()).
            long long num_negative_terms = std::distance(it, a.end());

            // If the count of negative terms is even, the product of all terms is positive.
            // (e.g., (-1)*(-1) = 1, (-1)*(-1)*(-1)*(-1) = 1)
            if (num_negative_terms % 2 == 0) {
                std::cout << "POSITIVE\n";
            } else {
                // If the count of negative terms is odd, the product of all terms is negative.
                // (e.g., (-1) = -1, (-1)*(-1)*(-1) = -1)
                std::cout << "NEGATIVE\n";
            }
        }
    }

    return 0; // Indicate successful execution.
}

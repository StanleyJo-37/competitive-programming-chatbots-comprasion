#include <iostream>
#include <vector>
#include <algorithm> // For std::lower_bound

int main() {
    // Optimize C++ standard streams for competitive programming.
    // This unties cin/cout from stdio and prevents flushing cout before cin.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    std::cin >> n; // Read the number of elements in the permutation.

    // 'tails' will store the smallest tail of all increasing subsequences of
    // a certain length. Specifically, tails[k] will be the smallest ending
    // element of an increasing subsequence of length k+1.
    // This vector will always be sorted in increasing order.
    std::vector<int> tails;

    // Iterate through each element of the input permutation.
    for (int i = 0; i < n; ++i) {
        int val;
        std::cin >> val; // Read the current element.

        // Find the first element in 'tails' that is not less than 'val'.
        // This is equivalent to finding the smallest element in 'tails' that is >= 'val'.
        auto it = std::lower_bound(tails.begin(), tails.end(), val);

        // If 'it' is 'tails.end()', it means 'val' is greater than all
        // elements currently in 'tails'. This implies that 'val' can extend
        // the longest increasing subsequence found so far by one element.
        if (it == tails.end()) {
            tails.push_back(val);
        } else {
            // Otherwise, 'val' can replace the element pointed to by 'it'.
            // This is because 'val' is smaller than or equal to *it,
            // allowing us to form an increasing subsequence of the same length
            // but ending with a smaller value ('val'). A smaller ending value
            // is always more favorable for extending the subsequence further.
            *it = val;
        }
    }

    // The size of the 'tails' vector at the end represents the length of the
    // Longest Increasing Subsequence (LIS).
    //
    // The problem asks for the size of the maximum independent set in a graph G.
    // The graph G is constructed by Bubble Sort: an edge (u, v) is added if
    // u and v are adjacent in the array and u > v, and then they are swapped.
    //
    // Key observation: An edge (u, v) is added if and only if u and v are
    // swapped by the Bubble Sort algorithm.
    //
    // Property of Bubble Sort: Two elements u and v are swapped if and only if
    // they form an inversion in the *initial* permutation.
    // (An inversion (u, v) means u appears before v in the array, but u > v).
    //
    // Therefore, an edge (u, v) exists in G if and only if u and v form an
    // inversion in the initial permutation.
    //
    // An independent set S is a set of vertices where no two vertices are adjacent.
    // This means for any u, v in S, (u, v) is NOT an edge.
    // Based on our observation, this means for any u, v in S, u and v do NOT
    // form an inversion in the initial permutation.
    //
    // If u and v do not form an inversion, it means if u appears before v in
    // the initial array, then u < v.
    // This is precisely the definition of an increasing subsequence.
    //
    // Thus, finding the maximum independent set in graph G is equivalent to
    // finding the Longest Increasing Subsequence (LIS) of the given permutation.
    std::cout << tails.size() << std::endl;

    return 0;
}

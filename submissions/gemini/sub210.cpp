#include <iostream>
#include <vector>
#include <algorithm> // For std::lower_bound

int main() {
    // Optimize C++ standard streams for competitive programming.
    // This unties cin/cout from the C standard streams and prevents flushing cout before cin.
    std::ios_base::sync_with_stdio(false);
    // This disables synchronization with C standard streams, potentially speeding up I/O.
    std::cin.tie(NULL);

    int n;
    // Read the number of elements in the permutation.
    std::cin >> n;

    // 'tails' will store the smallest tail of all increasing subsequences of a certain length.
    // tails[k] stores the smallest ending element of an increasing subsequence of length k+1.
    // This array will always be sorted in ascending order.
    std::vector<int> tails;

    // Iterate through each element of the input permutation.
    for (int i = 0; i < n; ++i) {
        int current_val;
        std::cin >> current_val;

        // Find the first element in 'tails' that is not less than 'current_val'.
        // This is equivalent to finding the smallest element in 'tails' that is >= current_val.
        // std::lower_bound returns an iterator to this element.
        auto it = std::lower_bound(tails.begin(), tails.end(), current_val);

        // If 'it' is 'tails.end()', it means 'current_val' is greater than all elements
        // currently in 'tails'. This implies that 'current_val' can extend the longest
        // increasing subsequence found so far, creating a new, longer one.
        if (it == tails.end()) {
            tails.push_back(current_val);
        } else {
            // If 'current_val' is not greater than all elements in 'tails', it means
            // we found an element '*it' in 'tails' such that '*it' >= 'current_val'.
            // By replacing '*it' with 'current_val', we are effectively finding an
            // increasing subsequence of the same length but with a smaller ending element.
            // A smaller ending element is more "flexible" and allows for potentially
            // longer increasing subsequences to be formed later.
            *it = current_val;
        }
    }

    // The length of the 'tails' vector at the end represents the length of the
    // Longest Increasing Subsequence (LIS) of the input permutation.
    //
    // The problem asks for the size of the maximum independent set in a graph G
    // constructed by Bubble Sort.
    //
    // Let's prove why this is equivalent to LIS:
    //
    // 1. If S is an increasing subsequence of the initial permutation 'a', then S is an independent set in G.
    //    Let S = {s_1, s_2, ..., s_k} be an increasing subsequence, meaning:
    //    - s_1 < s_2 < ... < s_k (sorted by value)
    //    - s_1 appears before s_2, s_2 before s_3, ..., s_{k-1} before s_k in the initial 'a' (sorted by position).
    //    Consider any two elements u, v in S. Without loss of generality, let u < v.
    //    Since S is an increasing subsequence, u must appear before v in the initial permutation.
    //    During Bubble Sort, an edge (x, y) is added if x is at a[i], y is at a[i+1], and x > y.
    //    For u and v: u is to the left of v, and u < v. They are in their "correct" relative order.
    //    Bubble Sort will never swap elements that are in their correct relative order (smaller element to the left of larger element).
    //    Therefore, no edge will ever be added between u and v.
    //    This holds for any pair in S, so S is an independent set.
    //
    // 2. If S is an independent set in G, then S must be an increasing subsequence of the initial permutation 'a'.
    //    Let S = {s_1, s_2, ..., s_k} be an independent set.
    //    Consider any two elements u, v in S. Since S is an independent set, no edge (u, v) exists in G.
    //    This means u and v are never swapped by Bubble Sort.
    //    Assume for contradiction that S is NOT an increasing subsequence.
    //    This means there exist u, v in S such that u < v, but v appears before u in the initial permutation.
    //    So, v is to the left of u, and v > u. This forms an inversion (v, u).
    //    Bubble Sort works by repeatedly resolving inversions. If v is to the left of u and v > u,
    //    Bubble Sort will eventually bring v and u adjacent to each other, with v at a[i] and u at a[i+1].
    //    At this point, since v > u, they will be swapped, and an edge (v, u) will be added to G.
    //    This contradicts the assumption that S is an independent set (because an edge (v, u) would exist between v and u, both in S).
    //    Therefore, our assumption must be false. For any u, v in S with u < v, u must appear before v in the initial permutation.
    //    This means S is an increasing subsequence of 'a'.
    //
    // From (1) and (2), the maximum independent set size is exactly the length of the Longest Increasing Subsequence.
    std::cout << tails.size() << std::endl;

    return 0;
}

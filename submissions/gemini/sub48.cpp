#include <iostream> // Required for input/output operations (std::cin, std::cout)
#include <vector>   // Required for using std::vector to store tree data
#include <algorithm> // Required for std::sort and std::min

// Define a struct to hold tree information: position and apples
struct Tree {
    int x; // Position of the tree on the coordinate line
    int a; // Number of apples on the tree
};

// Custom comparison function for sorting left trees (x < 0).
// Trees on the left side should be sorted by their x-coordinate in decreasing order.
// This ensures that trees closer to 0 (e.g., -1, then -2, then -3) come first.
bool compareLeftTrees(const Tree& t1, const Tree& t2) {
    return t1.x > t2.x;
}

// Custom comparison function for sorting right trees (x > 0).
// Trees on the right side should be sorted by their x-coordinate in increasing order.
// This ensures that trees closer to 0 (e.g., 1, then 2, then 3) come first.
bool compareRightTrees(const Tree& t1, const Tree& t2) {
    return t1.x < t2.x;
}

int main() {
    // Optimize C++ standard streams for faster input/output.
    // This is a common practice in competitive programming to prevent TLE (Time Limit Exceeded).
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n; // Declare an integer variable 'n' to store the number of apple trees
    std::cin >> n; // Read the value of 'n' from standard input

    // Create two vectors to store trees: one for trees on the left side (x < 0)
    // and one for trees on the right side (x > 0).
    std::vector<Tree> left_trees;
    std::vector<Tree> right_trees;

    // Loop 'n' times to read the position and apples for each tree
    for (int i = 0; i < n; ++i) {
        int x_i, a_i;
        std::cin >> x_i >> a_i; // Read the position (x_i) and apples (a_i) for the current tree
        if (x_i < 0) {
            // If x_i is negative, it's a left tree. Add it to the 'left_trees' vector.
            left_trees.push_back({x_i, a_i});
        } else { // x_i > 0 because the problem guarantees x_i != 0
            // If x_i is positive, it's a right tree. Add it to the 'right_trees' vector.
            right_trees.push_back({x_i, a_i});
        }
    }

    // Sort the 'left_trees' vector using the custom comparison function 'compareLeftTrees'.
    // This arranges them from closest to 0 to farthest from 0 (e.g., -1, -2, -3...).
    std::sort(left_trees.begin(), left_trees.end(), compareLeftTrees);
    // Sort the 'right_trees' vector using the custom comparison function 'compareRightTrees'.
    // This arranges them from closest to 0 to farthest from 0 (e.g., 1, 2, 3...).
    std::sort(right_trees.begin(), right_trees.end(), compareRightTrees);

    // Get the number of trees on each side
    int num_left = left_trees.size();
    int num_right = right_trees.size();

    // Initialize 'total_apples' to 0. Use 'long long' to prevent potential integer overflow,
    // as the maximum possible apples (100 trees * 10^5 apples/tree = 10^7) fits in int,
    // but long long is safer for sums in competitive programming.
    long long total_apples = 0;

    // Determine 'k', the number of pairs of trees (one left, one right) Amr can visit.
    // Amr always alternates directions and picks the closest unvisited tree. This means
    // he will visit trees in order of increasing absolute distance from 0, alternating sides.
    // Thus, he will visit an equal number of trees from each side, up to the count of the
    // side with fewer trees.
    int k = std::min(num_left, num_right);

    // Add apples from the first 'k' trees from both the left and right sides.
    // These are the trees that Amr is guaranteed to visit regardless of his initial direction,
    // as long as he can complete 'k' full cycles of alternating sides.
    for (int i = 0; i < k; ++i) {
        total_apples += left_trees[i].a;  // Add apples from the i-th closest left tree
        total_apples += right_trees[i].a; // Add apples from the i-th closest right tree
    }

    // After visiting 2*k trees (k from left, k from right), Amr might be able to collect
    // apples from one more tree if one side has more trees than the other.
    // If 'num_left' is greater than 'k' (meaning 'num_left > num_right'), Amr can choose
    // to start by going left. After visiting 'k' right trees and 'k' left trees, he will
    // have just visited the k-th right tree and reversed direction to face left. He can then
    // collect apples from the (k+1)-th left tree.
    if (num_left > k) {
        total_apples += left_trees[k].a; // Add apples from the (k+1)-th closest left tree
    }
    // Similarly, if 'num_right' is greater than 'k' (meaning 'num_right > num_left'), Amr can choose
    // to start by going right. After visiting 'k' left trees and 'k' right trees, he will
    // have just visited the k-th left tree and reversed direction to face right. He can then
    // collect apples from the (k+1)-th right tree.
    else if (num_right > k) {
        total_apples += right_trees[k].a; // Add apples from the (k+1)-th closest right tree
    }
    // If num_left == num_right == k, all trees have been visited, and no extra tree can be collected.

    // Print the calculated maximum number of apples Amr can collect
    std::cout << total_apples << std::endl;

    return 0; // Indicate successful program execution
}
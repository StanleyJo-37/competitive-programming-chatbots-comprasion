#include <iostream> // Required for input/output operations (cin, cout)
#include <string>   // Required for string manipulation
#include <vector>   // Required for dynamic arrays (std::vector)
#include <algorithm> // Required for std::max

int main() {
    // Optimize C++ standard streams for competitive programming.
    // This unties cin from cout and disables synchronization with C's stdio,
    // which can significantly speed up I/O operations.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, m; // Declare integers for lengths of strings s and t
    std::cin >> n >> m; // Read n and m from standard input

    std::string s, t; // Declare strings s and t
    std::cin >> s >> t; // Read strings s and t from standard input

    // left_indices[i] will store the smallest possible 0-based index p_i
    // such that s[p_i] == t[i] and p_i is greater than the previous index.
    // This is computed by a greedy scan from left to right.
    std::vector<int> left_indices(m);
    int current_s_idx = 0; // Pointer for string s, starts at the beginning (0-indexed)

    // Iterate through string t from left to right (0 to m-1)
    for (int i = 0; i < m; ++i) {
        // Find the first occurrence of t[i] in s starting from current_s_idx.
        // The current_s_idx ensures that p_i is strictly greater than p_{i-1}.
        while (s[current_s_idx] != t[i]) {
            current_s_idx++; // Move to the next character in s
        }
        left_indices[i] = current_s_idx; // Store the found index for t[i]
        current_s_idx++; // Move current_s_idx past the found character for the next search (t[i+1])
    }

    // right_indices[i] will store the largest possible 0-based index p_i
    // such that s[p_i] == t[i] and p_i is smaller than the next index.
    // This is computed by a greedy scan from right to left.
    std::vector<int> right_indices(m);
    current_s_idx = n - 1; // Pointer for string s, starts at the end (n-1, 0-indexed)

    // Iterate through string t from right to left (m-1 down to 0)
    for (int i = m - 1; i >= 0; --i) {
        // Find the last occurrence of t[i] in s starting from current_s_idx.
        // The current_s_idx ensures that p_i is strictly smaller than p_{i+1}.
        while (s[current_s_idx] != t[i]) {
            current_s_idx--; // Move to the previous character in s
        }
        right_indices[i] = current_s_idx; // Store the found index for t[i]
        current_s_idx--; // Move current_s_idx before the found character for the next search (t[i-1])
    }

    int max_width = 0; // Initialize maximum width to 0

    // The problem asks for the maximum width, defined as max(p_{i+1} - p_i).
    // To maximize a specific gap (p_{i+1} - p_i), we should choose p_{i+1} to be as large as possible
    // and p_i to be as small as possible, while maintaining a valid beautiful sequence.
    // The largest possible index for t_{i+1} is right_indices[i+1].
    // The smallest possible index for t_i is left_indices[i].
    // It can be proven that the maximum width is achieved by taking the maximum of
    // (right_indices[i+1] - left_indices[i]) for all possible i from 0 to m-2.
    // This is because:
    // 1. Any beautiful sequence's gap (p_{i+1} - p_i) must satisfy p_{i+1} - p_i <= right_indices[i+1] - left_indices[i],
    //    since p_i >= left_indices[i] and p_{i+1} <= right_indices[i+1].
    // 2. For any i, a beautiful sequence can be constructed by using left_indices for elements up to t_i,
    //    and right_indices for elements from t_{i+1} onwards. This sequence will contain the gap
    //    (right_indices[i+1] - left_indices[i]), and all its other gaps will be less than or equal to this value.
    // Therefore, the maximum width is exactly the maximum of these potential "maximal" gaps.
    for (int i = 0; i < m - 1; ++i) {
        max_width = std::max(max_width, right_indices[i+1] - left_indices[i]);
    }

    std::cout << max_width << std::endl; // Output the calculated maximum width

    return 0; // Indicate successful execution
}
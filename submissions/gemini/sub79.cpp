#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>
#include <map>

// Function to check if a string has duplicate characters.
// This is used to determine if a string can be obtained from itself by swapping two identical characters.
bool has_duplicates(const std::string& s) {
    std::map<char, int> freq;
    for (char c : s) {
        freq[c]++;
        if (freq[c] > 1) {
            return true;
        }
    }
    return false;
}

// Function to verify a candidate original string (s_cand) against all given strings (s_all).
// s_cand_has_duplicates is a precomputed flag for s_cand's duplicate status,
// which is the same as s_all[0]'s duplicate status because s_cand is a permutation of s_all[0].
bool verify(const std::string& s_cand, const std::vector<std::string>& s_all, int n, bool s_cand_has_duplicates) {
    // Iterate through each of the k given strings.
    for (const std::string& s_m : s_all) {
        int diff_count = 0;
        // Find positions where s_cand and s_m differ.
        for (int j = 0; j < n; ++j) {
            if (s_cand[j] != s_m[j]) {
                diff_count++;
            }
        }

        // Check if s_m could be obtained from s_cand by swapping exactly two characters.
        if (diff_count == 0) {
            // If s_cand and s_m are identical, it's valid only if s_cand has duplicate characters.
            // This allows for s_m to be formed by swapping two identical characters at different indices in s_cand.
            if (!s_cand_has_duplicates) {
                return false;
            }
        } else if (diff_count == 2) {
            // If s_cand and s_m differ at exactly two positions, it means s_m was formed by swapping
            // the characters at these two positions in s_cand. This is always valid if they are anagrams
            // (which is checked initially) and differ at exactly 2 positions.
            // No further explicit check is needed here beyond diff_count == 2.
        } else {
            // If diff_count is anything other than 0 or 2, s_m cannot be obtained from s_cand by a single swap.
            return false;
        }
    }
    return true;
}

int main() {
    // Optimize C++ standard streams for faster input/output.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int k, n;
    std::cin >> k >> n;

    std::vector<std::string> s_all(k);
    for (int i = 0; i < k; ++i) {
        std::cin >> s_all[i];
    }

    // Step 1: Initial Frequency Check
    // All k strings must be anagrams of each other.
    // Compare the frequency map of the first string (s_all[0]) with all other strings.
    std::map<char, int> s0_freq;
    for (char c : s_all[0]) {
        s0_freq[c]++;
    }

    for (int i = 1; i < k; ++i) {
        std::map<char, int> si_freq;
        for (char c : s_all[i]) {
            si_freq[c]++;
        }
        if (s0_freq != si_freq) {
            std::cout << -1 << std::endl;
            return 0;
        }
    }

    // Precompute if s_all[0] has duplicate characters.
    // This property (having duplicates or not) is invariant under character swaps.
    // So, any candidate string formed by swapping characters in s_all[0] will have the same duplicate status.
    bool s0_has_duplicates = has_duplicates(s_all[0]);

    // Case 1: k = 1
    // If only one string is given, we can always find a solution.
    // If s_all[0] has duplicate characters, s_all[0] itself is a valid original string
    // (e.g., swap two identical characters at different indices to get s_all[0]).
    // Otherwise (all characters are unique), we must swap two distinct characters in s_all[0]
    // to form the original string. Swapping s_all[0][0] and s_all[0][1] is a simple choice.
    if (k == 1) {
        if (s0_has_duplicates) {
            std::cout << s_all[0] << std::endl;
        } else {
            // n >= 2 is guaranteed by constraints.
            std::string s_cand = s_all[0];
            std::swap(s_cand[0], s_cand[1]); // Swap first two characters
            std::cout << s_cand << std::endl;
        }
        return 0;
    }

    // Case 2: k > 1
    // The true original string s_orig must be s_all[0] with two characters (at indices p_a, p_b) swapped.
    // Let s_all[0] be S_0 and s_all[1] be S_1.
    // S_0 is s_orig with {p_0, q_0} swapped.
    // S_1 is s_orig with {p_1, q_1} swapped.
    // The positions where S_0 and S_1 differ are D_01 = {p_0, q_0} XOR {p_1, q_1}.
    // The size of D_01 can only be 0, 2, or 4. If any other size, no solution exists.

    std::vector<int> diff_01_indices;
    for (int j = 0; j < n; ++j) {
        if (s_all[0][j] != s_all[1][j]) {
            diff_01_indices.push_back(j);
        }
    }

    // If |D_01| is not 0, 2, or 4, then no solution exists.
    if (diff_01_indices.size() > 4 || diff_01_indices.size() == 1 || diff_01_indices.size() == 3) {
        std::cout << -1 << std::endl;
        return 0;
    }

    // If s_all[0] and s_all[1] are identical (|D_01| == 0)
    // This implies that all k strings must be identical to s_all[0].
    // (If any s_i was different, it would have been caught by the initial frequency check or
    // by the general verification logic later).
    if (diff_01_indices.empty()) { // s_all[0] == s_all[1]
        // If s_all[0] has duplicate characters, then s_all[0] itself is a valid s_orig.
        // (It can be obtained from itself by swapping two identical characters).
        if (s0_has_duplicates) {
            std::cout << s_all[0] << std::endl;
        } else {
            // If s_all[0] has unique characters, it cannot be s_orig itself.
            // s_orig must be s_all[0] with two distinct characters swapped.
            // Since all s_i are identical to s_all[0], s_all[0] must be obtainable from s_orig by a swap.
            // This means s_orig must be s_all[0] with two characters swapped.
            // Any two distinct characters (e.g., at indices 0 and 1) will work to form a candidate s_orig.
            std::string s_cand = s_all[0];
            std::swap(s_cand[0], s_cand[1]); // Swap first two characters
            // Verify this candidate. It should always be valid under these conditions.
            if (verify(s_cand, s_all, n, s0_has_duplicates)) {
                std::cout << s_cand << std::endl;
            } else {
                // This case should theoretically not be reached if problem constraints are strict.
                // As a fallback, print -1.
                std::cout << -1 << std::endl;
            }
        }
        return 0;
    }

    // If |D_01| == 2:
    // Let D_01 = {a, b}. This means {p_0, q_0} XOR {p_1, q_1} = {a, b}.
    // This implies that one index is common between the two swap pairs, e.g., p_0 = p_1 = x, and q_0 = a, q_1 = b.
    // So, s_orig is S_0 with {x, a} swapped (or {x, b} swapped, which is equivalent).
    // We iterate through all possible values for x (0 to n-1) as the common swap index.
    // For each x, we form a candidate s_orig by swapping s_all[0][x] and s_all[0][a].
    // The total complexity for this part is O(N * k * N) = O(N * (k*N)).
    // Given k*N <= 5000, this is O(N * 5000), which is at most 5000 * 5000 = 2.5 * 10^7 character comparisons, acceptable.
    if (diff_01_indices.size() == 2) {
        int a = diff_01_indices[0]; // One of the differing indices
        
        for (int x = 0; x < n; ++x) {
            std::string s_cand = s_all[0];
            // Form candidate s_orig by swapping s_all[0][x] and s_all[0][a].
            std::swap(s_cand[x], s_cand[a]);
            if (verify(s_cand, s_all, n, s0_has_duplicates)) {
                std::cout << s_cand << std::endl;
                return 0;
            }
        }
        // If no candidate works after trying all possible x, then no solution.
        std::cout << -1 << std::endl;
        return 0;
    }

    // If |D_01| == 4:
    // Let D_01 = {a, b, c, d}. This means {p_0, q_0} XOR {p_1, q_1} = {a, b, c, d}.
    // This implies that the two swap pairs {p_0, q_0} and {p_1, q_1} are disjoint.
    // E.g., {p_0, q_0} = {a, b} and {p_1, q_1} = {c, d} (or any permutation of these indices).
    // So, s_orig is S_0 with {a, b} swapped.
    // We need to try all 4C2 = 6 possible pairs from D_01 as the swap pair for s_all[0].
    // The total complexity for this part is O(6 * k * N) = O(k*N), which is very fast.
    if (diff_01_indices.size() == 4) {
        std::vector<int> p = diff_01_indices; // p = {a, b, c, d}
        
        // Iterate through all unique pairs (x, y) from the 4 differing indices.
        for (int i = 0; i < 4; ++i) {
            for (int j = i + 1; j < 4; ++j) {
                std::string s_cand = s_all[0];
                // Form candidate s_orig by swapping s_all[0][p[i]] and s_all[0][p[j]].
                std::swap(s_cand[p[i]], s_cand[p[j]]);
                if (verify(s_cand, s_all, n, s0_has_duplicates)) {
                    std::cout << s_cand << std::endl;
                    return 0;
                }
            }
        }
        // If no candidate works after trying all 6 pairs, then no solution.
        std::cout << -1 << std::endl;
        return 0;
    }

    // This line should theoretically not be reached if all cases are covered.
    std::cout << -1 << std::endl;
    return 0;
}

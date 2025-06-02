#include <iostream>
#include <string>
#include <vector>
#include <algorithm> // For std::sort and std::next_permutation
#include <map>       // For std::map

// Function to calculate cross inversions between two sorted lists of indices.
// This counts pairs (idx1, idx2) where idx1 is from pos1, idx2 is from pos2, and idx1 > idx2.
// This is used to determine the number of inversions contributed by placing characters
// corresponding to pos1 before characters corresponding to pos2 in the output string 'b',
// given their original positions in string 'a'.
long long calculate_cross_inversions(const std::vector<int>& pos1, const std::vector<int>& pos2) {
    long long inversions = 0;
    int p1 = 0; // Pointer for pos1 (indices of char1 in 'a')
    int p2 = 0; // Pointer for pos2 (indices of char2 in 'a')

    // Iterate through both position lists. Both pos1 and pos2 are already sorted.
    while (p1 < pos1.size() && p2 < pos2.size()) {
        if (pos1[p1] > pos2[p2]) {
            // If the current position from pos1 (pos1[p1]) is greater than the current position from pos2 (pos2[p2]),
            // it means the character at pos2[p2] appears earlier in the original string 'a' than the character at pos1[p1].
            // If we arrange characters such that char1 comes before char2 in 'b',
            // then pos1[p1] will form an inversion with pos2[p2].
            // Furthermore, since pos1 is sorted, all subsequent elements in pos1 (from p1 to end)
            // will also be greater than pos2[p2].
            // So, pos2[p2] forms an inversion with (pos1.size() - p1) elements from pos1.
            inversions += (pos1.size() - p1);
            p2++; // Move to the next element in pos2, as pos2[p2] has been processed against all relevant pos1 elements.
        } else {
            // If pos1[p1] <= pos2[p2], it means the character at pos1[p1] appears earlier or at the same position
            // in 'a' than the character at pos2[p2]. No inversion is formed with pos2[p2] for the current pos1[p1].
            // Move to the next element in pos1.
            p1++;
        }
    }
    return inversions;
}

void solve() {
    std::string a;
    std::cin >> a;

    // Store original indices for each character type ('A', 'N', 'T', 'O').
    // This map helps in distinguishing identical characters by their original positions in 'a'.
    std::map<char, std::vector<int>> char_positions;
    for (int i = 0; i < a.length(); ++i) {
        char_positions[a[i]].push_back(i);
    }

    // Precompute inversion counts for all ordered pairs of distinct characters present in 'a'.
    // inv_counts[{c1, c2}] stores the number of pairs (idx1, idx2) such that
    // a[idx1] is c1, a[idx2] is c2, and idx1 > idx2.
    // This value represents the contribution to total inversions if c1 appears before c2 in string 'b'.
    std::map<std::pair<char, char>, long long> inv_counts;
    
    // Collect only the distinct characters that are actually present in the input string 'a'.
    std::string present_chars_str;
    // The problem states characters are 'A', 'N', 'T', 'O'. Iterate through them.
    std::string all_possible_chars = "ANOT"; 
    for(char c : all_possible_chars) {
        if (char_positions.count(c) && !char_positions[c].empty()) {
            present_chars_str += c;
        }
    }

    // Generate all pairs of present distinct characters and compute their cross inversions.
    for (char c1 : present_chars_str) {
        for (char c2 : present_chars_str) {
            if (c1 == c2) continue; // Skip pairs of identical characters
            inv_counts[{c1, c2}] = calculate_cross_inversions(char_positions[c1], char_positions[c2]);
        }
    }

    long long max_inversions = -1; // Initialize with a value lower than any possible inversion count
    std::string best_b_string = ""; // Stores the best string 'b' found

    // Sort present_chars_str to ensure std::next_permutation iterates through all unique permutations
    // in lexicographical order, starting from the smallest.
    std::sort(present_chars_str.begin(), present_chars_str.end());

    // Iterate through all permutations of the distinct characters present in 'a'.
    // There are at most 4! = 24 such permutations, so this loop is very fast.
    do {
        long long current_inversions = 0;
        // For a given permutation (C_1, C_2, ..., C_m) of characters,
        // the string 'b' is formed by concatenating all C_1's, then all C_2's, etc.
        // Inversions only occur between characters of different types.
        // If C_k appears before C_l in the current permutation (i.e., C_k = present_chars_str[i] and C_l = present_chars_str[j] with i < j),
        // then all instances of C_k appear before all instances of C_l in 'b'.
        // The number of inversions contributed by such a pair (C_k, C_l)
        // is the count of pairs (X, Y) where X is an instance of C_k, Y is an instance of C_l,
        // and X appears after Y in the original string 'a'.
        // This is exactly what inv_counts[{C_k, C_l}] stores.
        for (int i = 0; i < present_chars_str.length(); ++i) {
            for (int j = i + 1; j < present_chars_str.length(); ++j) {
                current_inversions += inv_counts[{present_chars_str[i], present_chars_str[j]}];
            }
        }

        // If the current permutation yields more inversions, update the maximum and store the corresponding string 'b'.
        if (current_inversions > max_inversions) {
            max_inversions = current_inversions;
            best_b_string = "";
            // Construct the candidate string 'b' based on the current character permutation.
            // Append all occurrences of each character type in the order specified by the permutation.
            for (char c : present_chars_str) {
                best_b_string += std::string(char_positions[c].size(), c);
            }
        }
    } while (std::next_permutation(present_chars_str.begin(), present_chars_str.end()));

    // Print the best string 'b' found.
    std::cout << best_b_string << std::endl;
}

int main() {
    // Optimize C++ standard streams for competitive programming.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams.
    // std::cin.tie(NULL) prevents std::cout from flushing before std::cin reads input.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t; // Read the number of testcases
    while (t--) {
        solve(); // Solve each testcase
    }

    return 0;
}

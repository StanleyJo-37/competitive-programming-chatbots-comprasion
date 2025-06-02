#include <iostream>
#include <vector>
#include <algorithm> // For std::sort and std::upper_bound

int main() {
    // Optimize C++ standard streams for competitive programming.
    // This unties cin/cout from C standard streams and disables synchronization
    // with C standard streams, potentially speeding up I/O operations.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    std::cin >> n; // Read the number of sequences.

    // Vector to store the minimum and maximum values of sequences that do NOT have an ascent.
    // Each pair will be (min_value_in_sequence, max_value_in_sequence).
    // For a non-increasing sequence, min_value is the last element and max_value is the first element.
    std::vector<std::pair<int, int>> no_ascent_seqs_data;

    // Iterate through each of the N sequences.
    for (int i = 0; i < n; ++i) {
        int l;
        std::cin >> l; // Read the length of the current sequence.

        // Read sequence elements and check for ascent.
        // An ascent exists if s[j] < s[k] for j < k.
        // For a sequence to NOT have an ascent, it must be non-increasing: s[j] >= s[j+1] for all j.
        // So, if we find any s[j] < s[j+1], it has an ascent.
        
        int first_val;
        std::cin >> first_val; // Read the first element. This will be the max_val if no ascent.
        int current_min_val = first_val; // Initialize current_min_val with the first element.
        bool has_ascent_current_seq = false; // Flag to check if the current sequence has an ascent.

        for (int j = 1; j < l; ++j) {
            int val;
            std::cin >> val; // Read subsequent elements.
            if (!has_ascent_current_seq && s[j-1] < val) { // s[j-1] is the previously read element
                // If an ascent is found and we haven't marked it yet, set the flag.
                has_ascent_current_seq = true;
            }
            // Update current_min_val. For a non-increasing sequence, the last element is the minimum.
            // We only need the last element if it's a non-ascending sequence.
            // For now, we just keep track of the last element read.
            current_min_val = val; 
        }

        if (!has_ascent_current_seq) {
            // If the current sequence does NOT have an ascent (it's non-increasing),
            // store its minimum (last element, which is current_min_val)
            // and maximum (first element, which is first_val) values.
            no_ascent_seqs_data.push_back({current_min_val, first_val});
        }
    }

    // The total number of possible pairs (s_x, s_y) is N * N.
    // We will calculate the number of pairs that DO NOT have an ascent and subtract from N*N.
    long long total_pairs = (long long)n * n;

    // Extract all maximum values from sequences that do not have an ascent.
    // These are the 'max_val_y' candidates for the condition s_x[l_x] >= s_y[1].
    std::vector<int> all_max_vals_from_no_ascent_seqs;
    for (const auto& p : no_ascent_seqs_data) {
        all_max_vals_from_no_ascent_seqs.push_back(p.second); // p.second is max_val (s_y[1])
    }

    // Sort the maximum values to enable efficient binary search (upper_bound).
    std::sort(all_max_vals_from_no_ascent_seqs.begin(), all_max_vals_from_no_ascent_seqs.end());

    // Calculate the number of pairs (s_x, s_y) where s_x + s_y does NOT have an ascent.
    // This occurs if and only if:
    // 1. s_x does not have an ascent.
    // 2. s_y does not have an ascent.
    // 3. s_x[l_x] >= s_y[1] (i.e., min_val_x >= max_val_y).
    long long count_no_ascent_concatenations = 0;

    // Iterate through each sequence s_x that does not have an ascent.
    for (const auto& p_x : no_ascent_seqs_data) {
        int min_val_x = p_x.first; // p_x.first is min_val (s_x[l_x])

        // Find how many sequences s_y (that also do not have an ascent) satisfy min_val_x >= max_val_y.
        // std::upper_bound returns an iterator to the first element strictly greater than min_val_x.
        // The number of elements less than or equal to min_val_x is the distance from begin() to this iterator.
        auto it = std::upper_bound(all_max_vals_from_no_ascent_seqs.begin(),
                                   all_max_vals_from_no_ascent_seqs.end(),
                                   min_val_x);
        count_no_ascent_concatenations += (it - all_max_vals_from_no_ascent_seqs.begin());
    }

    // The number of pairs (s_x, s_y) whose concatenation HAS an ascent is:
    // Total possible pairs - (pairs where s_x + s_y does NOT have an ascent).
    long long result = total_pairs - count_no_ascent_concatenations;

    std::cout << result << std::endl; // Print the final count.

    return 0;
}

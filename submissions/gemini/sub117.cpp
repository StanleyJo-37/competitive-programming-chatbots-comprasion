#include <iostream> // Required for input/output operations (std::cin, std::cout)
#include <vector>   // Required for std::vector
#include <string>   // Required for std::string

int main() {
    // Optimize C++ standard streams for competitive programming.
    // This unties cin/cout from C standard streams and disables synchronization
    // with C stdio, potentially speeding up I/O operations.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::string s;
    std::cin >> s; // Read the input string describing Oleg's life history.

    // all_subsequences will store all the zebra subsequences.
    // Each inner std::vector<int> represents a single zebra subsequence,
    // storing the 1-based indices of the days that form it.
    std::vector<std::vector<int>> all_subsequences;

    // available_ends_0 stores the IDs (indices in all_subsequences) of
    // subsequences that currently end with a '0' and are thus looking for a '1'.
    // These are potential candidates to extend with a '1'.
    // We use std::vector as a stack (push_back, pop_back) for O(1) amortized operations.
    std::vector<int> available_ends_0;

    // available_ends_1 stores the IDs (indices in all_subsequences) of
    // subsequences that currently end with a '1' and are thus looking for a '0'.
    // These are potential candidates to extend with a '0'.
    // We use std::vector as a stack (push_back, pop_back) for O(1) amortized operations.
    std::vector<int> available_ends_1;

    // Iterate through the input string character by character.
    // 'i' is the 0-based index of the character in the string.
    // 'day_idx' is the 1-based index of the day, as required by the output format.
    for (int i = 0; i < s.length(); ++i) {
        int day_idx = i + 1; // Convert 0-based index to 1-based day index.

        if (s[i] == '0') {
            // If the current day is '0' (bad day):
            // A '0' can either start a new zebra subsequence OR
            // extend an existing subsequence that currently ends with '1'.
            if (!available_ends_1.empty()) {
                // If there's an available subsequence ending with '1':
                // Take one such subsequence (we use the last one added for simplicity/efficiency).
                int sub_id = available_ends_1.back();
                available_ends_1.pop_back(); // Remove it from available_ends_1.

                // Append the current day's index to this subsequence.
                all_subsequences[sub_id].push_back(day_idx);

                // This subsequence now ends with '0', so it's available for a '1'.
                available_ends_0.push_back(sub_id);
            } else {
                // If no subsequence ending with '1' is available:
                // We must start a new zebra subsequence with this '0'.
                // Get a new ID for this subsequence (which is the current size of all_subsequences).
                int new_sub_id = all_subsequences.size();
                
                // Create a new subsequence vector and add the current day's index.
                all_subsequences.push_back({day_idx});

                // This new subsequence ends with '0', so it's available for a '1'.
                available_ends_0.push_back(new_sub_id);
            }
        } else { // s[i] == '1'
            // If the current day is '1' (good day):
            // A '1' cannot start a zebra subsequence (zebras must start with '0').
            // It can only extend an existing subsequence that currently ends with '0'.
            if (!available_ends_0.empty()) {
                // If there's an available subsequence ending with '0':
                // Take one such subsequence.
                int sub_id = available_ends_0.back();
                available_ends_0.pop_back(); // Remove it from available_ends_0.

                // Append the current day's index to this subsequence.
                all_subsequences[sub_id].push_back(day_idx);

                // This subsequence now ends with '1', so it's available for a '0'.
                available_ends_1.push_back(sub_id);
            } else {
                // If no subsequence ending with '0' is available:
                // It's impossible to place this '1' into any valid zebra subsequence.
                // Therefore, no solution exists.
                std::cout << -1 << std::endl;
                return 0; // Exit the program.
            }
        }
    }

    // After processing all days, all zebra subsequences must end with '0'.
    // If any subsequence currently ends with '1' (i.e., available_ends_1 is not empty),
    // it means those subsequences are incomplete zebras and cannot be completed.
    if (!available_ends_1.empty()) {
        std::cout << -1 << std::endl;
        return 0; // No valid division is possible.
    }

    // If we reached here, a valid division is possible.
    // Print the total number of subsequences.
    std::cout << all_subsequences.size() << std::endl;

    // Print each subsequence in the required format.
    for (const auto& sub : all_subsequences) {
        std::cout << sub.size(); // Print the length of the subsequence.
        for (int idx : sub) {
            std::cout << " " << idx; // Print each day index, separated by a space.
        }
        std::cout << std::endl; // New line for the next subsequence.
    }

    return 0; // Program finished successfully.
}
#include <iostream> // Required for input/output operations (std::cin, std::cout, std::endl)
#include <vector>   // Required for std::vector
#include <numeric>  // Not strictly needed for this solution, but often useful for algorithms
#include <algorithm> // Required for std::fill and std::swap

// Define the maximum possible strength value.
// Strengths a_i and x are up to 10^3.
// 10^3 in binary is 1111101000 (10 bits).
// The maximum possible value after XORing will be 2^10 - 1 = 1023.
// So, an array of size 1024 (indices 0 to 1023) is sufficient to store counts.
const int MAX_STRENGTH_VAL = 1023;
const int ARRAY_SIZE = MAX_STRENGTH_VAL + 1;

int main() {
    // Optimize C++ standard streams for competitive programming.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams,
    // potentially speeding up I/O.
    // std::cin.tie(NULL) unties std::cin from std::cout, meaning std::cin will not flush
    // std::cout before reading input, further speeding up I/O.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, k, x;
    // Read the number of rangers (n), number of operations (k), and favorite number (x).
    std::cin >> n >> k >> x;

    // Use two vectors to store counts of strengths.
    // `current_counts` holds the strengths for the current iteration.
    // `next_counts` will be populated with strengths for the next iteration.
    // Initialize all counts to 0.
    std::vector<int> current_counts(ARRAY_SIZE, 0);
    std::vector<int> next_counts(ARRAY_SIZE, 0);

    // Read initial strengths and populate `current_counts`.
    for (int i = 0; i < n; ++i) {
        int strength;
        std::cin >> strength;
        current_counts[strength]++; // Increment count for the read strength
    }

    // Perform k operations.
    for (int op = 0; op < k; ++op) {
        // Reset `next_counts` to all zeros for the current operation.
        // This ensures that `next_counts` only accumulates values for the current step.
        std::fill(next_counts.begin(), next_counts.end(), 0);

        // `current_pos_idx` keeps track of the 0-indexed position of the ranger
        // being processed in the globally sorted list of rangers.
        // This is crucial for determining if a ranger is at an even or odd position.
        int current_pos_idx = 0;

        // Iterate through all possible strength values from 0 to MAX_STRENGTH_VAL.
        // This loop implicitly processes rangers in increasing order of strength,
        // as required by the problem statement ("Arrange all the rangers in a straight line
        // in the order of increasing strengths").
        for (int s = 0; s < ARRAY_SIZE; ++s) {
            // If there are rangers with the current strength `s`.
            if (current_counts[s] > 0) {
                // `num_rangers_at_s` is the count of rangers with strength `s`.
                int num_rangers_at_s = current_counts[s];

                // Calculate how many rangers at strength `s` will be XORed and how many will be kept.
                // This depends on the parity of `current_pos_idx`.
                int num_xor_at_s;
                int num_keep_at_s;

                // The problem states "first ranger is updated", "second ranger remains the same", etc.
                // This implies 1st, 3rd, 5th... (odd 1-indexed positions) get XORed.
                // In 0-indexed terms, this means positions 0, 2, 4... (even 0-indexed positions) get XORed.
                if (current_pos_idx % 2 == 0) {
                    // If the first ranger with strength `s` is at an even 0-indexed position,
                    // then the rangers at even positions relative to `current_pos_idx` get XORed.
                    // Example: if 5 rangers at strength `s` and `current_pos_idx` is even:
                    // Positions: E O E O E (E=XORed, O=Kept)
                    // Number of XORed: (5+1)/2 = 3
                    // Number of Kept: 5/2 = 2
                    num_xor_at_s = (num_rangers_at_s + 1) / 2;
                    num_keep_at_s = num_rangers_at_s / 2;
                } else {
                    // If the first ranger with strength `s` is at an odd 0-indexed position,
                    // then the rangers at odd positions relative to `current_pos_idx` get XORed.
                    // Example: if 5 rangers at strength `s` and `current_pos_idx` is odd:
                    // Positions: O E O E O (O=Kept, E=XORed)
                    // Number of XORed: 5/2 = 2
                    // Number of Kept: (5+1)/2 = 3
                    num_xor_at_s = num_rangers_at_s / 2;
                    num_keep_at_s = (num_rangers_at_s + 1) / 2;
                }

                // Update `next_counts` based on the XORed and kept rangers.
                // Rangers that are XORed change their strength to `s ^ x`.
                next_counts[s ^ x] += num_xor_at_s;
                // Rangers that are kept retain their strength `s`.
                next_counts[s] += num_keep_at_s;

                // Advance `current_pos_idx` by the number of rangers just processed.
                current_pos_idx += num_rangers_at_s;
            }
        }
        // After processing all strengths for the current operation,
        // update `current_counts` to `next_counts` for the next iteration.
        // std::vector::swap is an efficient way to exchange contents.
        current_counts.swap(next_counts);
    }

    // Find the minimum and maximum strengths after k operations.
    int min_strength = -1; // Initialize with an invalid value
    int max_strength = -1; // Initialize with an invalid value

    // Iterate from the smallest possible strength (0) upwards to find the minimum.
    for (int s = 0; s < ARRAY_SIZE; ++s) {
        if (current_counts[s] > 0) {
            min_strength = s; // Found the smallest strength with a non-zero count
            break;            // No need to check further, this is the minimum
        }
    }

    // Iterate from the largest possible strength (MAX_STRENGTH_VAL) downwards to find the maximum.
    for (int s = ARRAY_SIZE - 1; s >= 0; --s) {
        if (current_counts[s] > 0) {
            max_strength = s; // Found the largest strength with a non-zero count
            break;            // No need to check further, this is the maximum
        }
    }

    // Output the maximum and minimum strengths, separated by a space.
    std::cout << max_strength << " " << min_strength << std::endl;

    return 0; // Indicate successful execution
}

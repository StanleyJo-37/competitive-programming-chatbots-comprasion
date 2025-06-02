#include <iostream>
#include <vector>
#include <numeric> // Not strictly needed, but often useful for competitive programming.
#include <algorithm> // Not strictly needed, but often useful for competitive programming.

// Global vector to store counts of each bit position.
// Max bit position is 2 * 10^5, so size 200001 covers indices 0 to 200000.
// Declared globally to avoid repeated allocation/deallocation across test cases.
std::vector<int> bit_counts(200001);

// Global vector of vectors to store the set bit positions for each number c_i.
// Declared globally for the same reason as bit_counts.
std::vector<std::vector<int>> c_bits_storage;

// Global vector to store all bit positions that were set in the current test case.
// Used for efficient cleanup of bit_counts array after each test case.
std::vector<int> active_bits_in_current_test_case;

void solve() {
    int n;
    std::cin >> n;

    // Resize c_bits_storage to accommodate 'n' elements for the current test case.
    // This clears any data from previous test cases and prepares for new input.
    c_bits_storage.assign(n, std::vector<int>());
    // Clear the list of active bits for the current test case.
    active_bits_in_current_test_case.clear();

    // Read the description of each number c_i.
    for (int i = 0; i < n; ++i) {
        int k_i; // Number of set bits in c_i.
        std::cin >> k_i;
        // Resize the inner vector for c_i to hold k_i bit positions.
        c_bits_storage[i].resize(k_i);
        for (int j = 0; j < k_i; ++j) {
            int p; // A bit position that is set in c_i.
            std::cin >> p;
            c_bits_storage[i][j] = p;
            // Increment the count for this bit position.
            bit_counts[p]++;
            // Add this bit position to our list of active bits for cleanup later.
            active_bits_in_current_test_case.push_back(p);
        }
    }

    bool found_redundant_c = false;
    // Iterate through each number c_i to check if it's "redundant".
    // A number c_i is redundant if all its set bits are also set in at least one other number c_j (j != i).
    // This is equivalent to checking if for every bit 'p' set in c_i, bit_counts[p] > 1.
    for (int i = 0; i < n; ++i) {
        bool current_c_is_redundant = true;
        for (int p : c_bits_storage[i]) {
            if (bit_counts[p] == 1) {
                // If any bit 'p' in c_i has a count of 1, it means 'p' is unique to c_i among all numbers.
                // In this case, removing c_i would change the total OR sum (bit 'p' would be lost).
                // So, c_i is not redundant.
                current_c_is_redundant = false;
                break; // No need to check other bits for this c_i.
            }
        }
        if (current_c_is_redundant) {
            // If we found a c_i where all its bits have counts > 1, it means c_i is redundant.
            // We can form two different subsequences with the same OR sum:
            // 1. The subsequence of all elements {c_1, ..., c_n}.
            // 2. The subsequence of all elements except c_i, i.e., {c_1, ..., c_{i-1}, c_{i+1}, ..., c_n}.
            // The OR sum of the second subsequence will contain all bits that are set in c_i
            // (because each such bit is also set in some other c_j).
            // Thus, OR({c_1, ..., c_n}) = OR({c_1, ..., c_{i-1}, c_{i+1}, ..., c_n}).
            found_redundant_c = true;
            break; // No need to check further, we found a "Yes" case.
        }
    }

    if (found_redundant_c) {
        std::cout << "Yes\n";
    } else {
        std::cout << "No\n";
    }

    // Cleanup: Reset bit counts for all bits that were active in this test case.
    // This is crucial for correctness in subsequent test cases and for performance.
    // We iterate only through the bits that were actually touched in this test case.
    for (int p : active_bits_in_current_test_case) {
        bit_counts[p] = 0;
    }
}

int main() {
    // Optimize C++ standard streams for competitive programming.
    // Unties cin from cout and disables synchronization with C stdio.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t; // Number of test cases.
    std::cin >> t;
    while (t--) {
        solve(); // Solve each test case.
    }

    return 0;
}

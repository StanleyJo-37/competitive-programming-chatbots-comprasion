#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

// Function to calculate the sum of an arithmetic progression from 1 to D.
// This is equivalent to the formula D * (D + 1) / 2.
// This function is used to calculate the mana cost for a continuous spell sequence.
long long sum_up_to_D(long long D) {
    return D * (D + 1) / 2;
}

void solve() {
    int n;
    std::cin >> n; // Read the number of monsters.

    // Read monster appearance times (k_i) and health points (h_i).
    // k_i are guaranteed to be sorted in increasing order.
    std::vector<long long> k(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> k[i];
    }
    std::vector<long long> h(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> h[i];
    }

    long long total_mana = 0; // Initialize total mana spent.

    // We process monsters from right to left (from k_n down to k_1).
    // This greedy approach is optimal because it allows us to extend an existing spell sequence
    // to the left if an earlier monster's requirement overlaps, minimizing mana by reusing spells.

    // current_segment_end_time: The time of the last spell in the current active sequence.
    // current_segment_start_time: The time of the first spell in the current active sequence.
    // These define a continuous spell casting sequence [current_segment_start_time, current_segment_end_time].
    // The damage at current_segment_end_time is (current_segment_end_time - current_segment_start_time + 1).
    long long current_segment_end_time = 0;
    long long current_segment_start_time = 0;

    // Iterate from the last monster (index n-1) down to the first monster (index 0).
    for (int i = n - 1; i >= 0; --i) {
        long long monster_k = k[i]; // Current monster's appearance time.
        long long monster_h = h[i]; // Current monster's health.

        // Calculate the earliest time a spell must be cast to achieve damage monster_h at monster_k.
        // This is monster_k - monster_h + 1. Let's call this L_i.
        long long required_start_time_for_monster = monster_k - monster_h + 1;

        if (i == n - 1) {
            // This is the rightmost monster. It initiates the first active spell segment.
            current_segment_end_time = monster_k;
            current_segment_start_time = required_start_time_for_monster;
        } else {
            // For subsequent monsters (moving leftwards):
            // Check if the current monster's required spell interval [L_i, k_i]
            // is completely to the left of the current active segment [current_segment_start_time, current_segment_end_time].
            if (monster_k < current_segment_start_time) {
                // If it's completely to the left, the current active segment is finalized.
                // Add its mana cost to the total.
                long long D = current_segment_end_time - current_segment_start_time + 1;
                total_mana += sum_up_to_D(D);

                // Start a new active segment for the current monster.
                current_segment_end_time = monster_k;
                current_segment_start_time = required_start_time_for_monster;
            } else {
                // The current monster's required spell interval overlaps with or is contained within
                // the current active segment.
                // We need to ensure that the damage at monster_k is at least monster_h.
                // The current segment provides damage:
                // (current_segment_end_time - current_segment_start_time + 1) at current_segment_end_time.
                // At monster_k, it provides damage:
                // (current_segment_end_time - current_segment_start_time + 1) - (current_segment_end_time - monster_k)
                // = monster_k - current_segment_start_time + 1.
                // If this damage is less than monster_h, we need to extend the segment to the left.
                // This means the new start time for the segment must be earlier.
                // The new start time will be the minimum of the current segment's start time
                // and the required start time for the current monster (L_i).
                current_segment_start_time = std::min(current_segment_start_time, required_start_time_for_monster);
                // The current_segment_end_time remains unchanged as it's determined by a monster to its right.
                // The damage at current_segment_end_time is implicitly increased if current_segment_start_time moved left.
            }
        }
    }

    // After the loop, there will be one last active segment whose mana cost needs to be added.
    long long D = current_segment_end_time - current_segment_start_time + 1;
    total_mana += sum_up_to_D(D);

    std::cout << total_mana << std::endl; // Print the total minimum mana required.
}

int main() {
    // Optimize C++ standard streams for competitive programming.
    // This unties cin/cout from stdio and prevents flushing cout before cin.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t; // Read the number of testcases.
    while (t--) {
        solve(); // Solve each testcase.
    }

    return 0;
}

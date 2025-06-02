#include <iostream> // Required for input/output operations (std::cin, std::cout)
#include <vector>   // Required for using std::vector to store spell data
#include <algorithm> // Required for std::min, std::max, and std::upper_bound

int main() {
    // Optimize C++ standard streams for faster input/output.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams.
    // std::cin.tie(NULL) prevents std::cout from flushing before std::cin reads input.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    long long n; // The total number of potions Anton needs to prepare.
    int m, k;    // m: number of Type 1 spells, k: number of Type 2 spells.
    std::cin >> n >> m >> k;

    long long x; // Initial time (seconds) to prepare one potion without any Type 1 spell.
    long long s; // Maximum manapoints Anton can spend.
    std::cin >> x >> s;

    // Read Type 1 spell data.
    // a[i]: preparation time per potion if i-th Type 1 spell is used.
    std::vector<long long> a(m);
    for (int i = 0; i < m; ++i) {
        std::cin >> a[i];
    }
    // b[i]: manapoints cost for i-th Type 1 spell.
    std::vector<long long> b(m);
    for (int i = 0; i < m; ++i) {
        std::cin >> b[i];
    }

    // Read Type 2 spell data.
    // c[i]: number of potions instantly created if i-th Type 2 spell is used.
    std::vector<long long> c(k);
    for (int i = 0; i < k; ++i) {
        std::cin >> c[i];
    }
    // d[i]: manapoints cost for i-th Type 2 spell.
    std::vector<long long> d(k);
    for (int i = 0; i < k; ++i) {
        std::cin >> d[i];
    }

    // Initialize the minimum total time.
    // The worst-case scenario is preparing all 'n' potions at 'x' seconds each,
    // without using any spells. This is a valid initial upper bound.
    long long min_total_time = n * x;

    // Iterate through all possible choices for a Type 1 spell.
    // This loop considers 'm' actual Type 1 spells and one additional "dummy" case.
    // The dummy case (when i == m) represents not using any Type 1 spell.
    for (int i = 0; i < m + 1; ++i) {
        long long current_a; // Preparation time per potion for the current Type 1 choice.
        long long current_b; // Manapoints cost for the current Type 1 choice.

        if (i < m) {
            // If 'i' is less than 'm', we are considering an actual Type 1 spell.
            current_a = a[i];
            current_b = b[i];
        } else {
            // If 'i' is equal to 'm', this is the dummy case: no Type 1 spell is used.
            // The preparation time per potion remains 'x', and the cost is 0.
            current_a = x;
            current_b = 0;
        }

        // If the cost of the current Type 1 spell exceeds the total manapoints 's',
        // this spell cannot be used, so we skip to the next iteration.
        if (current_b > s) {
            continue;
        }

        // Calculate the remaining manapoints available for a Type 2 spell.
        long long remaining_s = s - current_b;

        // Find the best Type 2 spell that can be afforded with 'remaining_s'.
        // We want to maximize the number of instantly created potions (c_j)
        // while ensuring its cost (d_j) is within 'remaining_s'.
        // Since 'd' and 'c' arrays are guaranteed to be non-decreasing,
        // we can use binary search (std::upper_bound) on the 'd' array.
        // std::upper_bound returns an iterator to the first element in 'd'
        // that is strictly greater than 'remaining_s'.
        auto it = std::upper_bound(d.begin(), d.end(), remaining_s);

        long long potions_instantly_created = 0; // Initialize to 0 if no Type 2 spell is used.
        if (it != d.begin()) {
            // If 'it' is not the beginning of the 'd' array, it means there is at least one
            // Type 2 spell whose cost is less than or equal to 'remaining_s'.
            // The element just before 'it' (i.e., *(it-1)) corresponds to the Type 2 spell
            // with the highest cost that is still affordable.
            // Since 'c' is non-decreasing, this spell also provides the maximum 'c_j'
            // among all affordable Type 2 spells.
            int idx = std::distance(d.begin(), it - 1); // Get the index of this spell.
            potions_instantly_created = c[idx]; // Get the potions created by this best Type 2 spell.
        }
        // If 'it == d.begin()', it means all Type 2 spells are too expensive (d_j > remaining_s),
        // so 'potions_instantly_created' remains 0, which is correct.

        // Calculate the number of potions that still need to be prepared manually.
        // Use std::max(0LL, ...) to ensure the count doesn't go negative if
        // more potions are instantly created than needed (e.g., n=10, c_j=15).
        long long potions_to_make = std::max(0LL, n - potions_instantly_created);

        // Calculate the total time for this specific combination of Type 1 and Type 2 spells.
        // This is (potions_to_make * current_a).
        // Use long long for multiplication to prevent potential overflow, as 'n' and 'x' can be large.
        long long current_total_time = potions_to_make * current_a;

        // Update the overall minimum total time found so far.
        min_total_time = std::min(min_total_time, current_total_time);
    }

    // Print the final minimum total time required.
    std::cout << min_total_time << std::endl;

    return 0; // Indicate successful execution.
}
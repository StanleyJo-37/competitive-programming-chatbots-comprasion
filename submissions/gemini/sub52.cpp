#include <iostream> // Required for input/output operations (cin, cout)
#include <algorithm> // Required for std::min and std::max functions

int main() {
    // Optimize C++ standard streams for competitive programming.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams,
    // potentially speeding up I/O operations.
    // std::cin.tie(NULL) prevents std::cout from flushing before each std::cin,
    // further speeding up I/O.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    // Declare variables to store the input values.
    // 'a': number of ties
    // 'b': number of scarves
    // 'c': number of vests
    // 'd': number of jackets
    // 'e': cost of a suit of the first type (tie + jacket)
    // 'f': cost of a suit of the second type (scarf + vest + jacket)
    int a, b, c, d, e, f;

    // Read the input values.
    std::cin >> a >> b >> c >> d >> e >> f;

    // Initialize max_total_cost to 0. This variable will store the maximum possible cost.
    // Use long long to prevent potential overflow. The maximum possible cost can be
    // (100,000 ties * 1,000 cost/tie-suit) + (100,000 scarves * 1,000 cost/scarf-suit)
    // which is approximately 2 * 10^8. While this fits in a 32-bit signed int (max ~2*10^9),
    // using long long is a safer practice in competitive programming to avoid unexpected overflows
    // with slightly larger constraints or intermediate calculations.
    long long max_total_cost = 0;

    // Iterate through all possible numbers of suits of the first type (tie + jacket).
    // Let 'i' be the number of Type 1 suits.
    // The number of Type 1 suits 'i' is limited by the available ties 'a' and jackets 'd'.
    // So, 'i' can range from 0 up to the minimum of 'a' and 'd'.
    for (int i = 0; i <= std::min(a, d); ++i) {
        // 'i' Type 1 suits are made. These suits consume 'i' ties and 'i' jackets.

        // Calculate the number of jackets remaining after making 'i' Type 1 suits.
        // Since 'i' is iterated up to std::min(a, d), 'i' will never exceed 'd',
        // so 'jackets_remaining' will always be non-negative.
        int jackets_remaining = d - i;

        // Calculate the maximum number of Type 2 suits (scarf + vest + jacket) that can be made
        // with the remaining items.
        // Type 2 suits are limited by three factors:
        // 1. The total number of scarves available ('b').
        // 2. The total number of vests available ('c').
        // 3. The number of jackets remaining after Type 1 suits were made ('jackets_remaining').
        // We take the minimum of these three to find the bottleneck.
        int max_type2_suits = std::min({b, c, jackets_remaining});

        // Calculate the current total cost for this specific combination:
        // 'i' Type 1 suits and 'max_type2_suits' Type 2 suits.
        // Cast 'i' and 'max_type2_suits' to long long before multiplication to ensure
        // the products are calculated using long long arithmetic, preventing potential
        // intermediate overflow if costs 'e' or 'f' were much larger.
        long long current_cost = (long long)i * e + (long long)max_type2_suits * f;

        // Update the overall maximum total cost found so far.
        // std::max compares the current maximum with the cost of the current combination.
        max_total_cost = std::max(max_total_cost, current_cost);
    }

    // Print the final maximum total cost that can be achieved.
    std::cout << max_total_cost << std::endl;

    return 0; // Indicate successful program execution.
}
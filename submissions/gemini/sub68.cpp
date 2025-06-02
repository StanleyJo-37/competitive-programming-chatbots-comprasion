#include <iostream> // Required for input/output operations (cin, cout)
#include <vector>   // Required for using std::vector to store lantern brightness values
#include <algorithm> // Required for std::max and std::min functions
#include <climits>  // Required for LLONG_MAX and LLONG_MIN constants

int main() {
    // Optimize C++ standard streams for competitive programming.
    // This unties cin/cout from C's stdio and prevents flushing cout before cin.
    std::ios_base::sync_with_stdio(false);
    // This disables synchronization with C's stdio, potentially speeding up I/O.
    std::cin.tie(NULL);

    int n, m;
    // Read the number of Tommy's lanterns (n) and Banban's lanterns (m).
    std::cin >> n >> m;

    // Declare vectors to store the brightness values of lanterns.
    // 'a' for Tommy's lanterns, 'b' for Banban's lanterns.
    std::vector<long long> a(n);
    std::vector<long long> b(m);

    // Read Tommy's lantern brightness values.
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    // Read Banban's lantern brightness values.
    for (int i = 0; i < m; ++i) {
        std::cin >> b[i];
    }

    // Initialize 'min_max_product' to the largest possible long long value.
    // This variable will store the minimum of Banban's maximum products.
    // Tommy wants to minimize Banban's maximum product, so we start with a very large value
    // and update it with smaller maximums found.
    long long min_max_product = LLONG_MAX;

    // Tommy's turn: Iterate through each of his lanterns to decide which one to hide.
    // 'i' represents the index of the lantern Tommy chooses to hide.
    for (int i = 0; i < n; ++i) {
        // Initialize 'current_max_product' to the smallest possible long long value.
        // This variable will store the maximum product Banban can achieve
        // if Tommy hides the lantern at index 'i'.
        // Banban wants to maximize the product, so we start with a very small value
        // and update it with larger products found.
        long long current_max_product = LLONG_MIN;

        // Banban's turn: Iterate through all of Tommy's non-hidden lanterns.
        // 'j' represents the index of Tommy's lantern Banban considers picking.
        for (int j = 0; j < n; ++j) {
            // If 'j' is the index of the lantern Tommy hid, skip it.
            if (i == j) {
                continue;
            }

            // Banban's turn: Iterate through all of his own lanterns.
            // 'k' represents the index of Banban's lantern Banban considers picking.
            for (int k = 0; k < m; ++k) {
                // Calculate the product of the brightness of the two chosen lanterns.
                // Use long long for the product to prevent overflow, as brightness values
                // can be up to 10^9, making products up to 10^18.
                long long product = a[j] * b[k];
                
                // Banban wants to maximize this product.
                // Update 'current_max_product' if the current product is larger.
                current_max_product = std::max(current_max_product, product);
            }
        }
        // After iterating through all possible pairs (Tommy's non-hidden, Banban's),
        // 'current_max_product' holds the maximum product Banban can achieve
        // if Tommy hides the lantern at index 'i'.

        // Tommy wants to minimize this maximum product.
        // Update 'min_max_product' if 'current_max_product' is smaller than
        // any previously found maximum product.
        min_max_product = std::min(min_max_product, current_max_product);
    }

    // Print the final result, which is the brightness of the chosen pair
    // when both players play optimally.
    std::cout << min_max_product << std::endl;

    return 0; // Indicate successful execution.
}

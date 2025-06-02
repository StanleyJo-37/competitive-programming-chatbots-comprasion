#include <iostream> // Required for input/output operations (cin, cout)
#include <vector>   // Required for using std::vector

// Define a constant for the maximum possible price.
// Prices x_i are guaranteed to be between 1 and 100,000.
// This constant determines the size of our frequency/prefix sum array.
const int MAX_PRICE = 100000;

int main() {
    // Optimize C++ standard streams for faster input/output.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams,
    // which can speed up I/O operations significantly.
    // std::cin.tie(NULL) prevents std::cout from being flushed before each std::cin operation,
    // further improving I/O performance.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n; // Declare variable for the number of shops
    std::cin >> n; // Read the number of shops from standard input

    // Create a vector named 'prefix_counts'.
    // Its size is MAX_PRICE + 1 to accommodate prices from 0 up to MAX_PRICE (inclusive).
    // It's initialized with all elements set to 0.
    // Initially, this vector will be used as a frequency array to count occurrences of each price.
    std::vector<int> prefix_counts(MAX_PRICE + 1, 0);

    // Loop n times to read the prices of bottles in each shop.
    for (int i = 0; i < n; ++i) {
        int x; // Declare variable for the current shop's price
        std::cin >> x; // Read the price x_i

        // Increment the count for the price 'x' in our 'prefix_counts' array.
        // For example, if x is 5, prefix_counts[5] will be incremented.
        // This effectively builds a frequency map of prices.
        prefix_counts[x]++;
    }

    // Compute the prefix sums.
    // After this loop, prefix_counts[i] will store the total number of shops
    // where the price of a bottle is less than or equal to 'i'.
    // This transformation allows us to answer queries in O(1) time.
    // We iterate from 1 up to MAX_PRICE, accumulating counts.
    for (int i = 1; i <= MAX_PRICE; ++i) {
        prefix_counts[i] += prefix_counts[i - 1];
    }

    int q; // Declare variable for the number of days (queries)
    std::cin >> q; // Read the number of queries

    // Process each query.
    // Loop q times, once for each day Vasiliy plans to buy the drink.
    for (int i = 0; i < q; ++i) {
        int m; // Declare variable for the money Vasiliy can spend on the current day
        std::cin >> m; // Read the amount of money m_i

        // Determine the number of shops Vasiliy can buy from based on his money 'm'.
        // If 'm' is greater than or equal to MAX_PRICE, it means Vasiliy has enough money
        // to buy from any shop whose price is within our tracked range (1 to MAX_PRICE).
        // In this scenario, the answer is the total count of all shops with prices up to MAX_PRICE,
        // which is stored in prefix_counts[MAX_PRICE].
        if (m >= MAX_PRICE) {
            std::cout << prefix_counts[MAX_PRICE] << "\n";
        } else {
            // If 'm' is less than MAX_PRICE, Vasiliy can only afford shops
            // with prices less than or equal to 'm'.
            // The value prefix_counts[m] directly gives this count,
            // as it represents the sum of frequencies for all prices from 1 up to 'm'.
            std::cout << prefix_counts[m] << "\n";
        }
    }

    return 0; // Indicate successful program execution
}

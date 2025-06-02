#include <iostream> // Required for input/output operations (std::cin, std::cout)
#include <vector>   // Required for using std::vector to store the items in the row
#include <algorithm> // Required for std::find and potentially other algorithms like std::erase, std::insert
#include <iterator>  // Required for std::distance, which is used to calculate position from iterators

int main() {
    // Optimize C++ standard streams for competitive programming.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard I/O.
    // std::cin.tie(NULL) prevents std::cout from flushing before each std::cin operation.
    // These optimizations can significantly speed up I/O in competitive programming.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, m, k;
    // Read the number of users (n), the number of items each user wants to buy (m),
    // and the total number of distinct items available at the market (k).
    std::cin >> n >> m >> k;

    // Create a std::vector to represent the current arrangement of items in the store row.
    // The vector is initialized with a size of 'k' to hold all distinct items.
    std::vector<int> current_row(k);
    // Read the initial positions of the 'k' items into the vector.
    // The items are numbered from 1 to k.
    for (int i = 0; i < k; ++i) {
        std::cin >> current_row[i];
    }

    // Initialize total_time to 0.
    // Using 'long long' for total_time to ensure it can hold large sums without overflow,
    // although for the given constraints (N, M, K <= 100), an 'int' would typically suffice
    // as the maximum total time is 100 * 100 * 100 = 1,000,000. 'long long' is a safer practice.
    long long total_time = 0;

    // Loop through each of the 'n' customers.
    for (int i = 0; i < n; ++i) {
        // For each customer, loop through 'm' items they want to buy.
        for (int j = 0; j < m; ++j) {
            int item_id;
            // Read the ID of the item the current customer wants to collect.
            std::cin >> item_id;

            // Find the item_id within the current_row vector.
            // std::find returns an iterator to the first element that matches item_id,
            // or current_row.end() if the item is not found (though problem implies it always exists).
            auto it = std::find(current_row.begin(), current_row.end(), item_id);

            // Calculate the 1-based position of the item.
            // std::distance calculates the number of elements between current_row.begin() and 'it'.
            // This gives the 0-based index. Adding 1 converts it to the 1-based position as required.
            int position = std::distance(current_row.begin(), it) + 1;

            // Add the time taken to find this item (its 1-based position) to the total time.
            total_time += position;

            // Move the found item to the front of the row.
            // 1. Erase the item from its current position.
            //    std::vector::erase shifts all elements after the erased one to the left,
            //    maintaining contiguity. This operation takes O(K) time.
            current_row.erase(it);
            // 2. Insert the item at the beginning of the row.
            //    std::vector::insert at the beginning shifts all existing elements to the right,
            //    making space for the new element. This operation also takes O(K) time.
            current_row.insert(current_row.begin(), item_id);
        }
    }

    // After processing all customers and their orders, print the accumulated total time.
    std::cout << total_time << std::endl;

    return 0; // Indicate successful program execution.
}
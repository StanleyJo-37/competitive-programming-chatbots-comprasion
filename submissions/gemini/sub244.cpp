#include <iostream> // Required for input/output operations (std::cin, std::cout)
#include <vector>   // Required for std::vector

// Fenwick Tree (also known as Binary Indexed Tree or BIT) class
// This data structure allows for efficient prefix sum queries and point updates.
class FenwickTree {
private:
    std::vector<int> bit; // The internal array representing the Fenwick Tree
    int size;             // The size of the array that the Fenwick Tree covers

public:
    // Constructor: Initializes the Fenwick Tree for an array of 'n' elements.
    // The BIT array is 1-indexed internally, so its size is n + 1.
    FenwickTree(int n) : size(n), bit(n + 1, 0) {}

    // Updates the value at a specific index by adding 'delta'.
    // 'idx' is 0-indexed (as used in the problem), so it's converted to 1-indexed for BIT operations.
    void update(int idx, int delta) {
        idx++; // Convert to 1-based indexing
        // Traverse up the tree, updating relevant nodes
        while (idx <= size) {
            bit[idx] += delta;
            idx += idx & (-idx); // Move to the next parent node
        }
    }

    // Queries the prefix sum up to a specific index (inclusive).
    // 'idx' is 0-indexed, so it's converted to 1-indexed for BIT operations.
    int query(int idx) {
        idx++; // Convert to 1-based indexing
        int sum = 0;
        // Traverse down the tree, summing up relevant nodes
        while (idx > 0) {
            sum += bit[idx];
            idx -= idx & (-idx); // Move to the parent node
        }
        return sum;
    }
};

int main() {
    // Optimize C++ standard streams for faster input/output.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams.
    // std::cin.tie(NULL) prevents std::cout from flushing before std::cin reads input.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    std::cin >> n; // Read the number of coins

    std::vector<int> p(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> p[i]; // Read the positions where coins are replaced
    }

    // `is_X` array: `is_X[i]` is true if the coin at 0-indexed position `i` is 'X' (in circulation),
    // and false if it's 'O' (out of circulation). Initially, all coins are 'O'.
    std::vector<bool> is_X(n, false);

    // Fenwick Tree `ft` is used to efficiently count the number of 'X' coins in any prefix.
    // When a coin becomes 'X', we update its position in the BIT by adding 1.
    // A query for a prefix sum then gives the count of 'X' coins in that range.
    FenwickTree ft(n);

    // `current_rightmost_O_idx` tracks the 0-indexed position of the rightmost 'O' coin.
    // Initially, all coins are 'O', so the rightmost 'O' is at `n-1`.
    // If all coins become 'X', this index will become -1.
    int current_rightmost_O_idx = n - 1;

    // Print the hardness of ordering for the initial state.
    // Initially, all coins are 'O' (`O O ... O`). This sequence is already sorted.
    // Dima makes one pass, finds no swaps, and terminates. So, hardness is 1.
    std::cout << 1;

    // Process each coin replacement operation
    for (int i = 0; i < n; ++i) {
        int pos = p[i] - 1; // Convert the 1-indexed input position to a 0-indexed array position

        // Mark the coin at `pos` as 'X' (in circulation).
        is_X[pos] = true;
        // Update the Fenwick Tree: add 1 at `pos` to reflect that this coin is now 'X'.
        ft.update(pos, 1);

        // Adjust `current_rightmost_O_idx`.
        // If the coin that just became 'X' was the `current_rightmost_O_idx`,
        // we need to find the new rightmost 'O' coin by moving `current_rightmost_O_idx` leftwards.
        // This loop continues as long as `current_rightmost_O_idx` is valid (>=0)
        // and the coin at that position is now 'X'.
        // This `while` loop's total iterations across all `N` steps is at most `N`,
        // making its amortized cost O(1) per step.
        while (current_rightmost_O_idx >= 0 && is_X[current_rightmost_O_idx]) {
            current_rightmost_O_idx--;
        }

        // Calculate the hardness of ordering based on the derived formula:
        // Hardness = 1 + (number of 'X' coins to the left of the rightmost 'O' coin).
        int num_X_left_of_R;
        if (current_rightmost_O_idx == -1) {
            // If `current_rightmost_O_idx` is -1, it means all coins are 'X'.
            // In this case, there are no 'O' coins, so there are no 'X' coins
            // to the left of any 'O' coin. The count is 0.
            num_X_left_of_R = 0;
        } else {
            // Otherwise, query the Fenwick Tree for the sum of 'X' coins
            // from index 0 up to `current_rightmost_O_idx - 1`.
            // This gives the count of 'X' coins strictly to the left of the rightmost 'O' coin.
            num_X_left_of_R = ft.query(current_rightmost_O_idx - 1);
        }

        // Print the calculated hardness, separated by a space.
        std::cout << " " << (1 + num_X_left_of_R);
    }
    std::cout << std::endl; // Print a newline character at the end of the output

    return 0; // Indicate successful execution
}

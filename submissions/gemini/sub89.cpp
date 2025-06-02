#include <iostream> // Required for input/output operations (std::cin, std::cout, std::endl)
#include <vector>   // Not strictly necessary for this solution, but often useful
#include <string>   // Required for reading the passenger order string
#include <set>      // Required for std::set, which provides ordered storage and efficient min/max retrieval
#include <algorithm> // Not strictly necessary, but often useful for various algorithms

int main() {
    // Optimize C++ standard streams for competitive programming.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard I/O,
    // potentially speeding up I/O operations.
    // std::cin.tie(NULL) prevents std::cin from flushing std::cout before each input operation,
    // further improving I/O performance.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    std::cin >> n; // Read the number of rows in the bus.

    // A std::set is used to store rows that are currently empty.
    // It stores std::pair<int, int>, where the first element is the seat width (w_i)
    // and the second element is the original 1-based row index.
    // std::set automatically keeps its elements sorted in ascending order based on the pair's first element,
    // then by the second element if the first elements are equal.
    // This allows efficient retrieval of the row with the smallest width (using .begin()).
    std::set<std::pair<int, int>> empty_rows;

    // A std::set is used to store rows that have exactly one seat occupied (by an introvert).
    // Similar to empty_rows, it stores {width, row_index}.
    // This set also keeps elements sorted by width in ascending order.
    // To find the row with the largest width among these, we will use .rbegin() (reverse iterator to the last element).
    std::set<std::pair<int, int>> partially_occupied_rows;

    // Populate the 'empty_rows' set with all initial rows.
    // Rows are 1-indexed in the problem description, so we use 'i' from 1 to 'n'.
    for (int i = 1; i <= n; ++i) {
        int w;
        std::cin >> w; // Read the width of the seats for the i-th row.
        empty_rows.insert({w, i}); // Insert the width and its corresponding row index into the set.
    }

    std::string passenger_order;
    std::cin >> passenger_order; // Read the string describing the order of passengers.

    // Iterate through each character in the passenger_order string.
    // Each character represents a passenger entering the bus.
    for (char passenger_type : passenger_order) {
        if (passenger_type == '0') { // If the passenger is an introvert ('0')
            // An introvert chooses an empty row with the smallest seat width.
            // In a std::set, the smallest element is always at the beginning.
            auto it = empty_rows.begin(); // Get an iterator to the smallest element.
            int row_idx = it->second;     // Extract the original row index from the pair.

            std::cout << row_idx << " "; // Print the chosen row index, followed by a space.

            // After an introvert takes a seat, this row is no longer empty; it now has one occupied seat.
            // So, move this row from 'empty_rows' to 'partially_occupied_rows'.
            partially_occupied_rows.insert(*it); // Insert the pair {width, row_idx} into the 'partially_occupied_rows' set.
            empty_rows.erase(it);                // Remove the element from the 'empty_rows' set.
        } else { // If the passenger is an extrovert ('1')
            // An extrovert chooses a row where exactly one seat is occupied (by an introvert)
            // and among these, chooses the one with the largest seat width.
            // In a std::set, the largest element is at the reverse beginning (accessed via .rbegin()).
            auto it = partially_occupied_rows.rbegin(); // Get a reverse iterator to the largest element.
            int row_idx = it->second;                   // Extract the original row index from the pair.

            std::cout << row_idx << " "; // Print the chosen row index, followed by a space.

            // After an extrovert takes a seat, this row becomes fully occupied (both seats taken).
            // Therefore, it is removed from 'partially_occupied_rows' and does not need to be tracked further.
            // To erase an element pointed to by a reverse_iterator, we can dereference it to get the value
            // and then use the erase-by-value overload of std::set::erase.
            partially_occupied_rows.erase(*it); // Erase the pair {width, row_idx} from the set.
        }
    }
    std::cout << std::endl; // Print a newline character at the end of all output.

    return 0; // Indicate successful execution.
}

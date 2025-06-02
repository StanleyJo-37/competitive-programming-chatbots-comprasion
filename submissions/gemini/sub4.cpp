#include <iostream> // Required for input/output operations (std::cin, std::cout, std::endl)
#include <vector>   // Required for using std::vector to store notes

void solve() {
    // Declare an integer 'n' to store the length of the song.
    int n;
    // Read the value of 'n' from standard input.
    std::cin >> n;

    // Declare a std::vector of integers 'x' of size 'n' to store the notes.
    // The problem states notes are already sorted in non-decreasing order.
    std::vector<int> x(n);
    // Loop to read 'n' notes into the vector.
    for (int i = 0; i < n; ++i) {
        std::cin >> x[i];
    }

    // Initialize 'current_max_note_value' to 0. This variable will keep track
    // of the largest note value successfully included in our diverse set so far.
    // Since all notes are positive integers (1 <= x_i), 0 is a safe initial value
    // that any valid note will be greater than.
    int current_max_note_value = 0;
    // Initialize 'diversity_count' to 0. This variable will count the number
    // of different notes in the final song.
    int diversity_count = 0;

    // Iterate through each note in the sorted input sequence.
    for (int i = 0; i < n; ++i) {
        // Case 1: The current note 'x[i]' is strictly greater than the
        // 'current_max_note_value'.
        // This means 'x[i]' can be chosen as a new distinct note without any modification.
        // This is the optimal choice because it uses the smallest possible value
        // for the current note, leaving 'x[i] + 1' available for future notes
        // if they happen to conflict with 'x[i]'. This greedy choice maximizes
        // flexibility for subsequent decisions.
        if (x[i] > current_max_note_value) {
            current_max_note_value = x[i]; // Update the largest chosen note.
            diversity_count++;             // Increment the diversity count.
        }
        // Case 2: The current note 'x[i]' is equal to the 'current_max_note_value'.
        // This means 'x[i]' cannot be chosen as it is, because it would not
        // increase the diversity (it's a duplicate of the last chosen note).
        // In this situation, we must try to increase 'x[i]' by 1 to 'x[i] + 1'.
        // Since 'x[i]' is equal to 'current_max_note_value', 'x[i] + 1' will
        // always be strictly greater than 'current_max_note_value'.
        // Therefore, 'x[i] + 1' will always be a new distinct note.
        else if (x[i] == current_max_note_value) {
            current_max_note_value = x[i] + 1; // Update the largest chosen note to x[i]+1.
            diversity_count++;                 // Increment the diversity count.
        }
        // Case 3: The current note 'x[i]' is less than 'current_max_note_value'.
        // This implies that 'x[i]' is already less than or equal to a note
        // we have already successfully included in our diverse set.
        // We cannot use 'x[i]' as it is not distinct.
        // We also cannot use 'x[i] + 1' because if 'x[i] < current_max_note_value',
        // then 'x[i] + 1' could be less than or equal to 'current_max_note_value'.
        // For example, if 'current_max_note_value' is 5 and 'x[i]' is 4,
        // then 'x[i] + 1' would be 5, which is not distinct.
        // In this case, neither 'x[i]' nor 'x[i] + 1' can contribute to increasing
        // the diversity. So, we simply skip this note and move to the next one.
        // The 'else' branch implicitly handles this by doing nothing.
    }

    // Output the final maximal diversity count for the current test case.
    std::cout << diversity_count << std::endl;
}

int main() {
    // Optimize C++ standard streams for competitive programming.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams,
    // which can speed up I/O operations.
    std::ios_base::sync_with_stdio(false);
    // std::cin.tie(NULL) unties std::cin from std::cout, meaning std::cin will not
    // flush std::cout before reading input, further speeding up I/O.
    std::cin.tie(NULL);

    // Declare an integer 't' to store the number of test cases.
    int t;
    // Read the number of test cases.
    std::cin >> t;

    // Loop 't' times, calling the 'solve' function for each test case.
    while (t--) {
        solve();
    }

    // Return 0 to indicate successful execution.
    return 0;
}
#include <iostream> // Required for input/output operations (cin, cout)
#include <vector>   // Required for using std::vector

// Function to solve a single test case
void solve() {
    int k, n, m; // k: initial lines, n: Monocarp's actions count, m: Polycarp's actions count
    std::cin >> k >> n >> m; // Read k, n, m

    std::vector<int> a(n); // Monocarp's actions
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i]; // Read Monocarp's actions
    }

    std::vector<int> b(m); // Polycarp's actions
    for (int i = 0; i < m; ++i) {
        std::cin >> b[i]; // Read Polycarp's actions
    }

    std::vector<int> result_sequence; // Stores the combined sequence of actions
    int ptr_a = 0; // Pointer for Monocarp's actions, indicates the next action to consider
    int ptr_b = 0; // Pointer for Polycarp's actions, indicates the next action to consider

    // Loop until all actions from both Monocarp and Polycarp are processed
    // The total number of actions in the combined sequence must be n + m
    while (ptr_a < n || ptr_b < m) {
        bool action_taken_in_current_step = false; // Flag to check if an action was successfully taken in this iteration

        // Greedy strategy: Prioritize 'add new line' (0) actions.
        // These actions increase 'k', which is beneficial as it allows more 'change line' actions later.
        // If Monocarp's next action is 'add new line' (0) and Monocarp still has actions left
        if (ptr_a < n && a[ptr_a] == 0) {
            result_sequence.push_back(a[ptr_a]); // Add Monocarp's action to the result sequence
            k++; // Increment current number of lines in the file
            ptr_a++; // Move Monocarp's pointer to the next action
            action_taken_in_current_step = true; // Mark that an action was taken
        }
        // Else if Polycarp's next action is 'add new line' (0) and Polycarp still has actions left
        // This branch is taken if Monocarp's next action is not '0' or Monocarp has no more actions
        else if (ptr_b < m && b[ptr_b] == 0) {
            result_sequence.push_back(b[ptr_b]); // Add Polycarp's action to the result sequence
            k++; // Increment current number of lines in the file
            ptr_b++; // Move Polycarp's pointer to the next action
            action_taken_in_current_step = true; // Mark that an action was taken
        }
        // If no 'add new line' action is available from either person,
        // try 'change line' actions.
        // If Monocarp's next action is 'change line' (a[ptr_a] > 0) and it's valid (line exists)
        // and Monocarp still has actions left
        else if (ptr_a < n && a[ptr_a] <= k) {
            result_sequence.push_back(a[ptr_a]); // Add Monocarp's action to the result sequence
            // 'k' does not change for 'change line' actions
            ptr_a++; // Move Monocarp's pointer to the next action
            action_taken_in_current_step = true; // Mark that an action was taken
        }
        // Else if Polycarp's next action is 'change line' (b[ptr_b] > 0) and it's valid (line exists)
        // and Polycarp still has actions left
        // This branch is taken if Monocarp's next action is not '0' or not valid, or Monocarp has no more actions
        else if (ptr_b < m && b[ptr_b] <= k) {
            result_sequence.push_back(b[ptr_b]); // Add Polycarp's action to the result sequence
            // 'k' does not change for 'change line' actions
            ptr_b++; // Move Polycarp's pointer to the next action
            action_taken_in_current_step = true; // Mark that an action was taken
        }

        // If, after checking all possibilities, no valid action could be taken in this iteration,
        // it means no correct sequence exists.
        if (!action_taken_in_current_step) {
            std::cout << -1 << std::endl; // Print -1 to indicate no solution
            return; // Exit the function for this test case
        }
    }

    // If the loop completes, it means a valid sequence was successfully constructed.
    // Print the elements of the result sequence separated by spaces.
    for (int i = 0; i < result_sequence.size(); ++i) {
        std::cout << result_sequence[i] << (i == result_sequence.size() - 1 ? "" : " "); // Print action, add space if not the last element
    }
    std::cout << std::endl; // Print a newline character after the sequence for this test case
}

int main() {
    // Optimize C++ standard streams for competitive programming.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard I/O.
    // std::cin.tie(NULL) prevents std::cout from being flushed before each std::cin operation.
    // These two lines can significantly speed up I/O in C++ programs.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t; // Variable to store the number of test cases
    std::cin >> t; // Read the number of test cases

    // Loop through each test case
    while (t--) {
        // The problem statement mentions an empty line before each test case.
        // When using `std::cin >> int_variable`, `std::cin` automatically skips
        // any leading whitespace characters (spaces, tabs, newlines), including
        // empty lines. Therefore, no explicit code is needed to handle these empty lines.
        solve(); // Call the solve function for the current test case
    }

    return 0; // Indicate successful program execution
}

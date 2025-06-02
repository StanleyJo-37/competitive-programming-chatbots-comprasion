#include <iostream> // Required for input/output operations (cin, cout)
#include <vector>   // Required for using std::vector to store explorer inexperience values
#include <algorithm> // Required for std::sort to sort the inexperience values

// Function to solve a single test case
void solve() {
    int n; // Declare an integer variable 'n' to store the number of young explorers
    std::cin >> n; // Read the number of explorers for the current test case

    std::vector<int> e(n); // Declare a vector 'e' of size 'n' to store inexperience values
    for (int i = 0; i < n; ++i) {
        std::cin >> e[i]; // Read each explorer's inexperience value into the vector
    }

    // Sort the inexperience values in ascending order.
    // This is crucial for the greedy strategy to work. By processing explorers
    // with lower inexperience first, we ensure that the 'max_e_in_current_group'
    // is always the inexperience of the last explorer added to the current group,
    // and we can form a valid group as soon as possible, leaving more explorers
    // for subsequent groups.
    std::sort(e.begin(), e.end());

    int num_groups = 0; // Initialize a counter for the total number of groups formed
    int current_group_members = 0; // Initialize a counter for members in the current group being formed
    int max_e_in_current_group = 0; // Initialize a variable to track the maximum inexperience
                                    // among explorers currently considered for the group.
                                    // Since the array is sorted, this will always be the
                                    // inexperience of the last explorer added to the current group.

    // Iterate through the sorted explorers
    for (int i = 0; i < n; ++i) {
        // Add the current explorer to the potential group
        current_group_members++;
        // Update the maximum inexperience in the current group.
        // Since 'e' is sorted, e[i] will always be greater than or equal to
        // any previous e[j] (where j < i) that was added to this group.
        // So, max_e_in_current_group simply becomes e[i].
        max_e_in_current_group = e[i]; 

        // Check if the current group can be formed.
        // A group of 'S' members is valid if every member 'm' in it has inexperience e_m <= S.
        // Since we are adding explorers in increasing order of inexperience,
        // the maximum inexperience in the current group is 'max_e_in_current_group' (which is e[i]).
        // If the number of members in the current group ('current_group_members')
        // is greater than or equal to 'max_e_in_current_group', then all members
        // (whose inexperience values are <= max_e_in_current_group) satisfy the condition.
        if (current_group_members >= max_e_in_current_group) {
            // If the condition is met, we can form a group.
            // This greedy choice forms a group as soon as it's valid, using the minimum
            // number of explorers (from the current sequence) to satisfy the condition.
            // This leaves the maximum number of remaining explorers for subsequent groups,
            // which is optimal for maximizing the total number of groups.
            num_groups++; // Increment the count of formed groups
            
            // Reset counters for the next group
            current_group_members = 0;
            max_e_in_current_group = 0;
        }
    }

    // Print the total number of groups formed for the current test case
    std::cout << num_groups << std::endl;
}

int main() {
    // Optimize C++ standard streams for faster input/output.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams.
    // std::cin.tie(NULL) prevents std::cout from flushing before std::cin reads input.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t; // Declare an integer variable 't' to store the number of test cases
    std::cin >> t; // Read the number of test cases

    // Loop through each test case
    while (t--) {
        solve(); // Call the solve function for each test case
    }

    return 0; // Indicate successful execution
}

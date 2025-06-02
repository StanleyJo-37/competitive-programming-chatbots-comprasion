#include <iostream> // Required for input/output operations (cin, cout)
#include <vector>   // Required for using std::vector to store skills
#include <algorithm> // Required for std::sort and std::abs

int main() {
    // Optimize C++ standard streams for competitive programming.
    // This unties cin/cout from C's stdio and disables synchronization,
    // potentially speeding up I/O operations.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n; // Declare an integer variable 'n' for the number of boys
    std::cin >> n; // Read the number of boys from standard input

    // Declare a vector 'a' of size 'n' to store boys' dancing skills.
    std::vector<int> a(n); 
    // Loop to read 'n' boy skills into the vector 'a'
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    int m; // Declare an integer variable 'm' for the number of girls
    std::cin >> m; // Read the number of girls from standard input

    // Declare a vector 'b' of size 'm' to store girls' dancing skills.
    std::vector<int> b(m);
    // Loop to read 'm' girl skills into the vector 'b'
    for (int i = 0; i < m; ++i) {
        std::cin >> b[i];
    }

    // Sort the boys' dancing skills in ascending order.
    // Sorting is crucial for the two-pointer greedy approach to work correctly.
    std::sort(a.begin(), a.end());
    // Sort the girls' dancing skills in ascending order.
    std::sort(b.begin(), b.end());

    int pairs = 0; // Initialize a counter for the number of formed pairs
    int i = 0;     // Pointer for the boys' skill array, starting from the smallest skill
    int j = 0;     // Pointer for the girls' skill array, starting from the smallest skill

    // Use a two-pointer approach to find the maximum number of pairs.
    // The loop continues as long as there are unconsidered boys and girls.
    while (i < n && j < m) {
        // Check if the current boy (a[i]) and girl (b[j]) can form a pair.
        // Their skill difference must be at most 1.
        if (std::abs(a[i] - b[j]) <= 1) {
            // If they can form a pair, increment the pairs count.
            pairs++;
            // Move to the next boy and next girl, as both are now paired.
            i++;
            j++;
        } else if (a[i] < b[j]) {
            // If the current boy's skill is significantly less than the current girl's skill
            // (i.e., a[i] < b[j] - 1, because if a[i] == b[j]-1, they would have paired),
            // then this boy cannot be paired with the current girl or any subsequent girl
            // (since girls' skills are sorted and only increase).
            // So, this boy must be skipped.
            i++;
        } else { // a[i] > b[j]
            // If the current girl's skill is significantly less than the current boy's skill
            // (i.e., b[j] < a[i] - 1, because if b[j] == a[i]-1, they would have paired),
            // then this girl cannot be paired with the current boy or any subsequent boy
            // (since boys' skills are sorted and only increase).
            // So, this girl must be skipped.
            j++;
        }
    }

    // Print the total number of pairs found.
    std::cout << pairs << std::endl;

    return 0; // Indicate successful execution
}

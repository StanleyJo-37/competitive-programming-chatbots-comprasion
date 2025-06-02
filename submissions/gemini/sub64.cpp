#include <iostream> // Required for input/output operations (cin, cout)
#include <vector>   // Required for std::vector to store numbers and permutations
#include <string>   // Required for std::string to handle k-digit numbers as strings
#include <algorithm> // Required for std::sort and std::next_permutation
#include <climits>  // Required for LLONG_MAX (or INT_MAX) for initial min_diff

int main() {
    // Optimize C++ standard streams for competitive programming.
    // Unties cin from cout, meaning cin won't flush cout before reading.
    // Disables synchronization with C standard I/O library.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, k; // n: number of integers, k: digit capacity
    std::cin >> n >> k;

    // Store the n k-digit integers as strings.
    // Using strings allows handling leading zeros and easy digit access.
    std::vector<std::string> numbers(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> numbers[i];
    }

    // Initialize a vector 'p' to represent the initial permutation of digit indices.
    // For k=4, p will be {0, 1, 2, 3}. These are the original column indices.
    std::vector<int> p(k);
    for (int i = 0; i < k; ++i) {
        p[i] = i;
    }

    // Initialize min_diff to a very large value.
    // This variable will store the minimum difference found across all permutations.
    long long min_diff = LLONG_MAX;

    // Iterate through all possible permutations of digit positions.
    // std::next_permutation generates permutations in lexicographical order.
    // The do-while loop ensures that the initial sorted permutation is also processed.
    do {
        long long current_min_val = LLONG_MAX; // Minimum number for the current permutation
        long long current_max_val = LLONG_MIN; // Maximum number for the current permutation

        // For each permutation, apply it to all n numbers.
        for (int i = 0; i < n; ++i) {
            std::string original_num_str = numbers[i];
            std::string rearranged_num_str(k, ' '); // Create a string to build the rearranged number

            // Build the rearranged number string based on the current permutation 'p'.
            // p[j] indicates which original digit index goes into the j-th position of the new number.
            // For example, if p = {2, 0, 3, 1} and original_num_str = "5237":
            // rearranged_num_str[0] = original_num_str[p[0]] = original_num_str[2] = '3'
            // rearranged_num_str[1] = original_num_str[p[1]] = original_num_str[0] = '5'
            // rearranged_num_str[2] = original_num_str[p[2]] = original_num_str[3] = '7'
            // rearranged_num_str[3] = original_num_str[p[3]] = original_num_str[1] = '2'
            // Resulting string: "3572"
            for (int j = 0; j < k; ++j) {
                rearranged_num_str[j] = original_num_str[p[j]];
            }

            // Convert the rearranged string to a long long integer.
            // std::stoll handles leading zeros correctly (e.g., "012" becomes 12).
            long long current_num = std::stoll(rearranged_num_str);

            // Update the minimum and maximum values for the current permutation.
            current_min_val = std::min(current_min_val, current_num);
            current_max_val = std::max(current_max_val, current_num);
        }

        // Calculate the difference for the current permutation and update the overall minimum difference.
        min_diff = std::min(min_diff, current_max_val - current_min_val);

    } while (std::next_permutation(p.begin(), p.end())); // Move to the next permutation

    // Print the final minimum difference found.
    std::cout << min_diff << std::endl;

    return 0; // Indicate successful execution
}
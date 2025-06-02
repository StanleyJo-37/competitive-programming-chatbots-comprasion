#include <iostream> // Required for input/output operations (cin, cout)
#include <vector>   // Required for using std::vector to store damages
#include <string>   // Required for using std::string to store the sequence of buttons
#include <algorithm> // Required for std::sort and std::min

int main() {
    // Optimize C++ standard streams for competitive programming.
    // This unties cin/cout from C's stdio and disables synchronization with C's stdio,
    // which can significantly speed up I/O operations.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n; // Declare n: the number of hits
    int k; // Declare k: the maximum number of times a button can be pressed in a row
    std::cin >> n >> k; // Read n and k from standard input

    std::vector<long long> a(n); // Declare a vector 'a' of size n to store damage values.
                                // Use long long because damage values can be up to 10^9,
                                // and their sum can exceed the capacity of a 32-bit integer.
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i]; // Read each damage value
    }

    std::string s; // Declare a string 's' to store the sequence of button presses
    std::cin >> s; // Read the string s

    long long total_damage = 0; // Initialize total damage to 0.
                                // Use long long for total_damage as it can be up to 2 * 10^14.

    int i = 0; // Initialize a pointer 'i' to the current position in the sequence

    // Iterate through the sequence of hits, processing them in blocks of identical characters.
    // The problem states that skipping a hit does not reset the consecutive press counter.
    // This implies that the constraint applies to *original* consecutive presses of a button,
    // regardless of whether a hit is skipped. Therefore, we should identify contiguous blocks
    // of the same character in the input string 's' and apply the 'k' limit to each block.
    while (i < n) {
        char current_char = s[i]; // Get the character for the current hit
        int j = i; // Initialize 'j' to find the end of the current block

        // Find the end of the consecutive block of 'current_char'
        while (j < n && s[j] == current_char) {
            j++; // Move 'j' forward as long as the character is the same
        }
        // At this point, 'j' is the index of the first character different from 'current_char'
        // or 'j' is equal to 'n' (end of string).
        // The block of 'current_char' spans from index 'i' to 'j-1'.

        std::vector<long long> current_block_damages; // Create a temporary vector to store damages for this block

        // Collect all damage values for the current block
        for (int p = i; p < j; ++p) {
            current_block_damages.push_back(a[p]);
        }

        // Sort the collected damages in descending order.
        // This is crucial for the greedy strategy: if we can only pick 'k' hits from a block
        // longer than 'k', we should pick the ones with the highest damage to maximize total damage.
        std::sort(current_block_damages.rbegin(), current_block_damages.rend());

        // Add the damages from the top 'k' (or fewer if the block is shorter than 'k') hits
        // to the total damage.
        // The number of hits we can take from this block is min(k, current_block_damages.size()).
        for (int count = 0; count < std::min((int)current_block_damages.size(), k); ++count) {
            total_damage += current_block_damages[count];
        }

        i = j; // Move 'i' to the start of the next block (which is 'j')
    }

    std::cout << total_damage << std::endl; // Print the maximum total damage

    return 0; // Indicate successful execution
}

#include <iostream> // Required for input/output operations (std::cin, std::cout).
#include <string>   // Required for using std::string to store puppy colors.
#include <vector>   // Required for using std::vector to store character counts.

int main() {
    // Optimize C++ standard streams for competitive programming.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard I/O.
    // std::cin.tie(NULL) prevents std::cout from flushing before each std::cin operation.
    // These optimizations can significantly speed up I/O, which is crucial for large inputs.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    std::cin >> n; // Read the number of puppies.

    std::string s;
    std::cin >> s; // Read the string representing the colors of the puppies.

    // Case 1: If there is only one puppy.
    // If n is 1, there's only one puppy, so all puppies are already of the same color.
    // No operations are needed, and it's always possible.
    if (n == 1) {
        std::cout << "Yes\n";
        return 0; // Exit the program.
    }

    // Case 2: If there are multiple puppies (n > 1).
    // We need to determine if it's possible to make all puppies the same color.
    // The key operation is: choose a color 'x' with at least two puppies,
    // and recolor all puppies of color 'x' into an arbitrary color 'y'.

    // The crucial observation is that if we can perform *at least one* operation,
    // we can eventually make all puppies the same color.
    // Why? Suppose we find a color 'x' that appears at least twice (count[x] >= 2).
    // We can choose this color 'x' and recolor all its puppies to any other color, say 'y'.
    // After this operation, the count of 'y' will be original_count(y) + original_count(x).
    // Since original_count(x) was at least 2, the new count of 'y' will also be at least 2.
    // This means we always have a color (the target color 'y') with at least two puppies.
    // We can then use this 'y' to absorb other colors that might have a count of 1.
    // By repeatedly picking the "large" group (which always has count >= 2) and merging
    // a singleton color into it, we can eventually consolidate all puppies into one color.

    // Therefore, the problem boils down to checking if there is *any* color
    // that appears at least twice in the initial string.
    // If such a color exists, it's "Yes".
    // If all colors appear exactly once (and n > 1), then no operation can be performed,
    // and it's "No".

    // Use a frequency array to count occurrences of each character ('a' through 'z').
    // 'a' corresponds to index 0, 'b' to 1, ..., 'z' to 25.
    std::vector<int> counts(26, 0); 
    for (char c : s) {
        counts[c - 'a']++; // Increment the count for the character 'c'.
    }

    // Iterate through the frequency counts to check if any color appears at least twice.
    bool possible = false;
    for (int i = 0; i < 26; ++i) {
        if (counts[i] >= 2) {
            possible = true; // Found a color with at least two puppies.
            break;           // No need to check further, the condition is met.
        }
    }

    // Output the result based on whether it's possible.
    std::cout << (possible ? "Yes" : "No") << "\n";

    return 0; // Indicate successful execution.
}

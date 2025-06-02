#include <string> // Required for std::string operations

// Function to generate the first 'n' digits of the Thue-Morse sequence.
std::string thue_morse(int n) {
    // The Thue-Morse sequence starts with "0".
    std::string sequence = "0";

    // The sequence is constructed iteratively. Each step involves appending
    // the bitwise complement of the current sequence to itself.
    // This process continues until the generated sequence is at least 'n' characters long.
    while (sequence.length() < n) {
        // Create a temporary string to build the complement part.
        std::string complement_part;
        // Iterate through each character of the current 'sequence'.
        for (char c : sequence) {
            // If the character is '0', its complement is '1'.
            // If the character is '1', its complement is '0'.
            if (c == '0') {
                complement_part += '1'; // Append '1' if current char is '0'
            } else {
                complement_part += '0'; // Append '0' if current char is '1'
            }
        }
        // Append the newly generated complement part to the existing sequence.
        sequence += complement_part;
    }

    // The problem requires returning only the first 'n' digits.
    // Since the sequence grows by doubling its length in each step (powers of 2),
    // the final 'sequence' string might be longer than 'n'.
    // We use std::string::substr to extract the desired first 'n' characters.
    return sequence.substr(0, n);
}

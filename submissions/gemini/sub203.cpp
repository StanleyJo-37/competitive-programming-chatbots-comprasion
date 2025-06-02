#include <string>   // Required for std::string
#include <vector>   // Required for std::vector
#include <sstream>  // Required for std::stringstream and std::getline
#include <algorithm> // Required for std::sort
#include <cctype>   // Required for std::tolower

// Function to calculate the 'som' value for a given name.
// 'som' is defined as the length of the firstname plus the sum of the ranks of its letters.
// 'A'/'a' have rank 1, 'B'/'b' rank 2, and so on.
long long calculate_som(const std::string& name) {
    long long sum_ranks = 0;
    // Iterate through each character of the name
    for (char c : name) {
        // Convert the character to lowercase to ensure consistent rank calculation
        // (e.g., 'A' and 'a' both map to rank 1).
        char lower_c = std::tolower(c);
        // Calculate the rank of the character. 'a' is 1, 'b' is 2, etc.
        // This is done by subtracting 'a' (ASCII value) and adding 1.
        sum_ranks += (lower_c - 'a' + 1);
    }
    // Add the length of the firstname to the sum of its character ranks to get 'som'.
    return name.length() + sum_ranks;
}

// Main function to solve the prize draw problem.
// Parameters:
//   st: A string containing comma-separated firstnames.
//   we: A vector of integer weights, corresponding to the firstnames in 'st'.
//   n: The rank (1-indexed) of the participant whose firstname should be returned.
// Returns:
//   The firstname of the participant at rank 'n', or an error message for edge cases.
std::string rank(const std::string& st, const std::vector<int>& we, int n) {
    // Handle the first edge case: if the input string of names is empty.
    if (st.empty()) {
        return "No participants";
    }

    // Use std::stringstream to easily parse the comma-separated names from the input string.
    std::stringstream ss(st);
    std::string segment; // Temporary string to hold each extracted name segment.
    
    // A vector to store pairs of (winning_number, name).
    // This structure is chosen because we need to sort based on winning_number first,
    // and then alphabetically by name if winning_numbers are equal.
    // Using long long for winning_number to prevent potential overflow, as sums of ranks
    // and lengths can be large, and then multiplied by weights.
    std::vector<std::pair<long long, std::string>> participants;
    
    int weight_index = 0; // Index to correctly pick the corresponding weight from the 'we' vector.

    // Loop to extract each name from the stringstream, delimited by a comma.
    while (std::getline(ss, segment, ',')) {
        // Calculate the 'som' value for the current name.
        long long som = calculate_som(segment);
        
        // Calculate the 'winning number' for the current participant.
        // This is 'som' multiplied by its corresponding weight from the 'we' vector.
        // The problem statement guarantees that 'we' is at least as long as the number of names.
        long long winning_number = som * we[weight_index];
        
        // Add the calculated winning number and the original name to our participants vector.
        participants.push_back({winning_number, segment});
        
        // Move to the next weight for the next participant.
        weight_index++;
    }

    // Handle the second edge case: if 'n' (the requested rank) is greater than
    // the total number of participants found.
    if (n > participants.size()) {
        return "Not enough participants";
    }

    // Sort the 'participants' vector.
    // std::sort uses a custom comparison lambda function to define the sorting order.
    std::sort(participants.begin(), participants.end(), [](const auto& a, const auto& b) {
        // Primary sorting criterion: Sort in decreasing order of 'winning numbers'.
        // If 'a's winning number is different from 'b's, the one with the larger winning number comes first.
        if (a.first != b.first) {
            return a.first > b.first;
        }
        // Secondary sorting criterion: If 'winning numbers' are equal, sort alphabetically by their firstnames.
        // std::string's operator< naturally provides alphabetical (lexicographical) comparison.
        return a.second < b.second;
    });

    // After sorting, the participant at the requested rank 'n' will be at index 'n-1'
    // in the sorted vector (because ranks are 1-indexed, but vector indices are 0-indexed).
    // Return the name (second element of the pair) of this participant.
    return participants[n - 1].second;
}
#include <vector> // Required for std::vector
#include <string> // Required for std::string
// No other headers like cmath or algorithm are strictly necessary for this specific implementation.
// cmath for sqrt was considered but not used.
// algorithm for sort is not needed as terms are naturally sorted by increasing n.

// Define an enum for internal representation of colors.
// This makes color comparisons more robust and less error-prone than string comparisons.
enum ColourType {
    RED,
    BLUE,
    // YELLOW_NONE is included to represent the 'yellow' color,
    // which, based on the problem's examples and derived pattern,
    // never actually appears as a color for any f(n) term.
    // Any request for 'yellow' will result in an empty list.
    YELLOW_NONE
};

// Helper function to determine the color type for a given 'n' based on the problem's pattern.
// The pattern derived from the examples is:
// n % 3 == 1 -> "red"
// n % 3 == 2 -> "blue"
// n % 3 == 0 -> "blue"
ColourType get_colour_type(long long n) {
    long long remainder = n % 3;
    if (remainder == 1) {
        return RED;
    } else if (remainder == 2) {
        return BLUE;
    } else { // remainder == 0
        return BLUE;
    }
}

// Helper function to calculate the f(n) term.
// f(n) is the sum of the first n natural numbers, also known as triangular numbers.
// The formula is n * (n + 1) / 2.
// Using long long for n to prevent overflow during intermediate calculation n * (n + 1)
// before division, especially for larger n values.
long long calculate_f_n(long long n) {
    return n * (n + 1) / 2;
}

// The main function to solve the problem.
// It finds the smallest 'k' terms of the sequence f(n) that have the specified 'colour'
// and are strictly greater than 'val'.
// It also adheres to a search range constraint for returning an empty list.
std::vector<long long> same_col_seq(long long val, int k, const std::string& colour) {
    std::vector<long long> result; // Stores the found terms.

    // Determine the target colour type from the input string.
    ColourType target_colour_type;
    if (colour == "red") {
        target_colour_type = RED;
    } else if (colour == "blue") {
        target_colour_type = BLUE;
    } else { // If the requested colour is "yellow"
        // As per the analysis of the problem's colour mapping, 'yellow' terms
        // never occur in the sequence. Thus, any request for 'yellow' should
        // immediately return an empty list.
        return result;
    }

    // Calculate the upper limit for the search range.
    // Terms are considered if they are within [val, 2 * k * val].
    // However, based on example analysis, this limit is only for determining
    // if an empty list should be returned (i.e., if 'k' terms cannot be found
    // within this range). If 'k' terms are found, they are returned even if
    // the last one exceeds this limit.
    // Use 2LL to ensure the multiplication promotes to long long to prevent overflow.
    long long max_value_limit = 2LL * k * val;

    // Find the smallest 'n' such that f(n) is strictly greater than 'val'.
    // We start from n=1 and increment until f(n) > val.
    // Given val > 100, n will quickly reach a value where f(n) > val,
    // so this loop is efficient.
    long long current_n = 1;
    while (calculate_f_n(current_n) <= val) {
        current_n++;
    }

    // Iterate to find 'k' terms that meet the criteria.
    // The loop continues until 'k' terms are collected.
    while (result.size() < k) {
        long long current_f_n = calculate_f_n(current_n);

        // Check if the current f(n) value exceeds the maximum allowed search range.
        // If it does, and we haven't found 'k' terms yet, it means we cannot
        // fulfill the request within the specified range, so we return an empty list.
        if (current_f_n > max_value_limit) {
            result.clear(); // Clear any partially collected terms.
            return result;
        }

        // Check if the current term's color matches the target color.
        if (get_colour_type(current_n) == target_colour_type) {
            // If it matches, add the term to our result vector.
            // Terms are naturally added in increasing order of 'n',
            // so the 'result' vector will be sorted as required.
            result.push_back(current_f_n);
        }

        current_n++; // Move to the next 'n' to continue the search.
    }

    // If the loop completes, it means 'k' terms have been successfully found
    // within the search criteria (or before exceeding the max_value_limit).
    return result;
}
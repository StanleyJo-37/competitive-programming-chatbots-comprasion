#include <iostream>
#include <vector>
#include <algorithm>
#include <map> // Although a fixed-size array is used for frequencies, map is a general alternative.

// Structure to store value and original index of an element.
struct Element {
    int value;
    int original_index;
};

// Custom comparison function for sorting Element objects.
// It sorts primarily by the 'value' field in ascending order.
// If 'value' fields are equal, it sorts by 'original_index' to ensure a stable sort
// (though for correctness of this specific problem, sorting by original_index for ties is not strictly necessary,
// any consistent tie-breaking rule would work).
bool compareElements(const Element& a, const Element& b) {
    if (a.value != b.value) {
        return a.value < b.value;
    }
    return a.original_index < b.original_index;
}

int main() {
    // Optimize C++ standard streams for faster input/output.
    // This is a common practice in competitive programming to prevent TLE (Time Limit Exceeded).
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, k;
    std::cin >> n >> k; // Read the length of the array (n) and the number of colors (k).

    std::vector<Element> elements(n); // A vector to store elements along with their original indices.
    // A frequency array to count occurrences of each number.
    // Max value of a_i is 5000, so an array of size 5001 is sufficient (indices 1 to 5000).
    std::vector<int> freq(5001, 0); 
    int max_freq = 0; // Variable to keep track of the maximum frequency found among all numbers.

    // Read array elements, store them with original indices, and calculate frequencies.
    for (int i = 0; i < n; ++i) {
        std::cin >> elements[i].value; // Read the value of the current element.
        elements[i].original_index = i; // Store its original 0-based index.
        freq[elements[i].value]++; // Increment the frequency count for this value.
        // Update max_freq if the current value's frequency is higher than the previously recorded max_freq.
        if (freq[elements[i].value] > max_freq) {
            max_freq = freq[elements[i].value];
        }
    }

    // Condition check: If the maximum frequency of any number in the array is greater than k,
    // it's impossible to color the array according to the rules.
    // This is because all occurrences of a single number must be assigned distinct colors.
    // If a number appears 'X' times, you need at least 'X' distinct colors for its occurrences.
    // If X > k, you don't have enough colors.
    if (max_freq > k) {
        std::cout << "NO\n"; // Print "NO" and exit.
        return 0;
    }

    // If max_freq <= k, a valid coloring is possible.
    std::cout << "YES\n"; // Print "YES".

    // Sort the 'elements' vector using the custom comparison function.
    // This arranges elements primarily by their value. For example, all '1's come first, then all '2's, etc.
    std::sort(elements.begin(), elements.end(), compareElements);

    // A vector to store the assigned colors for each element, indexed by its original position.
    std::vector<int> result_colors(n); 

    // Assign colors cyclically (1, 2, ..., k, 1, 2, ...) to the sorted elements.
    // This greedy strategy works because:
    // 1. Each element gets a color.
    // 2. Since n >= k (given constraint), all k colors will be used at least once (the first k elements in the sorted list will get colors 1 through k).
    // 3. For any specific color 'C', the elements assigned to it are those at indices i, i+k, i+2k, ... in the sorted 'elements' list, where (i % k) + 1 = C.
    //    Because the list is sorted by value, if two elements at indices 'j' and 'j+k*m' (for m > 0) have the same value,
    //    it implies that there are at least 'k*m + 1' elements with that same value.
    //    However, we've already checked that max_freq <= k. This means no value appears more than 'k' times.
    //    Therefore, it's impossible for two elements with the same value to be separated by a multiple of 'k' positions
    //    in the sorted list and thus receive the same color. All elements assigned to a single color will have distinct values.
    for (int i = 0; i < n; ++i) {
        // The color assigned is (current_index_in_sorted_array % k) + 1.
        // The modulo operator (%) ensures the color wraps around from k back to 0 (or 1 to k if we add 1).
        // Adding 1 converts the 0-indexed result of (i % k) to 1-indexed colors (1 to k).
        result_colors[elements[i].original_index] = (i % k) + 1;
    }

    // Print the assigned colors for each element in their original order.
    for (int i = 0; i < n; ++i) {
        std::cout << result_colors[i] << (i == n - 1 ? "" : " "); // Print space between numbers, no space after the last one.
    }
    std::cout << "\n"; // Print a newline at the end.

    return 0; // Indicate successful execution.
}
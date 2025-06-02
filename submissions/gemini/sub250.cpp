#include <iostream> // Required for input/output operations (std::cin, std::cout, std::endl)
#include <string>   // Required for string manipulation (std::string)
#include <vector>   // Required for dynamic arrays (std::vector)
#include <algorithm> // Required for std::max

int main() {
    // Optimize C++ standard streams for competitive programming.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard I/O,
    // which can speed up I/O operations.
    // std::cin.tie(NULL) prevents std::cout from being flushed before each std::cin operation,
    // further improving I/O performance.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::string s;
    std::cin >> s; // Read the main string 's' from standard input.

    int n;
    std::cin >> n; // Read the number of boring strings 'n'.

    std::vector<std::string> b(n); // Declare a vector to store 'n' boring strings.
    for (int i = 0; i < n; ++i) {
        std::cin >> b[i]; // Read each boring string into the vector 'b'.
    }

    int s_len = s.length(); // Get the length of the main string 's'.

    // max_start_in_prefix[i] will store the maximum starting index 'j'
    // such that s[j...k] is a boring string and 'k' (the end index of the boring string) is less than or equal to 'i'.
    // Initialize all elements to -1, indicating no boring string ends at or before that index yet.
    std::vector<int> max_start_in_prefix(s_len, -1);

    // First pass: Identify all occurrences of boring strings in 's'.
    // Iterate through each possible starting position 'i' in 's'.
    for (int i = 0; i < s_len; ++i) {
        // For each boring string 'b_j' in the list 'b'.
        for (int j = 0; j < n; ++j) {
            // Check if the boring string 'b_j' can fit into 's' starting at index 'i'.
            // i + b[j].length() gives the index one past the end of the potential match.
            if (i + b[j].length() <= s_len) {
                // Compare the substring of 's' starting at 'i' with length 'b[j].length()'
                // to the boring string 'b_j'.
                // std::string::compare returns 0 if the strings are equal.
                if (s.compare(i, b[j].length(), b[j]) == 0) {
                    // If a match is found, 'i' is the starting index and 'i + b[j].length() - 1' is the ending index.
                    // Update max_start_in_prefix at the ending index with the current starting index 'i'.
                    // We take std::max because we want the *latest* (largest index) starting position
                    // of any boring string that ends at this specific index.
                    max_start_in_prefix[i + b[j].length() - 1] = std::max(max_start_in_prefix[i + b[j].length() - 1], i);
                }
            }
        }
    }

    // Second pass: Propagate the maximum starting index across the array.
    // After the first pass, max_start_in_prefix[i] only considers boring strings that *end exactly* at 'i'.
    // This pass ensures that max_start_in_prefix[i] stores the maximum starting index 'j'
    // of any boring string that ends *at or before* 'i'.
    // This is crucial for the sliding window, as a boring string ending at 'i-1' still affects 'i'.
    for (int i = 1; i < s_len; ++i) {
        max_start_in_prefix[i] = std::max(max_start_in_prefix[i], max_start_in_prefix[i-1]);
    }

    int max_len = 0; // Variable to store the maximum length of a valid substring found.
    int max_pos = 0; // Variable to store the starting position of the longest valid substring.

    int left = 0; // The left pointer of the sliding window. It represents the start of the current candidate substring.

    // Iterate the right pointer of the sliding window from 0 to s_len - 1.
    // 'right' represents the end of the current candidate substring.
    for (int right = 0; right < s_len; ++right) {
        // current_max_start holds the latest starting position of a boring string
        // that ends at or before the current 'right' pointer.
        int current_max_start = max_start_in_prefix[right];

        // If current_max_start is greater than or equal to 'left', it means:
        // 1. There is a boring string s[current_max_start...end_idx] where end_idx <= right.
        // 2. This boring string starts at or after the current 'left' pointer (current_max_start >= left).
        // This implies that the current window s[left...right] contains a boring string.
        // To make the window valid, we must move 'left' past this invalidating boring string.
        // The new 'left' should be 'current_max_start + 1'.
        // We take std::max with the current 'left' because 'left' can only move forward (increase).
        if (current_max_start >= left) {
            left = current_max_start + 1;
        }

        // Calculate the length of the current valid window s[left...right].
        // If 'left' has moved past 'right' (e.g., after an invalidating boring string),
        // the length would be negative or zero, indicating an empty or invalid window.
        int current_len = right - left + 1;
        
        // If the current valid window is longer than the maximum found so far, update.
        // We only update if current_len is positive, as an empty string (length 0) is always valid
        // but we are looking for the longest non-empty one. However, if all substrings are invalid,
        // max_len will remain 0, and max_pos will remain 0, which is the correct output for that case.
        if (current_len > max_len) {
            max_len = current_len;
            max_pos = left;
        }
    }

    // Output the length of the longest valid substring and its starting position (0-indexed).
    std::cout << max_len << " " << max_pos << std::endl;

    return 0; // Indicate successful execution.
}

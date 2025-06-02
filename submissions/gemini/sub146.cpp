#include <iostream>
#include <vector>
// No need for <map> or <unordered_map> as element values are bounded,
// allowing for a direct array as a frequency map.

// Define the maximum possible value for elements in the array 'a'.
// Since a_i <= 10^5, an array of size 100001 is sufficient to store frequencies
// for values from 1 to 100000 (using 0-indexing for array, but values are 1-indexed).
const int MAX_VAL = 100001;
// Global or static allocation for `freq` array ensures it's zero-initialized.
// This array will store the frequency of each number within the current sliding window.
int freq[MAX_VAL];

int main() {
    // Optimize C++ standard streams for faster input/output operations.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams.
    // std::cin.tie(NULL) prevents std::cout from being flushed before each std::cin operation.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, k; // n: size of array, k: target number of distinct elements
    std::cin >> n >> k;

    std::vector<int> a(n); // Declare a vector to store the input array elements.
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i]; // Read array elements.
    }

    int l = 0; // Left pointer of the sliding window (0-indexed).
    int distinct_count = 0; // Current count of distinct numbers in the window [l, r].

    // Variables to store the 1-indexed result (l, r).
    // Initialized to -1 -1, which is the required output if no solution is found.
    int ans_l = -1, ans_r = -1;

    // The right pointer 'r' iterates from the beginning to the end of the array.
    // This forms the expanding part of the sliding window.
    for (int r = 0; r < n; ++r) {
        // Add the element at 'r' to the current window.
        // If its frequency was 0 before adding, it means it's a new distinct element.
        if (freq[a[r]] == 0) {
            distinct_count++;
        }
        freq[a[r]]++; // Increment the frequency of the current element.

        // While the current window [l, r] contains exactly 'k' distinct elements:
        // We attempt to shrink the window from the left ('l') to find a "minimal by inclusion" segment.
        while (distinct_count == k) {
            // A segment [l, r] is "minimal by inclusion" if:
            // 1. It contains exactly 'k' distinct numbers (ensured by the `while` loop condition).
            // 2. Removing `a[l]` would reduce the distinct count (i.e., `a[l]` is the only occurrence of its value in [l, r]).
            //    This is true if `freq[a[l]] == 1`.
            // 3. Removing `a[r]` would reduce the distinct count (i.e., `a[r]` is the only occurrence of its value in [l, r]).
            //    This is true if `freq[a[r]] == 1`.
            // If both `a[l]` and `a[r]` are critical (their frequencies are 1 within the current window),
            // then [l, r] is a valid "minimal by inclusion" segment.
            if (freq[a[l]] == 1 && freq[a[r]] == 1) {
                // We found a segment that satisfies all conditions.
                // Store the 1-indexed result and print it.
                // Since the problem asks for *any* correct answer, we can terminate here.
                ans_l = l + 1;
                ans_r = r + 1;
                std::cout << ans_l << " " << ans_r << std::endl;
                return 0; // Exit the program successfully.
            }

            // If `a[l]` is not critical (its frequency is greater than 1),
            // it means we can remove `a[l]` from the left side of the window
            // without changing the `distinct_count`.
            // So, we shrink the window from the left by incrementing `l`.
            if (freq[a[l]] > 1) {
                freq[a[l]]--; // Decrement frequency of a[l].
                l++;          // Move left pointer to the right.
            } else {
                // If `freq[a[l]] == 1`, it means `a[l]` is critical. We cannot shrink the window
                // from the left without reducing `distinct_count` below `k`.
                // At this point, if `distinct_count` is still `k`, it implies `freq[a[r]] > 1`.
                // If `freq[a[r]] > 1`, then `a[r]` is not critical. This means the segment `[l, r-1]`
                // would also contain `k` distinct elements, making `[l, r]` not minimal by inclusion.
                // Since we cannot shrink `l` further, this `[l, r]` is not the answer we are looking for.
                // We must break from this inner `while` loop and continue expanding `r`
                // to find a new candidate segment.
                break;
            }
        }
    }

    // If the loop completes without finding and printing a solution (i.e., `return 0` was not called),
    // it means no such segment exists. Print the default -1 -1.
    std::cout << ans_l << " " << ans_r << std::endl;

    return 0; // Indicate successful execution.
}

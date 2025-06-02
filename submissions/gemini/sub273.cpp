#include <iostream> // Required for input/output operations (cin, cout)
#include <vector>   // Required for using std::vector to store the array elements
#include <numeric>  // Required for std::accumulate to calculate the sum of elements (though manual sum is used here)
#include <algorithm> // Required for std::max

void solve() {
    int n; // Declare integer n for the number of elements in the array
    int x; // Declare integer x for the number Ehab hates
    std::cin >> n >> x; // Read n and x from standard input

    std::vector<int> a(n); // Declare a vector 'a' of size n to store array elements
    long long total_sum = 0; // Declare a long long to store the sum of elements to prevent overflow.
                             // Max sum: 10^5 elements * 10^4 max value = 10^9, which fits in a 32-bit signed int,
                             // but long long is safer and standard practice for sums in competitive programming.
    bool all_divisible_by_x = true; // Flag to check if all elements in the array are divisible by x

    for (int i = 0; i < n; ++i) { // Loop through each element of the array
        std::cin >> a[i]; // Read the current element
        total_sum += a[i]; // Add the current element to the total sum
        if (a[i] % x != 0) { // Check if the current element is not divisible by x
            all_divisible_by_x = false; // If any element is not divisible by x, set the flag to false
        }
    }

    // Case 1: The sum of the entire array is not divisible by x.
    // If the total sum of the array is not divisible by x, then the entire array itself is the longest
    // possible subarray satisfying the condition. Its length is 'n'.
    if (total_sum % x != 0) {
        std::cout << n << std::endl; // Print n and a newline
    } 
    // Case 2: The sum of the entire array is divisible by x.
    else {
        // If the total sum is divisible by x, we cannot use the entire array.
        // We must remove some elements to make the sum of the remaining subarray not divisible by x.
        // To maximize the length of the remaining subarray, we must remove the minimum number of elements.
        // This implies removing either a prefix or a suffix of the original array.

        // Subcase 2.1: All elements in the array are divisible by x.
        // If every single element a[i] is divisible by x, then any sum of a subarray will also be divisible by x.
        // In this specific scenario, no subarray exists whose sum is not divisible by x.
        if (all_divisible_by_x) {
            std::cout << -1 << std::endl; // Print -1 and a newline
        } 
        // Subcase 2.2: The total sum is divisible by x, but at least one element is NOT divisible by x.
        // Since total_sum % x == 0, if we remove a prefix/suffix whose sum is NOT divisible by x,
        // the remaining subarray's sum will also NOT be divisible by x.
        // (Because (S - R) % x != 0 if S % x == 0 and R % x != 0).

        // Option A: Remove a prefix.
        // Find the smallest index 'first_idx' from the left such that a[first_idx] is not divisible by x.
        // If we remove the prefix a[0...first_idx], the remaining subarray is a[first_idx+1 ... n-1].
        // The sum of a[0...first_idx] is not divisible by x (because a[first_idx] is not, and elements before it are).
        // The length of this subarray is n - (first_idx + 1).
        int first_idx = -1; // Initialize first_idx to -1 (indicating not found yet)
        for (int i = 0; i < n; ++i) {
            if (a[i] % x != 0) {
                first_idx = i; // Found the first element not divisible by x
                break; // Exit the loop as we only need the first one
            }
        }

        // Option B: Remove a suffix.
        // Find the largest index 'last_idx' from the right such that a[last_idx] is not divisible by x.
        // If we remove the suffix a[last_idx...n-1], the remaining subarray is a[0 ... last_idx-1].
        // The sum of a[last_idx...n-1] is not divisible by x (because a[last_idx] is not, and elements after it are).
        // The length of this subarray is last_idx.
        int last_idx = -1; // Initialize last_idx to -1 (indicating not found yet)
        for (int i = n - 1; i >= 0; --i) {
            if (a[i] % x != 0) {
                last_idx = i; // Found the last element not divisible by x
                break; // Exit the loop as we only need the last one
            }
        }
        
        // Since `all_divisible_by_x` was false, it guarantees that at least one element is not divisible by x.
        // Therefore, both `first_idx` and `last_idx` must have been found (i.e., they are not -1).
        // The answer is the maximum of the lengths obtained from these two options.
        std::cout << std::max(n - (first_idx + 1), last_idx) << std::endl; // Print the maximum length
    }
}

int main() {
    // Optimize C++ standard streams for faster input/output.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams,
    // which can speed up I/O operations significantly.
    // std::cin.tie(NULL) prevents std::cout from flushing before std::cin reads input,
    // further optimizing I/O when mixing cin and cout.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t; // Declare integer t for the number of test cases
    std::cin >> t; // Read t from standard input
    while (t--) { // Loop t times, decrementing t each iteration
        solve(); // Call the solve function for each test case
    }

    return 0; // Indicate successful program execution
}

#include <iostream> // Required for input/output operations (std::cin, std::cout)
#include <vector>   // Required for using std::vector to store the array elements
#include <numeric>  // Required for std::accumulate (though not strictly used in final code, sum is calculated manually)
#include <algorithm> // Required for std::max

// Function to solve a single test case
void solve() {
    int n; // Declare integer n for the length of the array
    long long s; // Declare long long s for the target sum. Using long long to be safe,
                 // as s can be up to 2 * 10^5, and sums can accumulate.
    std::cin >> n >> s; // Read the array length n and the target sum s

    std::vector<int> a(n); // Declare a vector of integers 'a' of size n to store array elements
    long long current_total_sum = 0; // Initialize a variable to store the sum of all elements in the array

    // Loop to read array elements and calculate their total sum
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i]; // Read the i-th element
        current_total_sum += a[i]; // Add the element to the total sum
    }

    // If the current total sum of the array is less than the target sum 's',
    // it's impossible to achieve 's' by removing elements. This is because all elements are 0 or 1,
    // so removing elements can only decrease or keep the sum the same, never increase it.
    // In this case, output -1.
    if (current_total_sum < s) {
        std::cout << -1 << std::endl;
        return; // Exit the function for this test case
    }

    // The problem asks for the minimum number of operations.
    // This is equivalent to finding the longest possible subarray whose sum is 's'.
    // If we find such a subarray of length 'L', then 'n - L' elements must be removed.
    // This is a classic sliding window problem.

    int max_len = 0; // Initialize max_len to 0. This variable will store the maximum length
                     // of a subarray found so far that sums up to 's'.
    int left = 0; // 'left' pointer of the sliding window
    long long current_window_sum = 0; // Sum of elements within the current sliding window [left, right]

    // Iterate with the 'right' pointer from the beginning to the end of the array
    for (int right = 0; right < n; ++right) {
        current_window_sum += a[right]; // Add the element at the 'right' pointer to the window sum

        // While the current window sum exceeds the target sum 's',
        // shrink the window from the left by removing elements.
        // This ensures that current_window_sum is always <= s.
        while (current_window_sum > s) {
            current_window_sum -= a[left]; // Subtract the element at the 'left' pointer from the window sum
            left++; // Move the 'left' pointer to the right
        }

        // If the current window sum is exactly equal to 's',
        // we have found a valid subarray [left, right] whose sum is 's'.
        // We want to maximize its length, so update max_len.
        if (current_window_sum == s) {
            max_len = std::max(max_len, right - left + 1); // Calculate length (right - left + 1) and update max_len
        }
    }

    // The minimum number of operations required is the total length of the array 'n'
    // minus the maximum length 'max_len' of a subarray that sums to 's'.
    // If 'max_len' remains 0 (which would only happen if 's' is positive and no '1's are present,
    // or 's' is 0 and no '0's are present, but the initial `current_total_sum < s` check
    // handles most of these cases), it means no subarray with sum 's' was found.
    // In such a scenario, 'n - 0 = n' operations would be needed (remove all elements).
    // This is correct for cases like `s=0` and `a=[1,1,1]` (remove all 3 elements).
    std::cout << n - max_len << std::endl;
}

int main() {
    // Optimize C++ standard streams for competitive programming.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams,
    // potentially speeding up I/O operations.
    // std::cin.tie(NULL) prevents std::cout from flushing before std::cin reads input,
    // further optimizing I/O.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t; // Declare integer t for the number of test cases
    std::cin >> t; // Read the number of test cases
    while (t--) { // Loop 't' times, decrementing 't' in each iteration
        solve(); // Call the solve function for each test case
    }

    return 0; // Indicate successful program execution
}
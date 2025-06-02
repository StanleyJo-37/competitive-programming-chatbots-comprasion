#include <iostream> // Required for input/output operations (cin, cout)
#include <vector>   // Required for using std::vector to store plank heights

int main() {
    // Optimize C++ standard streams for faster input/output.
    // This unties cin/cout from C's stdio and prevents flushing cout before cin.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n; // Declare n for the total number of planks
    int k; // Declare k for the number of consecutive planks to select
    std::cin >> n >> k; // Read n and k from standard input

    // Declare a vector to store the heights of the planks.
    // Using a vector allows dynamic sizing and convenient 0-based indexing.
    std::vector<int> h(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> h[i]; // Read each plank height into the vector
    }

    // Calculate the sum of the first k planks. This will be our initial window sum.
    // Using long long for sum to prevent potential overflow, although for given constraints
    // (max sum 1.5 * 10^5 * 100 = 1.5 * 10^7), int would also be sufficient.
    // It's a good practice in competitive programming to use long long for sums.
    long long current_sum = 0;
    for (int i = 0; i < k; ++i) {
        current_sum += h[i];
    }
    
    // Initialize min_sum with the sum of the first window.
    long long min_sum = current_sum;
    // Initialize min_idx with 1, as the first window (h[0]...h[k-1]) starts at 1-based index 1.
    int min_idx = 1;

    // Iterate through the rest of the possible starting positions for the window.
    // The loop variable 'i' represents the 0-based starting index of the current window.
    // It starts from i = 1 (meaning the window starts at h[1]).
    // It goes up to n - k, which is the last possible 0-based starting index for a window of size k.
    // For example, if n=7, k=3, the last window starts at h[4] (indices 4,5,6).
    // So 'i' goes from 1 to 7-3 = 4.
    for (int i = 1; i <= n - k; ++i) {
        // To slide the window one position to the right efficiently:
        // 1. Subtract the height of the plank that is leaving the window (h[i-1]).
        // 2. Add the height of the plank that is entering the window (h[i+k-1]).
        current_sum = current_sum - h[i-1] + h[i+k-1];

        // If the current window's sum is less than the minimum sum found so far,
        // update min_sum and min_idx.
        if (current_sum < min_sum) {
            min_sum = current_sum;
            // The current window starts at 0-based index 'i'.
            // Convert this to a 1-based index by adding 1.
            min_idx = i + 1;
        }
    }

    // Print the 1-based index of the starting plank of the window with the minimal sum.
    std::cout << min_idx << std::endl;

    return 0; // Indicate successful program execution
}
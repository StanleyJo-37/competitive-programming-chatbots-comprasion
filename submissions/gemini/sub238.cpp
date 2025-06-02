#include <iostream> // Required for input/output operations (std::cin, std::cout, std::endl)
#include <string>   // Required for string manipulation (std::string)
#include <vector>   // Not strictly needed for this solution, but often useful in competitive programming
#include <algorithm> // Required for std::max

// Function to solve a single test case
void solve() {
    int n;      // Length of the traffic light sequence string
    char c;     // Current color of the traffic light
    std::cin >> n >> c; // Read n and c
    std::string s; // The traffic light sequence string
    std::cin >> s; // Read the string s

    // If the current color 'c' is 'g' (green), we can cross immediately.
    // The guaranteed minimum time is 0.
    if (c == 'g') {
        std::cout << 0 << std::endl;
        return; // Exit the function for this test case
    }

    // To handle the cyclic nature of the traffic light sequence,
    // we concatenate the string 's' with itself.
    // This creates a string 's_double' of length '2n'.
    // For example, if s = "rggry", s_double = "rggryrggry".
    // This allows us to find the next 'g' without explicitly
    // checking for wrap-around from the end of 's' to its beginning.
    // If 'c' is at s[n-1] and the next 'g' is at s[0],
    // in s_double, 'c' would be at s_double[n-1] and 'g' would be at s_double[n],
    // making the distance calculation (j - i) straightforward.
    std::string s_double = s + s;

    int max_wait_time = 0; // Initialize the maximum waiting time found so far
    // 'last_g_idx' will store the index of the most recently encountered 'g'
    // when iterating from right to left through 's_double'.
    // This helps in efficiently finding the *closest* 'g' to the right of any 'c'.
    int last_g_idx = -1; 

    // Iterate from the end of the doubled string backwards.
    // The loop goes from (2 * n - 1) down to 0.
    // We iterate through the entire 's_double' to correctly populate 'last_g_idx'
    // for all possible starting positions in the first half of 's_double' (which
    // correspond to the original string 's').
    for (int i = 2 * n - 1; i >= 0; --i) {
        if (s_double[i] == 'g') {
            // If the current character is 'g', update 'last_g_idx' to its current position.
            // This 'g' is now the closest green light to the right for any 'c'
            // encountered at an index less than 'i' (as we are iterating backwards).
            last_g_idx = i;
        } else if (s_double[i] == c) {
            // If the current character is 'c' (and it's not 'g', because 'g' is handled
            // in the 'if' block above), we calculate the waiting time.
            // 'last_g_idx' now holds the index of the first 'g' to the right of 'i'.
            // The waiting time is the difference between the 'g' index and the 'c' index.
            // The problem guarantees that 'g' is in 's' and 'c' is in 's',
            // so 'last_g_idx' will always be a valid index when 's_double[i] == c'.
            // Also, since c != 'g', 'last_g_idx' must be strictly greater than 'i'.
            int current_wait_time = last_g_idx - i;
            
            // We are interested in the maximum waiting time for any starting position
            // within the *original* string 's' (indices 0 to n-1).
            // The indices 'i >= n' in 's_double' correspond to positions that are
            // cyclically equivalent to 'i - n' in the first half of 's_double'.
            // For example, s_double[n] is s[0], s_double[n+1] is s[1], etc.
            // The waiting time calculated from s_double[i] would be the same as
            // from s_double[i-n]. Therefore, we only need to consider 'i < n'
            // to find the maximum wait time for all unique starting points in the cycle.
            if (i < n) {
                max_wait_time = std::max(max_wait_time, current_wait_time);
            }
        }
    }

    // Output the maximum waiting time found, which is the guaranteed minimum time to cross.
    std::cout << max_wait_time << std::endl;
}

int main() {
    // Optimize C++ standard streams for faster input/output.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams.
    // std::cin.tie(NULL) prevents std::cout from flushing before std::cin reads input.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t; // Number of test cases
    std::cin >> t; // Read the number of test cases
    while (t--) { // Loop through each test case
        solve(); // Call the solve function for the current test case
    }

    return 0; // Indicate successful execution
}

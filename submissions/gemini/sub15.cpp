#include <iostream> // Required for input/output operations (std::cin, std::cout)
#include <vector>   // Required for using std::vector
#include <algorithm> // Required for std::max

// Function to solve a single test case
void solve() {
    int n; // Declare an integer variable 'n' to store the number of cake layers
    std::cin >> n; // Read the value of 'n' from standard input

    std::vector<int> a(n); // Declare a vector 'a' of size 'n' to store the cream amounts
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i]; // Read 'n' integers into the vector 'a'
    }

    std::vector<int> result(n); // Declare a vector 'result' of size 'n' to store the final drenching status (1 for drenched, 0 for not)

    // 'drench_depth' represents the number of layers from the current top of the stack
    // that are currently drenched by cream poured at or after the current step.
    // We iterate from the last layer (n-th layer) down to the first layer (1st layer).
    // This is because cream poured at step 'i' can affect layers added at steps 'j <= i'.
    // By iterating backwards, we can propagate the drenching effect from later pours
    // to earlier layers.
    int drench_depth = 0; 

    // Iterate from the last layer (index n-1, which corresponds to the n-th layer)
    // down to the first layer (index 0, which corresponds to the 1st layer).
    for (int i = n - 1; i >= 0; --i) {
        // The current cream pour 'a[i]' affects 'a[i]' layers from the top of the stack
        // at step 'i+1' (when layer 'i+1' is added and 'a[i]' cream is poured).
        // 'drench_depth' carries over the drenching effect from subsequent pours (a[i+1], a[i+2], ..., a[n-1]).
        // The effective number of layers drenched from the current top is the maximum
        // of the current pour amount and the inherited drenching depth.
        drench_depth = std::max(a[i], drench_depth);

        // If 'drench_depth' is greater than 0, it means the current layer (layer i+1)
        // is drenched by either the current pour 'a[i]' or by a previous pour that
        // had a deeper effect.
        if (drench_depth > 0) {
            result[i] = 1; // Mark the current layer as drenched
            drench_depth--; // Decrease 'drench_depth' as we move down to the next layer.
                            // This layer 'i+1' has been accounted for, so the cream effect
                            // for the layer below it (layer 'i') will be one less.
        } else {
            // If 'drench_depth' is 0, it means no cream is reaching this layer from above.
            // The layer remains undrenched.
            result[i] = 0; // Mark the current layer as undrenched (already initialized to 0, but explicit)
        }
    }

    // Print the final drenching status for all layers
    for (int i = 0; i < n; ++i) {
        std::cout << result[i] << (i == n - 1 ? "" : " "); // Print 1 or 0, with spaces in between
    }
    std::cout << "\n"; // Print a newline character after each test case output
}

int main() {
    // Optimize C++ standard streams for faster input/output.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams,
    // which can speed up I/O operations significantly.
    std::ios_base::sync_with_stdio(false);
    // std::cin.tie(NULL) prevents std::cout from flushing before std::cin reads input.
    // This is useful in competitive programming to avoid unnecessary flushes and improve performance.
    std::cin.tie(NULL);

    int t; // Declare an integer variable 't' to store the number of test cases
    std::cin >> t; // Read the number of test cases

    while (t--) { // Loop 't' times, decrementing 't' in each iteration
        solve(); // Call the 'solve' function for each test case
    }

    return 0; // Indicate successful program execution
}

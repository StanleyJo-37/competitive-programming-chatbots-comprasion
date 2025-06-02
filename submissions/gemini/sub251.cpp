#include <iostream>
#include <vector>
#include <algorithm> // Required for std::sort and std::min
#include <cmath>     // Required for std::abs
#include <limits>    // Required for std::numeric_limits

void solve() {
    int N;
    std::cin >> N; // Read the number of elements in the array.
    std::vector<long long> A(N); // Declare a vector to store array elements. Use long long for elements as A_i can be up to 10^9.
    for (int i = 0; i < N; ++i) {
        std::cin >> A[i]; // Read array elements.
    }

    // Sort the array A. This is crucial because the definition of median for a subsequence
    // requires sorting its elements. By sorting the original array, if we pick elements
    // A[i], A[j], A[k] with i < j < k, then A[i] <= A[j] <= A[k] is guaranteed.
    // These will serve as s1, s2, s3 respectively.
    std::sort(A.begin(), A.end());

    // Initialize minimum beauty to a very large value.
    // The beauty is abs(s1 + s3 - 2 * s2). The maximum possible value for this
    // is roughly 2 * 10^9 (e.g., s1=0, s2=0, s3=10^9, or s1=0, s2=10^9, s3=10^9).
    // A long long is necessary to store this value.
    long long min_beauty = std::numeric_limits<long long>::max();

    // Iterate through all possible elements that can be the median (s2) of a subsequence of size 3.
    // The median element A[j] must have at least one element before it (s1)
    // and at least one element after it (s3).
    // So, 'j' can range from index 1 to N-2.
    for (int j = 1; j < N - 1; ++j) {
        // For a fixed median A[j], we want to find A[i] (s1) and A[k] (s3)
        // such that i < j < k and abs(A[i] + A[k] - 2 * A[j]) is minimized.
        // Let target_sum = 2 * A[j]. We are looking for A[i] + A[k] to be as close as possible to target_sum.
        long long target_sum = 2 * A[j];

        // Use two pointers: 'left_ptr' for s1 and 'right_ptr' for s3.
        // 'left_ptr' starts at the beginning of the array (index 0).
        // 'right_ptr' starts at the end of the array (index N-1).
        int left_ptr = 0;
        int right_ptr = N - 1;

        // The loop continues as long as 'left_ptr' is to the left of 'j'
        // and 'right_ptr' is to the right of 'j'.
        // This ensures that A[left_ptr], A[j], A[right_ptr] are distinct elements
        // from the sorted array, forming a valid subsequence of size 3.
        while (left_ptr < j && right_ptr > j) {
            long long current_sum = A[left_ptr] + A[right_ptr];
            
            // Calculate the current beauty for the subsequence {A[left_ptr], A[j], A[right_ptr]}.
            // The beauty is abs(s1 + s3 - 2 * s2), which is abs(current_sum - target_sum).
            min_beauty = std::min(min_beauty, std::abs(current_sum - target_sum));

            // If current_sum is less than target_sum, we need a larger sum.
            // Since A is sorted, incrementing left_ptr will increase A[left_ptr]
            // and thus increase current_sum.
            if (current_sum < target_sum) {
                left_ptr++;
            } 
            // If current_sum is greater than target_sum, we need a smaller sum.
            // Decrementing right_ptr will decrease A[right_ptr]
            // and thus decrease current_sum.
            else if (current_sum > target_sum) {
                right_ptr--;
            } 
            // If current_sum equals target_sum, we found a beauty of 0.
            // This is the minimum possible beauty, so we can stop immediately.
            else {
                min_beauty = 0;
                // Use goto to break out of both the inner while loop and the outer for loop.
                goto end_loops; 
            }
        }
    }

    // Label for the goto statement to jump to when min_beauty becomes 0.
    end_loops:; 

    std::cout << min_beauty << std::endl; // Output the minimum beauty found.
}

int main() {
    // Optimize C++ standard streams for faster input/output.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams.
    // std::cin.tie(NULL) prevents std::cout from flushing before std::cin reads input.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int T;
    std::cin >> T; // Read the number of test cases.
    while (T--) { // Loop through each test case.
        solve(); // Call the solve function for each test case.
    }

    return 0; // Indicate successful execution.
}

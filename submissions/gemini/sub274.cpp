#include <iostream> // Required for input/output operations (std::cin, std::cout).
#include <algorithm> // Required for std::min function.

int main() {
    // Optimize C++ standard streams for faster input/output.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams,
    // potentially speeding up I/O operations.
    std::ios_base::sync_with_stdio(false);
    // std::cin.tie(NULL) unties std::cin from std::cout, meaning std::cin will not flush std::cout
    // before reading input, further speeding up I/O.
    std::cin.tie(NULL);

    int T;
    // Read the number of test cases.
    std::cin >> T;
    // Loop through each test case.
    while (T--) {
        int N;
        // Read the size of the array A for the current test case.
        std::cin >> N;

        int count_A_odd = 0;  // Counter for odd numbers in the input array A.
        int count_A_even = 0; // Counter for even numbers in the input array A.

        // Iterate N times to read each element of array A and count its parity.
        for (int i = 0; i < N; ++i) {
            int val;
            std::cin >> val; // Read an element from array A.
            if (val % 2 == 0) {
                // If the number is even (remainder when divided by 2 is 0), increment the even count.
                count_A_even++;
            } else {
                // If the number is odd, increment the odd count.
                count_A_odd++;
            }
        }

        // Calculate the number of odd and even indices from 1 to N.
        // The indices are 1-based: 1, 2, 3, ..., N.
        // For example, if N=3, indices are 1 (odd), 2 (even), 3 (odd).
        // Number of odd indices: (N + 1) / 2 using integer division.
        // If N=3, (3+1)/2 = 2.
        // If N=4, (4+1)/2 = 2.
        int count_idx_odd = (N + 1) / 2;
        // Number of even indices: N / 2 using integer division.
        // If N=3, 3/2 = 1.
        // If N=4, 4/2 = 2.
        int count_idx_even = N / 2;

        // The problem asks to maximize the sum of integers in array B, where B_i = (A_i + i) % 2.
        // B_i will be 1 if (A_i + i) is odd. This occurs when A_i and i have different parities.
        //   - A_i is odd and i is even.
        //   - A_i is even and i is odd.
        // B_i will be 0 if (A_i + i) is even. This occurs when A_i and i have the same parity.
        //   - A_i is odd and i is odd.
        //   - A_i is even and i is even.
        // To maximize the sum of B, we want to maximize the number of B_i that are 1.
        // This means we want to pair elements from A with indices such that their parities are different.

        // Calculate the maximum number of pairs where an odd A_k is placed at an even index.
        // This is limited by the total number of odd elements in A and the total number of even indices available.
        int ones_from_odd_A_even_idx = std::min(count_A_odd, count_idx_even);

        // Calculate the maximum number of pairs where an even A_k is placed at an odd index.
        // This is limited by the total number of even elements in A and the total number of odd indices available.
        int ones_from_even_A_odd_idx = std::min(count_A_even, count_idx_odd);

        // The total maximum sum of B is the sum of these two types of successful pairings.
        // This greedy approach works because each such pairing contributes 1 to the sum,
        // and using an element/index for a '1' pairing is always better than using it for a '0' pairing.
        // Any elements/indices not used in these '1' pairings will necessarily form '0' pairings.
        int max_sum_B = ones_from_odd_A_even_idx + ones_from_even_A_odd_idx;

        // Print the calculated maximum sum for the current test case, followed by a newline.
        std::cout << max_sum_B << "\n";
    }

    return 0; // Indicate successful execution.
}
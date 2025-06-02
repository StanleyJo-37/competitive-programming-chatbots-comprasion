#include <iostream> // Required for input/output operations (cin, cout)

// Main function where the program execution begins
int main() {
    // Optimize C++ standard streams for competitive programming.
    // This unties cin/cout from C's stdio and prevents flushing cout before cin.
    std::ios_base::sync_with_stdio(false);
    // This disables synchronization with C's stdio library, making cin/cout faster.
    std::cin.tie(NULL);
    // This unties cin from cout, meaning cin will not flush cout before reading input.

    int T; // Declare an integer variable T for the number of test cases
    std::cin >> T; // Read the number of test cases

    // Loop through each test case
    while (T--) {
        int N; // Declare an integer variable N for the input number
        std::cin >> N; // Read the value of N for the current test case

        // The problem asks for the length of the longest subarray [L, R]
        // in the sequence 1, 2, ..., N such that the bitwise AND of all elements
        // in the subarray is positive.
        //
        // Key observation: For the bitwise AND of a range of numbers [L, R] to be positive,
        // there must be at least one bit position 'k' such that the k-th bit is set (1)
        // for ALL numbers from L to R.
        //
        // Consider numbers that have the k-th bit set. These numbers fall into specific ranges.
        // For example, if k=0 (0th bit), numbers are 1, 3, 5, 7, ... (odd numbers).
        // If k=1 (1st bit), numbers are 2, 3, 6, 7, 10, 11, ...
        // If k=2 (2nd bit), numbers are 4, 5, 6, 7, 12, 13, 14, 15, ...
        //
        // A continuous block of integers where all numbers have the k-th bit set is of the form:
        // [m * 2^(k+1) + 2^k, m * 2^(k+1) + 2^(k+1) - 1] for some non-negative integer m.
        // For example, for k=2:
        // m=0: [0*8 + 4, 0*8 + 8 - 1] = [4, 7]
        // m=1: [1*8 + 4, 1*8 + 8 - 1] = [12, 15]
        //
        // The length of such a block is (m * 2^(k+1) + 2^(k+1) - 1) - (m * 2^(k+1) + 2^k) + 1
        // = 2^(k+1) - 2^k = 2^k.
        //
        // We want to find the maximum possible length, which means we want to find the largest 'k'
        // such that such a block of length 2^k exists and is entirely contained within [1, N].
        //
        // To maximize 'k', we should consider the block with the smallest possible starting value,
        // which corresponds to m=0.
        // The block for m=0 is [2^k, 2^(k+1) - 1].
        // For this block to be valid (i.e., all its elements are <= N), its end point must be <= N.
        // So, we need 2^(k+1) - 1 <= N.
        // This inequality can be rewritten as 2^(k+1) <= N + 1.
        //
        // We are looking for the largest integer 'k' that satisfies 2^(k+1) <= N + 1.
        // Let X = k+1. We are looking for the largest X such that 2^X <= N + 1.
        // This means X = floor(log2(N + 1)).
        // Once we find X, the desired 'k' is X - 1.
        // The length of the subarray is 2^k = 2^(X - 1).
        //
        // We can find 2^X (which is `ans` in the code below) by starting with 1 and repeatedly
        // multiplying by 2 as long as `ans * 2` does not exceed `N + 1`.
        //
        // Example trace for N=7:
        // N+1 = 8.
        // ans = 1 (represents 2^0)
        // Loop 1: (1 * 2) <= 8 (2 <= 8) is true. ans becomes 2 (represents 2^1).
        // Loop 2: (2 * 2) <= 8 (4 <= 8) is true. ans becomes 4 (represents 2^2).
        // Loop 3: (4 * 2) <= 8 (8 <= 8) is true. ans becomes 8 (represents 2^3).
        // Loop 4: (8 * 2) <= 8 (16 <= 8) is false. Loop terminates.
        // Final ans is 8. This is 2^X where X=3.
        // The result is ans / 2 = 8 / 2 = 4. This is 2^(X-1) = 2^2.
        // The subarray is [4, 7], bitwise AND is 4, length is 4.
        //
        // Example trace for N=2:
        // N+1 = 3.
        // ans = 1 (represents 2^0)
        // Loop 1: (1 * 2) <= 3 (2 <= 3) is true. ans becomes 2 (represents 2^1).
        // Loop 2: (2 * 2) <= 3 (4 <= 3) is false. Loop terminates.
        // Final ans is 2. This is 2^X where X=1.
        // The result is ans / 2 = 2 / 2 = 1. This is 2^(X-1) = 2^0.
        // The subarray is [1, 1] or [2, 2], bitwise AND is 1 or 2, length is 1.

        // Use long long for 'ans' to prevent potential overflow during 'ans * 2'
        // if N is close to INT_MAX. N is up to 10^9, so N+1 is ~10^9.
        // The largest 'ans' can become is 2^30 (when N+1 is 2^30).
        // Then 'ans * 2' would be 2^31, which fits in signed int.
        // However, if N was 2^31 - 1, then N+1 would be 2^31.
        // 'ans' would become 2^31, and 'ans * 2' would be 2^32, which overflows signed int.
        // Using long long for 'ans' is a safer practice in competitive programming
        // when dealing with powers of 2 that might approach integer limits.
        long long ans = 1; 

        // Loop to find the largest power of 2 (ans) such that ans <= N+1
        // and ans is a power of 2.
        // The condition (ans * 2LL) <= N + 1 ensures that the next power of 2
        // (ans * 2) does not exceed N + 1. The 2LL ensures the multiplication
        // is done using long long to prevent overflow before comparison.
        while ((ans * 2LL) <= (N + 1)) {
            ans *= 2; // Double 'ans'
        }

        // The final 'ans' is 2^X where X = floor(log2(N+1)).
        // The desired length is 2^(X-1), which is ans / 2.
        std::cout << ans / 2 << "\n"; // Output the result followed by a newline
    }

    return 0; // Indicate successful program execution
}

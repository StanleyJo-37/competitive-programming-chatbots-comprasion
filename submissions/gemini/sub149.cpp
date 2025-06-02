#include <iostream> // Required for input/output operations (std::cin, std::cout, std::endl)

// Function to solve a single test case
void solve() {
    long long A, B, N;
    // Read the three integers A, B, and N for the current test case.
    std::cin >> A >> B >> N;

    // Calculate the target XOR sum. This is the value that A needs to become 0 after XORing with chosen X's.
    // If A ^ B is 0, A is already equal to B.
    long long diff = A ^ B;

    // Case 1: A is already equal to B.
    if (diff == 0) {
        // If A is already B, no operations are needed.
        std::cout << 0 << std::endl;
        return; // Move to the next test case.
    }

    // Case 2: N = 1.
    // The allowed values for X are 1 <= X < N. If N = 1, there are no integers X that satisfy this condition.
    // Therefore, no operations can be performed. If A is not equal to B (diff != 0), it's impossible.
    if (N == 1) {
        std::cout << -1 << std::endl;
        return; // Move to the next test case.
    }

    // Case 3: One operation is sufficient.
    // If diff is less than N, we can choose X = diff.
    // Since 1 <= diff < N (diff is not 0, and diff < N), this is a valid operation.
    // Applying A := A ^ diff results in A ^ (A ^ B) = B.
    if (diff < N) {
        std::cout << 1 << std::endl;
        return; // Move to the next test case.
    }

    // Case 4: Determine if it's impossible or requires two operations.
    // At this point, we know:
    // - diff >= N (because the diff < N case was handled)
    // - N > 1 (because the N = 1 case was handled)

    // Find the smallest power of 2 that is greater than or equal to N. Let this be P.
    // This P defines a "boundary" for the bits. Any X < N will have its most significant bit (MSB)
    // strictly less than the MSB of P.
    // For example:
    // If N=3, P will be 4 (binary 100). Any X < 3 (i.e., 1 or 2) has MSB at position 0 or 1.
    // If N=4, P will be 4 (binary 100). Any X < 4 (i.e., 1, 2, 3) has MSB at position 0 or 1.
    unsigned long long P = 1;
    while (P < N) {
        P <<= 1; // Left shift P by 1 (equivalent to P = P * 2)
    }

    // If diff has a bit set at or above the MSB of P (i.e., diff >= P), it's impossible.
    // This is because any X < N has its MSB strictly less than the MSB of P.
    // The XOR sum of any number of values, all of which have their MSB strictly less than the MSB of P,
    // will also have its MSB strictly less than the MSB of P.
    // Therefore, if diff >= P, it cannot be formed by XORing numbers less than N.
    // This condition correctly handles cases where N is a power of 2 (e.g., N=4, P=4).
    // If N is a power of 2, then P = N. So if diff >= N, it means diff >= P, and it's impossible.
    if (diff >= P) {
        std::cout << -1 << std::endl;
        return; // Move to the next test case.
    }

    // Case 5: Two operations are sufficient.
    // At this point, we know:
    // 1. diff >= N (from previous checks)
    // 2. diff < P (from previous checks)
    // 3. N > 1 (from previous checks)
    //
    // From the condition `N <= diff < P`:
    // If N were a power of 2, then P would be equal to N. The condition `N <= diff < P` would become `N <= diff < N`,
    // which is a contradiction. Therefore, if we reach this point, N cannot be a power of 2.
    //
    // If N is not a power of 2, then P/2 < N < P.
    // This implies that P/2 is strictly less than N.
    // We can choose our first operation `X_1 = P/2`. This is a valid choice because `1 <= P/2 < N`.
    // (P/2 is at least 1 because N >= 2, so P >= 2).
    //
    // For the second operation, we need `X_2` such that `X_1 ^ X_2 = diff`, which means `X_2 = diff ^ X_1`.
    // So, `X_2 = diff ^ (P/2)`.
    // Since `P/2 <= diff < P` (because `diff` has its MSB at the same position as `P/2`, and `diff < P`),
    // XORing `diff` with `P/2` will flip its MSB, resulting in a number smaller than `P/2`.
    // Specifically, `0 <= diff ^ (P/2) < P/2`.
    // Since `P/2 < N`, it means `X_2 < N`.
    // We also need `X_2 > 0`. `X_2` would be 0 only if `diff = P/2`.
    // However, if `diff = P/2`, then `diff < N` (because `P/2 < N`), which would have been handled by Case 3 (1 operation).
    // So, `diff` cannot be `P/2`, which means `X_2 > 0`.
    //
    // Thus, both `X_1 = P/2` and `X_2 = diff ^ (P/2)` are valid operations (1 <= X < N).
    // This means 2 operations are always sufficient in this scenario.
    std::cout << 2 << std::endl;
}

int main() {
    // Optimize C++ standard streams for competitive programming.
    // This unties cin/cout from stdio and disables synchronization with C stdio,
    // which can significantly speed up I/O operations.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int T;
    // Read the number of test cases.
    std::cin >> T;
    // Loop through each test case and solve it.
    while (T--) {
        solve();
    }

    return 0; // Indicate successful execution.
}

#include <iostream>
#include <vector>
#include <algorithm> // Required for std::min and std::upper_bound

// Define the maximum possible value for M.
// This is used to size the precomputed divisors array.
const int MAX_M = 500000;

// A global vector of vectors to store divisors for numbers up to MAX_M.
// `divisors[i]` will contain a sorted list of all positive divisors of `i`.
// This is precomputed once to optimize multiple test cases.
std::vector<std::vector<int>> divisors(MAX_M + 1);

// Function to precompute all divisors for numbers from 1 to MAX_M.
// This function should be called exactly once at the beginning of the program.
void precompute_divisors() {
    // Iterate through all possible numbers `i` that can be a divisor.
    for (int i = 1; i <= MAX_M; ++i) {
        // For each `i`, iterate through its multiples `j`.
        // This means `i` is a divisor of `j`.
        for (int j = i; j <= MAX_M; j += i) {
            divisors[j].push_back(i);
        }
    }
    // After this loop, `divisors[k]` will contain all divisors of `k` in ascending order.
}

// Function to solve a single test case.
void solve() {
    int N, M;
    std::cin >> N >> M;

    // `ans` will store the total count of valid pairs (a, b).
    // Use `long long` because the count can be very large (up to N^2/2).
    long long ans = 0;

    // The problem condition is: ((M % a) % b) = ((M % b) % a)
    // Since 1 <= a < b <= N, we know M % a < a < b.
    // Therefore, (M % a) % b simplifies to M % a.
    // The condition becomes: M % a = (M % b) % a.
    // This is equivalent to: M % b is congruent to M % a modulo a.
    // Or, (M % b) - (M % a) is a multiple of a.
    // Let R_a = M % a and R_b = M % b. We need R_b = k * a + R_a for some integer k >= 0.
    // We know M = q_b * b + R_b. So M - R_b = q_b * b.
    // Substituting R_b = k * a + R_a, we get M - (k * a + R_a) = q_b * b.
    // Rearranging, M - R_a - k * a = q_b * b.
    // Since M - R_a is a multiple of a (M = q_a * a + R_a), M - R_a = q_a * a.
    // So, q_a * a - k * a = q_b * b.
    // (q_a - k) * a = q_b * b.
    // This implies that q_b * b must be a multiple of a.
    // q_b is integer division M / b. So the condition is (M / b) * b % a == 0.
    // This means `a` must be a divisor of `(M / b) * b`.

    // Case 1: b > M
    // If b > M, then M / b (integer division) is 0.
    // So, (M / b) * b = 0.
    // The condition becomes `a | 0`, which is true for any `a >= 1`.
    // We need to count pairs (a, b) such that 1 <= a < b <= N and b > M.
    // For a fixed `b` in this range, all `a` from 1 to `b-1` are valid.
    // The smallest `b` for this case is `M + 1`.
    // However, `b` must also be at least 2 (since `a < b` and `a >= 1`).
    // So, `b` ranges from `max(2, M + 1)` to `N`.
    long long b_start_case1 = M + 1;
    if (b_start_case1 < 2) {
        b_start_case1 = 2; // Ensure b starts from at least 2
    }

    if (b_start_case1 <= N) {
        // We need to sum (b-1) for b from b_start_case1 to N.
        // This is equivalent to summing `j` for `j` from `b_start_case1 - 1` to `N - 1`.
        long long first_term = b_start_case1 - 1;
        long long last_term = N - 1;
        long long num_terms = last_term - first_term + 1;
        // Sum of an arithmetic series: (first_term + last_term) * num_terms / 2
        ans += (first_term + last_term) * num_terms / 2;
    }

    // Case 2: b <= M
    // In this case, (M / b) * b is not necessarily 0.
    // The condition is `a | ((M / b) * b)`.
    // We need to count pairs (a, b) such that 1 <= a < b <= N and b <= M.
    // So, `b` ranges from 2 to `min(N, M)`.
    for (int b = 2; b <= std::min(N, M); ++b) {
        // Calculate P = (M / b) * b. This is equivalent to M - (M % b).
        // P is the largest multiple of b that is less than or equal to M.
        int P = (M / b) * b;

        // We need to count divisors `a` of `P` such that `1 <= a < b`.
        // Since `divisors[P]` is precomputed and sorted, we can use `std::upper_bound`.
        // `std::upper_bound(begin, end, val)` returns an iterator to the first element
        // in the range `[begin, end)` that is strictly greater than `val`.
        // So, `std::upper_bound(divisors[P].begin(), divisors[P].end(), b - 1)`
        // gives an iterator to the first divisor of `P` that is greater than or equal to `b`.
        // The distance from `divisors[P].begin()` to this iterator gives the count of divisors
        // that are less than `b`.
        ans += (std::upper_bound(divisors[P].begin(), divisors[P].end(), b - 1) - divisors[P].begin());
    }

    std::cout << ans << std::endl;
}

int main() {
    // Optimize C++ standard streams for faster input/output.
    // `std::ios_base::sync_with_stdio(false)` unties C++ streams from C standard streams.
    // `std::cin.tie(NULL)` prevents `cin` from flushing `cout` before each input operation.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    // Call the precomputation function once at the start of the program.
    // This populates the `divisors` array, which is then used by all test cases.
    precompute_divisors();

    int T; // Number of test cases
    std::cin >> T;
    while (T--) {
        solve(); // Solve each test case
    }

    return 0;
}

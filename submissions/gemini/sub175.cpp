#include <iostream>
#include <vector>
#include <algorithm> // Required for std::sort and std::upper_bound
#include <numeric>   // Required for std::distance

// Define the modulo constant as a global constant for easy access
const int MOD = 1000000007;

void solve() {
    int p, q, r;
    // Read the lengths of arrays A, B, and C
    std::cin >> p >> q >> r;

    // Declare and read elements of array A
    std::vector<long long> A(p);
    for (int i = 0; i < p; ++i) {
        std::cin >> A[i];
    }

    // Declare and read elements of array B
    std::vector<long long> B(q);
    for (int i = 0; i < q; ++i) {
        std::cin >> B[i];
    }

    // Declare and read elements of array C
    std::vector<long long> C(r);
    for (int i = 0; i < r; ++i) {
        std::cin >> C[i];
    }

    // Sort arrays A and C. This is crucial for efficient searching (upper_bound)
    // and for calculating prefix sums. Sorting takes O(P log P) and O(R log R) time.
    std::sort(A.begin(), A.end());
    std::sort(C.begin(), C.end());

    // Precompute prefix sums for sorted array A.
    // psA[i] will store the sum of A[0]...A[i-1] modulo MOD.
    // psA[0] is 0, representing the sum of an empty prefix.
    std::vector<long long> psA(p + 1, 0);
    for (int i = 0; i < p; ++i) {
        psA[i + 1] = (psA[i] + A[i]) % MOD;
    }

    // Precompute prefix sums for sorted array C.
    // psC[i] will store the sum of C[0]...C[i-1] modulo MOD.
    // psC[0] is 0, representing the sum of an empty prefix.
    std::vector<long long> psC(r + 1, 0);
    for (int i = 0; i < r; ++i) {
        psC[i + 1] = (psC[i] + C[i]) % MOD;
    }

    // Initialize the total sum of f(X, Y, Z) values
    long long total_sum = 0;

    // Iterate through each element Y in array B.
    // For each Y, we need to find all valid X from A and Z from C.
    for (long long Y : B) {
        // Find the count of elements in A that are less than or equal to Y.
        // std::upper_bound returns an iterator to the first element in A that is strictly greater than Y.
        // The distance from A.begin() to this iterator gives the count of elements <= Y.
        auto it_A = std::upper_bound(A.begin(), A.end(), Y);
        long long count_A_val = std::distance(A.begin(), it_A);

        // Find the count of elements in C that are less than or equal to Y.
        auto it_C = std::upper_bound(C.begin(), C.end(), Y);
        long long count_C_val = std::distance(C.begin(), it_C);

        // If there are no elements X in A such that X <= Y, or no elements Z in C such that Z <= Y,
        // then no valid triplet (X, Y, Z) can be formed for this Y that yields a non-zero f value.
        // So, this Y contributes 0 to the total sum.
        if (count_A_val == 0 || count_C_val == 0) {
            continue;
        }

        // Get the sum of elements in A that are less than or equal to Y.
        // This is directly available from the precomputed prefix sums: psA[count_A_val].
        long long sum_A_val = psA[count_A_val];

        // Get the sum of elements in C that are less than or equal to Y.
        // This is directly available from the precomputed prefix sums: psC[count_C_val].
        long long sum_C_val = psC[count_C_val];

        // The problem asks for Sum_{X,Y,Z} (X+Y)*(Y+Z) where X<=Y and Y>=Z.
        // For a fixed Y, this sum can be factored as:
        // (Sum_{X in A, X<=Y} (X + Y)) * (Sum_{Z in C, Z<=Y} (Y + Z))
        // Let's calculate the first part: Sum_{X in A, X<=Y} (X + Y)
        // This expands to (Sum_{X in A, X<=Y} X) + (Sum_{X in A, X<=Y} Y)
        // Which is sum_A_val + (Y * count_A_val).
        // All calculations are modulo MOD. Use 1LL to ensure multiplication is done using long long
        // before taking modulo, to prevent overflow if Y * count_A_val exceeds max int.
        long long term_X_sum = (sum_A_val + (1LL * Y * count_A_val) % MOD) % MOD;

        // Calculate the second part: Sum_{Z in C, Z<=Y} (Y + Z)
        // This expands to (Sum_{Z in C, Z<=Y} Y) + (Sum_{Z in C, Z<=Y} Z)
        // Which is (Y * count_C_val) + sum_C_val.
        long long term_Z_sum = ((1LL * Y * count_C_val) % MOD + sum_C_val) % MOD;

        // The contribution of the current Y to the total sum is the product of these two terms.
        long long current_Y_contribution = (term_X_sum * term_Z_sum) % MOD;

        // Add this contribution to the total sum, ensuring the sum remains within modulo.
        total_sum = (total_sum + current_Y_contribution) % MOD;
    }

    // Output the final total sum modulo MOD
    std::cout << total_sum << std::endl;
}

int main() {
    // Optimize C++ standard streams for faster input/output operations.
    // This is a common practice in competitive programming.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int T;
    // Read the number of test cases
    std::cin >> T;
    // Process each test case
    while (T--) {
        solve();
    }

    return 0;
}

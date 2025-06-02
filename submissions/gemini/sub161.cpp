#include <iostream>
#include <vector>
#include <numeric>
#include <map>
#include <tuple> // Required for std::tuple as map key

using namespace std;

long long N; // Stores the input 'n'
long long MOD = 1000000007; // Modulo for the answer
int K; // Target sum of q_i, which is (N-1)/2

// Memoization table to store results of subproblems.
// Key: tuple<idx, mask_b, mask_c, current_sum_q>
// Value: long long count of valid permutations
map<tuple<int, int, int, int>, long long> memo;

// Recursive function to count valid permutations b'
// We fix a'_idx = idx for simplicity, as the problem has a property
// that the count of valid b' permutations is independent of the choice of a'.
// idx: The current index (position) we are trying to fill in the permutations.
// mask_b: A bitmask representing the values already used in permutation b' up to (idx-1).
// mask_c: A bitmask representing the values already used in permutation c' up to (idx-1).
// current_sum_q: The sum of q_j values (where q_j = (a'_j + b'_j) / N) for j from 0 to idx-1.
long long solve(int idx, int mask_b, int mask_c, int current_sum_q) {
    // Base case: If all N positions have been filled (idx reaches N)
    if (idx == N) {
        // Check if the total sum of q_i matches the required K.
        // If it does, this is a valid way to complete the permutations.
        if (current_sum_q == K) {
            return 1;
        }
        // Otherwise, this path is not valid.
        return 0;
    }

    // Create a tuple representing the current state for memoization lookup.
    tuple<int, int, int, int> state = {idx, mask_b, mask_c, current_sum_q};

    // Check if this state has been computed before.
    // If yes, return the stored result to avoid redundant computations.
    if (memo.count(state)) {
        return memo[state];
    }

    long long ans = 0; // Initialize the count for the current state.
    int val_a = idx;   // Since we fixed a'_idx = idx.

    // Iterate through all possible values (0 to N-1) for b'_idx.
    for (int val_b = 0; val_b < N; ++val_b) {
        // Check if val_b has already been used in permutation b'.
        // (mask_b >> val_b) & 1 checks if the val_b-th bit is set in mask_b.
        if ((mask_b >> val_b) & 1) {
            continue; // If used, skip this value.
        }

        // Calculate c'_idx using the sum operation.
        int val_c = (val_a + val_b) % N;

        // Check if val_c has already been used in permutation c'.
        if ((mask_c >> val_c) & 1) {
            continue; // If used, skip this value.
        }

        // Calculate q_idx, which is the carry-over term.
        int q = (val_a + val_b) / N;

        // Pruning step: If adding 'q' to 'current_sum_q' would exceed the target 'K',
        // then this path cannot lead to a valid solution, as q_i are non-negative.
        if (current_sum_q + q > K) {
            continue; // Skip this path.
        }

        // Recursively call solve for the next index (idx + 1),
        // updating the masks and the sum of q values.
        // mask_b | (1 << val_b) sets the val_b-th bit in mask_b.
        // mask_c | (1 << val_c) sets the val_c-th bit in mask_c.
        ans = (ans + solve(idx + 1, mask_b | (1 << val_b), mask_c | (1 << val_c), current_sum_q + q)) % MOD;
    }

    // Store the computed result in the memoization table before returning.
    return memo[state] = ans;
}

int main() {
    // Optimize C++ standard streams for faster input/output.
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N; // Read the input integer n.

    // If N is an even number, no solutions exist based on the sum property derived.
    if (N % 2 == 0) {
        cout << 0 << endl;
        return 0;
    }

    // Calculate the target sum K for q_i values.
    K = (N - 1) / 2;

    // Calculate the number of valid b' permutations when a' is fixed as (0, 1, ..., N-1).
    // Start the recursion from index 0, with empty masks for b' and c', and initial sum_q of 0.
    long long count_b_for_fixed_a = solve(0, 0, 0, 0);

    // Calculate N! modulo MOD.
    long long factorial_N = 1;
    for (int i = 1; i <= N; ++i) {
        factorial_N = (factorial_N * i) % MOD;
    }

    // The total number of pairs (a, b) is N! multiplied by the count of b' permutations
    // found for a fixed a'. This is because for each of the N! choices for permutation 'a',
    // there are 'count_b_for_fixed_a' choices for permutation 'b'.
    long long total_pairs = (factorial_N * count_b_for_fixed_a) % MOD;

    cout << total_pairs << endl; // Print the final answer.

    return 0;
}

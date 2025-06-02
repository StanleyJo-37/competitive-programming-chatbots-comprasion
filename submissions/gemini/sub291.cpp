#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

// Function to solve a single test case
void solve() {
    int N;
    std::cin >> N; // Read N

    std::map<int, int> freq_B; // Map to store frequencies of elements in B
    for (int i = 0; i < 2 * N; ++i) {
        int b_val;
        std::cin >> b_val; // Read elements of B
        freq_B[b_val]++; // Increment frequency
    }

    // Special case for N=1
    // If N=1, A = [a_0].
    // Prefix medians: P_1 = [a_0], median = a_0.
    // Suffix medians: S_1 = [a_0], median = a_0.
    // So B must contain exactly two a_0's.
    if (N == 1) {
        if (freq_B.size() == 1 && freq_B.begin()->second == 2) {
            std::cout << freq_B.begin()->first << std::endl; // Output a_0
        } else {
            std::cout << -1 << std::endl; // Invalid B
        }
        return;
    }

    // General case for N > 1
    // The array A is [A_0, A_1, ..., A_{N-1}]
    // The median of a sorted array X of length L is X[(L-1)/2] (0-indexed).
    //
    // Let's analyze the counts of each A_i in B:
    //
    // Prefix medians: med(P_k) = A[(k-1)/2]
    // Suffix medians: med(S_k) = A[N-k + (k-1)/2]
    //
    // A_i for 0 <= i < (N-1)/2:
    //   A_i appears as med(P_{2i+1}) and med(P_{2i+2}).
    //   These are valid prefix lengths (2i+1 <= N, 2i+2 <= N).
    //   For example, A_0 is med(P_1) and med(P_2).
    //   Count = 2.
    //
    // A_{N-1}:
    //   A_{N-1} appears as med(S_1).
    //   Count = 1.
    //
    // A_i for (N-1)/2 < i < N-1:
    //   A_i appears as med(S_{2(N-1-i)+1}) and med(S_{2(N-1-i)+2}).
    //   These are valid suffix lengths.
    //   Count = 2.
    //
    // A_{(N-1)/2} (the "middle" element of A, 0-indexed):
    //   This element is med(P_N) and med(S_N).
    //   Let mid_idx_0based = (N-1)/2.
    //   A[mid_idx_0based] is med(P_N) and med(S_N).
    //   If N is odd (N=2M+1), mid_idx_0based = M.
    //     A_M is med(P_{2M+1}) and med(S_{2M+1}).
    //     A_M is also med(S_{2M}) = med([A_1, ..., A_{2M}]). Length 2M. Median is A_{1 + (2M-1)/2} = A_{1+M-1} = A_M.
    //     So A_M appears 3 times.
    //   If N is even (N=2M), mid_idx_0based = M-1.
    //     A_{M-1} is med(P_{2M-1}) and med(P_{2M}).
    //     A_{M-1} is also med(S_{2M}) = med([A_0, ..., A_{2M-1}]). Length 2M. Median is A_{(2M-1)/2} = A_{M-1}.
    //     So A_{M-1} appears 3 times.
    //   In both cases (N odd/even, N>1), A_{(N-1)/2} appears 3 times.
    //
    // Summary of expected counts for A_i (0-indexed):
    // - A_i for 0 <= i < (N-1)/2: count 2
    // - A_{(N-1)/2}: count 3
    // - A_i for (N-1)/2 < i < N-1: count 2
    // - A_{N-1}: count 1

    std::vector<int> A_candidate; // To store the reconstructed array A
    int current_a_idx = 0; // Current 0-indexed position in A we are trying to find
    int mid_idx_0based = (N - 1) / 2; // 0-indexed position of the "middle" element in A

    // Iterate through the frequency map. std::map iterates keys in sorted order.
    for (auto const& [val, count] : freq_B) {
        if (current_a_idx >= N) {
            // We have already found N elements for A, but there are still distinct elements in B.
            // This means B is invalid (too many distinct elements or wrong counts).
            std::cout << -1 << std::endl;
            return;
        }

        int expected_count;
        if (current_a_idx == mid_idx_0based) {
            expected_count = 3;
        } else if (current_a_idx == N - 1) {
            expected_count = 1;
        } else {
            expected_count = 2;
        }

        if (count != expected_count) {
            // Mismatch in expected frequency, B is invalid.
            std::cout << -1 << std::endl;
            return;
        }

        A_candidate.push_back(val); // Add the element to A
        current_a_idx++; // Move to the next position in A
    }

    // After iterating through all distinct elements in B, check if we found exactly N elements for A.
    if (A_candidate.size() != N) {
        // Not enough distinct elements in B to form A, B is invalid.
        std::cout << -1 << std::endl;
    } else {
        // All checks passed, A_candidate is the valid array A.
        for (int i = 0; i < N; ++i) {
            std::cout << A_candidate[i] << (i == N - 1 ? "" : " ");
        }
        std::cout << std::endl;
    }
}

int main() {
    // Optimize C++ standard streams for competitive programming
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int T;
    std::cin >> T; // Read the number of test cases
    while (T--) {
        solve(); // Solve each test case
    }

    return 0;
}

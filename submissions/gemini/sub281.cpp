#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // For std::min and std::max

void solve() {
    int N;
    std::cin >> N;
    std::string S;
    std::cin >> S;

    // prefix_open[i] stores the count of '(' characters in the prefix S[0...i-1].
    // This array has size N+1.
    // prefix_open[0] is 0 (representing an empty prefix before index 0).
    // For i > 0, prefix_open[i] stores the count of '(' in S[0...i-1].
    std::vector<int> prefix_open(N + 1, 0);
    for (int i = 0; i < N; ++i) {
        prefix_open[i + 1] = prefix_open[i] + (S[i] == '(' ? 1 : 0);
    }

    // suffix_close[i] stores the count of ')' characters in the suffix S[i...N-1].
    // This array has size N+1.
    // suffix_close[N] is 0 (representing an empty suffix starting at index N).
    // For i < N, suffix_close[i] stores the count of ')' in S[i...N-1].
    std::vector<int> suffix_close(N + 1, 0);
    for (int i = N - 1; i >= 0; --i) {
        suffix_close[i] = suffix_close[i + 1] + (S[i] == ')' ? 1 : 0);
    }

    // A bracket sequence S is called 'dense' if it is empty, or if S = (X) where X is dense.
    // This recursive definition implies that a dense sequence must be of the form
    // 'k' opening brackets followed by 'k' closing brackets, i.e., '((...()))'.
    // For example: "" (k=0), "()" (k=1), "(())" (k=2), "((()))" (k=3).
    //
    // The problem asks for the minimum number of brackets to remove to make S dense.
    // This is equivalent to finding the longest subsequence of S that is dense.
    // If the longest dense subsequence has length L_dense, then the minimum removals
    // will be N - L_dense.
    //
    // To form a dense subsequence of length 2k (k opening, k closing brackets),
    // we need to select k '(' characters and k ')' characters from the original string S.
    // The crucial condition for the '((...()))' structure is that all selected
    // '(' characters must appear before all selected ')' characters in the original string.
    //
    // This means there must exist a split point 'p' (an index in the original string S,
    // from 0 to N) such that:
    // 1. All k selected '(' characters come from the prefix S[0...p-1].
    // 2. All k selected ')' characters come from the suffix S[p...N-1].
    //
    // For a given split point 'p':
    // The number of available '(' characters is `prefix_open[p]`.
    // The number of available ')' characters is `suffix_close[p]`.
    // The maximum number of pairs 'k' that can be formed for this split point 'p'
    // is `min(prefix_open[p], suffix_close[p])`.
    //
    // We want to find the overall maximum 'k' by trying all possible split points 'p'.
    // 'p' iterates from 0 to N.
    // If p=0, no '(' can be chosen from the prefix, so k=0.
    // If p=N, no ')' can be chosen from the suffix, so k=0.

    int max_k = 0;
    for (int p = 0; p <= N; ++p) {
        max_k = std::max(max_k, std::min(prefix_open[p], suffix_close[p]));
    }

    // The length of the longest dense subsequence is 2 * max_k.
    // The minimum number of brackets to remove is the original length N minus
    // the length of the longest dense subsequence.
    std::cout << N - (2 * max_k) << std::endl;
}

int main() {
    // Optimize C++ standard streams for competitive programming.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams.
    // std::cin.tie(NULL) prevents std::cout from flushing before std::cin reads input.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int T;
    std::cin >> T; // Read the number of test cases.
    while (T--) {
        solve(); // Solve each test case.
    }

    return 0;
}

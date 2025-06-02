#include <unordered_set>
#include <vector>

int count_odd_pentaFib(int n) {
    // Handle edge cases where n is 0 or 1
    if (n == 0) return 0;
    if (n == 1 || n == 2) return 1;

    // Initialize the sequence with the first 5 terms
    std::vector<int> sequence = {0, 1, 1, 2, 4};
    std::unordered_set<int> odd_terms;

    // Add the initial odd terms (1 appears twice but set ensures uniqueness)
    if (sequence[1] % 2 != 0) odd_terms.insert(sequence[1]);
    if (sequence[2] % 2 != 0) odd_terms.insert(sequence[2]);

    // Generate terms from index 5 up to n (0-based to n-th term)
    for (int i = 5; i <= n; ++i) {
        // Compute next term as sum of previous 5 terms
        int next_term = sequence[i-1] + sequence[i-2] + sequence[i-3] + sequence[i-4] + sequence[i-5];
        sequence.push_back(next_term);

        // If the term is odd, add to the set (automatically handles duplicates)
        if (next_term % 2 != 0) {
            odd_terms.insert(next_term);
        }
    }

    return odd_terms.size();
}
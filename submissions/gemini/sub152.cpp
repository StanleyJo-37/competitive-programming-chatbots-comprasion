#include <iostream>
#include <vector>
#include <numeric> // For std::accumulate, though not used in final solution
#include <map>     // For std::map

// Function to solve a single test case
void solve() {
    int N;
    std::cin >> N; // Read N

    std::vector<int> A(N);
    for (int i = 0; i < N; ++i) {
        std::cin >> A[i]; // Read array elements
    }

    long long total_triples = 0; // Initialize total count of triples

    // current_xor_sum will store P_k (prefix XOR sum up to A_k)
    int current_xor_sum = 0; 

    // map_count stores the frequency of each prefix XOR sum value.
    // map_count[X] = number of times X has appeared as P_x for x < current k.
    std::map<int, int> map_count; 

    // map_sum_indices stores the sum of indices for each prefix XOR sum value.
    // map_sum_indices[X] = sum of x values where P_x = X for x < current k.
    std::map<int, long long> map_sum_indices; 

    // Initialize for P_0 = 0.
    // P_0 is the XOR sum up to index 0 (empty prefix), which is 0.
    // The index associated with P_0 is 0.
    map_count[0] = 1; 
    map_sum_indices[0] = 0; 

    // Iterate k from 1 to N (1-based indexing for A_k, 0-based for vector A)
    // In the problem, A_k corresponds to A[k-1] in 0-indexed vector.
    // The prefix XOR sum P_k corresponds to current_xor_sum after processing A[k-1].
    // The index k in P_k is 1-based.
    for (int k = 1; k <= N; ++k) {
        // Calculate P_k using A[k-1] (since A is 0-indexed)
        current_xor_sum ^= A[k-1]; 

        // Let X be the current prefix XOR sum P_k.
        int X = current_xor_sum;

        // We are looking for triples (i, j, k) such that 1 <= i < j <= k <= N
        // and A_i XOR ... XOR A_{j-1} = A_j XOR ... XOR A_k.
        // Using prefix XOR sums P_x = A_1 XOR ... XOR A_x (with P_0 = 0),
        // the equation becomes (P_{j-1} XOR P_{i-1}) = (P_k XOR P_{j-1}).
        // XORing both sides with P_{j-1} simplifies to P_{i-1} = P_k.
        //
        // Let x = i-1. The conditions on i, j, k imply:
        // 1 <= i  => 0 <= x
        // i < j   => x+1 < j
        // j <= k  => j <= k
        // So, x+1 < j <= k. This implies x+1 < k, or x <= k-2.
        //
        // Thus, for a fixed k, we need to find x such that P_x = P_k and 0 <= x <= k-2.
        // For each such x, the number of valid j's is k - (x+1).
        // The sum we need to add to total_triples is sum_{x: P_x=P_k, 0<=x<=k-2} (k - (x+1)).
        //
        // The maps (map_count, map_sum_indices) store information for P_0, ..., P_{k-1}.
        // When we query map_count[X] and map_sum_indices[X], they contain counts and sums
        // of indices x where P_x = X and x is in {0, ..., k-1}.
        //
        // If x = k-1, then i = k. The condition i < j becomes k < j.
        // But j <= k, so k < j <= k is impossible.
        // This means if x = k-1 is included in the sum, it contributes 0 to the count of j's.
        // (k - (x+1)) = (k - ((k-1)+1)) = (k - k) = 0.
        // So, we can sum (k - (x+1)) for all x in {0, ..., k-1} where P_x = P_k.
        // This sum is: sum(k-1) - sum(x) = (count of x) * (k-1) - (sum of x).

        // Check if P_k (current_xor_sum) has appeared before as P_x for x < k.
        if (map_count.count(X)) {
            // Get the count of previous occurrences of X (P_x = X for x < k)
            long long count_x = map_count[X];
            // Get the sum of indices x for previous occurrences of X
            long long sum_x = map_sum_indices[X];

            // Add to total_triples: (count_x * (k - 1)) - sum_x
            total_triples += count_x * (k - 1) - sum_x;
        }

        // After processing k, update maps for P_k.
        // The current P_k is associated with index k.
        map_count[X]++;
        map_sum_indices[X] += k;
    }

    std::cout << total_triples << std::endl; // Print the result
}

int main() {
    // Optimize C++ standard streams for faster input/output.
    // This is a common practice in competitive programming.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int T;
    std::cin >> T; // Read the number of test cases
    while (T--) {
        solve(); // Solve each test case
    }

    return 0; // Indicate successful execution
}

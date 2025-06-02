#include <iostream>
#include <vector>
#include <numeric> // Not strictly needed, but useful for some vector initializations.

// Modulo constant for the answer.
const int MOD = 1e9 + 7;

void solve() {
    int n;
    std::cin >> n;

    std::vector<int> a(n);
    std::vector<int> b(n);
    std::vector<int> d(n);

    // pos_a[val] will store the 0-indexed position `i` such that a[i] = val.
    // This helps in quickly finding the original index for a given value from permutation `a`.
    std::vector<int> pos_a(n + 1); 
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
        pos_a[a[i]] = i; // Store the 0-indexed position for value a[i].
    }
    for (int i = 0; i < n; ++i) {
        std::cin >> b[i];
    }
    for (int i = 0; i < n; ++i) {
        std::cin >> d[i];
    }

    // next_val[val] stores the value b[i] where a[i] = val.
    // This defines a functional graph where each node `val` has an outgoing edge to `next_val[val]`.
    // Since `a` and `b` are permutations, this functional graph is a collection of disjoint cycles.
    std::vector<int> next_val(n + 1);
    for (int i = 0; i < n; ++i) {
        next_val[a[i]] = b[i];
    }

    // visited[val] tracks if the node `val` has been visited during cycle traversal.
    std::vector<bool> visited(n + 1, false);
    long long ans = 1; // Initialize total ways to 1.

    // Iterate through all possible values (nodes) from 1 to n.
    for (int i = 1; i <= n; ++i) {
        // If node `i` has not been visited, it means we found a new cycle.
        if (!visited[i]) {
            int current_node = i;
            int cycle_len = 0;
            // has_fixed_choice becomes true if any d[k] != 0 for an index k that is part of this cycle.
            bool has_fixed_choice = false; 

            // Traverse the cycle starting from `current_node`.
            while (!visited[current_node]) {
                visited[current_node] = true; // Mark current node as visited.
                cycle_len++; // Increment cycle length.

                // Get the original 0-indexed position `k` such that a[k] = current_node.
                // This `k` is the index in the input arrays `a`, `b`, `d` that corresponds to the choice (current_node, next_val[current_node]).
                int original_idx = pos_a[current_node];
                
                // Check if the choice at this position `original_idx` is fixed by `d`.
                // If d[original_idx] is not 0, it means c[original_idx] is fixed.
                // This implies that for this entire cycle, the specific way of picking values (either all `a`s or all `b`s) is determined.
                if (d[original_idx] != 0) {
                    has_fixed_choice = true;
                }
                
                // Move to the next node in the cycle according to the `next_val` mapping.
                current_node = next_val[current_node];
            }

            // After traversing the entire cycle:
            if (has_fixed_choice) {
                // If any choice within this cycle was fixed by `d`, there's only 1 way to pick values for this cycle.
                // This covers both self-loops (a[k] == b[k]) where d[k] is fixed, and
                // longer cycles (a[k] != b[k]) where d[k] is fixed.
                ans = (ans * 1) % MOD;
            } else if (cycle_len == 1) {
                // If the cycle length is 1 (a self-loop: val -> val) and no choice was fixed by `d`.
                // This means a[k] = val and b[k] = val for some index k, and d[k] = 0.
                // In this scenario, c[k] must be `val`. There's only 1 way to choose for this index.
                ans = (ans * 1) % MOD;
            } else {
                // If the cycle length is greater than 1 and no choice was fixed by `d`.
                // There are two distinct ways to pick values for this cycle to form a valid permutation segment:
                // 1. Pick all `a[k]` values for indices `k` in the cycle.
                // 2. Pick all `b[k]` values for indices `k` in the cycle.
                ans = (ans * 2) % MOD;
            }
        }
    }

    std::cout << ans << std::endl;
}

int main() {
    // Optimize C++ standard streams for competitive programming.
    // This unties cin/cout from stdio and speeds up I/O operations.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t; // Read the number of test cases.
    while (t--) {
        solve(); // Solve each test case.
    }

    return 0;
}

#include <iostream>
#include <vector>
#include <algorithm>

// Define MAX_BITS for the maximum number of bits in the numbers.
// The maximum value for a_i is 10^12.
// 2^39 is approximately 5.5 * 10^11.
// 2^40 is approximately 1.1 * 10^12.
// Therefore, 40 bits are sufficient to represent numbers up to 10^12.
const int MAX_BITS = 40;

// Trie node structure. Using an array-based Trie for efficiency.
// `trie[node_idx][0]` stores the index of the child node for bit 0.
// `trie[node_idx][1]` stores the index of the child node for bit 1.
// In the worst case, the Trie can have N * MAX_BITS nodes.
// For N = 10^5 and MAX_BITS = 40, this is 4 * 10^6 nodes.
// Each node stores two integers (indices to other nodes).
std::vector<std::vector<int>> trie;

// Initializes the Trie.
void init_trie() {
    // Clear any previous Trie data.
    trie.clear();
    // Reserve space for potential nodes to avoid frequent reallocations.
    // A rough estimate for maximum nodes is N * MAX_BITS.
    // N=10^5, MAX_BITS=40, so 4*10^6 nodes.
    // We add 2 for the sentinel node (index 0) and the root node (index 1).
    trie.reserve(100000 * MAX_BITS + 2);
    
    // Add a dummy node at index 0. This node acts as a sentinel,
    // indicating that a child path does not exist if a pointer points to it.
    trie.emplace_back(std::vector<int>(2, 0)); // Node 0 (sentinel)
    // Add the root node at index 1. All insertions and queries start from this node.
    trie.emplace_back(std::vector<int>(2, 0)); // Node 1 (root)
}

// Inserts a number `val` into the Trie.
void insert(long long val) {
    int curr = 1; // Start from the root node (index 1).
    // Iterate from the most significant bit to the least significant bit.
    for (int i = MAX_BITS - 1; i >= 0; --i) {
        int bit = (val >> i) & 1; // Get the i-th bit of `val`.
        // If the child node for this bit does not exist (i.e., `trie[curr][bit]` is 0, pointing to sentinel).
        if (trie[curr][bit] == 0) {
            // Create a new node. The new node's index will be `trie.size()` before `emplace_back` returns.
            trie.emplace_back(std::vector<int>(2, 0)); // Add a new node, initialized with 0s.
            // Link the current node to the newly created child node.
            trie[curr][bit] = trie.size() - 1; // The index of the newly added node.
        }
        // Move to the child node.
        curr = trie[curr][bit];
    }
}

// Queries the Trie to find a number `val_in_trie` such that `val_in_trie XOR target_val` is maximized.
long long query_max_xor(long long target_val) {
    long long max_xor_val = 0;
    int curr = 1; // Start from the root node.
    // Iterate from the most significant bit to the least significant bit.
    for (int i = MAX_BITS - 1; i >= 0; --i) {
        int bit = (target_val >> i) & 1; // Get the i-th bit of `target_val`.
        // To maximize the XOR sum, we ideally want to choose a path in the Trie
        // that has the opposite bit at the current position.
        if (trie[curr][1 - bit] != 0) { // If the opposite bit child exists (not pointing to sentinel 0).
            max_xor_val |= (1LL << i); // Set the i-th bit in `max_xor_val` to 1.
            curr = trie[curr][1 - bit]; // Move to the opposite bit child.
        } else { // If the opposite bit child does not exist, we must take the same bit child.
            curr = trie[curr][bit]; // Move to the same bit child.
        }
    }
    return max_xor_val;
}

int main() {
    // Optimize C++ standard streams for faster input/output.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    std::cin >> n;

    std::vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    // Calculate prefix XOR sums.
    // P[k] represents the XOR sum of elements a[0] through a[k-1].
    // P[0] is defined as 0 (XOR sum of an empty prefix).
    std::vector<long long> P(n + 1);
    P[0] = 0;
    for (int i = 0; i < n; ++i) {
        P[i + 1] = P[i] ^ a[i];
    }

    // P_n is the total XOR sum of the entire array (a[0] ^ ... ^ a[n-1]).
    long long P_n = P[n];

    // Initialize the Trie.
    init_trie();

    long long max_pleasure = 0;

    // The problem asks to maximize (deliciousness of BitHaval's sausage) XOR (deliciousness of BitAryo's sausage).
    // Let BitHaval's sausage be a prefix a[0...i-1], its deliciousness is P[i].
    // Let BitAryo's sausage be a postfix a[j...n-1], its deliciousness is S[j].
    // The pieces must not intersect, meaning 0 <= i <= j <= n.
    // We know that S[j] = P[j] XOR P[n] (since P[j] XOR S[j] = P[n]).
    // So we want to maximize P[i] XOR (P[j] XOR P[n]) subject to 0 <= i <= j <= n.
    // We iterate through all possible split points `j` (from 0 to n).
    // For each `j`, `P[j] XOR P[n]` is a fixed value. Let this be `C_j`.
    // We then need to find a `P[i]` (where `i <= j`) that maximizes `P[i] XOR C_j`.
    // The Trie stores all `P[k]` values for `k <= j` encountered so far, allowing efficient lookup.
    for (int j = 0; j <= n; ++j) {
        // Insert P[j] into the Trie. This ensures that when we query,
        // all P_k for k <= j are available in the Trie.
        insert(P[j]);
        
        // Calculate C_j, the target value for the current j.
        long long C_j = P[j] ^ P_n;
        
        // Query the Trie to find the P_i (where i <= j) that maximizes XOR with C_j.
        long long current_max_xor = query_max_xor(C_j);
        
        // Update the overall maximum pleasure found so far.
        max_pleasure = std::max(max_pleasure, current_max_xor);
    }

    // Print the maximum pleasure.
    std::cout << max_pleasure << std::endl;

    return 0;
}

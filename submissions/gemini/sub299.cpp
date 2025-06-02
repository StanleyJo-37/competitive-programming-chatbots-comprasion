#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <map>
#include <array>

// Define constants for maximum values and modulo
const int MAX_VAL = 200005; // Maximum value of a_i
const int MOD = 1e9 + 7;    // Modulo for LCM calculation

// Sieve related arrays
int spf[MAX_VAL]; // Smallest Prime Factor for each number
std::vector<int> primes; // List of prime numbers up to MAX_VAL

// Precompute smallest prime factor for all numbers up to MAX_VAL
void sieve() {
    std::iota(spf, spf + MAX_VAL, 0); // Initialize spf[i] = i
    for (int i = 2; i < MAX_VAL; ++i) {
        if (spf[i] == i) { // If i is prime
            primes.push_back(i);
        }
        // For each prime p, mark multiples of p
        // Optimization: p > spf[i] means p is larger than any prime factor of i,
        // so i*p would have a smaller prime factor (spf[i]) already processed.
        // (long long)i * p >= MAX_VAL prevents overflow and bounds the loop.
        for (int p : primes) {
            if (p > spf[i] || (long long)i * p >= MAX_VAL) break;
            spf[i * p] = p;
        }
    }
}

// Get prime factorization of a number n
std::vector<std::pair<int, int>> get_prime_factorization(int n) {
    std::vector<std::pair<int, int>> factors;
    if (n == 1) return factors; // LCM of 1 is 1, it has no prime factors
    while (n > 1) {
        int p = spf[n]; // Get the smallest prime factor of n
        int count = 0;
        while (n % p == 0) { // Count occurrences of p
            n /= p;
            count++;
        }
        factors.push_back({p, count});
    }
    return factors;
}

// Modular exponentiation (base^exp % MOD)
long long power(long long base, long long exp) {
    long long res = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % MOD; // If exp is odd, multiply result by base
        base = (base * base) % MOD; // Square the base
        exp /= 2; // Halve the exponent
    }
    return res;
}

// Modular inverse (n^(MOD-2) % MOD for prime MOD, using Fermat's Little Theorem)
long long modInverse(long long n) {
    return power(n, MOD - 2);
}

// --- Segment Tree 1: For small primes ---
// Small primes are those <= SMALL_PRIME_THRESHOLD
const int SMALL_PRIME_THRESHOLD = 60;
// Number of primes <= 60: 2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59 (total 17)
const int SMALL_PRIME_COUNT = 17; 

std::vector<int> small_primes_list; // Stores the actual small prime values
std::map<int, int> small_prime_to_idx; // Maps small prime value to its index in small_primes_list

// Initialize small_primes_list and small_prime_to_idx map
void init_small_primes() {
    for (int p : primes) { // Iterate through primes found by sieve
        if (p > SMALL_PRIME_THRESHOLD) break; // Stop when primes exceed threshold
        small_prime_to_idx[p] = small_primes_list.size(); // Assign index
        small_primes_list.push_back(p); // Add to list
    }
}

// Node structure for Segment Tree 1
struct Node1 {
    std::array<int, SMALL_PRIME_COUNT> max_exponents; // Stores max exponent for each small prime
    Node1() { max_exponents.fill(0); } // Initialize all exponents to 0
};

std::vector<Node1> tree1; // Segment Tree 1 array
std::vector<std::vector<std::pair<int, int>>> a_factors; // Precomputed prime factorizations of array 'a' elements

// Merges two Node1 objects by taking the maximum exponent for each prime
void merge_nodes1(Node1& res, const Node1& left, const Node1& right) {
    for (int i = 0; i < SMALL_PRIME_COUNT; ++i) {
        res.max_exponents[i] = std::max(left.max_exponents[i], right.max_exponents[i]);
    }
}

// Builds Segment Tree 1
// node: current node index in tree1 vector
// start, end: range covered by current node
void build1(int node, int start, int end) {
    if (start == end) { // Leaf node: corresponds to a single element a[start]
        for (auto const& [p, e] : a_factors[start]) { // Iterate through prime factors of a[start]
            if (p <= SMALL_PRIME_THRESHOLD) { // If it's a small prime
                tree1[node].max_exponents[small_prime_to_idx[p]] = e; // Store its exponent
            }
        }
    } else { // Internal node
        int mid = (start + end) / 2;
        build1(2 * node, start, mid); // Build left child
        build1(2 * node + 1, mid + 1, end); // Build right child
        merge_nodes1(tree1[node], tree1[2 * node], tree1[2 * node + 1]); // Merge results from children
    }
}

// Queries Segment Tree 1 for a range [l, r]
// node: current node index
// start, end: range covered by current node
// l, r: query range
Node1 query1(int node, int start, int end, int l, int r) {
    if (r < start || end < l) {
        return Node1(); // Current node's range is completely outside query range, return identity (all zeros)
    }
    if (l <= start && end <= r) {
        return tree1[node]; // Current node's range is fully within query range, return its stored data
    }
    int mid = (start + end) / 2;
    Node1 p1 = query1(2 * node, start, mid, l, r); // Query left child
    Node1 p2 = query1(2 * node + 1, mid + 1, end, l, r); // Query right child
    Node1 res;
    merge_nodes1(res, p1, p2); // Merge results from children
    return res;
}

// --- Segment Tree 2: For large primes (p > SMALL_PRIME_THRESHOLD) ---
// This segment tree stores the product of distinct large primes in a range.
// It uses the "last occurrence" technique for online distinct range queries.

std::vector<long long> tree2; // Segment Tree 2 array
std::vector<int> last_pos_large_primes; // last_pos_large_primes[p] stores the last index where prime p appeared
std::vector<long long> prime_inverses; // prime_inverses[p] stores p^(-1) mod MOD

// Builds Segment Tree 2 (initializes all leaves to 1)
// node: current node index
// start, end: range covered by current node
void build2(int node, int start, int end) {
    if (start == end) {
        tree2[node] = 1; // Leaf node, initial value is 1 (identity for product)
    } else {
        int mid = (start + end) / 2;
        build2(2 * node, start, mid); // Build left child
        build2(2 * node + 1, mid + 1, end); // Build right child
        tree2[node] = (tree2[2 * node] * tree2[2 * node + 1]) % MOD; // Product of children
    }
}

// Updates a value at a specific index in Segment Tree 2
// Multiplies the current value at idx by 'val'
// node: current node index
// start, end: range covered by current node
// idx: index to update
// val: value to multiply by
void update2(int node, int start, int end, int idx, long long val) {
    if (start == end) { // Leaf node
        tree2[node] = (tree2[node] * val) % MOD; // Multiply current value by val
    } else {
        int mid = (start + end) / 2;
        if (start <= idx && idx <= mid) { // idx is in left child's range
            update2(2 * node, start, mid, idx, val);
        } else { // idx is in right child's range
            update2(2 * node + 1, mid + 1, end, idx, val);
        }
        tree2[node] = (tree2[2 * node] * tree2[2 * node + 1]) % MOD; // Update parent by merging children
    }
}

// Queries Segment Tree 2 for a range [l, r]
// node: current node index
// start, end: range covered by current node
// l, r: query range
long long query2(int node, int start, int end, int l, int r) {
    if (r < start || end < l) {
        return 1; // Current node's range is completely outside query range, return identity (1 for product)
    }
    if (l <= start && end <= r) {
        return tree2[node]; // Current node's range is fully within query range, return its stored product
    }
    int mid = (start + end) / 2;
    long long p1 = query2(2 * node, start, mid, l, r); // Query left child
    long long p2 = query2(2 * node + 1, mid + 1, end, l, r); // Query right child
    return (p1 * p2) % MOD; // Product of results from children
}

int main() {
    // Optimize C++ standard streams for faster input/output
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    // Precomputation steps
    sieve(); // Sieve to find SPF and list of primes
    init_small_primes(); // Initialize small primes list and map

    int n;
    std::cin >> n; // Read array length

    // Read array elements and precompute their prime factorizations
    a_factors.resize(n + 1); // Using 1-indexed arrays for convenience
    for (int i = 1; i <= n; ++i) {
        int val;
        std::cin >> val;
        a_factors[i] = get_prime_factorization(val);
    }

    // Precompute modular inverses for all primes up to MAX_VAL
    prime_inverses.resize(MAX_VAL);
    for (int p : primes) {
        prime_inverses[p] = modInverse(p);
    }

    // Build Segment Tree 1 for small primes
    tree1.resize(4 * (n + 1)); // Allocate memory for segment tree (approx 4N nodes)
    build1(1, 1, n); // Build from root (node 1) covering range [1, n]

    // Build and populate Segment Tree 2 for large primes
    tree2.resize(4 * (n + 1)); // Allocate memory
    last_pos_large_primes.resize(MAX_VAL, 0); // Initialize last_pos to 0 for all primes
    build2(1, 1, n); // Initialize all nodes to 1 (identity for product)

    // Populate Segment Tree 2 using the "last occurrence" technique
    // For each element a_i, for each large prime factor p:
    // If p appeared before at last_pos_large_primes[p], "undo" its contribution there.
    // Then "add" p's contribution at current index i.
    for (int i = 1; i <= n; ++i) {
        for (auto const& [p, e] : a_factors[i]) { // Iterate through prime factors of a[i]
            if (p > SMALL_PRIME_THRESHOLD) { // If it's a large prime
                if (last_pos_large_primes[p] != 0) {
                    // If this prime appeared before, divide by it at its old position
                    update2(1, 1, n, last_pos_large_primes[p], prime_inverses[p]);
                }
                // Multiply by this prime at its current position
                update2(1, 1, n, i, p);
                last_pos_large_primes[p] = i; // Update last occurrence to current index
            }
        }
    }

    int q;
    std::cin >> q; // Read number of queries

    long long last_ans = 0; // Initialize last answer to 0 as per problem statement

    // Process queries
    for (int k = 0; k < q; ++k) {
        int x, y;
        std::cin >> x >> y;

        // Calculate l and r based on online query rules
        int l = (last_ans + x) % n + 1;
        int r = (last_ans + y) % n + 1;
        if (l > r) std::swap(l, r); // Ensure l <= r

        long long current_lcm = 1;

        // Query Segment Tree 1 for small primes
        Node1 small_primes_result = query1(1, 1, n, l, r);
        for (int i = 0; i < SMALL_PRIME_COUNT; ++i) {
            if (small_primes_result.max_exponents[i] > 0) {
                // Multiply by p^e for each small prime with its max exponent
                current_lcm = (current_lcm * power(small_primes_list[i], small_primes_result.max_exponents[i])) % MOD;
            }
        }

        // Query Segment Tree 2 for large primes
        long long large_primes_product = query2(1, 1, n, l, r);
        current_lcm = (current_lcm * large_primes_product) % MOD;

        std::cout << current_lcm << "\n"; // Print the answer for current query
        last_ans = current_lcm; // Update last_ans for next query
    }

    return 0;
}

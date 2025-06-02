#include <iostream>
#include <vector>
#include <numeric> // Not strictly needed, but often useful for competitive programming
#include <algorithm> // Not strictly needed, but often useful for competitive programming

// Define a struct for Trie nodes.
// Using indices for children instead of raw pointers to manage memory efficiently
// and potentially improve cache locality.
struct TrieNode {
    int children[2]; // children[0] for bit 0, children[1] for bit 1
    int count;       // Number of elements currently passing through this node.
                     // This count helps determine if a path in the Trie is still "active"
                     // (i.e., if there are elements in the original array that still use this path).

    // Constructor to initialize a new node.
    TrieNode() : count(0) {
        children[0] = children[1] = -1; // -1 indicates no child exists for that bit
    }
};

// Global vector to store all Trie nodes. This allows managing nodes as a flat array,
// which is generally faster than dynamic allocation for each node.
std::vector<TrieNode> trie_nodes;
int root_idx; // Index of the root node in the trie_nodes vector (always 0 after init_trie)

// Function to initialize the Trie for a new test case.
// It clears any previous Trie structure and creates a new root node.
void init_trie() {
    trie_nodes.clear(); // Clear all previous nodes from the vector
    trie_nodes.emplace_back(); // Add the root node (at index 0)
    root_idx = 0; // Set root_idx to 0
}

// Function to insert a number into the Trie.
// It traverses the Trie based on the bits of the number, creating new nodes if necessary,
// and increments the 'count' for each node along the path.
void insert(int val) {
    int curr_idx = root_idx;
    trie_nodes[curr_idx].count++; // Increment count for the root node
    // Iterate from MSB (bit 29 for numbers up to 10^9, which is less than 2^30) down to LSB (bit 0).
    // This fixed bit range ensures consistent Trie depth.
    for (int i = 29; i >= 0; --i) {
        int bit = (val >> i) & 1; // Get the i-th bit of 'val'
        if (trie_nodes[curr_idx].children[bit] == -1) {
            // If the child node for this bit doesn't exist, create it.
            trie_nodes[curr_idx].children[bit] = trie_nodes.size(); // Assign the index of the new node
            trie_nodes.emplace_back(); // Add a new TrieNode to the vector
        }
        curr_idx = trie_nodes[curr_idx].children[bit]; // Move to the child node
        trie_nodes[curr_idx].count++; // Increment count for the current node
    }
}

// Function to find the number 'x' in the Trie that maximizes (x & (~current_OR)).
// This greedy choice is crucial because maximizing (x & (~current_OR)) is equivalent
// to maximizing (current_OR | x), which directly contributes to making the current
// prefix OR value (b_k) as large as possible.
int find_best(int current_OR) {
    int curr_idx = root_idx;
    int best_x = 0; // This will store the chosen 'x' value
    // Iterate from MSB down to LSB to make decisions based on bit significance.
    for (int i = 29; i >= 0; --i) {
        int bit_current_OR = (current_OR >> i) & 1; // Get the i-th bit of 'current_OR'

        // To maximize (x & (~current_OR)), we want the i-th bit of (x & (~current_OR)) to be 1 if possible.
        // This happens if (x_i is 1 AND current_OR_i is 0).
        // So, if current_OR_i is 0, we prefer x_i to be 1.
        // If current_OR_i is 1, then (x_i & (~current_OR_i)) will always be 0, regardless of x_i.
        // In this case, we prefer x_i to be 0 to potentially leave larger numbers (with higher bits set)
        // for later steps, though any choice is valid for the current b_k.
        // The logic `preferred_bit_for_x = 1 - bit_current_OR` captures this:
        // if bit_current_OR is 0, preferred_bit_for_x is 1.
        // if bit_current_OR is 1, preferred_bit_for_x is 0.
        int preferred_bit_for_x = 1 - bit_current_OR;

        // Check if the preferred child path exists and contains available numbers (count > 0).
        if (trie_nodes[curr_idx].children[preferred_bit_for_x] != -1 &&
            trie_nodes[trie_nodes[curr_idx].children[preferred_bit_for_x]].count > 0) {
            // If the preferred path is available, take it.
            best_x |= (preferred_bit_for_x << i); // Set the corresponding bit in 'best_x'
            curr_idx = trie_nodes[curr_idx].children[preferred_bit_for_x];
        } else {
            // If the preferred path is not available (either doesn't exist or no numbers left),
            // we must take the other path.
            // This means x's i-th bit will be (1 - preferred_bit_for_x), which is 'bit_current_OR'.
            best_x |= ((1 - preferred_bit_for_x) << i); // Set the corresponding bit in 'best_x'
            curr_idx = trie_nodes[curr_idx].children[1 - preferred_bit_for_x];
        }
    }
    return best_x;
}

// Function to remove a number from the Trie.
// It traverses the path corresponding to 'val' and decrements the 'count' for each node along the path.
// This effectively marks the number as "removed" from the available set.
void remove(int val) {
    int curr_idx = root_idx;
    trie_nodes[curr_idx].count--; // Decrement count for the root node
    // Traverse the path corresponding to 'val'
    for (int i = 29; i >= 0; --i) {
        int bit = (val >> i) & 1;
        curr_idx = trie_nodes[curr_idx].children[bit]; // Move to the child node
        trie_nodes[curr_idx].count--; // Decrement count for the current node
    }
}

// Function to solve a single test case.
void solve() {
    int n;
    std::cin >> n; // Read the length of the array 'a'
    
    init_trie(); // Initialize the Trie for this test case
    // Read all elements of 'a' and insert them into the Trie.
    // We don't need to store 'a' in a vector explicitly after inserting into Trie,
    // but it's common practice to read into a vector first.
    // Here, we can directly insert into Trie.
    for (int i = 0; i < n; ++i) {
        int val;
        std::cin >> val;
        insert(val); // Insert each element into the Trie
    }

    std::vector<int> result_array; // This will store the rearranged array
    int current_OR = 0; // Initialize the current prefix OR sum to 0

    // Build the rearranged array greedily, one element at a time.
    for (int k = 0; k < n; ++k) {
        // Find the best element to add next from the available elements in the Trie.
        int x_to_add = find_best(current_OR);
        
        result_array.push_back(x_to_add); // Add the chosen element to the result array
        current_OR |= x_to_add; // Update the current prefix OR sum
        remove(x_to_add); // Remove the chosen element from the Trie so it's not picked again
    }

    // Print the rearranged array elements, separated by spaces.
    for (int i = 0; i < n; ++i) {
        std::cout << result_array[i] << (i == n - 1 ? "" : " ");
    }
    std::cout << "\n"; // Newline after each test case output
}

int main() {
    // Optimize C++ standard streams for competitive programming.
    // std::ios_base::sync_with_stdio(false) unties C++ streams from C standard streams.
    // std::cin.tie(NULL) prevents std::cout from flushing before std::cin reads input.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t; // Read the number of test cases
    while (t--) {
        solve(); // Solve each test case
    }

    return 0;
}

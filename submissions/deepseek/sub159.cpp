#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    int k;
    cin >> k;

    // The idea is to represent k in binary and construct a graph where
    // the number of paths is the sum of powers of 2 (binary representation).
    // We'll use a diamond-like structure where each bit contributes to the count.
    // The graph will have layers: 1 -> middle nodes -> 2.
    // The number of middle nodes is equal to the number of bits set in k.
    // Each middle node connects to 1 and 2, and the number of such nodes is the count of bits.

    vector<string> adj;
    int n = 2; // Start with nodes 1 and 2
    adj.push_back("NY");
    adj.push_back("YN");

    // Handle k=1 separately
    if (k == 1) {
        cout << 2 << endl;
        cout << "NY" << endl << "YN" << endl;
        return 0;
    }

    // For k > 1, we need to add intermediate nodes.
    // The number of intermediate nodes is equal to the number of bits set in k.
    // Each bit corresponds to a group of nodes that contribute 2^bit to the total count.
    // We'll build the graph by adding layers for each bit set in k.

    // Find the highest bit set in k
    int highest_bit = 0;
    while ((1 << highest_bit) <= k) {
        highest_bit++;
    }
    highest_bit--;

    // The total nodes will be 2 (1 and 2) + highest_bit * 2 (two nodes per bit: one for the bit and one for the connection).
    // But we can optimize by grouping bits. For each bit set in k, we add 'bit_value' nodes connected to 1 and 2.
    // The total paths will be the sum of bit_values, which is k.

    // Reset the adjacency matrix for new construction
    adj.clear();
    n = 2 + highest_bit * 2;
    adj.resize(n, string(n, 'N'));

    // Connect 1 to the first layer and the first layer to 2
    for (int bit = 0; bit <= highest_bit; ++bit) {
        if (k & (1 << bit)) {
            int node1 = 2 + 2 * bit;
            int node2 = 2 + 2 * bit + 1;
            adj[0][node1] = 'Y';
            adj[node1][0] = 'Y';
            adj[node1][node2] = 'Y';
            adj[node2][node1] = 'Y';
            adj[node2][1] = 'Y';
            adj[1][node2] = 'Y';
        }
    }

    // Ensure the graph is undirected and simple
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j) adj[i][j] = 'N';
            else adj[i][j] = adj[j][i];
        }
    }

    // Output the graph
    cout << n << endl;
    for (int i = 0; i < n; ++i) {
        cout << adj[i] << endl;
    }

    return 0;
}
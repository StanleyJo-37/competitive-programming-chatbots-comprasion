#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

// The idea is to construct a layered graph where the number of shortest paths from 1 to 2 is exactly k.
// We use a "bitwise" construction: for each bit in k, we create a layer, and for each set bit, we add a "split" node
// that connects to the end, so the number of paths is the sum of 2^i for each set bit i, i.e., exactly k.

int main() {
    int k;
    cin >> k;

    // We will use at most 1000 nodes, so we can use up to 30 layers (since 2^30 > 1e9)
    // Let's build the graph as follows:
    // - Node 1: start
    // - Node 2: end
    // - For each bit position i (from 0 to 29), we create a layer of 2 nodes (for path splitting)
    // - For each set bit in k, we connect a "split" node to the end node (node 2)
    // - All layers are connected in a chain, and each layer is fully connected to the next layer

    // Let's keep track of the nodes
    vector<vector<char>> G(1000, vector<char>(1000, 'N'));
    int node_cnt = 2; // 1 and 2 are used

    vector<int> layer_nodes; // stores the entry node of each layer

    int last_layer_start = 1; // start from node 1

    // For each bit position, create a layer
    for (int i = 0; i < 32; ++i) {
        if ((1 << i) > k) break;
        // Each layer has 2 nodes: entry and exit
        int entry = ++node_cnt;
        int exit = ++node_cnt;
        // Connect last layer's exit to this layer's entry
        G[last_layer_start-1][entry-1] = 'Y';
        G[entry-1][last_layer_start-1] = 'Y';
        // Connect entry to exit
        G[entry-1][exit-1] = 'Y';
        G[exit-1][entry-1] = 'Y';
        // For the next layer, the exit becomes the new last_layer_start
        last_layer_start = exit;
        // Store the entry node for this layer
        layer_nodes.push_back(entry);
    }

    // Now, for each set bit in k, we add a "split" node that connects to the corresponding layer's entry
    // and also connects directly to node 2 (the end)
    int split_base = node_cnt;
    for (int i = 0; i < (int)layer_nodes.size(); ++i) {
        if ((k >> i) & 1) {
            int split_node = ++node_cnt;
            // Connect split_node to the corresponding layer's entry
            G[layer_nodes[i]-1][split_node-1] = 'Y';
            G[split_node-1][layer_nodes[i]-1] = 'Y';
            // Connect split_node to node 2 (end)
            G[split_node-1][1] = 'Y';
            G[1][split_node-1] = 'Y';
        }
    }

    // The total number of nodes used is node_cnt
    cout << node_cnt << endl;
    for (int i = 0; i < node_cnt; ++i) {
        for (int j = 0; j < node_cnt; ++j) {
            cout << G[i][j];
        }
        cout << endl;
    }
    return 0;
}
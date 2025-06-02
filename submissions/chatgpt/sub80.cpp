#include <bits/stdc++.h>
using namespace std;

// Each node in the broom/tree
struct Node {
    // Map from character to child node index
    unordered_map<char, int> children;
    // Depth of this node (distance from root, root is 0)
    int depth = 0;
    // For merging tries: pointer to the "main" child (the largest subtree)
    int heavy_child = -1;
    // For each depth, how many nodes are at that depth in the subtree rooted here
    // Used for efficient merging and counting
    unordered_map<int, int> depth_count;
};

int n;
vector<Node> tree;

// For each depth, how many nodes are at that depth in the whole tree
vector<int> total_at_depth;

// For each depth, how many nodes can be merged at that depth (i.e., how many nodes will be merged if we remove the p-th letter)
vector<int> merged_at_depth;

// For each node, store its parent (for building the tree)
vector<int> parent;

// For each node, store the letter from its parent
vector<char> from_parent;

// For each node, store the size of its subtree
vector<int> subtree_size;

// For each node, store the maximum depth in its subtree
vector<int> max_depth_in_subtree;

// For each node, store the depth of the node
vector<int> node_depth;

// For each node, store the number of leaves in its subtree
vector<int> leaves_in_subtree;

// For each node, store the number of leaves at each depth in its subtree
vector<unordered_map<int, int>> leaves_at_depth;

// For each node, store the mapping from depth to the number of nodes at that depth in its subtree
vector<unordered_map<int, int>> nodes_at_depth;

// For each node, store the mapping from depth to the number of leaves at that depth in its subtree
vector<unordered_map<int, int>> leaves_count_at_depth;

// For each node, store the mapping from depth to the number of nodes at that depth in its subtree
vector<unordered_map<int, int>> nodes_count_at_depth;

// For each node, store the mapping from depth to the number of leaves at that depth in its subtree
vector<unordered_map<int, int>> leaves_count;

// For each node, store the mapping from depth to the number of nodes at that depth in its subtree
vector<unordered_map<int, int>> nodes_count;

// For each node, store the mapping from depth to the number of leaves at that depth in its subtree
vector<unordered_map<int, int>> leaves_count2;

// For each node, store the mapping from depth to the number of nodes at that depth in its subtree
vector<unordered_map<int, int>> nodes_count2;

// For each node, store the mapping from depth to the number of leaves at that depth in its subtree
vector<unordered_map<int, int>> leaves_count3;

// For each node, store the mapping from depth to the number of nodes at that depth in its subtree
vector<unordered_map<int, int>> nodes_count3;

// For each node, store the mapping from depth to the number of leaves at that depth in its subtree
vector<unordered_map<int, int>> leaves_count4;

// For each node, store the mapping from depth to the number of nodes at that depth in its subtree
vector<unordered_map<int, int>> nodes_count4;

// For each node, store the mapping from depth to the number of leaves at that depth in its subtree
vector<unordered_map<int, int>> leaves_count5;

// For each node, store the mapping from depth to the number of nodes at that depth in its subtree
vector<unordered_map<int, int>> nodes_count5;

// For each node, store the mapping from depth to the number of leaves at that depth in its subtree
vector<unordered_map<int, int>> leaves_count6;

// For each node, store the mapping from depth to the number of nodes at that depth in its subtree
vector<unordered_map<int, int>> nodes_count6;

// For each node, store the mapping from depth to the number of leaves at that depth in its subtree
vector<unordered_map<int, int>> leaves_count7;

// For each node, store the mapping from depth to the number of nodes at that depth in its subtree
vector<unordered_map<int, int>> nodes_count7;

// For each node, store the mapping from depth to the number of leaves at that depth in its subtree
vector<unordered_map<int, int>> leaves_count8;

// For each node, store the mapping from depth to the number of nodes at that depth in its subtree
vector<unordered_map<int, int>> nodes_count8;

// For each node, store the mapping from depth to the number of leaves at that depth in its subtree
vector<unordered_map<int, int>> leaves_count9;

// For each node, store the mapping from depth to the number of nodes at that depth in its subtree
vector<unordered_map<int, int>> nodes_count9;

// For each node, store the mapping from depth to the number of leaves at that depth in its subtree
vector<unordered_map<int, int>> leaves_count10;

// For each node, store the mapping from depth to the number of nodes at that depth in its subtree
vector<unordered_map<int, int>> nodes_count10;

// For each node, store the mapping from depth to the number of leaves at that depth in its subtree
vector<unordered_map<int, int>> leaves_count11;

// For each node, store the mapping from depth to the number of nodes at that depth in its subtree
vector<unordered_map<int, int>> nodes_count11;

// For each node, store the mapping from depth to the number of leaves at that depth in its subtree
vector<unordered_map<int, int>> leaves_count12;

// For each node, store the mapping from depth to the number of nodes at that depth in its subtree
vector<unordered_map<int, int>> nodes_count12;

// For each node, store the mapping from depth to the number of leaves at that depth in its subtree
vector<unordered_map<int, int>> leaves_count13;

// For each node, store the mapping from depth to the number of nodes at that depth in its subtree
vector<unordered_map<int, int>> nodes_count13;

// For each node, store the mapping from depth to the number of leaves at that depth in its subtree
vector<unordered_map<int, int>> leaves_count14;

// For each node, store the mapping from depth to the number of nodes at that depth in its subtree
vector<unordered_map<int, int>> nodes_count14;

// For each node, store the mapping from depth to the number of leaves at that depth in its subtree
vector<unordered_map<int, int>> leaves_count15;

// For each node, store the mapping from depth to the number of nodes at that depth in its subtree
vector<unordered_map<int, int>> nodes_count15;

// For each node, store the mapping from depth to the number of leaves at that depth in its subtree
vector<unordered_map<int, int>> leaves_count16;

// For each node, store the mapping from depth to the number of nodes at that depth in its subtree
vector<unordered_map<int, int>> nodes_count16;

// For each node, store the mapping from depth to the number of leaves at that depth in its subtree
vector<unordered_map<int, int>> leaves_count17;

// For each node, store the mapping from depth to the number of nodes at that depth in its subtree
vector<unordered_map<int, int>> nodes_count17;

// For each node, store the mapping from depth to the number of leaves at that depth in its subtree
vector<unordered_map<int, int>> leaves_count18;

// For each node, store the mapping from depth to the number of nodes at that depth in its subtree
vector<unordered_map<int, int>> nodes_count18;

// For each node, store the mapping from depth to the number of leaves at that depth in its subtree
vector<unordered_map<int, int>> leaves_count19;

// For each node, store the mapping from depth to the number of nodes at that depth in its subtree
vector<unordered_map<int, int>> nodes_count19;

// For each node, store the mapping from depth to the number of leaves at that depth in its subtree
vector<unordered_map<int, int>> leaves_count20;

// For each node, store the mapping from depth to the number of nodes at that depth in its subtree
vector<unordered_map<int, int>> nodes_count20;

// For each node, store the mapping from depth to the number of leaves at that depth in its subtree
vector<unordered_map<int, int>> leaves_count21;

// For each node, store the mapping from depth to the number of nodes at that depth in its subtree
vector<unordered_map<int, int>> nodes_count21;

// For each node, store the mapping from depth to the number of leaves at that depth in its subtree
vector<unordered_map<int, int>> leaves_count22;

// For each node, store the mapping from depth to the number of nodes at that depth in its subtree
vector<unordered_map<int, int>> nodes_count22;

// For each node, store the mapping from depth to the number of leaves at that depth in its subtree
vector<unordered_map<int, int>> leaves_count23;

// For each node, store the mapping from depth to the number of nodes at that depth in its subtree
vector<unordered_map<int, int>> nodes_count23;

// For each node, store the mapping from depth to the number of leaves at that depth in its subtree
vector<unordered_map<int, int>> leaves_count24;

// For each node, store the mapping from depth to the number of nodes at that depth in its subtree
vector<unordered_map<int, int>> nodes_count24;

// For each node, store the mapping from depth to the number of leaves at that depth in its subtree
vector<unordered_map<int
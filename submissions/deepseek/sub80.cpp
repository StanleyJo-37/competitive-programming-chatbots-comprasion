#include <bits/stdc++.h>
using namespace std;

const int MAXN = 3e5 + 5;

vector<pair<int, char>> adj[MAXN];
int depth[MAXN];
vector<int> nodes_at_depth[MAXN];
int max_depth = 0;

// Compute depth of each node and group nodes by their depth
void dfs(int u, int parent) {
    for (auto &edge : adj[u]) {
        int v = edge.first;
        if (v != parent) {
            depth[v] = depth[u] + 1;
            nodes_at_depth[depth[v]].push_back(v);
            max_depth = max(max_depth, depth[v]);
            dfs(v, u);
        }
    }
}

// Trie node structure for merging subtrees
struct TrieNode {
    map<char, TrieNode*> children;
    int count = 0;
};

// Insert a string into the trie and return the number of new nodes created
int insert(TrieNode* root, const string &s) {
    int new_nodes = 0;
    TrieNode* current = root;
    for (char c : s) {
        if (current->children.find(c) == current->children.end()) {
            current->children[c] = new TrieNode();
            new_nodes++;
        }
        current = current->children[c];
    }
    return new_nodes;
}

// Compute the minimal size after removing a certain depth p
pair<int, int> compute_min_size(int n) {
    int min_size = n;
    int best_p = 1;

    for (int p = 1; p <= max_depth; ++p) {
        // For each node at depth p-1, we need to merge their subtrees
        // after removing the p-th character (i.e., the edges at depth p)
        TrieNode* root = new TrieNode();
        int current_size = 1; // root

        for (int u : nodes_at_depth[p - 1]) {
            for (auto &edge : adj[u]) {
                int v = edge.first;
                char c = edge.second;
                if (depth[v] == p) {
                    // For each child at depth p, we process its subtree
                    string subtree_path;
                    vector<pair<int, char>> stack;
                    stack.emplace_back(v, '\0');
                    while (!stack.empty()) {
                        auto [node, parent_char] = stack.back();
                        stack.pop_back();
                        if (parent_char != '\0') {
                            subtree_path += parent_char;
                        }
                        for (auto &next_edge : adj[node]) {
                            int next_node = next_edge.first;
                            if (depth[next_node] > depth[node]) {
                                stack.emplace_back(next_node, next_edge.second);
                            }
                        }
                    }
                    current_size += insert(root, subtree_path);
                }
            }
        }

        // Total size is (nodes up to depth p-1) + merged subtrees
        int total_size = 0;
        for (int d = 0; d < p; ++d) {
            total_size += nodes_at_depth[d].size();
        }
        total_size += current_size;

        if (total_size < min_size) {
            min_size = total_size;
            best_p = p;
        } else if (total_size == min_size && p < best_p) {
            best_p = p;
        }

        // Clean up the trie to avoid memory leaks
        // Note: In practice, you might want to implement a proper cleanup
        // But for competitive programming, it's often omitted for speed
    }

    return {min_size, best_p};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        char c;
        cin >> u >> v >> c;
        adj[u].emplace_back(v, c);
        adj[v].emplace_back(u, c);
    }

    depth[1] = 0;
    nodes_at_depth[0].push_back(1);
    dfs(1, -1);

    auto [min_size, best_p] = compute_min_size(n);
    cout << min_size << '\n' << best_p << '\n';

    return 0;
}
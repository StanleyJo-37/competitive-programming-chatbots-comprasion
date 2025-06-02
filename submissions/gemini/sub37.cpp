#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

const int MAXN = 200005;
const int MAXK = 5;

vector<int> adj[MAXN];
int n, k;
long long total_jumps = 0;

// dp[u][d] will store the number of nodes in the subtree of u that are at distance d from u.
// d can be positive (distance down from u) or negative (distance up from u).
// To handle negative distances, we can offset them.
// A distance of 'd' from u is stored at index 'd + MAXK' in the dp array.
// So, dp[u][MAXK] is distance 0, dp[u][MAXK + 1] is distance 1, ..., dp[u][MAXK + k] is distance k.
// And dp[u][MAXK - 1] is distance -1, ..., dp[u][0] is distance -k.
long long dp[MAXN][2 * MAXK + 1];

// subtree_size[u] stores the total number of nodes in the subtree rooted at u.
int subtree_size[MAXN];

// Centroid decomposition variables
bool visited_centroid[MAXN];
vector<int> centroid_tree_adj[MAXN]; // Optional: to build centroid tree if needed
int parent_centroid[MAXN]; // Stores parent in centroid tree

// dfs_size calculates the size of each subtree in the current component
// and helps find the centroid.
void dfs_size(int u, int p, int& current_component_size, vector<int>& nodes_in_component) {
    subtree_size[u] = 1;
    nodes_in_component.push_back(u);
    current_component_size++;
    for (int v : adj[u]) {
        if (v == p || visited_centroid[v]) {
            continue;
        }
        dfs_size(v, u, current_component_size, nodes_in_component);
        subtree_size[u] += subtree_size[v];
    }
}

// find_centroid finds the centroid of the current component.
int find_centroid(int u, int p, int current_component_size) {
    for (int v : adj[u]) {
        if (v == p || visited_centroid[v]) {
            continue;
        }
        if (subtree_size[v] > current_component_size / 2) {
            return find_centroid(v, u, current_component_size);
        }
    }
    return u; // u is the centroid
}

// dfs_calc_dp calculates the dp states for a subtree rooted at u,
// considering distances relative to a pivot node.
// It populates `dp` arrays for nodes in the current component
// and also `current_path_counts`.
// current_path_counts[d] stores the number of nodes at distance 'd'
// from the pivot node within the current DFS traversal path.
void dfs_calc_dp(int u, int p, int dist_from_pivot, vector<long long>& current_path_counts) {
    // Only consider distances up to k for direct jumps.
    // However, we need to know counts up to k to combine later.
    // A distance of `d` from the pivot `c` is stored at index `d`.
    if (dist_from_pivot <= k) {
        current_path_counts[dist_from_pivot]++;
    }

    for (int v : adj[u]) {
        if (v == p || visited_centroid[v]) {
            continue;
        }
        dfs_calc_dp(v, u, dist_from_pivot + 1, current_path_counts);
    }
}

// dfs_calc_ans calculates the number of jumps needed for pairs within a component
// relative to the current centroid.
// It uses dp states to count pairs that need 1 or 2 jumps.
void dfs_calc_ans(int u, int p, int dist_from_centroid, vector<long long>& current_dp_sum) {
    // current_dp_sum[d] stores the number of nodes at distance d from the centroid within this subtree.
    // The range of d is [0, k].
    if (dist_from_centroid <= k) {
        current_dp_sum[dist_from_centroid]++;
    }

    for (int v : adj[u]) {
        if (v == p || visited_centroid[v]) {
            continue;
        }
        dfs_calc_ans(v, u, dist_from_centroid + 1, current_dp_sum);
    }
}


// centroid_decompose performs the centroid decomposition.
void centroid_decompose(int u, int p_centroid) {
    // Step 1: Find the size of the current component and collect its nodes.
    int current_component_size = 0;
    vector<int> nodes_in_component;
    dfs_size(u, 0, current_component_size, nodes_in_component);

    // Step 2: Find the centroid of the current component.
    int centroid = find_centroid(u, 0, current_component_size);
    visited_centroid[centroid] = true;
    parent_centroid[centroid] = p_centroid; // Set parent in centroid tree (optional for this problem)

    // Step 3: Calculate contributions for pairs passing through the centroid.

    // Initialize the main DP table for the current centroid to 0.
    // dp[centroid][MAXK + d] counts nodes at distance d from centroid.
    // dp[centroid][MAXK - d] counts nodes for paths coming up.
    for (int i = 0; i <= 2 * k; ++i) {
        dp[centroid][i] = 0;
    }
    dp[centroid][MAXK]++; // The centroid itself is at distance 0 from itself.

    // total_pairs_one_jump accounts for pairs (x, y) where x is in one child subtree
    // and y is in another child subtree, and dist(x,y) <= k.
    // total_pairs_two_jumps accounts for pairs (x, y) where x is in one child subtree
    // and y is in another child subtree, and k < dist(x,y) <= 2*k.
    // Or for pairs (x, centroid) and (y, centroid) where dist(x, centroid) > k and dist(y, centroid) > k,
    // and dist(x,y) <= 2*k.
    // We want to count pairs (s,t) with s<t.
    // This is equivalent to total_jumps += sum of f(s,t) for all s!=t.
    // Then we divide by 2 at the end (or count carefully for s<t).
    // Let's count for all (s,t) and divide by 2 later.
    // Alternatively, we can ensure s<t when we add to total_jumps. This will be harder.
    // Let's count total unordered pairs (s,t) such that s!=t and then divide by 2.

    long long current_component_pairs_1_jump = 0;
    long long current_component_pairs_2_jumps = 0;

    // dp_total_from_centroid stores the sum of dp[centroid][MAXK+d] values from all subtrees processed so far.
    // It helps combine counts from different subtrees.
    vector<long long> dp_total_from_centroid(k + 1, 0); // stores counts for distances 0 to k
    dp_total_from_centroid[0] = 1; // for the centroid itself

    for (int v : adj[centroid]) {
        if (visited_centroid[v]) {
            continue;
        }

        // current_subtree_dp stores counts for nodes in subtree 'v'
        // relative to the centroid.
        vector<long long> current_subtree_dp(k + 1, 0); // stores counts for distances 0 to k
        dfs_calc_ans(v, centroid, 1, current_subtree_dp);

        // Calculate contributions for pairs (x,y) where x is in a previously processed subtree
        // (or is the centroid) and y is in the current subtree 'v'.
        for (int d_prev = 0; d_prev <= k; ++d_prev) {
            for (int d_curr = 0; d_curr <= k; ++d_curr) {
                if (dp_total_from_centroid[d_prev] == 0 || current_subtree_dp[d_curr] == 0) continue;

                int total_dist = d_prev + d_curr;
                if (total_dist <= k) {
                    current_component_pairs_1_jump += dp_total_from_centroid[d_prev] * current_subtree_dp[d_curr];
                } else if (total_dist <= 2 * k) {
                    current_component_pairs_2_jumps += dp_total_from_centroid[d_prev] * current_subtree_dp[d_curr];
                }
            }
        }

        // Add current_subtree_dp to dp_total_from_centroid for future calculations.
        for (int d = 0; d <= k; ++d) {
            dp_total_from_centroid[d] += current_subtree_dp[d];
        }
    }

    // Now, let's sum up total_jumps based on current_component_pairs_1_jump and current_component_pairs_2_jumps.
    // These are pairs (s,t) where s, t are in the current component and the path goes through the centroid.
    // The centroid itself is also counted.
    // The pairs counted here are unordered. So when we add to total_jumps, we add the actual
    // sum of f(s,t) which is 1*count_1_jump + 2*count_2_jump.
    total_jumps += current_component_pairs_1_jump * 1;
    total_jumps += current_component_pairs_2_jumps * 2;


    // Step 4: Recursively call centroid_decompose for remaining components.
    for (int v : adj[centroid]) {
        if (!visited_centroid[v]) {
            centroid_decompose(v, centroid);
        }
    }
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> k;

    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    centroid_decompose(1, 0); // Start centroid decomposition from node 1 (arbitrary root)

    cout << total_jumps << endl;

    return 0;
}
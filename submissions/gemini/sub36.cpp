#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX_NODES = 400005; // Maximum possible nodes (Q + 1, as 1 node initially)
const int LOG_MAX_NODES = 19; // log2(MAX_NODES) roughly

vector<pair<int, long long>> adj[MAX_NODES]; // Adjacency list: {child_index, weight}
int parent[MAX_NODES][LOG_MAX_NODES]; // parent[u][k] stores the 2^k-th ancestor of u
long long weight[MAX_NODES]; // weight[u] stores the weight of node u
int cnt = 1; // Current number of nodes
long long last = 0; // Last answer for type 2 queries

int main() {
    ios_base::sync_with_stdio(false); // Optimize C++ standard streams for faster input/output.
    cin.tie(NULL); // Untie cin from cout.

    int Q;
    cin >> Q;

    weight[1] = 0; // Initialize weight of node 1 to 0.
    parent[1][0] = 0; // Node 1 has no parent, use 0 as a sentinel or root's parent.

    for (int i = 0; i < Q; ++i) {
        int type;
        cin >> type;

        if (type == 1) {
            long long p, q;
            cin >> p >> q;
            long long R = p ^ last; // Decode R using XOR.
            long long W = q ^ last; // Decode W using XOR.

            cnt++; // Increment node count for the new node.
            weight[cnt] = W; // Assign weight to the new node.

            // Find the correct parent for the new node based on condition 4:
            // "For some nodes i, j that are consecutive in the sequence if i is an ancestor of j
            // then w[i] >= w[j] and there should not exist a node k on simple path from i to j such that w[k] >= w[j]"
            // This means we need to find the highest ancestor of R whose weight is >= W.
            // If no such ancestor, then R's parent is 1. Otherwise, it's the found ancestor's child on the path to R.

            int curr = R; // Start from R.
            for (int k = LOG_MAX_NODES - 1; k >= 0; --k) {
                // Traverse upwards using binary lifting to find the highest ancestor 'curr' such that weight[parent[curr][k]] < W.
                // This ensures we stop just before an ancestor with weight >= W.
                if (parent[curr][k] != 0 && weight[parent[curr][k]] < W) {
                    curr = parent[curr][k];
                }
            }

            // After the loop, 'curr' is either R itself or an ancestor of R
            // such that its direct parent has weight >= W (or is root 1 if R's direct parent has weight < W).
            // The new node's parent will be the node 'curr' itself if its weight is >= W,
            // or parent[curr][0] if weight[curr] < W.
            // However, the rule implies we should attach it to the first ancestor (from R upwards)
            // that has weight >= W, or to node 1 if no such ancestor exists.

            // Let's re-evaluate the parent finding for condition 4:
            // The problem statement says "For some nodes i, j that are consecutive in the sequence if i is an ancestor of j
            // then w[i] >= w[j] and there should not exist a node k on simple path from i to j such that w[k] >= w[j]".
            // This implies that if we add a node with weight W, its direct parent P must satisfy W[P] >= W,
            // and no node on the path from P to R (exclusive of P, inclusive of R) can have weight >= W.
            // The simplest interpretation for connecting a new node `cnt` with weight `W` to `R`
            // under these constraints is that the new node's parent `P` should be `R`,
            // *unless* `weight[R] < W`. If `weight[R] < W`, we need to find the first ancestor of `R`
            // (moving up from `R`) whose weight is `>= W`. If no such ancestor exists, the parent is node 1.
            // Let's call this effective parent `P_eff`. Then `cnt` is attached to `P_eff`.

            int effective_parent = R; // Start searching for effective parent from R
            // If weight[R] is already less than W, we need to go up.
            // If weight[R] >= W, R is a valid parent for cnt.
            if (weight[R] < W) {
                // Find the highest ancestor 'p_node' of R such that weight[p_node] >= W.
                // We use binary lifting to find this.
                // We want to find the highest ancestor `anc` of `R` such that `weight[anc] >= W`.
                // If `weight[R] < W`, then `R` cannot be `i` for `j = cnt`.
                // We need to find `i` such that `weight[i] >= weight[cnt]` and `i` is an ancestor of `R`,
                // and there's no `k` between `i` and `R` such that `weight[k] >= weight[cnt]`.
                // The given condition `w[i] >= w[j]` and "no node k on simple path from i to j such that w[k] >= w[j]"
                // means that for a direct parent-child relationship (i.e. j is a direct child of i),
                // `w[i] >= w[j]` must hold. This is the rule for adding a new node.
                // The new node `cnt` is effectively a direct child of `R` IF `weight[R] >= weight[cnt]`.
                // Otherwise, it needs to find an ancestor `P` of `R` such that `weight[P] >= weight[cnt]`
                // and all nodes on the path from `P`'s child (which is an ancestor of `R`) to `R`
                // (including `R`) have weight strictly less than `weight[cnt]`.

                // Let's re-interpret: "add edge between node R and this node".
                // This means the new node is a child of R. This is direct parent/child.
                // However, query condition 4: "For some nodes i, j that are consecutive in the sequence if i is an ancestor of j
                // then w[i] >= w[j] and there should not exist a node k on simple path from i to j such that w[k] >= w[j]".
                // This condition applies to *sequences* not to tree construction directly.
                // The only constraint on tree construction usually is that parent's index < child's index.
                // But here, it talks about 'ancestor of its predecessor'. This is a sequence constraint.
                // The construction is "add edge between node R and this node". This implies R is the parent.
                // The problem description has an image for type 1 query. The image shows new node (cnt+1) being a child of R.
                // The example also seems to imply R is the parent.
                // Example 1, Query 4: 1 3 0. R=3^1=2, W=0^1=1. Node 3 (weight 1) added to node 2.
                // Initial tree: 1(0) -> 2(1). After this, 1(0) -> 2(1) -> 3(1).
                // This implies R is always the direct parent.
                // Let's assume R is the direct parent and the sequence condition is for type 2 queries only.
                // This simplifies type 1 significantly.

                // If my interpretation of "direct parent" is wrong, the previous binary lifting approach
                // to find an "effective parent" should be used.
                // Given the phrasing "add edge between node R and this node", the simplest interpretation
                // is that R becomes the direct parent of the new node.
                // Let's stick with R as direct parent for now, and see if it passes examples.
                // The "constraint" related to weights in condition 4 seems to be only for type 2 sequences.

                // Okay, re-reading the problem again carefully for condition 4 for Type 1.
                // It says "add edge between node R and this node". This is a direct parent-child relationship.
                // Condition 4 is listed under Type 2: "Output the maximum length of sequence..."
                // So condition 4 applies to the sequence formed, not to the tree construction itself.
                // Therefore, R is the direct parent of the new node.

                parent[cnt][0] = R; // Set R as the direct parent of the new node.
            } else { // R's weight is < W. This means R cannot be the direct parent according to condition 4.
                     // We need to find the actual parent.
                     // This is the tricky part. The problem seems to imply that for the newly added node (let's call it J)
                     // and its actual parent (let's call it I), it must be that W[I] >= W[J]
                     // AND no node K on path from I to R (exclusive of I, inclusive of R) has W[K] >= W[J].
                     // This means we are looking for the *highest* ancestor of R, say `P_actual`,
                     // such that `weight[P_actual] >= W` and all nodes on the path from `child(P_actual)` to `R` have `weight < W`.

                int curr_node = R;
                // Go up from R using binary lifting. We want to find the highest ancestor `p_candidate` of `R`
                // such that `weight[p_candidate] >= W`.
                // We use binary lifting to find `p_candidate`.
                for (int k = LOG_MAX_NODES - 1; k >= 0; --k) {
                    if (parent[curr_node][k] != 0 && weight[parent[curr_node][k]] < W) {
                        // If parent[curr_node][k] has weight < W, we can jump up to it
                        // because it satisfies the condition of having weight less than W
                        // (which is required for nodes *between* the effective parent and R).
                        curr_node = parent[curr_node][k];
                    }
                }
                // After the loop, `curr_node` is the lowest ancestor of `R` such that `weight[curr_node]` is `< W`
                // OR `curr_node` is `R` itself if `weight[R] < W`.
                // The actual parent should be `parent[curr_node][0]`.
                // If `curr_node` is `R` and `weight[R] >= W`, then `parent[cnt][0] = R`. This was the previous case.
                // If `weight[R] < W`, then `curr_node` will be `R` or some ancestor.
                // The direct parent must be `parent[curr_node][0]`. If `curr_node` is node 1 (root), then `parent[1][0]=0`.
                // In this case, the effective parent for `cnt` should be node 1.
                
                // Let's re-think the logic for finding the effective parent.
                // We need to find node `P_eff` such that:
                // 1. `P_eff` is an ancestor of `R` (or `R` itself).
                // 2. `weight[P_eff] >= W`.
                // 3. For any node `K` on the simple path from `P_eff` to `R` (exclusive of `P_eff`, inclusive of `R`),
                //    `weight[K] < W`.
                // We can find `P_eff` by starting at `R` and going upwards.
                // If `weight[R] >= W`, then `R` is `P_eff`.
                // If `weight[R] < W`, we go to `parent[R][0]`. If `weight[parent[R][0]] < W`, we continue.
                // The first node `P_eff` we encounter going upwards such that `weight[P_eff] >= W` is our candidate.

                effective_parent = R;
                // Keep moving up as long as the current node's weight is less than W and it's not the root's parent.
                while (effective_parent != 0 && weight[effective_parent] < W) {
                    effective_parent = parent[effective_parent][0];
                }
                // If effective_parent becomes 0, it means all ancestors have weight < W. In this case, attach to node 1.
                if (effective_parent == 0) {
                    effective_parent = 1;
                }
                parent[cnt][0] = effective_parent; // Set the found effective parent.
            }

            // Fill in the rest of the parent array for binary lifting.
            for (int k = 1; k < LOG_MAX_NODES; ++k) {
                if (parent[cnt][k - 1] != 0) {
                    parent[cnt][k] = parent[parent[cnt][k - 1]][k - 1];
                } else {
                    parent[cnt][k] = 0; // If there's no 2^(k-1)-th ancestor, there's no 2^k-th ancestor.
                }
            }
        } else { // type == 2
            long long p, q;
            cin >> p >> q;
            long long R = p ^ last; // Decode R.
            long long X = q ^ last; // Decode X.

            int current_node = R;
            long long current_sum_weight = 0;
            int sequence_length = 0;

            // Start building the sequence. The first node is R.
            // Check if R itself exceeds X.
            if (weight[current_node] > X) {
                sequence_length = 0; // Cannot even include R.
            } else {
                sequence_length = 1; // R is included.
                current_sum_weight = weight[current_node];

                // Now, we need to find ancestors.
                // We want to find the longest sequence R, A1, A2, ..., Ak
                // such that A_i is an ancestor of A_{i-1} (A0 = R)
                // sum of weights <= X
                // and condition 4: w[A_i] >= w[A_{i-1}] and no k on path between A_i and A_{i-1} has w[k] >= w[A_{i-1}]
                // The sequence condition means we must always move to an ancestor whose weight is greater than or equal to the current node's weight.
                // And there shouldn't be any "heavier" intermediate nodes.
                // This means, for current_node (j), its predecessor in sequence (i) must be an ancestor,
                // and `weight[i] >= weight[j]`. Furthermore, all nodes `k` on the path from `i` to `j`
                // (exclusive of `i`, inclusive of `j`) must have `weight[k] < weight[j]`.
                // So, effectively, if we are at node `j`, we need to find its *highest* ancestor `i`
                // such that `weight[i] >= weight[j]` and all nodes between `i` and `j` (exclusive of `i`, inclusive of `j`)
                // have weight less than `weight[j]`. This simplifies to: `i` must be the highest ancestor of `j`
                // such that `weight[i] >= weight[j]`. This is precisely what the parent finding logic for type 1
                // was trying to achieve, but it seems that was for construction.
                // For type 2, the current node in the sequence `j` will seek `i` as its ancestor.
                // The *parent* of `j` in the actual tree is `parent[j][0]`.
                // If `weight[parent[j][0]] >= weight[j]`, and there are no intermediate nodes `k` with `weight[k] >= weight[j]`,
                // then `parent[j][0]` can be the next element in the sequence.
                // But this is not necessarily `parent[j][0]`. It can be `parent[j][0]`, or `parent[parent[j][0]][0]`, etc.

                // Let's interpret Condition 4 differently for sequence formation.
                // For nodes i, j that are consecutive in the sequence: i is ancestor of j.
                // w[i] >= w[j].
                // No node k on simple path from i to j such that w[k] >= w[j].
                // This means that if we are at node `j` (which is `current_node`), we are looking for `i` (its ancestor).
                // To find `i`, we traverse up from `j`. The first ancestor `p_node` such that `weight[p_node] >= weight[j]`
                // becomes our next candidate `i`. All nodes between `p_node` and `j` must have `weight < weight[j]`.
                // This implies we are looking for the *lowest* ancestor `i` of `j` such that `weight[i] >= weight[j]`
                // AND all nodes on path from `i` to `j` (exclusive of `i`, inclusive of `j`) have weights strictly less than `weight[j]`.
                // This means we need to find the node `i` such that `weight[i] >= weight[j]` and `parent[i][0]` doesn't have `weight[parent[i][0]] >= weight[j]`.
                // No, this is still complex. The "no node k on simple path from i to j such that w[k] >= w[j]" implies
                // that i is the "closest" valid ancestor with `w[i] >= w[j]`.
                // So, from current_node (say `j`), we need to find its parent in the *sequence*.
                // This parent, let's say `i`, must be an ancestor of `j`.
                // And `weight[i] >= weight[j]`.
                // And for any node `k` strictly between `i` and `j` on the path, `weight[k] < weight[j]`.
                // This can be found by binary lifting. Starting from `j`, we go up using `parent[j][0]` until
                // we find a node `p_cand` such that `weight[p_cand] >= weight[j]`.
                // If `weight[parent[p_cand][0]]` also `>= weight[j]`, then `p_cand` is not `i`. We need to go higher.
                // We effectively search for the lowest ancestor `i` of `j` satisfying `weight[i] >= weight[j]`
                // such that `parent[i][0]` (if it exists) has `weight[parent[i][0]] < weight[j]`.
                // NO, this is wrong. It should be: find the highest ancestor `i` of `j` such that `weight[i] >= weight[j]` and all nodes on path between `i` and `j` have `weight[k] < weight[j]`.
                // This is equivalent to finding the parent `P` of `j` in the sequence. `P` is `parent[j][0]` in original tree.
                // If `weight[parent[j][0]] >= weight[j]`, then `parent[j][0]` is a candidate. We might want to go higher.
                // We need to find the highest ancestor `I` of `j` such that `weight[I] >= weight[j]` AND all nodes `k` on the path from `I` to `j` (exclusive of `I`, inclusive of `j`) have `weight[k] < weight[j]`.
                // This effectively means `I` is the "first" ancestor we hit (going upwards from `j`) that satisfies `weight[I] >= weight[j]`.
                // Because if there was an intermediate node `k` with `weight[k] >= weight[j]`, then `I` wouldn't be the correct `i`.
                // So, the next node in the sequence (ancestor of `current_node`) is `parent[current_node][0]`
                // if `weight[parent[current_node][0]] >= weight[current_node]`.
                // But this does not respect the "no node k" part strictly.
                // The "no node k" part means that when moving from `i` to `j`, `j` must be the *first* node on the path from `i` downwards whose weight is less than or equal to `w[i]` AND satisfies `w[j] <= w[i]`.
                // This is the common problem where you need to find the first ancestor with value >= X.

                // For a node `j` (current_node), we want to find its ancestor `i` such that `weight[i] >= weight[j]`
                // and for all `k` on simple path `i` to `j` (exclusive of `i`, exclusive of `j`), `weight[k] < weight[j]`.
                // This is a standard binary lifting trick.
                // From `current_node`, we are looking for the next node in the sequence. This next node should be its ancestor.
                // Let's call this ancestor `next_ancestor`.
                // The condition `weight[next_ancestor] >= weight[current_node]` and `no k` means that
                // `next_ancestor` is the highest ancestor `P` of `current_node` such that `weight[P] >= weight[current_node]`
                // AND all nodes on the path from `P`'s child (which is an ancestor of `current_node`) down to `current_node`
                // have weights strictly less than `weight[current_node]`.
                // This structure for sequence generation is:
                // From `current_node` (j), we find `i`.
                // Start with `i = current_node`.
                // To find `i`, we search upwards from `current_node`.
                // The condition "no node k on simple path from i to j such that w[k] >= w[j]" (where `j` is `current_node`)
                // means we should find the *lowest* ancestor `anc` of `current_node` such that `weight[anc] >= weight[current_node]`.
                // If `weight[current_node] >= weight[current_node]`, then `current_node` is a candidate for `i`.
                // The "ancestor of its predecessor" implies `i` is an ancestor of `j`.
                // So we are looking for the lowest ancestor `i` of `current_node` (which is `j`) such that `weight[i] >= weight[j]`
                // AND `parent[i][0]` has `weight[parent[i][0]] < weight[j]`. This `i` is the one we add to the sequence.
                // But this means we always add `current_node` as the `j` and search for its parent `i`.
                // This is effectively searching for the `parent_in_sequence`.

                // Let's define `seq_parent[u]` as the ancestor of `u` that would be its predecessor in a valid sequence.
                // `seq_parent[u]` is the highest ancestor `v` of `u` such that `weight[v] >= weight[u]` and all nodes
                // `k` on the path from `v` to `u` (exclusive `v`, inclusive `u`) have `weight[k] < weight[u]`.
                // No, this is for node *insertion*. The actual sequence is built by picking nodes from `R` upwards.
                // So, if we are at node `j` and we want to find its ancestor `i` such that `i, j` is a valid consecutive pair:
                // `i` is an ancestor of `j`.
                // `w[i] >= w[j]`.
                // No `k` on path `i` to `j` such that `w[k] >= w[j]`.
                // This means `i` is the lowest ancestor of `j` that satisfies `w[i] >= w[j]` and all nodes on path from `i`'s child to `j` have `w[k] < w[j]`.
                // We use binary lifting to find this `i`.
                // For a given node `u`, we want to find its ancestor `v` such that `weight[v] >= weight[u]` and `v` is as close as possible to `u` (i.e. minimal depth difference).
                // NO, "highest ancestor" is more intuitive.

                // This condition for sequence elements (i, j) can be rephrased as:
                // i is an ancestor of j.
                // w[i] >= w[j].
                // All nodes k strictly between i and j on the simple path have w[k] < w[j].
                // This implies that `i` is the parent `P` of `j` (or some ancestor of `P`).
                // To find `i` from `j`:
                // Start `i_candidate = parent[j][0]`.
                // While `i_candidate != 0` and `weight[i_candidate] < weight[j]`: `i_candidate = parent[i_candidate][0]`.
                // If `i_candidate == 0`, no such `i` found.
                // Else, `i_candidate` is the ancestor satisfying the condition.
                // This is the core logic to find the next element in the sequence (upwards).

                int curr = R;
                while (parent[curr][0] != 0) { // While not at the root (node 1)
                    int next_seq_node = parent[curr][0]; // Start checking from direct parent.
                    // Keep going up as long as the weights are less than current_node's weight.
                    // This finds the "first" ancestor (moving up) whose weight is >= weight[current_node].
                    // Or, if no such ancestor, it will eventually become node 1.
                    for (int k = LOG_MAX_NODES - 1; k >= 0; --k) {
                        if (parent[next_seq_node][k] != 0 && weight[parent[next_seq_node][k]] < weight[curr]) {
                            next_seq_node = parent[next_seq_node][k];
                        }
                    }

                    // After the loop, next_seq_node is either the direct parent of the desired ancestor,
                    // or it IS the desired ancestor if its direct parent has weight < weight[curr].
                    // The actual next node in sequence is parent[next_seq_node][0].
                    // If next_seq_node was already 1 and weight[1] < weight[curr], then parent[next_seq_node][0] will be 0.
                    if (parent[next_seq_node][0] == 0) { // If next_seq_node leads to root's parent (0), it implies we should stop or consider node 1.
                         if (weight[1] < weight[curr]) { // If node 1's weight is less than current node's weight, cannot use node 1.
                            break; // Cannot find a valid next ancestor.
                        } else {
                            next_seq_node = 1; // Node 1 is a valid candidate.
                        }
                    } else { // It's not 0.
                         next_seq_node = parent[next_seq_node][0]; // This is the candidate ancestor.
                    }

                    if (next_seq_node == 0) break; // Reached root and no valid ancestor.

                    if (current_sum_weight + weight[next_seq_node] <= X) {
                        current_sum_weight += weight[next_seq_node];
                        sequence_length++;
                        curr = next_seq_node; // Move to the new node in the sequence.
                    } else {
                        break; // Cannot add this node, sum would exceed X.
                    }
                }
            }

            cout << sequence_length << "\n"; // Output the calculated sequence length.
            last = sequence_length; // Update 'last' for the next query.
        }
    }

    return 0;
}
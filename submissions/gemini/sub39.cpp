#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include <limits>

// Define a large value for infinity, used for shortest path distances.
const long long INF = std::numeric_limits<long long>::max();

// Structure to represent an edge in the graph.
struct Edge {
    int to;         // Destination node of the edge.
    int capacity;   // Current capacity of the edge.
    int cost;       // Cost per unit of flow through this edge.
    int rev;        // Index of the reverse edge in the adjacency list of 'to' node.
};

// Adjacency list for the graph.
std::vector<std::vector<Edge>> adj;
// Stores the shortest path distance from the source to each node.
std::vector<long long> dist;
// Stores the index of the parent edge in the parent node's adjacency list to reconstruct the path.
std::vector<int> parent_edge;
// Stores the parent node in the shortest path tree.
std::vector<int> parent_node;
// Stores potentials for Dijkstra's algorithm. Potentials are updated after each shortest path
// to ensure reduced costs are non-negative, allowing Dijkstra to work with negative original costs.
std::vector<long long> potentials;
// Total number of nodes in the graph.
int N_NODES;

// Function to add an edge and its corresponding reverse (residual) edge to the graph.
void add_edge(int u, int v, int cap, int cost) {
    // Add forward edge from u to v.
    adj[u].push_back({v, cap, cost, (int)adj[v].size()});
    // Add reverse (residual) edge from v to u. Capacity is 0 initially, cost is negative of forward cost.
    adj[v].push_back({u, 0, -cost, (int)adj[u].size() - 1});
}

// SPFA (Shortest Path Faster Algorithm) to find the shortest path in a graph that might have negative edge weights.
// This is typically used for the first path in min-cost max-flow when initial costs can be negative.
bool spfa(int s, int t) {
    dist.assign(N_NODES, INF); // Initialize all distances to infinity.
    parent_node.assign(N_NODES, -1); // Initialize parent nodes to -1 (no parent).
    parent_edge.assign(N_NODES, -1); // Initialize parent edges to -1.
    std::vector<bool> in_queue(N_NODES, false); // Tracks if a node is currently in the queue.
    std::queue<int> q; // Queue for SPFA.

    dist[s] = 0; // Distance from source to itself is 0.
    q.push(s);
    in_queue[s] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        in_queue[u] = false; // Node u is no longer in the queue.

        // Iterate over all edges from node u.
        for (int i = 0; i < adj[u].size(); ++i) {
            Edge &e = adj[u][i];
            // If the edge has capacity and a shorter path to e.to is found through u.
            if (e.capacity > 0 && dist[e.to] > dist[u] + e.cost) {
                dist[e.to] = dist[u] + e.cost; // Update distance.
                parent_node[e.to] = u;         // Set parent node.
                parent_edge[e.to] = i;          // Set parent edge index.
                // If e.to is not in the queue, add it.
                if (!in_queue[e.to]) {
                    q.push(e.to);
                    in_queue[e.to] = true;
                }
            }
        }
    }
    return dist[t] != INF; // Return true if the sink is reachable from the source.
}

// Dijkstra's algorithm with potentials to find the shortest path.
// This is used for subsequent paths in min-cost max-flow after potentials have been updated,
// ensuring all reduced costs are non-negative.
bool dijkstra(int s, int t) {
    dist.assign(N_NODES, INF); // Initialize all distances to infinity.
    parent_node.assign(N_NODES, -1); // Initialize parent nodes.
    parent_edge.assign(N_NODES, -1); // Initialize parent edges.
    // Priority queue stores pairs of (distance, node), ordered by distance (min-heap).
    std::priority_queue<std::pair<long long, int>, std::vector<std::pair<long long, int>>, std::greater<std::pair<long long, int>>> pq;

    dist[s] = 0; // Distance from source to itself is 0.
    pq.push({0, s});

    while (!pq.empty()) {
        long long d = pq.top().first; // Current shortest distance to node u.
        int u = pq.top().second;      // Current node.
        pq.pop();

        // If we've already found a shorter path to u, skip this entry.
        if (d > dist[u]) continue;

        // Iterate over all edges from node u.
        for (int i = 0; i < adj[u].size(); ++i) {
            Edge &e = adj[u][i];
            // Calculate the reduced cost: original_cost + potential_u - potential_v.
            // This transformation makes all edge costs non-negative if potentials are correct.
            long long reduced_cost = e.cost + potentials[u] - potentials[e.to];
            // If the edge has capacity and a shorter path to e.to is found through u.
            if (e.capacity > 0 && dist[e.to] > dist[u] + reduced_cost) {
                dist[e.to] = dist[u] + reduced_cost; // Update distance.
                parent_node[e.to] = u;               // Set parent node.
                parent_edge[e.to] = i;                // Set parent edge index.
                pq.push({dist[e.to], e.to});         // Add to priority queue.
            }
        }
    }
    return dist[t] != INF; // Return true if the sink is reachable.
}

// Min-cost max-flow algorithm using successive shortest paths.
// Finds K_flow units of flow with minimum total cost.
long long min_cost_max_flow(int s, int t, int K_flow) {
    long long total_cost = 0; // Accumulates the total minimum cost.
    int total_flow = 0;       // Accumulates the total flow pushed.
    potentials.assign(N_NODES, 0); // Initialize potentials to 0.

    // Find the first path using SPFA because initial edge costs can be negative.
    if (!spfa(s, t)) {
        return 0; // If no path found initially, no melodies can be formed.
    }
    // Update potentials based on the distances found by SPFA.
    // This ensures reduced costs are non-negative for subsequent Dijkstra runs.
    for (int i = 0; i < N_NODES; ++i) {
        if (dist[i] != INF) {
            potentials[i] += dist[i];
        }
    }

    // Loop to find K_flow paths.
    for (int flow_count = 0; flow_count < K_flow; ++flow_count) {
        // For subsequent paths, use Dijkstra with potentials.
        if (!dijkstra(s, t)) {
            break; // No more paths can be found.
        }

        // Calculate the actual path cost using original costs.
        // The dist[t] from Dijkstra is a reduced cost, so we convert it back.
        long long path_cost = dist[t] - potentials[s] + potentials[t];
        int path_flow = 1; // Each path in this problem uses 1 unit of flow (capacity on node edges is 1).

        total_cost += path_cost; // Add path cost to total.
        total_flow += path_flow; // Increment total flow.

        // Augment flow along the found path by updating residual capacities.
        int curr = t;
        while (curr != s) {
            int prev = parent_node[curr];
            int edge_idx = parent_edge[curr];
            adj[prev][edge_idx].capacity -= path_flow; // Decrease forward capacity.
            adj[curr][adj[prev][edge_idx].rev].capacity += path_flow; // Increase reverse capacity.
            curr = prev;
        }

        // Update potentials for the next iteration of Dijkstra.
        // This is crucial for maintaining non-negative reduced costs.
        for (int i = 0; i < N_NODES; ++i) {
            if (dist[i] != INF) {
                potentials[i] += dist[i];
            }
        }
    }

    // The problem asks for two non-empty subsequences. If we couldn't find K_flow paths,
    // it means we cannot form two melodies. In this case, the answer is 0.
    if (total_flow < K_flow) {
        return 0;
    }
    
    return total_cost;
}

int main() {
    // Optimize C++ standard streams for faster input/output.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    std::cin >> n;

    std::vector<int> a(n);
    // Collect unique values from the input array for coordinate compression.
    std::vector<int> unique_a_vals;
    // Map to store the compressed index for each unique original value.
    std::map<int, int> val_to_idx; 

    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
        unique_a_vals.push_back(a[i]);
    }

    // Sort unique values and remove duplicates.
    std::sort(unique_a_vals.begin(), unique_a_vals.end());
    unique_a_vals.erase(std::unique(unique_a_vals.begin(), unique_a_vals.end()), unique_a_vals.end());

    // Populate the map for coordinate compression.
    for (int i = 0; i < unique_a_vals.size(); ++i) {
        val_to_idx[unique_a_vals[i]] = i;
    }

    // Define node indices for the flow network.
    int S = 0; // Source node.
    int T = 1; // Sink node.
    int current_node_idx = 2; // Start assigning node indices from 2.

    // Node indices for each a[i] in the input sequence.
    std::vector<int> node_in(n);  // Represents a[i] as a potential start of a melody segment.
    std::vector<int> node_out(n); // Represents a[i] as a potential end of a melody segment.
    for (int i = 0; i < n; ++i) {
        node_in[i] = current_node_idx++;
    }
    for (int i = 0; i < n; ++i) {
        node_out[i] = current_node_idx++;
    }

    // Node indices for value-based connections (using coordinate compressed indices).
    int N_unique = unique_a_vals.size(); // Number of unique values.
    std::vector<int> val_node_in(N_unique);  // Collects flow from nodes ending with a specific value.
    std::vector<int> val_node_out(N_unique); // Distributes flow to nodes starting with a specific value.
    for (int i = 0; i < N_unique; ++i) {
        val_node_in[i] = current_node_idx++;
    }
    for (int i = 0; i < N_unique; ++i) {
        val_node_out[i] = current_node_idx++;
    }

    // Node indices for modulo-based connections.
    std::vector<int> mod_node_in(7);  // Collects flow from nodes ending with a specific modulo.
    std::vector<int> mod_node_out(7); // Distributes flow to nodes starting with a specific modulo.
    for (int i = 0; i < 7; ++i) {
        mod_node_in[i] = current_node_idx++;
    }
    for (int i = 0; i < 7; ++i) {
        mod_node_out[i] = current_node_idx++;
    }

    N_NODES = current_node_idx; // Total number of nodes in the graph.
    adj.resize(N_NODES); // Resize the adjacency list to accommodate all nodes.

    // Add edges to the graph based on the min-cost max-flow model.

    // 1. Edges from Source to node_in[i]:
    //    Capacity 1, Cost 0. Allows each a[i] to be the start of a melody segment at most once.
    for (int i = 0; i < n; ++i) {
        add_edge(S, node_in[i], 1, 0);
    }

    // 2. Edges from node_out[i] to Sink:
    //    Capacity 1, Cost 0. Allows each a[i] to be the end of a melody segment at most once.
    for (int i = 0; i < n; ++i) {
        add_edge(node_out[i], T, 1, 0);
    }

    // 3. Edges from node_in[i] to node_out[i]:
    //    Capacity 1, Cost -1. Represents using a[i] in a melody, contributing 1 to length (cost -1).
    for (int i = 0; i < n; ++i) {
        add_edge(node_in[i], node_out[i], 1, -1);
    }

    // 4. Edges from node_out[j] to val_node_in[a[j]] (value-based collection):
    //    Capacity 1, Cost 0. Connects the end of a segment at a[j] to the value-specific collection node.
    for (int j = 0; j < n; ++j) {
        add_edge(node_out[j], val_node_in[val_to_idx[a[j]]], 1, 0);
    }

    // 5. Edges from node_out[j] to mod_node_in[a[j]%7] (modulo-based collection):
    //    Capacity 1, Cost 0. Connects the end of a segment at a[j] to the modulo-specific collection node.
    for (int j = 0; j < n; ++j) {
        add_edge(node_out[j], mod_node_in[a[j]%7], 1, 0);
    }

    // 6. Edges from val_node_in[idx] to val_node_out[idx] (value-based transition):
    //    Capacity 'n' (sufficiently large, as we only need 2 paths). Cost 0.
    //    Allows multiple melodies to pass through the same value connection point.
    for (int i = 0; i < N_unique; ++i) {
        add_edge(val_node_in[i], val_node_out[i], n, 0);
    }

    // 7. Edges from mod_node_in[mod] to mod_node_out[mod] (modulo-based transition):
    //    Capacity 'n'. Cost 0.
    //    Allows multiple melodies to pass through the same modulo connection point.
    for (int i = 0; i < 7; ++i) {
        add_edge(mod_node_in[i], mod_node_out[i], n, 0);
    }

    // 8. Edges from val_node_out[a[i]-1] to node_in[i] (melody connection for value-1):
    //    Capacity 1, Cost 0. Connects a value-specific distribution node to the start of a segment at a[i]
    //    if a[i]-1 is a valid predecessor (exists in unique_a_vals and >= 1).
    for (int i = 0; i < n; ++i) {
        if (a[i] - 1 >= 1 && val_to_idx.count(a[i] - 1)) {
            add_edge(val_node_out[val_to_idx[a[i] - 1]], node_in[i], 1, 0);
        }
    }

    // 9. Edges from val_node_out[a[i]+1] to node_in[i] (melody connection for value+1):
    //    Capacity 1, Cost 0. Connects a value-specific distribution node to the start of a segment at a[i]
    //    if a[i]+1 is a valid predecessor (exists in unique_a_vals and <= MAX_A_VAL).
    const int MAX_A_VAL = 100000; // Maximum possible value for a_i.
    for (int i = 0; i < n; ++i) {
        if (a[i] + 1 <= MAX_A_VAL && val_to_idx.count(a[i] + 1)) {
            add_edge(val_node_out[val_to_idx[a[i] + 1]], node_in[i], 1, 0);
        }
    }

    // 10. Edges from mod_node_out[a[i]%7] to node_in[i] (melody connection for same modulo):
    //     Capacity 1, Cost 0. Connects a modulo-specific distribution node to the start of a segment at a[i]
    //     if a[i]%7 is a valid predecessor modulo.
    for (int i = 0; i < n; ++i) {
        add_edge(mod_node_out[a[i]%7], node_in[i], 1, 0);
    }

    // Calculate the minimum cost for 2 units of flow.
    long long min_cost = min_cost_max_flow(S, T, 2);

    // The total length is the negative of the total cost, because we assigned a cost of -1 for each unit of length.
    // If min_cost_max_flow returns 0, it means it couldn't find 2 paths, so the answer is 0.
    std::cout << -min_cost << std::endl;

    return 0;
}

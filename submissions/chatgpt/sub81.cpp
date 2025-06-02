#include <bits/stdc++.h>
using namespace std;

// n: number of guests, m: number of initial friendships
int n, m;

// adj[i]: bitmask of friends of guest i (0-based)
int adj[22];

// dp[1<<n]: minimum steps to reach each friendship state
int dp[1<<22];

// prev_state[1<<n]: previous state for reconstructing the path
int prev_state[1<<22];

// who[1<<n]: which guest was chosen to reach this state
int who[1<<22];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;
    // Initialize adjacency masks
    for (int i = 0; i < n; ++i) adj[i] = 0;
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v; // 0-based
        adj[u] |= (1 << v);
        adj[v] |= (1 << u);
    }

    // The friendship state is represented as a bitmask of all pairs (i, j) with i < j
    // Since n <= 22, there are at most 231 pairs (n*(n-1)/2)
    // We'll encode the friendship state as a bitmask of all pairs (i, j) with i < j
    // For each pair (i, j), assign it an index in [0, n*(n-1)/2)
    int pair_idx[22][22], idx = 0;
    for (int i = 0; i < n; ++i)
        for (int j = i+1; j < n; ++j)
            pair_idx[i][j] = idx++;

    int total_pairs = idx;
    // friendship_mask: bitmask of all current friendships
    // friendship_mask has total_pairs bits
    // We'll use uint64_t for up to 64 pairs, but for n=22, we need up to 231 bits
    // So we use vector<uint64_t> to represent the bitmask

    // Helper to convert adjacency to friendship mask
    auto get_mask = [&](int adj[]) {
        vector<uint64_t> mask((total_pairs+63)/64, 0);
        for (int i = 0; i < n; ++i) {
            for (int j = i+1; j < n; ++j) {
                if (adj[i] & (1<<j)) {
                    int k = pair_idx[i][j];
                    mask[k/64] |= (1ULL << (k%64));
                }
            }
        }
        return mask;
    };

    // Helper to set a pair in a mask
    auto set_pair = [&](vector<uint64_t> &mask, int i, int j) {
        if (i > j) swap(i, j);
        int k = pair_idx[i][j];
        mask[k/64] |= (1ULL << (k%64));
    };

    // Helper to check if mask is complete (all pairs are friends)
    auto is_complete = [&](const vector<uint64_t> &mask) {
        for (int i = 0; i < (int)mask.size(); ++i) {
            if (i < (int)mask.size()-1) {
                if (mask[i] != ~0ULL) return false;
            } else {
                int rem = total_pairs - 64*i;
                if (rem < 64) {
                    if (mask[i] != ((1ULL<<rem)-1)) return false;
                } else {
                    if (mask[i] != ~0ULL) return false;
                }
            }
        }
        return true;
    };

    // Initial friendship mask
    vector<uint64_t> start_mask = get_mask(adj);

    // BFS: state is friendship mask, store in map for visited
    unordered_map<string, int> dist;
    unordered_map<string, pair<string, int>> parent; // mask_str -> (prev_mask_str, guest)
    queue<vector<uint64_t>> q;

    // Helper to convert mask to string for map key
    auto mask_to_str = [](const vector<uint64_t> &mask) {
        string s;
        for (uint64_t x : mask) {
            for (int i = 0; i < 8; ++i) {
                s += char((x >> (i*8)) & 0xFF);
            }
        }
        return s;
    };

    string start_str = mask_to_str(start_mask);
    dist[start_str] = 0;
    q.push(start_mask);

    // BFS
    while (!q.empty()) {
        auto mask = q.front(); q.pop();
        string mask_str = mask_to_str(mask);
        int d = dist[mask_str];

        // If complete, reconstruct path
        if (is_complete(mask)) {
            vector<int> steps;
            string cur = mask_str;
            while (parent.count(cur)) {
                steps.push_back(parent[cur].second+1); // 1-based
                cur = parent[cur].first;
            }
            reverse(steps.begin(), steps.end());
            cout << steps.size() << '\n';
            for (int i = 0; i < (int)steps.size(); ++i) {
                cout << steps[i] << (i+1==(int)steps.size() ? '\n' : ' ');
            }
            return 0;
        }

        // Try all guests as the next "introducer"
        for (int g = 0; g < n; ++g) {
            // Find all friends of g
            vector<int> friends;
            for (int j = 0; j < n; ++j) {
                if (g != j) {
                    // Check if g and j are friends in current mask
                    int i1 = min(g, j), i2 = max(g, j);
                    int k = pair_idx[i1][i2];
                    if (mask[k/64] & (1ULL << (k%64))) {
                        friends.push_back(j);
                    }
                }
            }
            if ((int)friends.size() < 2) continue; // No new pairs can be introduced

            // Create new mask: all friends of g become friends with each other
            vector<uint64_t> new_mask = mask;
            for (int i = 0; i < (int)friends.size(); ++i) {
                for (int j = i+1; j < (int)friends.size(); ++j) {
                    set_pair(new_mask, friends[i], friends[j]);
                }
            }
            string new_str = mask_to_str(new_mask);
            if (!dist.count(new_str) || dist[new_str] > d+1) {
                dist[new_str] = d+1;
                parent[new_str] = {mask_str, g};
                q.push(new_mask);
            }
        }
    }
    // Should never reach here due to problem guarantee
    return 0;
}
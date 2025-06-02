#include <iostream>
#include <vector>
using namespace std;

// n: number of vertices, k: max jump distance
int n, k;
vector<vector<int>> tree;

// The answer to accumulate
long long answer = 0;

// For each node, we keep a vector<int> cnt of size k,
// where cnt[d] is the number of nodes in the subtree at distance d from the current node.
// cnt[0] is always 1 (the node itself).
vector<int> dfs(int v, int parent) {
    // cnt[d]: number of nodes in subtree rooted at v at distance d from v
    vector<int> cnt(k, 0);
    cnt[0] = 1; // itself

    for (int u : tree[v]) {
        if (u == parent) continue;
        vector<int> child_cnt = dfs(u, v);

        // For all pairs (a, b) where a is in v's subtree (excluding u's subtree),
        // and b is in u's subtree, and a < b, we want to count the number of pairs
        // whose distance is d1 + d2 + 1 (the +1 is the edge between v and u).
        // For each d1 in [0, k-1], d2 in [0, k-1], if d1 + d2 + 1 <= k-1,
        // then they can be reached in one jump, else need more jumps.

        // For all pairs (d1, d2), count how many pairs are at distance d1+d2+1
        for (int d1 = 0; d1 < k; ++d1) {
            for (int d2 = 0; d2 < k; ++d2) {
                int dist = d1 + d2 + 1;
                // The minimal number of jumps needed is (dist + k - 1) / k
                int jumps = (dist + k - 1) / k;
                answer += 1LL * cnt[d1] * child_cnt[d2] * jumps;
            }
        }

        // Now, merge child_cnt into cnt, increasing all distances by 1
        for (int d = 0; d < k - 1; ++d) {
            cnt[d + 1] += child_cnt[d];
        }
    }
    return cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    tree.resize(n);

    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b; // 0-based indexing
        tree[a].push_back(b);
        tree[b].push_back(a);
    }

    dfs(0, -1);

    // Each pair (s, t) is counted exactly once in the dfs
    cout << answer << '\n';
    return 0;
}
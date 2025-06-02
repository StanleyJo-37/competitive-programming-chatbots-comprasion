#include <bits/stdc++.h>
using namespace std;

// Maximum number of nodes (Q + 2 for safety)
const int MAXN = 400005;
// Maximum bits for binary lifting (log2(MAXN) ~ 19, but for weights up to 1e9, we need up to 60 for safety)
const int LOG = 60;

// parent[i][j]: 2^j-th ancestor of node i
// maxw[i][j]: maximum weight on path from i to its 2^j-th ancestor (excluding i itself)
// sumw[i][j]: sum of weights on path from i to its 2^j-th ancestor (including i itself)
int parent[MAXN][LOG];
long long maxw[MAXN][LOG];
long long sumw[MAXN][LOG];
long long w[MAXN]; // weight of each node

// For each node, we also need to store the "special parent" for the sequence
// special_parent[i][j]: 2^j-th special parent of node i (where special parent is the first ancestor with weight >= w[i])
int special_parent[MAXN][LOG];
long long special_sumw[MAXN][LOG]; // sum of weights along special parent jumps

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int Q;
    cin >> Q;

    // Node 1 is root, weight 0
    int cnt = 1;
    w[1] = 0;
    for (int j = 0; j < LOG; ++j) {
        parent[1][j] = 0;
        maxw[1][j] = 0;
        sumw[1][j] = 0;
        special_parent[1][j] = 0;
        special_sumw[1][j] = 0;
    }

    long long last = 0;

    for (int q = 0; q < Q; ++q) {
        int type;
        long long p, qv;
        cin >> type >> p >> qv;

        // Compute R and W/X using XOR with last
        long long R = p ^ last;
        long long val = qv ^ last;

        if (type == 1) {
            // Add node
            ++cnt;
            w[cnt] = val;

            // Set parent[cnt][0] = R
            parent[cnt][0] = R;
            maxw[cnt][0] = w[R];
            sumw[cnt][0] = w[R];
            // Fill binary lifting for parent and maxw, sumw
            for (int j = 1; j < LOG; ++j) {
                int mid = parent[cnt][j-1];
                if (mid == 0) {
                    parent[cnt][j] = 0;
                    maxw[cnt][j] = maxw[cnt][j-1];
                    sumw[cnt][j] = sumw[cnt][j-1];
                } else {
                    parent[cnt][j] = parent[mid][j-1];
                    maxw[cnt][j] = max(maxw[cnt][j-1], maxw[mid][j-1]);
                    sumw[cnt][j] = sumw[cnt][j-1] + sumw[mid][j-1];
                }
            }

            // Find the "special parent" for cnt
            // The special parent is the first ancestor of cnt (including R) whose weight >= w[cnt]
            int cur = R;
            if (w[cur] >= w[cnt]) {
                special_parent[cnt][0] = cur;
                special_sumw[cnt][0] = w[cur];
            } else {
                // Binary lift up to find the first ancestor with weight >= w[cnt]
                for (int j = LOG-1; j >= 0; --j) {
                    if (parent[cur][j] && maxw[cur][j] < w[cnt]) {
                        cur = parent[cur][j];
                    }
                }
                // Now, cur is the highest ancestor whose all ancestors up to cur have weight < w[cnt]
                // So, parent[cur][0] is the first ancestor with weight >= w[cnt] (or 0 if none)
                special_parent[cnt][0] = parent[cur][0];
                special_sumw[cnt][0] = w[parent[cur][0]];
            }
            // Fill binary lifting for special parent
            for (int j = 1; j < LOG; ++j) {
                int mid = special_parent[cnt][j-1];
                if (mid == 0) {
                    special_parent[cnt][j] = 0;
                    special_sumw[cnt][j] = special_sumw[cnt][j-1];
                } else {
                    special_parent[cnt][j] = special_parent[mid][j-1];
                    special_sumw[cnt][j] = special_sumw[cnt][j-1] + special_sumw[mid][j-1];
                }
            }
        } else {
            // Query: Output the maximum length of sequence starting at R, sum of weights <= val
            // The sequence must go up via special parents, and sum of weights <= val
            int u = R;
            long long X = val;
            if (w[u] > X) {
                // Can't even take the starting node
                cout << 0 << '\n';
                last = 0;
                continue;
            }
            long long sum = w[u];
            int ans = 1;
            int cur = u;
            for (int j = LOG-1; j >= 0; --j) {
                int sp = special_parent[cur][j];
                if (sp == 0) continue;
                if (sum + special_sumw[cur][j] <= X) {
                    sum += special_sumw[cur][j];
                    ans += (1 << j);
                    cur = sp;
                }
            }
            cout << ans << '\n';
            last = ans;
        }
    }
    return 0;
}
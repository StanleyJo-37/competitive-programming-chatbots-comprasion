#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;
const int MAXK = 6;

vector<int> adj[MAXN];
long long dp[MAXN][MAXK]; // dp[u][d] = number of nodes at distance d from u in subtree rooted at u
long long sum[MAXN];       // sum[u] = total sum of f(s, t) for pairs within subtree of u
int n, k;
long long total = 0;

void dfs(int u, int parent) {
    dp[u][0] = 1; // The node itself is at distance 0
    for (int v : adj[u]) {
        if (v == parent) continue;
        dfs(v, u);
        
        // Update the sum for pairs (s, t) where s is in v's subtree and t is in u's other subtrees
        for (int d1 = 0; d1 <= k; ++d1) {
            for (int d2 = 0; d2 <= k; ++d2) {
                if (d1 + d2 + 1 <= k) continue; // These pairs can be covered in one jump
                // Each such pair requires an extra jump
                total += dp[v][d1] * dp[u][d2];
            }
        }
        
        // Update dp[u][d] with nodes from v's subtree
        for (int d = 0; d < k; ++d) {
            dp[u][d + 1] += dp[v][d];
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n >> k;
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    
    dfs(1, -1);
    
    // The total sum is the initial total (pairs needing extra jumps) plus all pairs (n choose 2)
    // minus the pairs that can be covered in one jump (which is sum of dp[u][d] for d <= k)
    // But the initial approach counts the extra jumps, so we need to add the total number of pairs
    // and subtract the pairs that can be covered in one jump (since they contribute 1 instead of 0 extra jumps)
    // So total = (n choose 2) + total (extra jumps)
    // But the initial total already counts the extra jumps, so the answer is total + (n choose 2)
    // But the initial total counts the number of pairs needing extra jumps, so the answer is (n choose 2) + total
    // Because each pair (s, t) contributes ceil(d(s, t) / (k + 1)) - 1 extra jumps
    // So total is sum over all pairs (s, t) of (ceil(d(s, t) / (k + 1)) - 1)
    // But the problem asks for sum of f(s, t) = ceil(d(s, t) / (k + 1))
    // So the answer is total + (n choose 2)
    cout << total + n * (n - 1LL) / 2 << endl;
    
    return 0;
}
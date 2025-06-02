#include <bits/stdc++.h>
using namespace std;

const int MOD = 1'000'000'007;

// DSU (Disjoint Set Union) structure for finding connected components
struct DSU {
    vector<int> parent, rank;
    DSU(int n) : parent(n), rank(n, 0) {
        for(int i=0; i<n; ++i) parent[i] = i;
    }
    int find(int x) {
        if(parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }
    void unite(int x, int y) {
        x = find(x), y = find(y);
        if(x == y) return;
        if(rank[x] < rank[y]) swap(x, y);
        parent[y] = x;
        if(rank[x] == rank[y]) ++rank[x];
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        vector<int> a(n), b(n), d(n);
        for(int i=0; i<n; ++i) cin >> a[i];
        for(int i=0; i<n; ++i) cin >> b[i];
        for(int i=0; i<n; ++i) cin >> d[i];

        // Map value to index for quick lookup
        vector<int> pos_a(n+1), pos_b(n+1);
        for(int i=0; i<n; ++i) {
            pos_a[a[i]] = i;
            pos_b[b[i]] = i;
        }

        // DSU to group positions that are "linked" by a_i and b_i
        DSU dsu(n);
        for(int i=0; i<n; ++i) {
            if(a[i] != b[i]) dsu.unite(i, pos_b[a[i]]);
        }

        // For each component, check if it is "forced" (i.e., at least one d[i] != 0)
        vector<bool> forced(n, false);
        for(int i=0; i<n; ++i) {
            if(d[i] != 0) {
                forced[dsu.find(i)] = true;
            }
        }

        // For each component, if not forced, it can be chosen in 2 ways (swap or not)
        long long ans = 1;
        vector<bool> counted(n, false);
        for(int i=0; i<n; ++i) {
            int root = dsu.find(i);
            if(!counted[root]) {
                counted[root] = true;
                if(!forced[root]) {
                    ans = (ans * 2) % MOD;
                }
            }
        }
        cout << ans << '\n';
    }
    return 0;
}
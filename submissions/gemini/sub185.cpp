#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MOD = 998244353;

struct SegTreeNode {
    long long val;
    long long lazy;
};

vector<SegTreeNode> tree;
int N_seg;

void build(int node, int start, int end) {
    tree[node].val = 0;
    tree[node].lazy = 0;
    if (start == end) {
        return;
    }
    int mid = (start + end) / 2;
    build(2 * node, start, mid);
    build(2 * node + 1, mid + 1, end);
}

void push(int node, int start, int end) {
    if (tree[node].lazy != 0) {
        tree[node].val = (tree[node].val + tree[node].lazy * (end - start + 1)) % MOD;
        if (start != end) {
            tree[2 * node].lazy = (tree[2 * node].lazy + tree[node].lazy) % MOD;
            tree[2 * node + 1].lazy = (tree[2 * node + 1].lazy + tree[node].lazy) % MOD;
        }
        tree[node].lazy = 0;
    }
}

void update_range(int node, int start, int end, int l, int r, long long val) {
    push(node, start, end);
    if (start > end || start > r || end < l) {
        return;
    }
    if (l <= start && end <= r) {
        tree[node].lazy = (tree[node].lazy + val) % MOD;
        push(node, start, end);
        return;
    }
    int mid = (start + end) / 2;
    update_range(2 * node, start, mid, l, r, val);
    update_range(2 * node + 1, mid + 1, end, l, r, val);
    tree[node].val = (tree[2 * node].val + tree[2 * node + 1].val) % MOD;
}

long long query_range(int node, int start, int end, int l, int r) {
    push(node, start, end);
    if (start > end || start > r || end < l) {
        return 0;
    }
    if (l <= start && end <= r) {
        return tree[node].val;
    }
    int mid = (start + end) / 2;
    long long p1 = query_range(2 * node, start, mid, l, r);
    long long p2 = query_range(2 * node + 1, mid + 1, end, l, r);
    return (p1 + p2) % MOD;
}

void solve() {
    int N;
    cin >> N;
    vector<int> A(2 * N);
    vector<vector<int>> positions(N + 1);
    for (int i = 0; i < 2 * N; ++i) {
        cin >> A[i];
        positions[A[i]].push_back(i);
    }

    N_seg = 2 * N;
    tree.assign(4 * N_seg, {0, 0});
    build(1, 0, N_seg - 1);

    long long total_good_pairs = 0;

    for (int i = 0; i < N; ++i) {
        int u = positions[A[i]][0];
        int v = positions[A[i]][1];
        if (u != i) { // A[i] is the second occurrence of A[i]
            // This case should not happen based on problem constraints (all numbers from 1 to N appear twice)
            // but for safety, ensure u < v
            swap(u, v); 
        }

        long long current_val = (query_range(1, 0, N_seg - 1, 0, i - 1) + 1) % MOD;
        total_good_pairs = (total_good_pairs + current_val) % MOD;

        update_range(1, 0, N_seg - 1, v, N_seg - 1, current_val);
        update_range(1, 0, N_seg - 1, u, u, (-current_val + MOD) % MOD); // "remove" dp[u] contribution for future
    }

    cout << total_good_pairs << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin >> T;
    while (T--) {
        solve();
    }

    return 0;
}
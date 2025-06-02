#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
using namespace std;

// We use a dynamic segment tree with lazy propagation to handle the huge range [0, n] efficiently.
// Each defense system is tracked by its current interval, so we can move it efficiently.

struct Node {
    int l, r;
    Node *left, *right;
    int64_t sum, lazy;
    Node(int l, int r): l(l), r(r), left(nullptr), right(nullptr), sum(0), lazy(0) {}
};

class DynamicSegmentTree {
public:
    Node* root;
    int n;
    DynamicSegmentTree(int n): n(n) {
        root = new Node(0, n);
    }
    // Pushes lazy updates to children
    void push(Node* node) {
        if (node->l == node->r || node->lazy == 0) return;
        int m = (node->l + node->r) / 2;
        if (!node->left) node->left = new Node(node->l, m);
        if (!node->right) node->right = new Node(m+1, node->r);
        node->left->sum += (m - node->l + 1) * node->lazy;
        node->left->lazy += node->lazy;
        node->right->sum += (node->r - m) * node->lazy;
        node->right->lazy += node->lazy;
        node->lazy = 0;
    }
    // Range add: add val to [l, r]
    void add(Node* node, int l, int r, int val) {
        if (!node || l > node->r || r < node->l) return;
        if (l <= node->l && node->r <= r) {
            node->sum += (node->r - node->l + 1) * val;
            node->lazy += val;
            return;
        }
        push(node);
        int m = (node->l + node->r) / 2;
        if (!node->left) node->left = new Node(node->l, m);
        if (!node->right) node->right = new Node(m+1, node->r);
        add(node->left, l, r, val);
        add(node->right, l, r, val);
        node->sum = (node->left ? node->left->sum : 0) + (node->right ? node->right->sum : 0);
    }
    // Point query: get value at pos
    int64_t query(Node* node, int pos) {
        if (!node || pos < node->l || pos > node->r) return 0;
        if (node->l == node->r) return node->sum;
        push(node);
        int m = (node->l + node->r) / 2;
        if (pos <= m) return query(node->left, pos);
        else return query(node->right, pos);
    }
    // Public interface
    void add(int l, int r, int val) { add(root, l, r, val); }
    int64_t query(int pos) { return query(root, pos); }
};

struct Interval {
    int l, r;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    DynamicSegmentTree seg(n);

    // Store intervals for each system, 1-based index
    vector<Interval> systems(1); // systems[0] unused

    for (int op = 0; op < m; ++op) {
        string cmd;
        cin >> cmd;
        if (cmd == "P") {
            int u, v;
            cin >> u >> v;
            systems.push_back({u, v});
            seg.add(u, v, 1);
        } else if (cmd == "M") {
            int i, d;
            cin >> i >> d;
            // Remove old interval
            seg.add(systems[i].l, systems[i].r, -1);
            // Move interval
            int new_l = systems[i].l + d;
            int new_r = systems[i].r + d;
            // Clamp to [0, n]
            new_l = max(0, new_l);
            new_r = min(n, new_r);
            if (new_l > new_r) new_l = new_r; // If interval is invalid, make it empty
            systems[i] = {new_l, new_r};
            seg.add(new_l, new_r, 1);
        } else if (cmd == "B") {
            int x;
            cin >> x;
            cout << seg.query(x) << '\n';
        }
    }
    return 0;
}
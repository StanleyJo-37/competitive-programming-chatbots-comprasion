#include <bits/stdc++.h>
using namespace std;

const int MAX_BITS = 20;
const int MAX_VAL = 1 << MAX_BITS;

struct Node {
    int cnt;
    int lazy_and, lazy_or, lazy_xor;
    Node() : cnt(0), lazy_and((1 << MAX_BITS) - 1), lazy_or(0), lazy_xor(0) {}
};

vector<Node> seg(4 * MAX_VAL);

void apply_and(int node, int val) {
    seg[node].lazy_and &= val;
    seg[node].lazy_or &= val;
    seg[node].lazy_xor &= val;
}

void apply_or(int node, int val) {
    seg[node].lazy_or |= val;
    seg[node].lazy_xor &= ~val;
}

void apply_xor(int node, int val) {
    seg[node].lazy_xor ^= val;
}

void push(int node, int l, int r) {
    if (l == r) {
        int val = l;
        val &= seg[node].lazy_and;
        val |= seg[node].lazy_or;
        val ^= seg[node].lazy_xor;
        seg[node].cnt = (val == l) ? seg[node].cnt : 0;
        seg[node].lazy_and = (1 << MAX_BITS) - 1;
        seg[node].lazy_or = 0;
        seg[node].lazy_xor = 0;
        return;
    }
    int mid = (l + r) / 2;
    apply_and(2 * node, seg[node].lazy_and);
    apply_and(2 * node + 1, seg[node].lazy_and);
    apply_or(2 * node, seg[node].lazy_or);
    apply_or(2 * node + 1, seg[node].lazy_or);
    apply_xor(2 * node, seg[node].lazy_xor);
    apply_xor(2 * node + 1, seg[node].lazy_xor);
    seg[node].lazy_and = (1 << MAX_BITS) - 1;
    seg[node].lazy_or = 0;
    seg[node].lazy_xor = 0;
}

void update_cnt(int node, int l, int r, int pos, int delta) {
    if (l == r) {
        seg[node].cnt += delta;
        return;
    }
    push(node, l, r);
    int mid = (l + r) / 2;
    if (pos <= mid) update_cnt(2 * node, l, mid, pos, delta);
    else update_cnt(2 * node + 1, mid + 1, r, pos, delta);
    seg[node].cnt = seg[2 * node].cnt + seg[2 * node + 1].cnt;
}

void update_and(int node, int l, int r, int ql, int qr, int val) {
    if (qr < l || ql > r) return;
    if (ql <= l && r <= qr) {
        apply_and(node, val);
        return;
    }
    push(node, l, r);
    int mid = (l + r) / 2;
    update_and(2 * node, l, mid, ql, qr, val);
    update_and(2 * node + 1, mid + 1, r, ql, qr, val);
}

void update_or(int node, int l, int r, int ql, int qr, int val) {
    if (qr < l || ql > r) return;
    if (ql <= l && r <= qr) {
        apply_or(node, val);
        return;
    }
    push(node, l, r);
    int mid = (l + r) / 2;
    update_or(2 * node, l, mid, ql, qr, val);
    update_or(2 * node + 1, mid + 1, r, ql, qr, val);
}

void update_xor(int node, int l, int r, int ql, int qr, int val) {
    if (qr < l || ql > r) return;
    if (ql <= l && r <= qr) {
        apply_xor(node, val);
        return;
    }
    push(node, l, r);
    int mid = (l + r) / 2;
    update_xor(2 * node, l, mid, ql, qr, val);
    update_xor(2 * node + 1, mid + 1, r, ql, qr, val);
}

int query_distinct(int node, int l, int r, int ql, int qr) {
    if (qr < l || ql > r) return 0;
    push(node, l, r);
    if (ql <= l && r <= qr) return seg[node].cnt;
    int mid = (l + r) / 2;
    return query_distinct(2 * node, l, mid, ql, qr) + 
           query_distinct(2 * node + 1, mid + 1, r, ql, qr);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        update_cnt(1, 0, MAX_VAL - 1, a[i], 1);
    }

    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int l, r, x;
            cin >> l >> r >> x;
            update_and(1, 0, MAX_VAL - 1, l, r, x);
        } else if (t == 2) {
            int l, r, x;
            cin >> l >> r >> x;
            update_or(1, 0, MAX_VAL - 1, l, r, x);
        } else if (t == 3) {
            int l, r, x;
            cin >> l >> r >> x;
            update_xor(1, 0, MAX_VAL - 1, l, r, x);
        } else if (t == 4) {
            int l, r;
            cin >> l >> r;
            cout << query_distinct(1, 0, MAX_VAL - 1, l, r) << '\n';
        }
    }

    return 0;
}
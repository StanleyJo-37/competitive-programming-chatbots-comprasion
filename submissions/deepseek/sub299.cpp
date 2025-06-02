#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;
const int MAX_A = 2e5 + 5;

vector<int> spf; // Smallest Prime Factor

void sieve() {
    spf.resize(MAX_A);
    iota(spf.begin(), spf.end(), 0);
    for (int i = 2; i * i < MAX_A; ++i) {
        if (spf[i] == i) {
            for (int j = i * i; j < MAX_A; j += i) {
                if (spf[j] == j) {
                    spf[j] = i;
                }
            }
        }
    }
}

vector<pair<int, int>> factorize(int x) {
    vector<pair<int, int>> factors;
    while (x > 1) {
        int p = spf[x];
        int cnt = 0;
        while (x % p == 0) {
            x /= p;
            cnt++;
        }
        factors.emplace_back(p, cnt);
    }
    return factors;
}

struct SegmentTree {
    int n;
    vector<map<int, int>> tree;

    SegmentTree(const vector<int>& arr) {
        n = arr.size();
        tree.resize(4 * n);
        build(1, 0, n - 1, arr);
    }

    void build(int node, int l, int r, const vector<int>& arr) {
        if (l == r) {
            int val = arr[l];
            auto factors = factorize(val);
            for (auto [p, cnt] : factors) {
                tree[node][p] = cnt;
            }
            return;
        }
        int mid = (l + r) / 2;
        build(2 * node, l, mid, arr);
        build(2 * node + 1, mid + 1, r, arr);
        merge(node);
    }

    void merge(int node) {
        tree[node].clear();
        for (auto [p, cnt] : tree[2 * node]) {
            tree[node][p] = cnt;
        }
        for (auto [p, cnt] : tree[2 * node + 1]) {
            tree[node][p] = max(tree[node][p], cnt);
        }
    }

    map<int, int> query(int node, int l, int r, int ql, int qr) {
        if (qr < l || ql > r) {
            return {};
        }
        if (ql <= l && r <= qr) {
            return tree[node];
        }
        int mid = (l + r) / 2;
        auto left = query(2 * node, l, mid, ql, qr);
        auto right = query(2 * node + 1, mid + 1, r, ql, qr);
        map<int, int> res;
        for (auto [p, cnt] : left) {
            res[p] = cnt;
        }
        for (auto [p, cnt] : right) {
            res[p] = max(res[p], cnt);
        }
        return res;
    }

    int getLCM(int l, int r) {
        auto factors = query(1, 0, n - 1, l, r);
        long long res = 1;
        for (auto [p, cnt] : factors) {
            for (int i = 0; i < cnt; ++i) {
                res = (res * p) % MOD;
            }
        }
        return res;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    sieve();

    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    SegmentTree st(a);

    int q;
    cin >> q;
    int last = 0;
    while (q--) {
        int x, y;
        cin >> x >> y;
        int l = (last + x) % n;
        int r = (last + y) % n;
        if (l > r) {
            swap(l, r);
        }
        last = st.getLCM(l, r);
        cout << last << '\n';
    }

    return 0;
}
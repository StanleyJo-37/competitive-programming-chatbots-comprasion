#include <bits/stdc++.h>
using namespace std;

// Constants
const int MAX_A = 200000; // maximum value of a_i
const int MAX_N = 100005; // maximum n
const int MOD = 1000000007;

// Sieve for smallest prime factor (SPF)
int spf[MAX_A + 1];

// Precompute SPF for all numbers up to MAX_A
void compute_spf() {
    for (int i = 2; i <= MAX_A; ++i) {
        if (spf[i] == 0) {
            for (int j = i; j <= MAX_A; j += i) {
                if (spf[j] == 0) spf[j] = i;
            }
        }
    }
}

// Fast modular exponentiation
long long modpow(long long a, long long b, long long mod) {
    long long res = 1;
    a %= mod;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

// For each a_i, store its prime factorization as vector<pair<prime, exponent>>
vector<pair<int, int>> factorize(int x) {
    vector<pair<int, int>> res;
    while (x > 1) {
        int p = spf[x];
        int cnt = 0;
        while (x % p == 0) {
            x /= p;
            ++cnt;
        }
        res.emplace_back(p, cnt);
    }
    return res;
}

// For each prime, store a segment tree of exponents
struct SegmentTree {
    vector<int> tree;
    int n;
    SegmentTree(int sz) {
        n = sz;
        tree.assign(4 * n, 0);
    }
    // Build segment tree from exponents array
    void build(const vector<int>& exps, int v, int tl, int tr) {
        if (tl == tr) {
            tree[v] = exps[tl];
        } else {
            int tm = (tl + tr) / 2;
            build(exps, v * 2, tl, tm);
            build(exps, v * 2 + 1, tm + 1, tr);
            tree[v] = max(tree[v * 2], tree[v * 2 + 1]);
        }
    }
    // Query max exponent in [l, r]
    int query(int v, int tl, int tr, int l, int r) {
        if (l > r) return 0;
        if (l == tl && r == tr) return tree[v];
        int tm = (tl + tr) / 2;
        return max(
            query(v * 2, tl, tm, l, min(r, tm)),
            query(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r)
        );
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    // Precompute SPF for all numbers up to MAX_A
    compute_spf();

    int n;
    cin >> n;
    vector<int> a(n);
    for (int& x : a) cin >> x;

    // For each a_i, store its prime factorization
    vector<unordered_map<int, int>> a_factors(n);
    set<int> all_primes; // all primes that appear in a
    for (int i = 0; i < n; ++i) {
        int x = a[i];
        while (x > 1) {
            int p = spf[x];
            int cnt = 0;
            while (x % p == 0) {
                x /= p;
                ++cnt;
            }
            a_factors[i][p] = cnt;
            all_primes.insert(p);
        }
    }

    // For each prime, build an array of exponents for all a_i
    // and build a segment tree for that prime
    unordered_map<int, SegmentTree> prime_st;
    unordered_map<int, vector<int>> prime_exp_arr;
    for (int p : all_primes) {
        vector<int> exps(n, 0);
        for (int i = 0; i < n; ++i) {
            if (a_factors[i].count(p)) exps[i] = a_factors[i][p];
        }
        prime_exp_arr[p] = exps;
        prime_st.emplace(p, SegmentTree(n));
        prime_st[p].build(exps, 1, 0, n - 1);
    }

    int q;
    cin >> q;
    long long last = 0;
    while (q--) {
        int x, y;
        cin >> x >> y;
        // Compute l and r as per the problem statement (1-based)
        int l = (last + x) % n + 1;
        int r = (last + y) % n + 1;
        if (l > r) swap(l, r);
        // Convert to 0-based indices
        int L = l - 1, R = r - 1;

        // For each prime, get the max exponent in [L, R]
        long long lcm = 1;
        for (int p : all_primes) {
            int e = prime_st[p].query(1, 0, n - 1, L, R);
            if (e > 0) {
                lcm = lcm * modpow(p, e, MOD) % MOD;
            }
        }
        last = lcm;
        cout << lcm << '\n';
    }
    return 0;
}
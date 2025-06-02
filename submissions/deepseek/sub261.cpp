#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;
const int MAXN = 3e5 + 5;

int n, m;
int l[MAXN], r[MAXN];
pair<int, int> hate[20];
int fact[MAXN], inv_fact[MAXN];

int power(int a, int b) {
    int res = 1;
    while (b > 0) {
        if (b & 1) res = 1LL * res * a % MOD;
        a = 1LL * a * a % MOD;
        b >>= 1;
    }
    return res;
}

void precompute() {
    fact[0] = 1;
    for (int i = 1; i < MAXN; ++i) {
        fact[i] = 1LL * fact[i - 1] * i % MOD;
    }
    inv_fact[MAXN - 1] = power(fact[MAXN - 1], MOD - 2);
    for (int i = MAXN - 2; i >= 0; --i) {
        inv_fact[i] = 1LL * inv_fact[i + 1] * (i + 1) % MOD;
    }
}

int comb(int n, int k) {
    if (k < 0 || k > n) return 0;
    return 1LL * fact[n] * inv_fact[k] % MOD * inv_fact[n - k] % MOD;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    precompute();

    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> l[i] >> r[i];
    }
    for (int i = 0; i < m; ++i) {
        cin >> hate[i].first >> hate[i].second;
    }

    // Compute total valid subsets without considering hate pairs
    vector<int> cnt(n + 2, 0);
    for (int i = 1; i <= n; ++i) {
        cnt[l[i]]++;
        if (r[i] + 1 <= n) cnt[r[i] + 1]--;
    }
    for (int i = 1; i <= n; ++i) {
        cnt[i] += cnt[i - 1];
    }

    vector<int> total(n + 1, 0);
    for (int k = 1; k <= n; ++k) {
        total[k] = comb(cnt[k], k);
    }

    // Inclusion-Exclusion for hate pairs
    int res = 0;
    for (int mask = 0; mask < (1 << m); ++mask) {
        int bits = __builtin_popcount(mask);
        set<int> forbidden;
        for (int i = 0; i < m; ++i) {
            if (mask & (1 << i)) {
                forbidden.insert(hate[i].first);
                forbidden.insert(hate[i].second);
            }
        }
        int L = 1, R = n;
        for (int u : forbidden) {
            L = max(L, l[u]);
            R = min(R, r[u]);
        }
        int k_min = max(L, (int)forbidden.size());
        int k_max = R;
        if (k_min > k_max) continue;
        int sum = 0;
        for (int k = k_min; k <= k_max; ++k) {
            int c = comb(cnt[k] - forbidden.size(), k - forbidden.size());
            sum = (sum + c) % MOD;
        }
        if (bits % 2 == 0) {
            res = (res + sum) % MOD;
        } else {
            res = (res - sum + MOD) % MOD;
        }
    }

    cout << res << '\n';

    return 0;
}
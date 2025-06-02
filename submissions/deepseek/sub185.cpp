#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;

// Precompute factorial, inverse factorial, and powers of 2 modulo MOD up to max N
vector<int> fact, inv_fact, pow2;

void precompute(int max_n) {
    fact.resize(max_n + 1);
    inv_fact.resize(max_n + 1);
    pow2.resize(max_n + 1);
    
    fact[0] = 1;
    for (int i = 1; i <= max_n; ++i) {
        fact[i] = (1LL * fact[i-1] * i) % MOD;
    }
    
    inv_fact[max_n] = 1;
    for (int i = max_n; i >= 1; --i) {
        inv_fact[i-1] = (1LL * inv_fact[i] * i) % MOD;
    }
    
    pow2[0] = 1;
    for (int i = 1; i <= max_n; ++i) {
        pow2[i] = (2LL * pow2[i-1]) % MOD;
    }
}

inline int nCr(int n, int k) {
    if (k < 0 || k > n) return 0;
    return (1LL * fact[n] * inv_fact[k] % MOD) * inv_fact[n - k] % MOD;
}

void solve() {
    int T;
    scanf("%d", &T);
    vector<pair<int, vector<int>>> test_cases(T);
    int max_n = 0;
    
    for (int t = 0; t < T; ++t) {
        int N;
        scanf("%d", &N);
        vector<int> A(2 * N);
        for (int i = 0; i < 2 * N; ++i) {
            scanf("%d", &A[i]);
        }
        test_cases[t] = {N, A};
        max_n = max(max_n, N);
    }
    
    precompute(max_n);
    
    for (auto &tc : test_cases) {
        int N = tc.first;
        vector<int> &A = tc.second;
        
        // For each value, store the positions of its two occurrences
        vector<pair<int, int>> pos(N + 1);
        vector<bool> visited(N + 1, false);
        for (int i = 0; i < 2 * N; ++i) {
            int x = A[i];
            if (!visited[x]) {
                pos[x].first = i;
                visited[x] = true;
            } else {
                pos[x].second = i;
            }
        }
        
        // Sort all intervals [l, r] where l and r are the two positions of x
        vector<pair<int, int>> intervals;
        for (int x = 1; x <= N; ++x) {
            int l = pos[x].first;
            int r = pos[x].second;
            if (l > r) swap(l, r);
            intervals.emplace_back(l, r);
        }
        sort(intervals.begin(), intervals.end());
        
        // Process intervals in order and count the number of non-overlapping pairs
        int res = 0;
        // The total is sum_{k=1 to N} (C(N, k) * 2^k * k! )
        // Because for each subset of k pairs, we can choose any of the 2^k ways to pick one element from each pair,
        // and then arrange them in k! ways for P and Q.
        for (int k = 1; k <= N; ++k) {
            int term = (1LL * nCr(N, k) * pow2[k]) % MOD;
            term = (1LL * term * fact[k]) % MOD;
            res = (res + term) % MOD;
        }
        
        printf("%d\n", res);
    }
}

int main() {
    solve();
    return 0;
}
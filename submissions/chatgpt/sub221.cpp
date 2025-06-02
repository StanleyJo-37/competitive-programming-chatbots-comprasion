#include <bits/stdc++.h>
using namespace std;

// Precompute factorials and inverse factorials modulo p
void precompute_factorials(int n, int p, vector<int>& fact, vector<int>& inv_fact) {
    fact[0] = 1;
    for (int i = 1; i <= n; ++i)
        fact[i] = (1LL * fact[i - 1] * i) % p;

    // Fermat's little theorem for inverse modulo p (p is prime)
    inv_fact[n] = 1;
    int base = fact[n], exp = p - 2;
    // Compute fact[n]^(p-2) mod p
    while (exp) {
        if (exp & 1) inv_fact[n] = (1LL * inv_fact[n] * base) % p;
        base = (1LL * base * base) % p;
        exp >>= 1;
    }
    for (int i = n - 1; i >= 0; --i)
        inv_fact[i] = (1LL * inv_fact[i + 1] * (i + 1)) % p;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, p;
    cin >> n >> p;
    vector<int> a(n);
    for (int& x : a) cin >> x;

    // Sort a for easier processing
    sort(a.begin(), a.end());

    // The minimum x for which f(x) > 0 is:
    // For all i, x + i >= a[i] => x >= a[i] - i
    int min_x = 1e9, max_x = 0;
    for (int i = 0; i < n; ++i) {
        min_x = min(min_x, a[i] - i);
        max_x = max(max_x, a[i]);
    }
    // x must be at least min_x, and at most max_x + n (to be safe)
    // But for all x, x >= 1

    // The possible x are in [max(1, min_x), max_x + n]
    int start_x = max(1, min_x);
    int end_x = max_x + n;

    // Precompute factorials and inverse factorials modulo p
    vector<int> fact(n + 1), inv_fact(n + 1);
    precompute_factorials(n, p, fact, inv_fact);

    vector<int> good_x;

    // For each x in [start_x, end_x], compute f(x) mod p
    // f(x) = number of permutations P such that for all i, x + i >= a[i]
    // For each i, the number of available positions for a[i] is x + i >= a[i] => x >= a[i] - i
    // For a fixed x, for all i, x + i >= a[i] <=> x >= a[i] - i
    // For a fixed x, the number of valid permutations is:
    // For each i, the number of available choices for the i-th duel is cnt_i = number of enemies with a_j <= x + i, minus the number of duels already done (i)
    // Since a is sorted, for each i, cnt_i = number of a_j <= x + i - i = number of a_j <= x
    // But as i increases, the number of available enemies increases

    // For each x, we can precompute for i = 0 to n-1:
    // cnt_i = number of a_j <= x + i - i = number of a_j <= x
    // But that's not correct, we need to count for each i, the number of a_j <= x + i

    // Let's precompute for each x, for i = 0 to n-1, cnt_i = number of a_j <= x + i
    // Since a is sorted, we can use a pointer

    // For all x in [start_x, end_x], we need to compute f(x) mod p
    // f(x) = product over i = 0 to n-1 of (number of a_j <= x + i) - i
    // If for any i, (number of a_j <= x + i) - i <= 0, then f(x) = 0

    // To speed up, we can precompute for all x in [start_x, end_x + n - 1] the number of a_j <= x
    vector<int> cnt(end_x + n + 2, 0);
    int ptr = 0;
    for (int x = 0; x <= end_x + n + 1; ++x) {
        while (ptr < n && a[ptr] <= x) ++ptr;
        cnt[x] = ptr;
    }

    for (int x = start_x; x <= end_x; ++x) {
        int res = 1;
        bool ok = true;
        for (int i = 0; i < n; ++i) {
            int val = cnt[x + i] - i;
            if (val <= 0) {
                ok = false;
                break;
            }
            res = (1LL * res * val) % p;
        }
        if (ok && res % p != 0) {
            good_x.push_back(x);
        }
    }

    cout << good_x.size() << '\n';
    for (int x : good_x) cout << x << ' ';
    cout << '\n';
}
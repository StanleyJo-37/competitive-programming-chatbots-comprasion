#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

vector<pair<ll, ll>> factorize(ll k) {
    vector<pair<ll, ll>> factors;
    if (k == 1) return factors;
    for (ll i = 2; i * i <= k; ++i) {
        if (k % i == 0) {
            ll cnt = 0;
            while (k % i == 0) {
                k /= i;
                ++cnt;
            }
            factors.emplace_back(i, cnt);
        }
    }
    if (k > 1) {
        factors.emplace_back(k, 1);
    }
    return factors;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    ll k;
    cin >> n >> k;
    vector<ll> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    if (k == 1) {
        cout << (ll)n * (n + 1) / 2 << '\n';
        return 0;
    }

    auto factors = factorize(k);
    int m = factors.size();
    if (m == 0) {
        cout << (ll)n * (n + 1) / 2 << '\n';
        return 0;
    }

    vector<vector<ll>> prefix_counts(n + 1, vector<ll>(m, 0));
    for (int i = 0; i < n; ++i) {
        ll num = a[i];
        for (int j = 0; j < m; ++j) {
            ll p = factors[j].first;
            ll cnt = 0;
            while (num % p == 0 && num > 0) {
                num /= p;
                ++cnt;
            }
            prefix_counts[i + 1][j] = prefix_counts[i][j] + cnt;
        }
    }

    ll res = 0;
    for (int l = 0; l < n; ++l) {
        int low = l + 1, high = n, r = n;
        while (low <= high) {
            int mid = (low + high) / 2;
            bool ok = true;
            for (int j = 0; j < m; ++j) {
                ll required = factors[j].second;
                ll current = prefix_counts[mid][j] - prefix_counts[l][j];
                if (current < required) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                r = mid;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        res += n - r + 1;
    }

    cout << res << '\n';
    return 0;
}
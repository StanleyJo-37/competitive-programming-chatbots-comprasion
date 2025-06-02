#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Read input
    ll n; // number of potions to make
    int m, k; // number of spells of type 1 and type 2
    cin >> n >> m >> k;

    ll x, s; // base time per potion, total manapoints available
    cin >> x >> s;

    vector<ll> a(m), b(m); // a: new time per potion, b: cost for type 1 spells
    for (int i = 0; i < m; ++i) cin >> a[i];
    for (int i = 0; i < m; ++i) cin >> b[i];

    vector<ll> c(k), d(k); // c: potions instantly made, d: cost for type 2 spells
    for (int i = 0; i < k; ++i) cin >> c[i];
    for (int i = 0; i < k; ++i) cin >> d[i];

    // Add "no spell" options for both types (cost 0, effect is default)
    a.push_back(x); b.push_back(0); // no type 1 spell: time per potion is x, cost 0
    c.push_back(0); d.push_back(0); // no type 2 spell: 0 potions instantly, cost 0

    // For type 2 spells, since d is sorted, we can binary search for best affordable
    // Precompute for type 2: for each d[i], the max c[i] up to i (since c is non-decreasing, c[i] is always max up to i)
    // But since c is non-decreasing, we can just use c[i] directly.

    // The answer is the minimum time to make n potions, using at most one spell of each type, total cost <= s
    ll ans = n * x; // baseline: no spells

    // For each type 1 spell (including "no spell"), try to pair with best affordable type 2 spell
    for (int i = 0; i < (int)a.size(); ++i) {
        ll cost1 = b[i];
        if (cost1 > s) continue; // can't afford this type 1 spell

        ll time_per_potion = a[i];
        ll mana_left = s - cost1;

        // For type 2, find the best c[j] with d[j] <= mana_left
        // Since d is sorted, use upper_bound to find first d[j] > mana_left, then use j-1
        int l = 0, r = k; // c and d have size k+1
        int idx = -1;
        while (l <= r) {
            int mid = (l + r) / 2;
            if (d[mid] <= mana_left) {
                idx = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        ll potions_instant = (idx == -1) ? 0 : c[idx];
        ll potions_left = n - potions_instant;
        if (potions_left < 0) potions_left = 0;
        ll total_time = potions_left * time_per_potion;
        if (total_time < ans) ans = total_time;
    }

    cout << ans << '\n';
    return 0;
}
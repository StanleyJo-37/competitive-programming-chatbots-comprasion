#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Read input
    int n;
    ll k, x;
    cin >> n >> k >> x;
    vector<ll> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];

    // Sort the levels to process them in order
    sort(a.begin(), a.end());

    // Store the number of "gaps" between consecutive students that are > x
    vector<ll> gaps;

    for (int i = 1; i < n; ++i) {
        ll diff = a[i] - a[i-1];
        if (diff > x) {
            // To bridge this gap, we need to insert enough students so that
            // the difference between any two consecutive is <= x.
            // The number of students needed is ceil((diff-1)/x)
            // which is (diff-1)/x (integer division) + 1
            // But since we want the number of insertions, it's (diff-1)/x
            ll need = (diff - 1) / x;
            gaps.push_back(need);
        }
    }

    // The initial number of groups is the number of gaps + 1
    int groups = gaps.size() + 1;

    // Sort the gaps by the number of students needed to bridge them (smallest first)
    sort(gaps.begin(), gaps.end());

    // Try to bridge as many gaps as possible with at most k students
    for (ll need : gaps) {
        if (k >= need) {
            k -= need;
            --groups; // Bridged this gap, so one less group
        } else {
            break; // Can't bridge further gaps
        }
    }

    cout << groups << '\n';
    return 0;
}
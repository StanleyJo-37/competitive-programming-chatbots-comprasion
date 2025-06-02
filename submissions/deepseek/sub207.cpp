#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < n; ++i) cin >> b[i];

    vector<int> diff(n);
    for (int i = 0; i < n; ++i) diff[i] = a[i] - b[i];

    sort(diff.begin(), diff.end());

    long long res = 0;
    for (int i = 0; i < n; ++i) {
        // We need to find the number of elements > -diff[i] after i
        int target = -diff[i];
        int left = i + 1, right = n;
        // Binary search for the first element > target
        auto it = upper_bound(diff.begin() + i + 1, diff.end(), target);
        res += (diff.end() - it);
    }

    cout << res << '\n';
    return 0;
}
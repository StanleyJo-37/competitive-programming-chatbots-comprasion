#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, p;
    cin >> n >> p;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    sort(a.begin(), a.end());

    vector<int> good_x;
    // The minimal x is a[0], since x must be >= a[0] - 0 to win the first duel in any permutation.
    // The maximal x to check is a[n-1] + n - 1, because for x >= a[n-1] + n, f(x) = n! which is divisible by p (since p <= n).
    int max_x = a[n-1] + n;
    for (int x = 1; x <= max_x; ++x) {
        int total = 1;
        bool divisible = false;
        for (int i = 0; i < n; ++i) {
            // For each position i in the permutation, the number of available choices is the count of a_j <= x + i.
            // The available choices for position i is (count of a_j <= x + i) - i.
            int cnt = upper_bound(a.begin(), a.end(), x + i) - a.begin();
            int choices = cnt - i;
            if (choices <= 0) {
                total = 0;
                break;
            }
            total = (total * choices) % p;
        }
        if (total % p != 0) {
            good_x.push_back(x);
        }
    }

    cout << good_x.size() << endl;
    for (int x : good_x) {
        cout << x << " ";
    }
    cout << endl;

    return 0;
}